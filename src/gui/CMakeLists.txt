# Copyright (c) Lawrence Livermore National Security, LLC and other VisIt
# Project developers.  See the top-level LICENSE file for dates and other
# details.  No copyright assignment is required to contribute to VisIt.

#****************************************************************************
# Modifications:
#   Cyrus Harrison, Mon Feb  8 15:40:54 PST 2010
#   Added QvisPythonSyntaxHighlighter
#
#   Cyrus Harrison, Thu Feb 11 09:37:20 PST 2010
#   Added QvisPythonFilterEditor
#
#   Cyrus Harrison, Mon Mar 15 13:27:16 PDT 2010
#   Added QvisTimeSliderControlWidget & QvisSourceManagerWidget.
#
#   Hank Childs, Sun Aug  1 14:41:50 PDT 2010
#   Add QvisCMFEWizard.
#
#   Brad Whitlock, Fri Aug  6 16:34:54 PDT 2010
#   Added QvisSelectionsWindow.
#
#   Brad Whitlock, Mon Dec 27 16:15:50 PST 2010
#   Added QvisHistogram, QvisHistogramLimits, QvisVariableListLimiter.
#
#   Brad Whitlock, Thu Jun  9 15:22:21 PDT 2011
#   Added QvisSelectionsDialog.
#
#   Kathleen Biagas, Fri Jun 10 08:57:36 PDT 2011
#   Added widgets for PickQuery, LineoutQuery, HohlraumFluxQuery,
#   XRayImageQuery,  TimeQueryOtions.
#
#   Brad Whitlock, Thu Sep 14 16:53:41 PDT 2017
#   Cinema support.
#
#   Eric Brugger, Thu Aug  5 11:21:21 PDT 2021
#   Removed support for SeedMe.
#
#****************************************************************************

