// Copyright (c) Lawrence Livermore National Security, LLC and other VisIt
// Project developers.  See the top-level LICENSE file for dates and other
// details.  No copyright assignment is required to contribute to VisIt.

// ************************************************************************* //
//                            avtDatasetQuery.C                              //
// ************************************************************************* //

#include <avtDatasetQuery.h>
#include <avtOriginatingSource.h>

#include <avtParallel.h>

#include <vtkDataSet.h>

#include <BadIndexException.h>
#include <DebugStream.h>

// ****************************************************************************
//  Method: avtDatasetQuery constructor
//
//  Programmer: Kathleen Bonnell
//  Creation:   September 12, 2002
//
//  Modifications:
//    Kathleen Bonnell, Fri Nov 15 09:07:36 PST 2002
//    Initialize new members currentNode, totalNodes.
//
//    Kathleen Bonnell, Fri Jul 11 16:19:32 PDT 2003
//    Initialize value.
//
// ****************************************************************************

avtDatasetQuery::avtDatasetQuery() : avtDatasetSink()
{
    currentNode = 0;
    totalNodes = 0;
    // always have 1 value.
    resValue.push_back(0.);
}


// ****************************************************************************
//  Method: avtDatasetQuery destructor
//
//  Purpose:
//      Defines the destructor.  Note: this should not be inlined in the header
//      because it causes problems for certain compilers.
//
//  Programmer: Hank Childs
//  Creation:   February 5, 2004
//
// ****************************************************************************

avtDatasetQuery::~avtDatasetQuery()
{
    ;
}


// ****************************************************************************
//  Method: avtDatasetQuery::PerformQuery
//
//  Purpose:
//    Perform  the requested query.
//
//  Programmer: Kathleen Bonnell
//  Creation:   September 12, 2002
//
//  Modifications:
//    Kathleen Bonnell, Fri Nov 15 09:07:36 PST 2002
//    Use recursive Execute on the input data tree.  Initialize queryAtts
//    member from argument.  Move creation of artificial pipeline to
//    the derived types that actually need one.
//
//    Kathleen Bonnell, Fri Nov 15 09:07:36 PST 2002
//    Set queryAtts results value.
//
//    Hank Childs, Mon Feb 28 15:40:45 PST 2005
//    Do not assume the tree is valid.  It is not with DLB.
//
//    Kathleen Bonnell, Tue Mar  1 11:20:15 PST 2005
//    Test for empty data tree after ApplyFilters, and submit an error
//    message.
//
//    Kathleen Bonnell, Thu Mar  3 16:38:16 PST 2005
//    Ensure all procs Execute, even if they have empty trees (a valid state
//    when in parallel and more processors than domains.)
//
//    Hank Childs, Fri Aug 25 17:47:21 PDT 2006
//    Change error message with no data, as it is misleading.
//
//    Hank Childs, Sat Aug  4 12:31:43 PDT 2007
//    Catch exceptions, as they lead to parallel hangs if we don't.
//
//    Cyrus Harrison, Wed Dec 19 15:11:36 PST 2007
//    Added set of query xml result.
//
//    Hank Childs, Sun Dec 26 09:47:15 PST 2010
//    Don't worry about whether other processors have error conditions when we
//    are parallelizing over time.
//
// ****************************************************************************

void
avtDatasetQuery::PerformQuery(QueryAttributes *qA)
{
    queryAtts = *qA;

    Init();

    UpdateProgress(0, 0);
    //
    // Allow derived types to apply any necessary filters.
    //
    avtDataObject_p dob = ApplyFilters(GetInput());

    //
    // Reset the input so that we have access to the data tree.
    //
    SetTypedInput(dob);

    avtDataTree_p tree = GetInputDataTree();
    int validInputTree = 0;
    totalNodes = 0;

    if (*tree != NULL && !tree->IsEmpty())
    {
        validInputTree = 1;
        totalNodes = tree->GetNumberOfLeaves();
    }
    else
    {
        debug2 << "Query encountered EMPTY InputDataTree after ApplyFilters.  "
               << "This may be a valid state if running parallel and there "
               << "are more processors than domains." << endl;
    }

    bool hadError = false;
    PreExecute();
    TRY
    {
        Execute(tree);
    }
    CATCH2(VisItException, e)
    {
        debug1 << "Exception occurred in " << GetType() << endl
             << "Going to keep going to prevent a parallel hang." << endl;
        queryAtts.SetResultsMessage(e.Message());
        hadError = true;
    }
    ENDTRY
    PostExecute();

    if (! ParallelizingOverTime())
        validInputTree = UnifyMaximumValue(validInputTree);

    if (!hadError)
    {
        if (validInputTree)
        {
            //
            // Retrieve the query results and set the message in the atts.
            //
            queryAtts.SetResultsMessage(resMsg);
            queryAtts.SetResultsValue(resValue);
            queryAtts.SetXmlResult(xmlResult);
        }
        else
        {
            queryAtts.SetResultsMessage("Query(" + queryAtts.GetName() + ")"
                    " was asked to execute on an empty data set.  The query "
                    "produced the following message: " + resMsg);
            queryAtts.SetResultsValue(resValue);
        }
    }

    UpdateProgress(1, 0);
    SetOutputQueryAtts(qA, hadError);
}


// ****************************************************************************
//  Method: avtDatasetQuery::Execute
//
//  Purpose:
//    Recursive method to traverse an avtDataTree, calling Execute on the leaf
//    nodes.
//
//  Notes:
//    Adapted from avtFilter.
//
//  Programmer: Kathleen Bonnell
//  Creation:   November 15, 2002
//
//  Modifications:
//    Kathleen Bonnell, Wed May 17 15:22:06 PDT 2006
//    Remove call to SetSource(NULL) as it now removes information necessary
//    for the dataset.
//
// ****************************************************************************

