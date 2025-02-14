# DO NOT EDIT THIS FILE! THIS FILE IS AUTOMATICALLY GENERATED BY xml2cmake
PROJECT(Spreadsheet_plot)

ADD_PLOT_CODE_GEN_TARGETS(Spreadsheet)

SET(COMMON_SOURCES
SpreadsheetPluginInfo.C
SpreadsheetCommonPluginInfo.C
SpreadsheetAttributes.C
)

SET(LIBI_SOURCES
SpreadsheetPluginInfo.C
)

SET(LIBG_SOURCES
SpreadsheetGUIPluginInfo.C
QvisSpreadsheetPlotWindow.C
${COMMON_SOURCES}
)
SET(LIBG_MOC_SOURCES
QvisSpreadsheetPlotWindow.h
)

SET(LIBV_SOURCES
SpreadsheetViewerEnginePluginInfo.C
SpreadsheetViewerPluginInfo.C
avtSpreadsheetPlot.C
avtSpreadsheetFilter.C
avtSpreadsheetRenderer.C
avtSpreadsheetRenderer_Viewer.C
avtSpreadsheetTraceRenderer.C
avtOpenGLSpreadsheetTraceRenderer.C
SpreadsheetViewer.C
SpreadsheetCurveViewer.C
SpreadsheetTable.C
SpreadsheetTabWidget.C
${COMMON_SOURCES}
)
SET(LIBV_MOC_SOURCES
SpreadsheetViewer.h
SpreadsheetCurveViewer.h
SpreadsheetTable.h
SpreadsheetTabWidget.h
)

SET(LIBE_SOURCES
SpreadsheetViewerEnginePluginInfo.C
SpreadsheetEnginePluginInfo.C
avtSpreadsheetPlot.C
avtSpreadsheetFilter.C
avtSpreadsheetRenderer.C
avtSpreadsheetRenderer_Engine.C
avtSpreadsheetTraceRenderer.C
avtOpenGLSpreadsheetTraceRenderer.C
${COMMON_SOURCES}
)


INCLUDE_DIRECTORIES(
${CMAKE_CURRENT_SOURCE_DIR}
${VISIT_PLOT_INCLUDES}
)

LINK_DIRECTORIES(${VISIT_LIBRARY_DIR} )

ADD_LIBRARY(ISpreadsheetPlot ${LIBI_SOURCES})
TARGET_LINK_LIBRARIES(ISpreadsheetPlot visitcommon)
SET(INSTALLTARGETS ISpreadsheetPlot)

IF(NOT VISIT_SERVER_COMPONENTS_ONLY AND NOT VISIT_ENGINE_ONLY AND NOT VISIT_DBIO_ONLY)
    QT_WRAP_CPP(GSpreadsheetPlot LIBG_SOURCES ${LIBG_MOC_SOURCES})
    ADD_LIBRARY(GSpreadsheetPlot ${LIBG_SOURCES})
    TARGET_LINK_LIBRARIES(GSpreadsheetPlot visitcommon gui )

    QT_WRAP_CPP(VSpreadsheetPlot LIBV_SOURCES ${LIBV_MOC_SOURCES})
    ADD_LIBRARY(VSpreadsheetPlot ${LIBV_SOURCES})
    ADD_TARGET_DEFINITIONS(VSpreadsheetPlot VIEWER)
    TARGET_LINK_LIBRARIES(VSpreadsheetPlot visitcommon viewer )

    SET(INSTALLTARGETS ${INSTALLTARGETS} GSpreadsheetPlot VSpreadsheetPlot)

    IF(VISIT_PYTHON_SCRIPTING)
        SET(LIBS_SOURCES
            SpreadsheetScriptingPluginInfo.C
            PySpreadsheetAttributes.C
            ${COMMON_SOURCES}
        )
        ADD_LIBRARY(SSpreadsheetPlot ${LIBS_SOURCES})
        IF(WIN32)
            # This prevents python from #defining snprintf as _snprintf
            SET_TARGET_PROPERTIES(SSpreadsheetPlot PROPERTIES COMPILE_DEFINITIONS HAVE_SNPRINTF)
        ENDIF()
        TARGET_LINK_LIBRARIES(SSpreadsheetPlot visitcommon visitpy ${PYTHON_LIBRARY})
        SET(INSTALLTARGETS ${INSTALLTARGETS} SSpreadsheetPlot)
    ENDIF(VISIT_PYTHON_SCRIPTING)

    IF(VISIT_JAVA)
        FILE(COPY SpreadsheetAttributes.java DESTINATION ${JavaClient_BINARY_DIR}/src/plots)
        ADD_CUSTOM_TARGET(JavaSpreadsheet ALL ${Java_JAVAC_EXECUTABLE} ${VISIT_Java_FLAGS} -d ${JavaClient_BINARY_DIR} -classpath ${JavaClient_BINARY_DIR} -sourcepath ${JavaClient_BINARY_DIR} SpreadsheetAttributes.java
            DEPENDS JavaClient
            WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})
    ENDIF(VISIT_JAVA)
ENDIF(NOT VISIT_SERVER_COMPONENTS_ONLY AND NOT VISIT_ENGINE_ONLY AND NOT VISIT_DBIO_ONLY)

ADD_LIBRARY(ESpreadsheetPlot_ser ${LIBE_SOURCES})
TARGET_LINK_LIBRARIES(ESpreadsheetPlot_ser visitcommon avtpipeline_ser avtplotter_ser )
ADD_TARGET_DEFINITIONS(ESpreadsheetPlot_ser ENGINE)
SET(INSTALLTARGETS ${INSTALLTARGETS} ESpreadsheetPlot_ser)

IF(VISIT_PARALLEL)
    ADD_PARALLEL_LIBRARY(ESpreadsheetPlot_par ${LIBE_SOURCES})
    TARGET_LINK_LIBRARIES(ESpreadsheetPlot_par visitcommon avtpipeline_par avtplotter_par )
    ADD_TARGET_DEFINITIONS(ESpreadsheetPlot_par ENGINE)
    SET(INSTALLTARGETS ${INSTALLTARGETS} ESpreadsheetPlot_par)
ENDIF(VISIT_PARALLEL)

VISIT_INSTALL_PLOT_PLUGINS(${INSTALLTARGETS})
VISIT_PLUGIN_TARGET_RTOD(plots ${INSTALLTARGETS})
VISIT_PLUGIN_TARGET_FOLDER(plots Spreadsheet ${INSTALLTARGETS})

