# DO NOT EDIT THIS FILE! THIS FILE IS AUTOMATICALLY GENERATED BY xml2cmake
PROJECT(PICS_Tester_database)

ADD_DATABASE_CODE_GEN_TARGETS(PICS_Tester)

SET(COMMON_SOURCES
PICS_TesterPluginInfo.C
PICS_TesterCommonPluginInfo.C
)

SET(LIBI_SOURCES
PICS_TesterPluginInfo.C
)

SET(LIBM_SOURCES
PICS_TesterMDServerPluginInfo.C
${COMMON_SOURCES}
avtPICS_TesterFileFormat.C
)

SET(LIBE_SOURCES
PICS_TesterEnginePluginInfo.C
${COMMON_SOURCES}
avtPICS_TesterFileFormat.C
)

INCLUDE_DIRECTORIES(
${CMAKE_CURRENT_SOURCE_DIR}
${VISIT_DATABASE_INCLUDES}
)

LINK_DIRECTORIES(${VISIT_LIBRARY_DIR} )

ADD_LIBRARY(IPICS_TesterDatabase ${LIBI_SOURCES})
TARGET_LINK_LIBRARIES(IPICS_TesterDatabase visitcommon)
SET(INSTALLTARGETS IPICS_TesterDatabase)

IF(NOT VISIT_ENGINE_ONLY AND NOT VISIT_DBIO_ONLY)
    ADD_LIBRARY(MPICS_TesterDatabase ${LIBM_SOURCES})
    TARGET_LINK_LIBRARIES(MPICS_TesterDatabase visitcommon avtdbatts avtdatabase_ser )
    ADD_TARGET_DEFINITIONS(MPICS_TesterDatabase MDSERVER)
    SET(INSTALLTARGETS ${INSTALLTARGETS} MPICS_TesterDatabase)
ENDIF(NOT VISIT_ENGINE_ONLY AND NOT VISIT_DBIO_ONLY)

ADD_LIBRARY(EPICS_TesterDatabase_ser ${LIBE_SOURCES})
TARGET_LINK_LIBRARIES(EPICS_TesterDatabase_ser visitcommon avtpipeline_ser avtdatabase_ser )
ADD_TARGET_DEFINITIONS(EPICS_TesterDatabase_ser ENGINE)
SET(INSTALLTARGETS ${INSTALLTARGETS} EPICS_TesterDatabase_ser)

IF(VISIT_PARALLEL)
    ADD_PARALLEL_LIBRARY(EPICS_TesterDatabase_par ${LIBE_SOURCES})
    TARGET_LINK_LIBRARIES(EPICS_TesterDatabase_par visitcommon avtpipeline_par avtdatabase_par )
    ADD_TARGET_DEFINITIONS(EPICS_TesterDatabase_par ENGINE)
    SET(INSTALLTARGETS ${INSTALLTARGETS} EPICS_TesterDatabase_par)
ENDIF(VISIT_PARALLEL)

VISIT_INSTALL_DATABASE_PLUGINS(${INSTALLTARGETS})
VISIT_PLUGIN_TARGET_RTOD(databases ${INSTALLTARGETS})
VISIT_PLUGIN_TARGET_FOLDER(databases PICS_Tester ${INSTALLTARGETS})

