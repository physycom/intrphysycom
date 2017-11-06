cmake_minimum_required (VERSION 3.1)
project (intrphysycom)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/Modules/")

if(MSVC)
  add_definitions(-D_SCL_SECURE_NO_WARNINGS)
  add_definitions(-D_CRT_SECURE_NO_WARNINGS)
#  add_definitions(-DFREEGLUT_STATIC)
endif()

### Set output directories on a per-configuration base
# Single configuration
set( CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin )
# Multi configuration
foreach( OUTPUTCONFIG ${CMAKE_CONFIGURATION_TYPES} )
    string( TOUPPER ${OUTPUTCONFIG} OUTPUTCONFIG )
    if( OUTPUTCONFIG STREQUAL "RELEASE" )
    set( CMAKE_RUNTIME_OUTPUT_DIRECTORY_${OUTPUTCONFIG} ${CMAKE_SOURCE_DIR}/bin )
    else()
    set( CMAKE_RUNTIME_OUTPUT_DIRECTORY_${OUTPUTCONFIG} ${CMAKE_SOURCE_DIR}/bin/${OUTPUTCONFIG} )
    endif()
endforeach( OUTPUTCONFIG CMAKE_CONFIGURATION_TYPES )


find_package(Boost REQUIRED)
find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)
find_package(FLTK REQUIRED)
find_package(JPEG REQUIRED)
find_package(NR3)

add_definitions(-DBOOST_NO_RVALUE_REFERENCES)

if (NR3_FOUND)
	add_executable(PDE_KDV
	    ${CMAKE_SOURCE_DIR}/PDE_KDV/draw.cpp
	    ${CMAKE_SOURCE_DIR}/PDE_KDV/form.cpp
	    ${CMAKE_SOURCE_DIR}/PDE_KDV/Frame_1.cpp
	    ${CMAKE_SOURCE_DIR}/PDE_KDV/KDV.cpp
	    ${CMAKE_SOURCE_DIR}/PDE_KDV/Main.cpp
    )
    target_link_libraries(PDE_KDV ${FLTK_LIBRARIES} ${OPENGL_gl_LIBRARY} ${OPENGL_glu_LIBRARY} ${JPEG_LIBRARIES} ${GLUT_glut_LIBRARY})
endif()

include_directories(${GLUT_INCLUDE_DIRS} ${OPENGL_INCLUDE_DIRS} ${FLTK_INCLUDE_DIR}) 

add_executable(FrameLight 
	${CMAKE_SOURCE_DIR}/FrameLight/draw.cpp
	${CMAKE_SOURCE_DIR}/FrameLight/form.cpp
	${CMAKE_SOURCE_DIR}/FrameLight/Frame_1.cpp
	${CMAKE_SOURCE_DIR}/FrameLight/Main.cpp
)

add_executable(FrameVuoto 
	${CMAKE_SOURCE_DIR}/FrameVuoto/draw.cpp
	${CMAKE_SOURCE_DIR}/FrameVuoto/form.cpp
	${CMAKE_SOURCE_DIR}/FrameVuoto/Frame.cpp
	${CMAKE_SOURCE_DIR}/FrameVuoto/Main.cpp
)

add_executable(NPuntiSfera 
	${CMAKE_SOURCE_DIR}/NPuntiSfera/avanza.cpp
	${CMAKE_SOURCE_DIR}/NPuntiSfera/draw.cpp
	${CMAKE_SOURCE_DIR}/NPuntiSfera/form.cpp
	${CMAKE_SOURCE_DIR}/NPuntiSfera/Frame_1.cpp
	${CMAKE_SOURCE_DIR}/NPuntiSfera/Main.cpp
	${CMAKE_SOURCE_DIR}/NPuntiSfera/messaggi.cpp
	${CMAKE_SOURCE_DIR}/NPuntiSfera/texture_jpg.cpp
)

add_executable(ODE_exponential 
	${CMAKE_SOURCE_DIR}/ODE_exponential/exp.cpp
)

add_executable(ODE_oscillator 
	${CMAKE_SOURCE_DIR}/ODE_oscillator/main.cpp
)