void
avtDatasetQuery::Execute(avtDataTree_p inDT)
{
    if (*inDT == NULL)
    {
        return;
    }

    int nc = inDT->GetNChildren();

    if (nc <= 0 && !inDT->HasData())
    {
        return;
    }

    if ( nc == 0 )
    {
        //
        // There is only one dataset to process.
        //
        vtkDataSet *in_ds = inDT->GetDataRepresentation().GetDataVTK();
        int dom = inDT->GetDataRepresentation().GetDomain();

        //
        // Setting the source to NULL for the input will break the
        // pipeline.
        //
        // NO LONGER A GOOD IDEA
        //in_ds->SetSource(NULL);
        Execute(in_ds, dom);
        if (!timeVarying)
        {
            currentNode++;
            UpdateProgress(currentNode, totalNodes);
        }
    }
    else
    {
        //
        // There is more than one input dataset to process.
        // Recurse through the children.
        //
        for (int j = 0; j < nc; j++)
        {
            if (inDT->ChildIsPresent(j))
            {
                Execute(inDT->GetChild(j));
            }
        }
    }
}


// ****************************************************************************
//  Method: avtDatasetQuery::PreExecute
//
//  Purpose:
//    Method that allows derived types to perform necessary initialization
//    before Execute.  Stub so that derived types do not have to define.
//
//  Programmer: Kathleen Bonnell
//  Creation:   September 12, 2002
//
// ****************************************************************************

void
avtDatasetQuery::PreExecute()
{
    ;
}

// ****************************************************************************
//  Method: avtDatasetQuery::PostExecute
//
//  Purpose:
//    Method that allows derived types to perform necessary cleanup  after
//    Excute.  Stub so that derived types do not have to define.
//
//  Programmer: Kathleen Bonnell
//  Creation:   September 12, 2002
//
// ****************************************************************************

void
avtDatasetQuery::PostExecute()
{
    ;
}

// ****************************************************************************
//  Method: avtDatasetQuery::ApplyFilters
//
//  Purpose:
//    Allow derived types to apply any necessary avtFilters.
//
//  Programmer: Kathleen Bonnell
//  Creation:   September 12, 2002
//
//  Modifications:
//    Kathleen Bonnell, Wed Mar 31 15:52:54 PST 2004
//    Allow for time-varying case.
//
//    Hank Childs, Fri Apr  9 16:25:40 PDT 2004
//    Minimize work done by creating new SIL.
//
//    Kathleen Bonnell, Mon Jan  3 15:12:19 PST 2005
//    Modify timeVarying case.
//
//    David Bremer, Fri Jan  5 11:13:38 PST 2007
//    Add secondary variables to the query, by querying a
//    virtual function that derived classes can override.
//
// ****************************************************************************

avtDataObject_p
avtDatasetQuery::ApplyFilters(avtDataObject_p dob)
{
    std::vector<std::string>  secondaryVars;
    GetSecondaryVars( secondaryVars );

    if (!timeVarying && secondaryVars.size() == 0)
    {
        avtDataObject_p rv;
        CopyTo(rv, dob);
        return rv;
    }
    else
    {
        avtContract_p orig_contract = dob->GetOriginatingSource()->
            GetGeneralContract();

        avtDataRequest_p oldSpec = orig_contract->GetDataRequest();

        avtDataRequest_p newDS = new
            avtDataRequest(oldSpec, querySILR);

        if (timeVarying)
        {
            newDS->SetTimestep(queryAtts.GetTimeStep());
        }

        for (size_t ii = 0 ; ii < secondaryVars.size() ; ii++)
        {
            newDS->AddSecondaryVariable( secondaryVars[ii].c_str() );
        }

        avtContract_p contract =
            new avtContract(newDS, queryAtts.GetPipeIndex());

        avtDataObject_p rv;
        CopyTo(rv, dob);
        rv->Update(contract);
        return rv;
    }
}

// ****************************************************************************
//  Method: avtDatasetQuery::SetResultValue
//
//  Purpose:
//    Set the result value for the specified index.
//
//  Programmer: Kathleen Bonnell
//  Creation:   November 12, 2003
//
// ****************************************************************************

void
avtDatasetQuery::SetResultValue(const double &d, const int i)
{
    if (i < 0 || i >= (int)resValue.size())
        EXCEPTION2(BadIndexException, i, (int)resValue.size()-1)

    resValue[i] = d;
}


// ****************************************************************************
//  Method: avtDatasetQuery::GetResultValue
//
//  Purpose:
//    Return  the result value for the specified index.
//
//  Programmer: Kathleen Bonnell
//  Creation:   November 12, 2003
//
// ****************************************************************************

double
avtDatasetQuery::GetResultValue(const int i)
{
    if (i < 0 || i >= (int)resValue.size())
        EXCEPTION2(BadIndexException,i, (int)resValue.size()-1)

    return resValue[i];
}


// ****************************************************************************
//  Method: avtDatasetQuery::GetSecondaryVars
//
//  Purpose:
//    Returns an array of secondary variables to be added to the query.  This
//    is a stub method to be overridden by derived classes.
//
//  Programmer: David Bremer
//  Creation:   January 4, 2007
//
// ****************************************************************************

void
avtDatasetQuery::GetSecondaryVars( std::vector<std::string> &outVars )
{
    outVars.clear();
}
