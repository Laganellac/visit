// Copyright (c) Lawrence Livermore National Security, LLC and other VisIt
// Project developers.  See the top-level LICENSE file for dates and other
// details.  No copyright assignment is required to contribute to VisIt.

// 
// This example creates a simple 8x8 multimesh split across 4 domains
// and provides connectivity info via Silo's Mulitmeshadj Object.
//
// Modifications
//    Mark C. Miller, Mon Jan 25 16:44:01 PST 2010
//    Made it work with either silo driver.
//
//    Mark C. Miller, Wed Jan 27 07:03:51 PST 2010
//    Added missing include for cstring (Jed Brown patch)
//

#include <cstdlib>
#include <cstring>
#include <iostream>
#include <iomanip>
#include <sstream>
#include <sys/stat.h>
#include <silo.h>
#ifndef _WIN32
#include <errno.h>
#endif

// suppress the following since silo uses char * in its API
#if defined(__clang__)
# pragma clang diagnostic ignored "-Wwritable-strings"
#elif defined(__GNUC__)
# pragma GCC diagnostic ignored "-Wwrite-strings"
#endif

#ifdef _WIN32
  #ifndef S_ISDIR
    #define S_ISDIR(m) (((m &S_IFMT) == S_IFDIR))
  #endif
  #include <direct.h>
#endif
using namespace std;

// function prototypes
void write_root(int driver);
void write_mmadj(DBfile *db);
void write_domain(int id, int driver);

//---------------------------------------------------------------------------//
void
write_example(int driver)
{
    // create the root file & directory to store our domains.
    write_root(driver);
    // save each domain
    for(int i=0; i < 4; i++)
        write_domain(i,driver);
}

//---------------------------------------------------------------------------//
void write_root(int driver)
{
    // create the root file
    DBfile *db = DBCreate("mmadj_rect_2d_root.silo", DB_CLOBBER, DB_LOCAL,
                          "Multimeshadj Object 2d Rect Example", driver);
    
    // create the directory to hold the silo files for our domains.
    struct stat buf;
    stat("mmadj_rect_2d_data/", &buf);
    if (S_ISDIR(buf.st_mode))
    {
        int ierr = system("rm -rf mmadj_rect_2d_data/"); (void) ierr;
    }
#ifndef _WIN32
    if (mkdir("mmadj_rect_2d_data/", S_IRWXU|S_IRWXG|S_IRWXO) && (errno!=EEXIST))
    {
        cerr << "ERROR: failed to mkdir mmadj_rect_2d_data" << endl;
    }
#else
    _mkdir("mmadj_rect_2d_data/");
#endif

    // create a multimesh that specifies where the domains exist.
    int   types[4] = {DB_QUAD_RECT, DB_QUAD_RECT, DB_QUAD_RECT, DB_QUAD_RECT};
    char *names[4];
    names[0] = "mmadj_rect_2d_data/domain000.silo:quadmesh";
    names[1] = "mmadj_rect_2d_data/domain001.silo:quadmesh";
    names[2] = "mmadj_rect_2d_data/domain002.silo:quadmesh";
    names[3] = "mmadj_rect_2d_data/domain003.silo:quadmesh";   
    
    DBPutMultimesh(db, "quadmesh", 4, names, types,NULL);
    
    // create a multivar that specifies where the scalar values exist.
    names[0] = "mmadj_rect_2d_data/domain000.silo:value";
    names[1] = "mmadj_rect_2d_data/domain001.silo:value";
    names[2] = "mmadj_rect_2d_data/domain002.silo:value";
    names[3] = "mmadj_rect_2d_data/domain003.silo:value";   
    
    types[0] = DB_QUADVAR; 
    types[1] = DB_QUADVAR;
    types[2] = DB_QUADVAR;
    types[3] = DB_QUADVAR;
    
    DBPutMultivar(db, "value", 4, names, types, NULL);
    
    // write the Multimeshadj object so VisIt can understand domain
    // connectivity. 
    
    write_mmadj(db);
    
    // close the root file.
    DBClose(db);
}

