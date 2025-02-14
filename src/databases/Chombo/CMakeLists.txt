# DO NOT EDIT THIS FILE! THIS FILE IS AUTOMATICALLY GENERATED BY xml2cmake
PROJECT(Chombo_database)

ADD_DATABASE_CODE_GEN_TARGETS(Chombo)

SET(COMMON_SOURCES
ChomboPluginInfo.C
ChomboCommonPluginInfo.C
)

SET(LIBI_SOURCES
ChomboPluginInfo.C
)

SET(LIBM_SOURCES
ChomboMDServerPluginInfo.C
${COMMON_SOURCES}
avtChomboFileFormat.C
avtChomboOptions.C
)

SET(LIBE_SOURCES
ChomboEnginePluginInfo.C
${COMMON_SOURCES}
avtChomboFileFormat.C
avtChomboOptions.C
)

INCLUDE_DIRECTORIES(
${CMAKE_CURRENT_SOURCE_DIR}
${HDF5_INCLUDE_DIR}
${VISIT_DATABASE_INCLUDES}
)

LINK_DIRECTORIES(${VISIT_LIBRARY_DIR} ${HDF5_LIBRARY_DIR} )

ADD_LIBRARY(IChomboDatabase ${LIBI_SOURCES})
TARGET_LINK_LIBRARIES(IChomboDatabase visitcommon)
SET(INSTALLTARGETS IChomboDatabase)

IF(NOT VISIT_ENGINE_ONLY AND NOT VISIT_DBIO_ONLY)
    ADD_LIBRARY(MChomboDatabase ${LIBM_SOURCES})
    TARGET_LINK_LIBRARIES(MChomboDatabase visitcommon avtdbatts avtdatabase_ser ${HDF5_LIB} )
    ADD_TARGET_DEFINITIONS(MChomboDatabase MDSERVER)
    SET(INSTALLTARGETS ${INSTALLTARGETS} MChomboDatabase)
ENDIF(NOT VISIT_ENGINE_ONLY AND NOT VISIT_DBIO_ONLY)

ADD_LIBRARY(EChomboDatabase_ser ${LIBE_SOURCES})
TARGET_LINK_LIBRARIES(EChomboDatabase_ser visitcommon avtpipeline_ser avtdatabase_ser ${HDF5_LIB} )
ADD_TARGET_DEFINITIONS(EChomboDatabase_ser ENGINE)
SET(INSTALLTARGETS ${INSTALLTARGETS} EChomboDatabase_ser)

IF(VISIT_PARALLEL)
    ADD_PARALLEL_LIBRARY(EChomboDatabase_par ${LIBE_SOURCES})
    TARGET_LINK_LIBRARIES(EChomboDatabase_par visitcommon avtpipeline_par avtdatabase_par ${HDF5_LIB} )
    ADD_TARGET_DEFINITIONS(EChomboDatabase_par ENGINE)
    SET(INSTALLTARGETS ${INSTALLTARGETS} EChomboDatabase_par)
ENDIF(VISIT_PARALLEL)

VISIT_INSTALL_DATABASE_PLUGINS(${INSTALLTARGETS})
VISIT_PLUGIN_TARGET_RTOD(databases ${INSTALLTARGETS})
VISIT_PLUGIN_TARGET_FOLDER(databases Chombo ${INSTALLTARGETS})