SET(GUILIB_SOURCES
AccessViewerSession.C
ColorTableObserver.C
FileServerList.C
GUIBase.C
KeyframeData.C
KeyframeDataModel.C
MovieSequence.C
MovieSequenceCompositeTransition.C
MovieSequenceCurrentPlots.C
MovieSequenceFactory.C
MovieSequenceRotate.C
MovieSequenceScripting.C
MovieSequenceTransition.C
MovieTemplateConfig.C
MovieUtility.C
NameSimplifier.C
QualifiedFilename.C
QvisAbstractOpacityBar.C
QvisAnimationSlider.C
QvisAnimationWindow.C
QvisAnnotationObjectInterface.C
QvisAnnotationObjectInterfaceFactory.C
QvisAnnotationWindow.C
QvisAppearanceWindow.C
QvisApplication.C
QvisAxisAttributesWidget.C
QvisCinemaWizard.C
QvisCMFEWizard.C
QvisCollapsibleFrame.C
QvisColorButton.C
QvisColorGridWidget.C
QvisColorManagerWidget.C
QvisColorSelectionWidget.C
QvisColorSwatchListWidget.C
QvisColorTableWindow.C
QvisCommandWindow.C
QvisCompositeTransition.C
QvisDBOptionsDialog.C
QvisDBOptionsHelpWindow.C
QvisDatabaseCorrelationListWindow.C
QvisDatabaseCorrelationWindow.C
QvisDelayedWindow.C
QvisDelayedWindowObserver.C
QvisDelayedWindowSimpleObserver.C
QvisDialogLineEdit.C
QvisDownloader.C
QvisElementButton.C
QvisElementSelectionWidget.C
QvisEngineWindow.C
QvisExportDBWindow.C
QvisExpressionsWindow.C
QvisFileInformationWindow.C
QvisFileOpenDialog.C
QvisFileOpenWindow.C
QvisSessionFileDialog.C
QvisFilePanel.C
QvisFilePanelItem.C
QvisFileSelectionWindow.C
QvisFileWindowBase.C
QvisFontAttributesWidget.C
QvisGUIApplication.C
QvisGaussianOpacityBar.C
QvisGlobalLineoutWindow.C
QvisGridWidget.C
QvisHelpWindow.C
QvisHistogram.C
QvisHistogramLimits.C
QvisHohlraumFluxQueryWidget.C
QvisHostProfileWindow.C
QvisImageAnnotationInterface.C
QvisInteractorWindow.C
QvisInterpreter.C
QvisKeyframeDelegate.C
QvisKeyframeDrawer.C
QvisKeyframePlotRangeWidget.C
QvisKeyframeWidget.C
QvisKeyframeWindow.C
QvisLegendAttributesInterface.C
QvisLightingWidget.C
QvisLightingWindow.C
QvisLine2DInterface.C
QvisLine3DInterface.C
QvisLineoutQueryWidget.C
QvisLineWidthWidget.C
QvisMacroWindow.C
QvisMainWindow.C
QvisMaterialWindow.C
QvisMeshManagementWindow.C
QvisMessageWindow.C
QvisMovieProgressDialog.C
QvisNotepadArea.C
QvisOpacitySlider.C
QvisOperatorWindow.C
QvisOutputWindow.C
QvisPeriodicTableWidget.C
QvisPickQueryWidget.C
QvisPickWindow.C
QvisPlotListBox.C
QvisPlotListBoxItem.C
QvisPlotManagerWidget.C
QvisPluginManagerAttributesDataModel.C
QvisPluginWindow.C
QvisPointControl.C
QvisPostableMainWindow.C
QvisPostableWindow.C
QvisPostableWindowObserver.C
QvisPostableWindowSimpleObserver.C
QvisPredefinedViewports.C
QvisPreferencesWindow.C
QvisPythonFilterEditor.C
QvisPythonSyntaxHighlighter.C
QvisQueryOverTimeWindow.C
QvisQueryWindow.C
QvisRecentPathRemovalWindow.C
QvisRenderingWindow.C
QvisRotationTransition.C
QvisSILSetSelector.C
QvisSaveMovieWizard.C
QvisSaveWindow.C
QvisScreenPositionEdit.C
QvisScreenPositioner.C
QvisScribbleOpacityBar.C
QvisSelectionsDialog.C
QvisSelectionsWindow.C
QvisSetupHostProfilesAndConfigWindow.C
QvisSequenceButton.C
QvisSequenceMappingModel.C
QvisSequenceTransition.C
QvisSequenceView.C
QvisSessionFileDatabaseLoader.C
QvisSessionSourceChanger.C
QvisSessionSourceChangerDialog.C
QvisSimulationCommandWindow.C
QvisSimulationMessageWindow.C
QvisSimulationWindow.C
QvisSourceManagerWidget.C
QvisSpectrumBar.C
QvisStripChart.C
QvisStripChartMgr.C
QvisStripChartTabWidget.C
QvisSubsetPanelItem.C
QvisSubsetPanelWidget.C
QvisSubsetWindow.C
QvisText2DInterface.C
QvisText3DInterface.C
QvisTimeQueryOptionsWidget.C
QvisTimeSliderControlWidget.C
QvisTimeSliderInterface.C
QvisTurnDownButton.C
QvisUiLoader.C
QvisVariableListLimiter.C
QvisVCRControl.C
QvisViewWindow.C
QvisViewportWidget.C
QvisVisItUpdate.C
QvisWindowBase.C
QvisWizard.C
QvisXRayImageQueryWidget.C
SimCommandSlots.C
SplashScreen.C
WidgetDataNode.C
mini3D.C
)

