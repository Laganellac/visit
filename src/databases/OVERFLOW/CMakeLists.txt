# DO NOT EDIT THIS FILE! THIS FILE IS AUTOMATICALLY GENERATED BY xml2cmake
PROJECT(OVERFLOW_database)

ADD_DATABASE_CODE_GEN_TARGETS(OVERFLOW SKIP_INFO)

SET(COMMON_SOURCES
OVERFLOWPluginInfo.C
OVERFLOWCommonPluginInfo.C
)

SET(LIBI_SOURCES
OVERFLOWPluginInfo.C
)

SET(LIBM_SOURCES
OVERFLOWMDServerPluginInfo.C
${COMMON_SOURCES}
avtOVERFLOWFileFormat.C
)

SET(LIBE_SOURCES
OVERFLOWEnginePluginInfo.C
${COMMON_SOURCES}
avtOVERFLOWFileFormat.C
)

INCLUDE_DIRECTORIES(
${CMAKE_CURRENT_SOURCE_DIR}
${VISIT_DATABASE_INCLUDES}
)

LINK_DIRECTORIES(${VISIT_LIBRARY_DIR} )

ADD_LIBRARY(IOVERFLOWDatabase ${LIBI_SOURCES})
TARGET_LINK_LIBRARIES(IOVERFLOWDatabase visitcommon)
SET(INSTALLTARGETS IOVERFLOWDatabase)

IF(NOT VISIT_ENGINE_ONLY AND NOT VISIT_DBIO_ONLY)
    ADD_LIBRARY(MOVERFLOWDatabase ${LIBM_SOURCES})
    TARGET_LINK_LIBRARIES(MOVERFLOWDatabase visitcommon avtdbatts avtdatabase_ser )
    ADD_TARGET_DEFINITIONS(MOVERFLOWDatabase MDSERVER)
    SET(INSTALLTARGETS ${INSTALLTARGETS} MOVERFLOWDatabase)
ENDIF(NOT VISIT_ENGINE_ONLY AND NOT VISIT_DBIO_ONLY)

ADD_LIBRARY(EOVERFLOWDatabase_ser ${LIBE_SOURCES})
TARGET_LINK_LIBRARIES(EOVERFLOWDatabase_ser visitcommon avtpipeline_ser avtdatabase_ser )
ADD_TARGET_DEFINITIONS(EOVERFLOWDatabase_ser ENGINE)
SET(INSTALLTARGETS ${INSTALLTARGETS} EOVERFLOWDatabase_ser)

IF(VISIT_PARALLEL)
    ADD_PARALLEL_LIBRARY(EOVERFLOWDatabase_par ${LIBE_SOURCES})
    TARGET_LINK_LIBRARIES(EOVERFLOWDatabase_par visitcommon avtpipeline_par avtdatabase_par )
    ADD_TARGET_DEFINITIONS(EOVERFLOWDatabase_par ENGINE)
    SET(INSTALLTARGETS ${INSTALLTARGETS} EOVERFLOWDatabase_par)
ENDIF(VISIT_PARALLEL)

VISIT_INSTALL_DATABASE_PLUGINS(${INSTALLTARGETS})
VISIT_PLUGIN_TARGET_RTOD(databases ${INSTALLTARGETS})
VISIT_PLUGIN_TARGET_FOLDER(databases OVERFLOW ${INSTALLTARGETS})

