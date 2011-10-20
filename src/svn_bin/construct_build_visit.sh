#!/bin/bash

# *****************************************************************************
#   Script: build_visit
#
#   Purpose:
#       A script that performs a complete build of VisIt and its support
#       libraries.  The script will detect if support libraries have already
#       been built and, if so, use those pre-built libraries.
#
#   Warning:
#       This script is only expected to work for Linux, and Darwin systems.
#       If you need to build VisIt for another platform, you should consult
#       the BUILD_NOTES that come with the VisIt source.  That document
#       contains instructions on how to build VisIt and its third party
#       libraries.
#
#   This script has been tested and is known to work with the following OS/
#   compiler combinations:
#
#   OS  Hardware    Compiler    Machine
#   -----   --------    --------    -------
#       RHEL3,  x86,        GCC 3.2.3   hoth.llnl.gov
#       CHAOS,  x86_64,     GCC 4.1.2   aztec.llnl.gov
#       SuSE,   x86_64,     GCC 4.0.2   antares.lbl.gov
#       SuSE,   x86_64,     GCC 4.1.0   octagon.lbl.gov
#       MacOSX  i386,       GCC 4.0.1   corellia.llnl.gov
#       MacOSX  x86_64          GCC 4.2.1       galvatron.llnl.gov
#       MacOSX  ppc,        GCC 4.0.1   snailbait.llnl.gov
#
#   It is believed that this script will also work with other Linux variations.
#   Please send feedback to visit-users@ornl.gov if you run into problems
#   so that this script can be improved in the future.  If you have built
#   VisIt using this script on an OS/hardware/compiler combination not listed
#   above, please send a note to visit-users@ornl.gov, so we can add that
#   information to the script.
#



# To create your own modular file these 7 functions need to be implemented..
#filename: bv_<module>.sh
#bv_<module>_initialize : Initialize any variables you may want to export
#bv_<module>_enable : Enables the module 
#bv_<module>_disable : Disables the module
#bv_<module>_info : Where to get the module, the version, etc...
#bv_<module>_ensure : Ensure the module has been downloaded and extracted properly
#bv_<module>_depends_on : What other modules does this module depend on. Example "adios" returns string "mxml"
#bv_<module>_build : build the module

INITIAL_PWD=$PWD

#First step download the support directory from svn repository..
bv_PATH=`dirname $0`
bv_PREFIX=$bv_PATH/bv_support/

#import initialize and run functions..
. $bv_PREFIX/bv_main.sh

#import helper functions..
. $bv_PREFIX/helper_funcs.sh

#These options can be read from a file..

#import functions that that install required visit libraries
reqlibs[0]="cmake"
reqlibs[1]="python"
reqlibs[2]="mesa"
reqlibs[3]="vtk"
reqlibs[4]="qt"


