# DO NOT EDIT THIS FILE! THIS FILE IS AUTOMATICALLY GENERATED BY xml2cmake
PROJECT(Tetrad_database)

ADD_DATABASE_CODE_GEN_TARGETS(Tetrad)

SET(COMMON_SOURCES
TetradPluginInfo.C
TetradCommonPluginInfo.C
)

SET(LIBI_SOURCES
TetradPluginInfo.C
)

SET(LIBM_SOURCES
TetradMDServerPluginInfo.C
${COMMON_SOURCES}
avtTetradFileFormat.C
)

SET(LIBE_SOURCES
TetradEnginePluginInfo.C
${COMMON_SOURCES}
avtTetradFileFormat.C
)

INCLUDE_DIRECTORIES(
${CMAKE_CURRENT_SOURCE_DIR}
${HDF5_INCLUDE_DIR}
${VISIT_DATABASE_INCLUDES}
)

LINK_DIRECTORIES(${VISIT_LIBRARY_DIR} ${HDF5_LIBRARY_DIR} )

ADD_LIBRARY(ITetradDatabase ${LIBI_SOURCES})
TARGET_LINK_LIBRARIES(ITetradDatabase visitcommon)
SET(INSTALLTARGETS ITetradDatabase)

IF(NOT VISIT_ENGINE_ONLY AND NOT VISIT_DBIO_ONLY)
    ADD_LIBRARY(MTetradDatabase ${LIBM_SOURCES})
    TARGET_LINK_LIBRARIES(MTetradDatabase visitcommon avtdbatts avtdatabase_ser ${HDF5_LIB} )
    ADD_TARGET_DEFINITIONS(MTetradDatabase MDSERVER)
    SET(INSTALLTARGETS ${INSTALLTARGETS} MTetradDatabase)
ENDIF(NOT VISIT_ENGINE_ONLY AND NOT VISIT_DBIO_ONLY)

ADD_LIBRARY(ETetradDatabase_ser ${LIBE_SOURCES})
TARGET_LINK_LIBRARIES(ETetradDatabase_ser visitcommon avtpipeline_ser avtdatabase_ser ${HDF5_LIB} )
ADD_TARGET_DEFINITIONS(ETetradDatabase_ser ENGINE)
SET(INSTALLTARGETS ${INSTALLTARGETS} ETetradDatabase_ser)

IF(VISIT_PARALLEL)
    ADD_PARALLEL_LIBRARY(ETetradDatabase_par ${LIBE_SOURCES})
    TARGET_LINK_LIBRARIES(ETetradDatabase_par visitcommon avtpipeline_par avtdatabase_par ${HDF5_LIB} )
    ADD_TARGET_DEFINITIONS(ETetradDatabase_par ENGINE)
    SET(INSTALLTARGETS ${INSTALLTARGETS} ETetradDatabase_par)
ENDIF(VISIT_PARALLEL)

VISIT_INSTALL_DATABASE_PLUGINS(${INSTALLTARGETS})
VISIT_PLUGIN_TARGET_RTOD(databases ${INSTALLTARGETS})
VISIT_PLUGIN_TARGET_FOLDER(databases Tetrad ${INSTALLTARGETS})

