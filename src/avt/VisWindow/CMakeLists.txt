# Copyright (c) Lawrence Livermore National Security, LLC and other VisIt
# Project developers.  See the top-level LICENSE file for dates and other
# details.  No copyright assignment is required to contribute to VisIt.

#****************************************************************************
# Modifications:
#   Eric Brugger, Thu Mar  1 10:56:34 PST 2012
#   I modified the CMakeList to remove the include path for the mesa header
#   files when building without Mesa. This caused a compile failure on some
#   systems because the include path was blank.
#
#   Brad Whitlock, Fri May 17 11:12:55 PDT 2013
#   Link with Objective C library on Mac.
#
#   Kathleen Biagas, Mon Jul 13 20:09:58 PDT 2015
#   Add Colleagues/avtText3DColleague.C
#
#   Eric Brugger, Fri Aug 30 11:07:45 PDT 2019
#   Add OPENGL_INCLUDE_DIR to INCLUDE_DIRECTORIES.
#
#****************************************************************************/

SET(COLLEAGUES_SOURCES
Colleagues/VisWinAnnotations.C
Colleagues/VisWinAxes.C
Colleagues/VisWinAxes3D.C
Colleagues/VisWinAxesArray.C
Colleagues/VisWinBackground.C
Colleagues/VisWinColleague.C
Colleagues/VisWinFrame.C
Colleagues/VisWinInteractions.C
Colleagues/VisWinLegends.C
Colleagues/VisWinLighting.C
Colleagues/VisWinParallelAxes.C
Colleagues/VisWinPathTracker.C
Colleagues/VisWinPlots.C
Colleagues/VisWinQuery.C
Colleagues/VisWinRendering.C
Colleagues/VisWinRenderingWithoutWindow.C
Colleagues/VisWinRenderingWithoutWindowWithInteractions.C
Colleagues/VisWinTools.C
Colleagues/VisWinTriad.C
Colleagues/VisWinUserInfo.C
Colleagues/VisWinView.C
Colleagues/avtAnnotationColleague.C
Colleagues/avtAnnotationWithTextColleague.C
Colleagues/avtImageColleague.C
Colleagues/avtLegendAttributesColleague.C
Colleagues/avtLine2DColleague.C
Colleagues/avtLine3DColleague.C
Colleagues/avtText2DColleague.C
Colleagues/avtText3DColleague.C
Colleagues/avtTimeSliderColleague.C
)

SET(EXCEPTIONS_SOURCES
Exceptions/BadColleagueException.C
Exceptions/BadInteractorException.C
Exceptions/BadPlotException.C
Exceptions/BadWindowModeException.C
Exceptions/PlotDimensionalityException.C
)

SET(INTERACTORS_SOURCES
Interactors/Dolly3D.C
Interactors/FlyThrough.C
Interactors/Lineout2D.C
Interactors/Navigate2D.C
Interactors/Navigate3D.C
Interactors/NavigateAxisArray.C
Interactors/NavigateCurve.C
Interactors/NullInteractor.C
Interactors/Pick.C
Interactors/VisitHotPointInteractor.C
Interactors/VisitInteractor.C
Interactors/Zoom2D.C
Interactors/Zoom3D.C
Interactors/ZoomAxisArray.C
Interactors/ZoomCurve.C
Interactors/ZoomInteractor.C
)

SET(PROXIES_SOURCES
Proxies/VisWindowProtectionProxy.C
)

SET(TOOLS_SOURCES
Tools/VisitInteractiveTool.C
Tools/VisitAxisRestrictionTool.C
Tools/VisitBoxTool.C
Tools/VisitLineTool.C
Tools/VisitPlaneTool.C
Tools/VisitPointTool.C
Tools/VisitSphereTool.C
Tools/avtAxisRestrictionToolInterface.C
Tools/avtBoxToolInterface.C
Tools/avtLineToolInterface.C
Tools/avtPlaneToolInterface.C
Tools/avtPointToolInterface.C
Tools/avtSphereToolInterface.C
Tools/avtToolInterface.C
)