# The subset of the sources that have Q_OBJECT in their header.
SET(GUILIB_MOC_SOURCES
QvisAbstractOpacityBar.h
QvisAnimationSlider.h
QvisAnimationWindow.h
QvisAnnotationObjectInterface.h
QvisAnnotationWindow.h
QvisAppearanceWindow.h
QvisApplication.h
QvisAxisAttributesWidget.h
QvisCinemaWizard.h
QvisColorButton.h
QvisColorGridWidget.h
QvisColorSelectionWidget.h
QvisColorTableWindow.h
QvisCommandWindow.h
QvisDBOptionsDialog.h
QvisDBOptionsHelpWindow.h
QvisDatabaseCorrelationListWindow.h
QvisDatabaseCorrelationWindow.h
QvisDelayedWindow.h
QvisDelayedWindowObserver.h
QvisDelayedWindowSimpleObserver.h
QvisDialogLineEdit.h
QvisDownloader.h
QvisMeshManagementWindow.h
QvisElementButton.h
QvisElementSelectionWidget.h
QvisEngineWindow.h
QvisExportDBWindow.h
QvisExpressionsWindow.h
QvisFileInformationWindow.h
QvisFilePanel.h
QvisFileSelectionWindow.h
QvisFileOpenWindow.h
QvisFileWindowBase.h
QvisFontAttributesWidget.h
QvisGaussianOpacityBar.h
QvisGlobalLineoutWindow.h
QvisGridWidget.h
QvisGUIApplication.h
QvisHelpWindow.h
QvisHistogram.h
QvisHistogramLimits.h
QvisHohlraumFluxQueryWidget.h
QvisHostProfileWindow.h
QvisImageAnnotationInterface.h
QvisInteractorWindow.h
QvisInterpreter.h
QvisLightingWidget.h
QvisLightingWindow.h
QvisLineoutQueryWidget.h
QvisLineWidthWidget.h
QvisMacroWindow.h
QvisMainWindow.h
QvisMaterialWindow.h
QvisMessageWindow.h
QvisMovieProgressDialog.h
QvisNotepadArea.h
QvisOperatorWindow.h
QvisOpacitySlider.h
QvisOutputWindow.h
QvisPeriodicTableWidget.h
QvisPickQueryWidget.h
QvisPickWindow.h
QvisPlotListBox.h
QvisPluginManagerAttributesDataModel.h
QvisPointControl.h
QvisPlotManagerWidget.h
QvisPluginWindow.h
#QvisPostableMainWindow.h #nothing to moc
QvisPostableWindow.h
QvisPostableWindowObserver.h
QvisPostableWindowSimpleObserver.h
QvisPreferencesWindow.h
QvisPythonFilterEditor.h
QvisPythonSyntaxHighlighter.h
QvisQueryOverTimeWindow.h
QvisQueryWindow.h
QvisRecentPathRemovalWindow.h
QvisRenderingWindow.h
QvisSaveWindow.h
QvisScreenPositionEdit.h
QvisScreenPositioner.h
QvisScribbleOpacityBar.h
QvisSelectionsDialog.h
QvisSelectionsWindow.h
QvisSessionFileDatabaseLoader.h
QvisSessionSourceChanger.h
QvisSessionSourceChangerDialog.h
QvisSourceManagerWidget.h
QvisSpectrumBar.h
QvisTurnDownButton.h
QvisVCRControl.h
QvisViewWindow.h
QvisWindowBase.h
QvisWizard.h
SplashScreen.h
QvisSimulationWindow.h
QvisStripChartMgr.h
QvisStripChart.h
QvisStripChartTabWidget.h
SimCommandSlots.h
QvisSimulationMessageWindow.h
QvisSimulationCommandWindow.h
QvisFileOpenDialog.h
QvisCMFEWizard.h
QvisCollapsibleFrame.h
QvisColorManagerWidget.h
QvisColorSwatchListWidget.h
QvisSILSetSelector.h
QvisSubsetWindow.h
QvisSubsetPanelWidget.h
QvisTimeQueryOptionsWidget.h
QvisTimeSliderInterface.h
QvisLegendAttributesInterface.h
QvisLine2DInterface.h
QvisLine3DInterface.h
QvisText3DInterface.h
QvisText2DInterface.h
QvisTimeSliderControlWidget.h
QvisVariableListLimiter.h
QvisVisItUpdate.h
QvisSequenceButton.h
QvisCompositeTransition.h
QvisSequenceTransition.h
QvisPredefinedViewports.h
QvisSaveMovieWizard.h
QvisSetupHostProfilesAndConfigWindow.h
QvisSequenceView.h
QvisSequenceMappingModel.h
QvisKeyframeWindow.h
QvisKeyframeWidget.h
QvisKeyframePlotRangeWidget.h
QvisViewportWidget.h
QvisXRayImageQueryWidget.h
)

