# DO NOT EDIT THIS FILE! THIS FILE IS AUTOMATICALLY GENERATED BY xml2cmake
PROJECT(CoordSwap_operator)

ADD_OPERATOR_CODE_GEN_TARGETS(CoordSwap)

SET(COMMON_SOURCES
CoordSwapPluginInfo.C
CoordSwapCommonPluginInfo.C
CoordSwapAttributes.C
)

SET(LIBI_SOURCES
CoordSwapPluginInfo.C
)

SET(LIBG_SOURCES
CoordSwapGUIPluginInfo.C
QvisCoordSwapWindow.C
${COMMON_SOURCES}
)
SET(LIBG_MOC_SOURCES
QvisCoordSwapWindow.h
)

SET(LIBV_SOURCES
CoordSwapViewerEnginePluginInfo.C
CoordSwapViewerPluginInfo.C
${COMMON_SOURCES}
)

SET(LIBE_SOURCES
CoordSwapViewerEnginePluginInfo.C
CoordSwapEnginePluginInfo.C
avtCoordSwapFilter.C
${COMMON_SOURCES}
)


INCLUDE_DIRECTORIES(
${CMAKE_CURRENT_SOURCE_DIR}
${VISIT_OPERATOR_INCLUDES}
)

LINK_DIRECTORIES(${VISIT_LIBRARY_DIR} )

ADD_LIBRARY(ICoordSwapOperator ${LIBI_SOURCES})
TARGET_LINK_LIBRARIES(ICoordSwapOperator visitcommon)
SET(INSTALLTARGETS ICoordSwapOperator)

IF(NOT VISIT_SERVER_COMPONENTS_ONLY AND NOT VISIT_ENGINE_ONLY AND NOT VISIT_DBIO_ONLY)
    QT_WRAP_CPP(GCoordSwapOperator LIBG_SOURCES ${LIBG_MOC_SOURCES})
    ADD_LIBRARY(GCoordSwapOperator ${LIBG_SOURCES})
    TARGET_LINK_LIBRARIES(GCoordSwapOperator visitcommon gui )

    ADD_LIBRARY(VCoordSwapOperator ${LIBV_SOURCES})
    ADD_TARGET_DEFINITIONS(VCoordSwapOperator VIEWER)
    TARGET_LINK_LIBRARIES(VCoordSwapOperator visitcommon viewer )

    SET(INSTALLTARGETS ${INSTALLTARGETS} GCoordSwapOperator VCoordSwapOperator)

    IF(VISIT_PYTHON_SCRIPTING)
        SET(LIBS_SOURCES
            CoordSwapScriptingPluginInfo.C
            PyCoordSwapAttributes.C
            ${COMMON_SOURCES}
        )
        ADD_LIBRARY(SCoordSwapOperator ${LIBS_SOURCES})
        IF(WIN32)
            # This prevents python from #defining snprintf as _snprintf
            SET_TARGET_PROPERTIES(SCoordSwapOperator PROPERTIES COMPILE_DEFINITIONS HAVE_SNPRINTF)
        ENDIF()
        TARGET_LINK_LIBRARIES(SCoordSwapOperator visitcommon visitpy ${PYTHON_LIBRARY})
        SET(INSTALLTARGETS ${INSTALLTARGETS} SCoordSwapOperator)
    ENDIF(VISIT_PYTHON_SCRIPTING)

    IF(VISIT_JAVA)
        FILE(COPY CoordSwapAttributes.java DESTINATION ${JavaClient_BINARY_DIR}/src/operators)
        ADD_CUSTOM_TARGET(JavaCoordSwap ALL ${Java_JAVAC_EXECUTABLE} ${VISIT_Java_FLAGS} -d ${JavaClient_BINARY_DIR} -classpath ${JavaClient_BINARY_DIR} -sourcepath ${JavaClient_BINARY_DIR} CoordSwapAttributes.java
            DEPENDS JavaClient
            WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})
    ENDIF(VISIT_JAVA)
ENDIF(NOT VISIT_SERVER_COMPONENTS_ONLY AND NOT VISIT_ENGINE_ONLY AND NOT VISIT_DBIO_ONLY)

ADD_LIBRARY(ECoordSwapOperator_ser ${LIBE_SOURCES})
TARGET_LINK_LIBRARIES(ECoordSwapOperator_ser visitcommon avtpipeline_ser avtexpressions_ser avtfilters_ser )
SET(INSTALLTARGETS ${INSTALLTARGETS} ECoordSwapOperator_ser)

IF(VISIT_PARALLEL)
    ADD_PARALLEL_LIBRARY(ECoordSwapOperator_par ${LIBE_SOURCES})
    TARGET_LINK_LIBRARIES(ECoordSwapOperator_par visitcommon avtpipeline_par avtexpressions_par avtfilters_par )
    SET(INSTALLTARGETS ${INSTALLTARGETS} ECoordSwapOperator_par)
ENDIF(VISIT_PARALLEL)

VISIT_INSTALL_OPERATOR_PLUGINS(${INSTALLTARGETS})
VISIT_PLUGIN_TARGET_RTOD(operators ${INSTALLTARGETS})
VISIT_PLUGIN_TARGET_FOLDER(operators CoordSwap ${INSTALLTARGETS})

