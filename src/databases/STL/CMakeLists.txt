# DO NOT EDIT THIS FILE! THIS FILE IS AUTOMATICALLY GENERATED BY xml2cmake
PROJECT(STL_database)

ADD_DATABASE_CODE_GEN_TARGETS(STL)

SET(COMMON_SOURCES
STLPluginInfo.C
STLCommonPluginInfo.C
)

SET(LIBI_SOURCES
STLPluginInfo.C
)

SET(LIBM_SOURCES
STLMDServerPluginInfo.C
${COMMON_SOURCES}
avtSTLFileFormat.C
avtSTLOptions.C
)

SET(LIBE_SOURCES
STLEnginePluginInfo.C
${COMMON_SOURCES}
avtSTLFileFormat.C
avtSTLWriter.C
avtSTLOptions.C
)

INCLUDE_DIRECTORIES(
${CMAKE_CURRENT_SOURCE_DIR}
${VISIT_DATABASE_INCLUDES}
)

if(VTK_VERSION VERSION_EQUAL "8.1.0")
    set(vtk_libs vtkIOGeometry )
else()
    set(vtk_libs VTK::IOGeometry )
endif()

LINK_DIRECTORIES(${VISIT_LIBRARY_DIR} )

ADD_LIBRARY(ISTLDatabase ${LIBI_SOURCES})
TARGET_LINK_LIBRARIES(ISTLDatabase visitcommon)
SET(INSTALLTARGETS ISTLDatabase)

IF(NOT VISIT_ENGINE_ONLY AND NOT VISIT_DBIO_ONLY)
    ADD_LIBRARY(MSTLDatabase ${LIBM_SOURCES})
    TARGET_LINK_LIBRARIES(MSTLDatabase visitcommon avtdbatts avtdatabase_ser ${vtk_libs} )
    ADD_TARGET_DEFINITIONS(MSTLDatabase MDSERVER)
    SET(INSTALLTARGETS ${INSTALLTARGETS} MSTLDatabase)
ENDIF(NOT VISIT_ENGINE_ONLY AND NOT VISIT_DBIO_ONLY)

ADD_LIBRARY(ESTLDatabase_ser ${LIBE_SOURCES})
TARGET_LINK_LIBRARIES(ESTLDatabase_ser visitcommon avtpipeline_ser avtdatabase_ser ${vtk_libs} )
ADD_TARGET_DEFINITIONS(ESTLDatabase_ser ENGINE)
SET(INSTALLTARGETS ${INSTALLTARGETS} ESTLDatabase_ser)

IF(VISIT_PARALLEL)
    ADD_PARALLEL_LIBRARY(ESTLDatabase_par ${LIBE_SOURCES})
    TARGET_LINK_LIBRARIES(ESTLDatabase_par visitcommon avtpipeline_par avtdatabase_par ${vtk_libs} )
    ADD_TARGET_DEFINITIONS(ESTLDatabase_par ENGINE)
    SET(INSTALLTARGETS ${INSTALLTARGETS} ESTLDatabase_par)
ENDIF(VISIT_PARALLEL)

VISIT_INSTALL_DATABASE_PLUGINS(${INSTALLTARGETS})
VISIT_PLUGIN_TARGET_RTOD(databases ${INSTALLTARGETS})
VISIT_PLUGIN_TARGET_FOLDER(databases STL ${INSTALLTARGETS})