for (( i = 0; i < ${#reqlibs[*]}; ++i ))
do
    . "${bv_PREFIX}/bv_${reqlibs[$i]}.sh" 
    
    #check if required functions exist..
    declare -F "bv_${reqlibs[$i]}_enable" &>/dev/null || errorFunc "${reqlibs[$i]} enable not found"
    declare -F "bv_${reqlibs[$i]}_disable" &>/dev/null || errorFunc "${reqlibs[$i]} disable not found"
    declare -F "bv_${reqlibs[$i]}_initialize" &>/dev/null || errorFunc "${reqlibs[$i]} initialize not found"
    declare -F "bv_${reqlibs[$i]}_info" &>/dev/null || errorFunc "${reqlibs[$i]} info not found"
    declare -F "bv_${reqlibs[$i]}_ensure" &>/dev/null || errorFunc "${reqlibs[$i]} ensure not found"
    declare -F "bv_${reqlibs[$i]}_build" &>/dev/null || errorFunc "${reqlibs[$i]} build not found"
    declare -F "bv_${reqlibs[$i]}_depends_on" &>/dev/null || errorFunc "${reqlibs[$i]} depends_on not found"
    declare -F "bv_${reqlibs[$i]}_print" &>/dev/null || errorFunc "${reqlibs[$i]} print not found"
    declare -F "bv_${reqlibs[$i]}_print_usage" &>/dev/null || errorFunc "${reqlibs[$i]} print_usage not found"
done


#import functions that support optional visit dependencies
optlibs[0]="szip"
optlibs[1]="hdf5"
optlibs[2]="mili"
optlibs[3]="icet"
optlibs[4]="hdf4"
optlibs[5]="netcdf"
optlibs[6]="cgns"
optlibs[7]="gdal"
optlibs[8]="exodus"
optlibs[9]="tcmalloc"
optlibs[10]="boxlib"
optlibs[11]="cfitsio"
optlibs[12]="mdsplus"
optlibs[13]="h5part"
optlibs[14]="fastbit"
optlibs[15]="ccmio"
optlibs[16]="silo"
optlibs[17]="itaps"
optlibs[18]="advio"
optlibs[19]="xdmf"
optlibs[20]="mxml"
optlibs[21]="adios"
optlibs[22]="visus"
optlibs[23]="pyside"

#import functions that that install required visit libraries
for (( i = 0; i < ${#optlibs[*]}; ++i ))
do
    . "${bv_PREFIX}/bv_${optlibs[$i]}.sh"
    
    declare -F "bv_${optlibs[$i]}_enable" &>/dev/null || errorFunc "${optlibs[$i]} enable not found"
    declare -F "bv_${optlibs[$i]}_disable" &>/dev/null || errorFunc "${optlibs[$i]} disable not found"
    declare -F "bv_${optlibs[$i]}_initialize" &>/dev/null || errorFunc "${optlibs[$i]} info not found"
    declare -F "bv_${optlibs[$i]}_info" &>/dev/null || errorFunc "${optlibs[$i]} info not found" 
    declare -F "bv_${optlibs[$i]}_ensure" &>/dev/null || errorFunc "${optlibs[$i]} ensure not found"
    declare -F "bv_${optlibs[$i]}_build" &>/dev/null || errorFunc "${optlibs[$i]} build not found"  
    declare -F "bv_${optlibs[$i]}_depends_on" &>/dev/null || errorFunc "${optlibs[$i]} depends_on not found"  
    declare -F "bv_${optlibs[$i]}_print" &>/dev/null || errorFunc "${optlibs[$i]} print not found" 
    declare -F "bv_${optlibs[$i]}_print_usage" &>/dev/null || errorFunc "${optlibs[$i]} print_usage not found" 
    declare -F "bv_${optlibs[$i]}_host_profile" &>/dev/null || errorFunc "${optlibs[$i]} host_profile not found" 
    declare -F "bv_${optlibs[$i]}_graphical" &>/dev/null || errorFunc "${optlibs[$i]} graphical not found" 
done

#for thirdparty option..
thirdpartylibs[0]="mesa"
thirdpartylibs[1]="qt"
thirdpartylibs[2]="cmake"
thirdpartylibs[3]="vtk"
thirdpartylibs[4]="python"

#turn off non dbio
nodbiolibs[0]="mesa"
nodbiolibs[1]="qt"
nodbiolibs[2]="python"

#all the io libraries
iolibs[0]="advio"
iolibs[1]="boxlib"
iolibs[2]="cgns"
iolibs[3]="cfitsio"
iolibs[4]="ccmio"
iolibs[5]="exodus"
iolibs[6]="fastbit"
iolibs[7]="gdal"
iolibs[8]="hdf4"
iolibs[9]="hdf5"
iolibs[10]="itaps"
iolibs[11]="netcdf"
iolibs[12]="h5part"
iolibs[13]="szip"
iolibs[14]="silo"
iolibs[15]="xdmf"
iolibs[16]="adios"
iolibs[17]="mxml"


#
# Releasibility of these libs is not yet understood
#
advancedlibs[0]="mili"
advancedlibs[1]="visus"
advancedlibs[2]="mdsplus"
advancedlibs[3]="tcmalloc"
advancedlibs[4]="icet"

function bv_write_unified_file
{
    OUTPUT_bv_FILE=$@

    echo "Writing to File: $OUTPUT_bv_FILE"
    #go up one directory so that if $bv_PREFIX was set to relative path it will work again..
    if [[ $OUTPUT_bv_FILE == "" ]]; then
        echo "Output file not given or proper. No "
        return
    fi

    OLDPWD=$PWD
    cd $INITIAL_PWD

    echo "#!/bin/bash" > $OUTPUT_bv_FILE
    cat $bv_PREFIX/bv_main.sh >> $OUTPUT_bv_FILE
    cat $bv_PREFIX/helper_funcs.sh >> $OUTPUT_bv_FILE

    for (( i = 0; i < ${#reqlibs[*]}; ++i ))
    do
        echo "reqlibs[$i]=\"${reqlibs[$i]}\"" >> $OUTPUT_bv_FILE
        cat "${bv_PREFIX}/bv_${reqlibs[$i]}.sh" >> $OUTPUT_bv_FILE
    done

    #write out all modules
    for (( i = 0; i < ${#optlibs[*]}; ++i ))
    do
        echo "optlibs[$i]=\"${optlibs[$i]}\"" >> $OUTPUT_bv_FILE
        cat "${bv_PREFIX}/bv_${optlibs[$i]}.sh" >> $OUTPUT_bv_FILE
    done

    for (( i = 0; i < ${#optlibs[*]}; ++i ))
    do
        echo "optlibs[$i]=\"${optlibs[$i]}\"" >> $OUTPUT_bv_FILE
        cat "${bv_PREFIX}/bv_${optlibs[$i]}.sh" >> $OUTPUT_bv_FILE
    done

    #write out all grouped variables..
    for (( i = 0; i < ${#thirdpartylibs[*]}; ++i ))
    do
        echo "thirdpartylibs[$i]=\"${thirdpartylibs[$i]}\"" >> $OUTPUT_bv_FILE
    done

    for (( i = 0; i < ${#nodbiolibs[*]}; ++i ))
    do
        echo "nodbiolibs[$i]=\"${nodbiolibs[$i]}\"" >> $OUTPUT_bv_FILE
    done

    for (( i = 0; i < ${#iolibs[*]}; ++i ))
    do
        echo "iolibs[$i]=\"${iolibs[$i]}\"" >> $OUTPUT_bv_FILE
    done

    for (( i = 0; i < ${#advancedlibs[*]}; ++i ))
    do
        echo "advancedlibs[$i]=\"${advancedlibs[$i]}\"" >> $OUTPUT_bv_FILE
    done

    echo "function bv_write_unified_file" >> $OUTPUT_bv_FILE
    echo "{" >> $OUTPUT_bv_FILE
    echo "cat \$0 > \$@" >> $OUTPUT_bv_FILE
    echo "chmod 755 \$@" >> $OUTPUT_bv_FILE
    echo "}" >> $OUTPUT_bv_FILE

    #write command to run and execute VisIt
    echo "initialize_build_visit" >> $OUTPUT_bv_FILE
    echo "run_build_visit \$@" >> $OUTPUT_bv_FILE
    chmod 755 $OUTPUT_bv_FILE
    cd $OLDPWD
}

#initialize all build visit variables
initialize_build_visit

#run all build visit 
run_build_visit $@