add_executable(ODE_oscillator_3D
	${CMAKE_SOURCE_DIR}/ODE_oscillator_3D/classi.cpp
	${CMAKE_SOURCE_DIR}/ODE_oscillator_3D/main.cpp
)

add_executable(PDE_Gottlieb
	${CMAKE_SOURCE_DIR}/PDE_Gottlieb/draw.cpp
	${CMAKE_SOURCE_DIR}/PDE_Gottlieb/EqOnde.cpp
	${CMAKE_SOURCE_DIR}/PDE_Gottlieb/form.cpp
	${CMAKE_SOURCE_DIR}/PDE_Gottlieb/Frame_1.cpp
	${CMAKE_SOURCE_DIR}/PDE_Gottlieb/Main.cpp
	${CMAKE_SOURCE_DIR}/PDE_Gottlieb/utili.cpp
)

add_executable(PDE_waves
	${CMAKE_SOURCE_DIR}/PDE_waves/draw.cpp
	${CMAKE_SOURCE_DIR}/PDE_waves/EqOnde.cpp
	${CMAKE_SOURCE_DIR}/PDE_waves/form.cpp
	${CMAKE_SOURCE_DIR}/PDE_waves/Frame_1.cpp
	${CMAKE_SOURCE_DIR}/PDE_waves/Main.cpp
)

target_link_libraries(FrameLight ${FLTK_LIBRARIES} ${OPENGL_gl_LIBRARY} ${OPENGL_glu_LIBRARY} ${JPEG_LIBRARIES} ${GLUT_glut_LIBRARY})
target_link_libraries(FrameVuoto ${FLTK_LIBRARIES} ${OPENGL_gl_LIBRARY} ${OPENGL_glu_LIBRARY} ${JPEG_LIBRARIES} ${GLUT_glut_LIBRARY})
target_link_libraries(NPuntiSfera ${FLTK_LIBRARIES} ${OPENGL_gl_LIBRARY} ${OPENGL_glu_LIBRARY} ${JPEG_LIBRARIES} ${GLUT_glut_LIBRARY})
target_link_libraries(ODE_exponential ${FLTK_LIBRARIES} ${OPENGL_gl_LIBRARY} ${OPENGL_glu_LIBRARY} ${JPEG_LIBRARIES} ${GLUT_glut_LIBRARY})
target_link_libraries(ODE_oscillator ${FLTK_LIBRARIES} ${OPENGL_gl_LIBRARY} ${OPENGL_glu_LIBRARY} ${JPEG_LIBRARIES} ${GLUT_glut_LIBRARY})
target_link_libraries(ODE_oscillator_3D ${FLTK_LIBRARIES} ${OPENGL_gl_LIBRARY} ${OPENGL_glu_LIBRARY} ${JPEG_LIBRARIES} ${GLUT_glut_LIBRARY})
target_link_libraries(PDE_Gottlieb ${FLTK_LIBRARIES} ${OPENGL_gl_LIBRARY} ${OPENGL_glu_LIBRARY} ${JPEG_LIBRARIES} ${GLUT_glut_LIBRARY})
target_link_libraries(PDE_waves ${FLTK_LIBRARIES} ${OPENGL_gl_LIBRARY} ${OPENGL_glu_LIBRARY} ${JPEG_LIBRARIES} ${GLUT_glut_LIBRARY})


if(UNIX)
target_link_libraries(FrameLight            ${CMAKE_DL_LIBS} )
target_link_libraries(FrameVuoto            ${CMAKE_DL_LIBS} )
target_link_libraries(NPuntiSfera           ${CMAKE_DL_LIBS} )
target_link_libraries(ODE_exponential       ${CMAKE_DL_LIBS} )
target_link_libraries(ODE_oscillator        ${CMAKE_DL_LIBS} )
target_link_libraries(ODE_oscillator_3D     ${CMAKE_DL_LIBS} )
target_link_libraries(PDE_Gottlieb          ${CMAKE_DL_LIBS} )
target_link_libraries(PDE_waves             ${CMAKE_DL_LIBS} )
endif()
