/*****************************************************************************
*
* Copyright (c) 2000 - 2009, Lawrence Livermore National Security, LLC
* Produced at the Lawrence Livermore National Laboratory
* LLNL-CODE-400124
* All rights reserved.
*
* This file is  part of VisIt. For  details, see https://visit.llnl.gov/.  The
* full copyright notice is contained in the file COPYRIGHT located at the root
* of the VisIt distribution or at http://www.llnl.gov/visit/copyright.html.
*
* Redistribution  and  use  in  source  and  binary  forms,  with  or  without
* modification, are permitted provided that the following conditions are met:
*
*  - Redistributions of  source code must  retain the above  copyright notice,
*    this list of conditions and the disclaimer below.
*  - Redistributions in binary form must reproduce the above copyright notice,
*    this  list of  conditions  and  the  disclaimer (as noted below)  in  the
*    documentation and/or other materials provided with the distribution.
*  - Neither the name of  the LLNS/LLNL nor the names of  its contributors may
*    be used to endorse or promote products derived from this software without
*    specific prior written permission.
*
* THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT  HOLDERS AND CONTRIBUTORS "AS IS"
* AND ANY EXPRESS OR  IMPLIED WARRANTIES, INCLUDING,  BUT NOT  LIMITED TO, THE
* IMPLIED WARRANTIES OF MERCHANTABILITY AND  FITNESS FOR A PARTICULAR  PURPOSE
* ARE  DISCLAIMED. IN  NO EVENT  SHALL LAWRENCE  LIVERMORE NATIONAL  SECURITY,
* LLC, THE  U.S.  DEPARTMENT OF  ENERGY  OR  CONTRIBUTORS BE  LIABLE  FOR  ANY
* DIRECT,  INDIRECT,   INCIDENTAL,   SPECIAL,   EXEMPLARY,  OR   CONSEQUENTIAL
* DAMAGES (INCLUDING, BUT NOT  LIMITED TO, PROCUREMENT OF  SUBSTITUTE GOODS OR
* SERVICES; LOSS OF  USE, DATA, OR PROFITS; OR  BUSINESS INTERRUPTION) HOWEVER
* CAUSED  AND  ON  ANY  THEORY  OF  LIABILITY,  WHETHER  IN  CONTRACT,  STRICT
* LIABILITY, OR TORT  (INCLUDING NEGLIGENCE OR OTHERWISE)  ARISING IN ANY  WAY
* OUT OF THE  USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH
* DAMAGE.
*
*****************************************************************************/

#ifndef ONIONPEELATTRIBUTES_H
#define ONIONPEELATTRIBUTES_H
#include <string>
#include <AttributeSubject.h>


// ****************************************************************************
// Class: OnionPeelAttributes
//
// Purpose:
//    Attributes for the onion peel operator
//
// Notes:      Autogenerated by xml2atts.
//
// Programmer: xml2atts
// Creation:   omitted
//
// Modifications:
//   
// ****************************************************************************

class OnionPeelAttributes : public AttributeSubject
{
public:
    enum NodeFace
    {
        Node,
        Face
    };
    enum SeedIdType
    {
        SeedCell,
        SeedNode
    };

    // These constructors are for objects of this class
    OnionPeelAttributes();
    OnionPeelAttributes(const OnionPeelAttributes &obj);
protected:
    // These constructors are for objects derived from this class
    OnionPeelAttributes(private_tmfs_t tmfs);
    OnionPeelAttributes(const OnionPeelAttributes &obj, private_tmfs_t tmfs);
public:
    virtual ~OnionPeelAttributes();

    virtual OnionPeelAttributes& operator = (const OnionPeelAttributes &obj);
    virtual bool operator == (const OnionPeelAttributes &obj) const;
    virtual bool operator != (const OnionPeelAttributes &obj) const;
private:
    void Init();
    void Copy(const OnionPeelAttributes &obj);
public:

    virtual const std::string TypeName() const;
    virtual bool CopyAttributes(const AttributeGroup *);
    virtual AttributeSubject *CreateCompatible(const std::string &) const;
    virtual AttributeSubject *NewInstance(bool) const;

    // Property selection methods
    virtual void SelectAll();
    void SelectCategoryName();
    void SelectSubsetName();
    void SelectIndex();

    // Property setting methods
    void SetAdjacencyType(NodeFace adjacencyType_);
    void SetUseGlobalId(bool useGlobalId_);
    void SetCategoryName(const std::string &categoryName_);
    void SetSubsetName(const std::string &subsetName_);
    void SetIndex(const intVector &index_);
    void SetLogical(bool logical_);
    void SetRequestedLayer(int requestedLayer_);
    void SetSeedType(SeedIdType seedType_);

    // Property getting methods
    NodeFace          GetAdjacencyType() const;
    bool              GetUseGlobalId() const;
    const std::string &GetCategoryName() const;
          std::string &GetCategoryName();
    const std::string &GetSubsetName() const;
          std::string &GetSubsetName();
    const intVector   &GetIndex() const;
          intVector   &GetIndex();
    bool              GetLogical() const;
    int               GetRequestedLayer() const;
    SeedIdType        GetSeedType() const;

    // Persistence methods
    virtual bool CreateNode(DataNode *node, bool completeSave, bool forceAdd);
    virtual void SetFromNode(DataNode *node);

    // Enum conversion functions
    static std::string NodeFace_ToString(NodeFace);
    static bool NodeFace_FromString(const std::string &, NodeFace &);
protected:
    static std::string NodeFace_ToString(int);
public:
    static std::string SeedIdType_ToString(SeedIdType);
    static bool SeedIdType_FromString(const std::string &, SeedIdType &);
protected:
    static std::string SeedIdType_ToString(int);
public:

    // Keyframing methods
    virtual std::string               GetFieldName(int index) const;
    virtual AttributeGroup::FieldType GetFieldType(int index) const;
    virtual std::string               GetFieldTypeName(int index) const;
    virtual bool                      FieldsEqual(int index, const AttributeGroup *rhs) const;


    // IDs that can be used to identify fields in case statements
    enum {
        ID_adjacencyType = 0,
        ID_useGlobalId,
        ID_categoryName,
        ID_subsetName,
        ID_index,
        ID_logical,
        ID_requestedLayer,
        ID_seedType,
        ID__LAST
    };

private:
    int         adjacencyType;
    bool        useGlobalId;
    std::string categoryName;
    std::string subsetName;
    intVector   index;
    bool        logical;
    int         requestedLayer;
    int         seedType;

    // Static class format string for type map.
    static const char *TypeMapFormatString;
    static const private_tmfs_t TmfsStruct;
};
#define ONIONPEELATTRIBUTES_TMFS "ibssi*bii"

#endif
