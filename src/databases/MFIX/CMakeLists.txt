# DO NOT EDIT THIS FILE! THIS FILE IS AUTOMATICALLY GENERATED BY xml2cmake
PROJECT(MFIX_database)

ADD_DATABASE_CODE_GEN_TARGETS(MFIX)

SET(COMMON_SOURCES
MFIXPluginInfo.C
MFIXCommonPluginInfo.C
)

SET(LIBI_SOURCES
MFIXPluginInfo.C
)

SET(LIBM_SOURCES
MFIXMDServerPluginInfo.C
${COMMON_SOURCES}
avtMFIXFileFormat.C
avtMFIXOptions.C
vtkMFIXReader.C
)

SET(LIBE_SOURCES
MFIXEnginePluginInfo.C
${COMMON_SOURCES}
avtMFIXFileFormat.C
avtMFIXOptions.C
vtkMFIXReader.C
)

INCLUDE_DIRECTORIES(
${CMAKE_CURRENT_SOURCE_DIR}
${VISIT_DATABASE_INCLUDES}
)

LINK_DIRECTORIES(${VISIT_LIBRARY_DIR} )

ADD_LIBRARY(IMFIXDatabase ${LIBI_SOURCES})
TARGET_LINK_LIBRARIES(IMFIXDatabase visitcommon)
SET(INSTALLTARGETS IMFIXDatabase)

IF(NOT VISIT_ENGINE_ONLY AND NOT VISIT_DBIO_ONLY)
    ADD_LIBRARY(MMFIXDatabase ${LIBM_SOURCES})
    TARGET_LINK_LIBRARIES(MMFIXDatabase visitcommon avtdbatts avtdatabase_ser )
    ADD_TARGET_DEFINITIONS(MMFIXDatabase MDSERVER)
    SET(INSTALLTARGETS ${INSTALLTARGETS} MMFIXDatabase)
ENDIF(NOT VISIT_ENGINE_ONLY AND NOT VISIT_DBIO_ONLY)

ADD_LIBRARY(EMFIXDatabase_ser ${LIBE_SOURCES})
TARGET_LINK_LIBRARIES(EMFIXDatabase_ser visitcommon avtpipeline_ser avtdatabase_ser )
ADD_TARGET_DEFINITIONS(EMFIXDatabase_ser ENGINE)
SET(INSTALLTARGETS ${INSTALLTARGETS} EMFIXDatabase_ser)

IF(VISIT_PARALLEL)
    ADD_PARALLEL_LIBRARY(EMFIXDatabase_par ${LIBE_SOURCES})
    TARGET_LINK_LIBRARIES(EMFIXDatabase_par visitcommon avtpipeline_par avtdatabase_par )
    ADD_TARGET_DEFINITIONS(EMFIXDatabase_par ENGINE)
    SET(INSTALLTARGETS ${INSTALLTARGETS} EMFIXDatabase_par)
ENDIF(VISIT_PARALLEL)

VISIT_INSTALL_DATABASE_PLUGINS(${INSTALLTARGETS})
VISIT_PLUGIN_TARGET_RTOD(databases ${INSTALLTARGETS})
VISIT_PLUGIN_TARGET_FOLDER(databases MFIX ${INSTALLTARGETS})

