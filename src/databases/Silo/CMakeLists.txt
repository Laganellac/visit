# DO NOT EDIT THIS FILE! THIS FILE IS AUTOMATICALLY GENERATED BY xml2cmake
PROJECT(Silo_database)

ADD_DATABASE_CODE_GEN_TARGETS(Silo)

SET(COMMON_SOURCES
SiloPluginInfo.C
SiloCommonPluginInfo.C
)

SET(LIBI_SOURCES
SiloPluginInfo.C
)

SET(LIBM_SOURCES
SiloMDServerPluginInfo.C
${COMMON_SOURCES}
avtSiloFileFormat.C
avtSiloMBObjectCache.C
avtSiloOptions.C
)

SET(LIBE_SOURCES
SiloEnginePluginInfo.C
${COMMON_SOURCES}
avtSiloFileFormat.C
avtSiloMBObjectCache.C
avtSiloOptions.C
avtSiloWriter.C
)

INCLUDE_DIRECTORIES(
${CMAKE_CURRENT_SOURCE_DIR}
${SILO_INCLUDE_DIR}
${VISIT_DATABASE_INCLUDES}
)

LINK_DIRECTORIES(${VISIT_LIBRARY_DIR} ${SILO_LIBRARY_DIR} )

ADD_LIBRARY(ISiloDatabase ${LIBI_SOURCES})
TARGET_LINK_LIBRARIES(ISiloDatabase visitcommon)
SET(INSTALLTARGETS ISiloDatabase)

IF(NOT VISIT_ENGINE_ONLY AND NOT VISIT_DBIO_ONLY)
    ADD_LIBRARY(MSiloDatabase ${LIBM_SOURCES})
    TARGET_LINK_LIBRARIES(MSiloDatabase visitcommon avtdbatts avtdatabase_ser ${SILO_LIB} )
    ADD_TARGET_DEFINITIONS(MSiloDatabase MDSERVER)
    SET(INSTALLTARGETS ${INSTALLTARGETS} MSiloDatabase)
ENDIF(NOT VISIT_ENGINE_ONLY AND NOT VISIT_DBIO_ONLY)

ADD_LIBRARY(ESiloDatabase_ser ${LIBE_SOURCES})
TARGET_LINK_LIBRARIES(ESiloDatabase_ser visitcommon avtpipeline_ser avtdatabase_ser ${SILO_LIB} )
ADD_TARGET_DEFINITIONS(ESiloDatabase_ser ENGINE)
SET(INSTALLTARGETS ${INSTALLTARGETS} ESiloDatabase_ser)

IF(VISIT_PARALLEL)
    ADD_PARALLEL_LIBRARY(ESiloDatabase_par ${LIBE_SOURCES})
    TARGET_LINK_LIBRARIES(ESiloDatabase_par visitcommon avtpipeline_par avtdatabase_par ${SILO_LIB} )
    ADD_TARGET_DEFINITIONS(ESiloDatabase_par ENGINE)
    SET(INSTALLTARGETS ${INSTALLTARGETS} ESiloDatabase_par)
ENDIF(VISIT_PARALLEL)

VISIT_INSTALL_DATABASE_PLUGINS(${INSTALLTARGETS})
VISIT_PLUGIN_TARGET_RTOD(databases ${INSTALLTARGETS})
VISIT_PLUGIN_TARGET_FOLDER(databases Silo ${INSTALLTARGETS})

