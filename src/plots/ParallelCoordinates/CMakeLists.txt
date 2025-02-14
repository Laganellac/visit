# DO NOT EDIT THIS FILE! THIS FILE IS AUTOMATICALLY GENERATED BY xml2cmake
PROJECT(ParallelCoordinates_plot)

ADD_PLOT_CODE_GEN_TARGETS(ParallelCoordinates)

SET(COMMON_SOURCES
ParallelCoordinatesPluginInfo.C
ParallelCoordinatesCommonPluginInfo.C
ParallelCoordinatesAttributes.C
)

SET(LIBI_SOURCES
ParallelCoordinatesPluginInfo.C
)

SET(LIBG_SOURCES
ParallelCoordinatesGUIPluginInfo.C
QvisParallelCoordinatesPlotWindow.C
${COMMON_SOURCES}
QvisParallelCoordinatesWidget.C
QvisParallelCoordinatesPlotWizard.C
QvisParallelCoordinatesPlotWizardPage.C
)
SET(LIBG_MOC_SOURCES
QvisParallelCoordinatesPlotWindow.h
QvisParallelCoordinatesWidget.h
QvisParallelCoordinatesPlotWizard.h
QvisParallelCoordinatesPlotWizardPage.h
)

SET(LIBV_SOURCES
ParallelCoordinatesViewerEnginePluginInfo.C
ParallelCoordinatesViewerPluginInfo.C
avtParallelCoordinatesPlot.C
avtParallelCoordinatesFilter.C
${COMMON_SOURCES}
)

SET(LIBE_SOURCES
ParallelCoordinatesViewerEnginePluginInfo.C
ParallelCoordinatesEnginePluginInfo.C
avtParallelCoordinatesPlot.C
avtParallelCoordinatesFilter.C
${COMMON_SOURCES}
)


INCLUDE_DIRECTORIES(
${CMAKE_CURRENT_SOURCE_DIR}
${VISIT_PLOT_INCLUDES}
)

LINK_DIRECTORIES(${VISIT_LIBRARY_DIR} )

ADD_LIBRARY(IParallelCoordinatesPlot ${LIBI_SOURCES})
TARGET_LINK_LIBRARIES(IParallelCoordinatesPlot visitcommon)
SET(INSTALLTARGETS IParallelCoordinatesPlot)

IF(NOT VISIT_SERVER_COMPONENTS_ONLY AND NOT VISIT_ENGINE_ONLY AND NOT VISIT_DBIO_ONLY)
    QT_WRAP_CPP(GParallelCoordinatesPlot LIBG_SOURCES ${LIBG_MOC_SOURCES})
    ADD_LIBRARY(GParallelCoordinatesPlot ${LIBG_SOURCES})
    TARGET_LINK_LIBRARIES(GParallelCoordinatesPlot visitcommon gui )

    ADD_LIBRARY(VParallelCoordinatesPlot ${LIBV_SOURCES})
    ADD_TARGET_DEFINITIONS(VParallelCoordinatesPlot VIEWER)
    TARGET_LINK_LIBRARIES(VParallelCoordinatesPlot visitcommon viewer )

    SET(INSTALLTARGETS ${INSTALLTARGETS} GParallelCoordinatesPlot VParallelCoordinatesPlot)

    IF(VISIT_PYTHON_SCRIPTING)
        SET(LIBS_SOURCES
            ParallelCoordinatesScriptingPluginInfo.C
            PyParallelCoordinatesAttributes.C
            ${COMMON_SOURCES}
        )
        ADD_LIBRARY(SParallelCoordinatesPlot ${LIBS_SOURCES})
        IF(WIN32)
            # This prevents python from #defining snprintf as _snprintf
            SET_TARGET_PROPERTIES(SParallelCoordinatesPlot PROPERTIES COMPILE_DEFINITIONS HAVE_SNPRINTF)
        ENDIF()
        TARGET_LINK_LIBRARIES(SParallelCoordinatesPlot visitcommon visitpy ${PYTHON_LIBRARY})
        SET(INSTALLTARGETS ${INSTALLTARGETS} SParallelCoordinatesPlot)
    ENDIF(VISIT_PYTHON_SCRIPTING)

    IF(VISIT_JAVA)
        FILE(COPY ParallelCoordinatesAttributes.java DESTINATION ${JavaClient_BINARY_DIR}/src/plots)
        ADD_CUSTOM_TARGET(JavaParallelCoordinates ALL ${Java_JAVAC_EXECUTABLE} ${VISIT_Java_FLAGS} -d ${JavaClient_BINARY_DIR} -classpath ${JavaClient_BINARY_DIR} -sourcepath ${JavaClient_BINARY_DIR} ParallelCoordinatesAttributes.java
            DEPENDS JavaClient
            WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})
    ENDIF(VISIT_JAVA)
ENDIF(NOT VISIT_SERVER_COMPONENTS_ONLY AND NOT VISIT_ENGINE_ONLY AND NOT VISIT_DBIO_ONLY)

ADD_LIBRARY(EParallelCoordinatesPlot_ser ${LIBE_SOURCES})
TARGET_LINK_LIBRARIES(EParallelCoordinatesPlot_ser visitcommon avtpipeline_ser avtplotter_ser )
ADD_TARGET_DEFINITIONS(EParallelCoordinatesPlot_ser ENGINE)
SET(INSTALLTARGETS ${INSTALLTARGETS} EParallelCoordinatesPlot_ser)

IF(VISIT_PARALLEL)
    ADD_PARALLEL_LIBRARY(EParallelCoordinatesPlot_par ${LIBE_SOURCES})
    TARGET_LINK_LIBRARIES(EParallelCoordinatesPlot_par visitcommon avtpipeline_par avtplotter_par )
    ADD_TARGET_DEFINITIONS(EParallelCoordinatesPlot_par ENGINE)
    SET(INSTALLTARGETS ${INSTALLTARGETS} EParallelCoordinatesPlot_par)
ENDIF(VISIT_PARALLEL)

VISIT_INSTALL_PLOT_PLUGINS(${INSTALLTARGETS})
VISIT_PLUGIN_TARGET_RTOD(plots ${INSTALLTARGETS})
VISIT_PLUGIN_TARGET_FOLDER(plots ParallelCoordinates ${INSTALLTARGETS})