QT_WRAP_CPP(gui GUILIB_SOURCES ${GUILIB_MOC_SOURCES})

IF (NOT WIN32)
    # This keeps comm's exceptions visible when using -fvisibility=hidden
    ADD_DEFINITIONS(-DCOMM_EXPORTS)
ENDIF (NOT WIN32)

INCLUDE_DIRECTORIES(
${CMAKE_CURRENT_SOURCE_DIR}
${VISIT_COMMON_INCLUDES}
${VISIT_SOURCE_DIR}/avt/DBAtts/MetaData
${VISIT_SOURCE_DIR}/avt/DBAtts/SIL
${VISIT_SOURCE_DIR}/common
${VISIT_SOURCE_DIR}/mdserver/proxy
${VISIT_SOURCE_DIR}/mdserver/rpc
${VISIT_SOURCE_DIR}/viewer/proxy
${VISIT_SOURCE_DIR}/viewer/rpc
${VISIT_SOURCE_DIR}/winutil
${VISIT_SOURCE_DIR}/third_party_builtin
${QWT_INCLUDE_DIR}
)
LINK_DIRECTORIES(${LIBRARY_OUTPUT_DIRECTORY} )

SET(GUI_QT_LIBS
${QT_QTUITOOLS_LIBRARY}
${QT_QTOPENGL_LIBRARY} 
${QT_QTGUI_LIBRARY} 
${QT_QTNETWORK_LIBRARY} 
${QT_QTXML_LIBRARY} 
${QT_QTCORE_LIBRARY}
)
IF(VISIT_STATIC)
    SET(GUI_QT_LIBS
        ${GUI_QT_LIBS}
        ${QT_QTCORE_LIB_DEPENDENCIES} 
        ${QT_QTGUI_LIB_DEPENDENCIES} 
        ${QT_QTOPENGL_LIB_DEPENDENCIES} 
        ${QT_QTNETWORK_LIB_DEPENDENCIES} 
        ${QT_QTXML_LIB_DEPENDENCIES} 
        ${QT_QTUITOOLS_LIB_DEPENDENCIES}
    )
ENDIF(VISIT_STATIC)

#***************************** The gui library *******************************
ADD_LIBRARY(gui ${GUILIB_SOURCES})

IF (WIN32)
    SET_TARGET_PROPERTIES(gui PROPERTIES OUTPUT_NAME guilib)
    SET_TARGET_PROPERTIES(gui PROPERTIES COMPILE_DEFINITIONS QWT_DLL)
ENDIF (WIN32)
TARGET_LINK_LIBRARIES(gui 
viewerrpc
viewerproxy
visitcommon
mdserverrpc
mdserverproxy
avtdbatts
winutil
${GUI_QT_LIBS}
${QWT_LIBRARY}
)

IF(APPLE)
    SET_TARGET_PROPERTIES(gui 
        PROPERTIES
        LINK_FLAGS "-framework Carbon"
    )
ELSEIF(WIN32)
# Needed because QT-4.6.3 has one library, QT_QTUITOOLS_LIBRARY,
# with a default link library in it.
    SET_TARGET_PROPERTIES(gui
        PROPERTIES
        LINK_FLAGS "/NODEFAULTLIB:libcmt"
    )
ELSEIF(UNIX)
    TARGET_LINK_LIBRARIES(gui X11)
ENDIF(APPLE)

# Install these targets
VISIT_INSTALL_TARGETS(gui)

IF(NOT VISIT_STATIC)
    ADD_SUBDIRECTORY(main)
ENDIF(NOT VISIT_STATIC)