SET(VISWINDOW_SOURCES
VisWindow/VisWindow.C
VisWindow/VisWindowWithInteractions.C
VisWindow/VisWindowTypes.C
)

SET(AVTVISWINDOW_SOURCES
${COLLEAGUES_SOURCES}
${EXCEPTIONS_SOURCES}
${INTERACTORS_SOURCES}
${PROXIES_SOURCES}
${TOOLS_SOURCES}
${VISWINDOW_SOURCES}
)

INCLUDE_DIRECTORIES(
${VISIT_COMMON_INCLUDES}
${CMAKE_CURRENT_SOURCE_DIR}/Colleagues
${CMAKE_CURRENT_SOURCE_DIR}/Exceptions
${CMAKE_CURRENT_SOURCE_DIR}/Interactors
${CMAKE_CURRENT_SOURCE_DIR}/Proxies
${CMAKE_CURRENT_SOURCE_DIR}/Tools
${CMAKE_CURRENT_SOURCE_DIR}/VisWindow
${VISIT_SOURCE_DIR}/avt/DBAtts/MetaData
${VISIT_SOURCE_DIR}/avt/DBAtts/SIL
${VISIT_SOURCE_DIR}/avt/Database/Database
${VISIT_SOURCE_DIR}/avt/Math
${VISIT_SOURCE_DIR}/avt/Pipeline/AbstractFilters
${VISIT_SOURCE_DIR}/avt/Pipeline/Data
${VISIT_SOURCE_DIR}/avt/Pipeline/Pipeline
${VISIT_SOURCE_DIR}/avt/Pipeline/Sinks
${VISIT_SOURCE_DIR}/avt/Pipeline/Sources
${VISIT_SOURCE_DIR}/avt/Plotter
${VISIT_SOURCE_DIR}/avt/Plotter/vtk
${VISIT_SOURCE_DIR}/avt/View
${VISIT_SOURCE_DIR}/visit_vtk/full
${VISIT_SOURCE_DIR}/visit_vtk/lightweight
${VTK_INCLUDE_DIRS}
${OPENGL_INCLUDE_DIR}
)

if(VTK_VERSION VERSION_EQUAL "8.1.0")
    set(vtklibs vtkFiltersModeling vtkImagingCore vtkInteractionStyle)
else()
    set(vtklibs VTK::FiltersModeling VTK::ImagingCore VTK::InteractionStyle)
endif()
# Add link directories
LINK_DIRECTORIES(${LIBRARY_OUTPUT_DIRECTORY})

#********************************* SERIAL ************************************
ADD_LIBRARY(avtviswindow_ser ${AVTVISWINDOW_SOURCES})
TARGET_LINK_LIBRARIES(avtviswindow_ser visitcommon avtview avtmath avtplotter_ser visit_vtk lightweight_visit_vtk ${vtklibs} ${OBJC_LIBS})
if(VTK_VERSION VERSION_EQUAL "8.1.0" AND VISIT_OSPRAY)
    TARGET_LINK_LIBRARIES(avtviswindow_ser vtkRenderingOSPRay)
endif()
VISIT_INSTALL_TARGETS(avtviswindow_ser)

#********************************* PARALLEL **********************************
IF(VISIT_PARALLEL)
    ADD_PARALLEL_LIBRARY(avtviswindow_par ${AVTVISWINDOW_SOURCES})
    TARGET_LINK_LIBRARIES(avtviswindow_par visitcommon avtview avtmath avtplotter_par visit_vtk lightweight_visit_vtk ${vtklibs} ${OBJC_LIBS})
    if(VTK_VERSION VERSION_EQUAL "8.1.0" AND VISIT_OSPRAY)
        TARGET_LINK_LIBRARIES(avtviswindow_par vtkRenderingOSPRay)
    endif()
    VISIT_INSTALL_TARGETS(avtviswindow_par)
ENDIF(VISIT_PARALLEL)