//---------------------------------------------------------------------------//
void write_mmadj(DBfile *db)
{
    // we have a total of 4 domains
    int nmesh = 4;
    // all of our domains are rectilinear meshes.
    int mesh_types[4] = {DB_QUADMESH, DB_QUADMESH, DB_QUADMESH, DB_QUADMESH};
    // in this example all domains have 3 neighbors: 
    //    one in each logical dimension (2 neighbors)
    //    one diagonal (sharing the center node)
    int nneighbors[4] = {3,3,3,3};
    // create 'neighbors'
    int neighbors[12]  = {1,2,3, 0,2,3, 0,1,3, 0,1,2};
    //  create 'back' w/ position of each domain in its neighbor's nodelists
    int back[12]       = {0,0,0, 0,1,1, 1,1,2, 2,2,2};
    // ever ynode list contains 15 values
    int nnodes[12]     = {15,15,15, 15,15,15, 15,15,15, 15,15,15};
    
    // holds pointers to the beginning of each nodelist.
    int *nodelist_ptrs[12];
    
    // construct all of our nodelists
    int  nodelists[12*15] = { // 0 to 1
                             0,4,0,4,-1,-1,
                             4,4,0,4,-1,-1,
                             1,2,3,
                             // 0 to 2
                             0,4,0,4,-1,-1,
                             0,4,4,4,-1,-1,
                             1,2,3,
                             // 0 to 3
                             0,4,0,4,-1,-1,
                             4,4,4,4,-1,-1,
                             1,2,3,
                             
                             // 1 to 0
                             4,8,0,4,-1,-1,
                             4,4,0,4,-1,-1,
                             1,2,3,
                             // 1 to 2
                             4,8,0,4,-1,-1,
                             4,4,4,4,-1,-1,
                             1,2,3,
                             // 1 to 3
                             4,8,0,4,-1,-1,
                             4,8,4,4,-1,-1,
                             1,2,3,
                             
                             // 2 to 0
                             0,4,4,8,-1,-1,
                             0,4,4,4,-1,-1,
                             1,2,3,
                             // 2 to 1
                             0,4,4,8,-1,-1,
                             4,4,4,4,-1,-1,
                             1,2,3,
                             // 2 to 3
                             0,4,4,8,-1,-1,
                             4,4,4,8,-1,-1,
                             1,2,3,
                             
                             // 3 to 0
                             4,8,4,8,-1,-1,
                             4,4,4,4,-1,-1,
                             1,2,3,
                             // 3 to 1
                             4,8,4,8,-1,-1,
                             4,8,4,4,-1,-1,
                             1,2,3,
                             // 3 to 2
                             4,8,4,8,-1,-1,
                             4,4,4,8,-1,-1,
                             1,2,3
                             };
    
    // VisIt expects the Multimeshadj object to live at:
    //   Decomposition/Domain_Decomposition in the root file.
    DBMkDir(db,"Decomposition");
    DBSetDir(db,"Decomposition");
    for(int i=0; i < 12; i++)
        nodelist_ptrs[i] = &nodelists[i*15];
    
    DBPutMultimeshadj(db, "Domain_Decomposition", nmesh, mesh_types,
                     nneighbors, neighbors, back, nnodes,
                     nodelist_ptrs, NULL, NULL, NULL);
    // VisIt also expects a variable that specifies the # of Domains at:
    //    Decomposition/NumDomains
    int dims[2] = {1,1};
    DBWrite(db, "NumDomains", &nmesh, dims, 1, DB_INT);
}

//---------------------------------------------------------------------------//
void write_domain(int id, int driver)
{
    // generate destination domain name.
    ostringstream oss;
    oss << "mmadj_rect_2d_data/domain" 
        << setw(3) << setfill('0') << id <<".silo";

    // Setup coord arrays.
    float  coords_lo[5] =  {0.0f, 1.0f, 2.0f, 3.0f, 4.0f};
    float  coords_hi[5] =  {4.0f, 5.0f, 6.0f, 7.0f, 8.0f};
    int    dims[2] = {5,5};
    float *coords[2];
    
    // select proper coord arrays for this domain.
    if( id == 0 )
    {
        coords[0] = coords_lo;
        coords[1] = coords_lo;
    }
    else if( id == 1 )
    {
        coords[0] = coords_hi;
        coords[1] = coords_lo;
    }
    else if( id == 2 )
    {
        coords[0] = coords_lo;
        coords[1] = coords_hi;
    }
    else if( id == 3 )
    {
        coords[0] = coords_hi;
        coords[1] = coords_hi;
    }
    
    // create a silo file for the domain.
    DBfile *db =DBCreate(oss.str().c_str(), DB_CLOBBER, DB_LOCAL, 
                         "Rect Domain", driver);
    
    // write the mesh
    DBPutQuadmesh(db, "quadmesh", NULL, coords, dims, 2,
                  DB_FLOAT, DB_COLLINEAR, NULL);
                  
    // Create a sample scalar variable w/ values set to the domain id.
    float values[16];
    // for zonal data we have 4x4 values for each domain.
    dims[0] -=1;
    dims[1] -=1;
    
    for(int i=0;i<16;i++)
        values[i] = (float) id;
    
    // Write the scalar variable.
    DBPutQuadvar1(db, "value", "quadmesh", values, dims, 2, 
                  NULL, 0,DB_FLOAT, DB_ZONECENT, NULL);
    // close the domain's silo file.
    DBClose(db);                  
}


//---------------------------------------------------------------------------//
int 
main(int argc, char **argv)
{
    int driver = DB_PDB;
    int i = 1;
    while (i < argc)
    {
        if (strcmp(argv[i], "DB_HDF5") == 0)
            driver = DB_HDF5;
        else if (strcmp(argv[i], "DB_PDB") == 0)
            driver = DB_PDB;
        else
           fprintf(stderr,"Uncrecognized driver name \"%s\"\n", argv[i]);
        i++;
    }

    // call the driver routine
    write_example(driver);
}

