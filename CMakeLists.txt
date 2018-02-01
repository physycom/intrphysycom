cmake_minimum_required (VERSION 3.1)
project (intrphysycom)

if (EXISTS "$ENV{WORKSPACE}/sysconfig/cmake/physycom_config.cmake")
   message(STATUS "Enabling physycom settings")
   include("$ENV{WORKSPACE}/sysconfig/cmake/physycom_config.cmake")
else()
   message(STATUS "Unable to find physycom settings file")
endif()


set (INTERNET_DISABLED OFF CACHE BOOL "DO NOT USE INTERNET CONNECTION")

find_package(Boost REQUIRED)
find_package(OpenGL REQUIRED)
find_package(FLTK REQUIRED)
find_package(JPEG REQUIRED)
find_package(GLUT REQUIRED)

set (NR3_FOUND FALSE)
# if not found, download from official repo and https://www.astro.umd.edu/~ricotti/NEWWEB/teaching/ASTR415/NR3/ only required files
if (NOT EXISTS "${CMAKE_SOURCE_DIR}/cmake/nr.h" AND NOT INTERNET_DISABLED)
  file(DOWNLOAD "http://numerical.recipes/codefile.php?nr3"
    ${CMAKE_SOURCE_DIR}/cmake/nr.h
    TIMEOUT 3
    STATUS download_status
  )
  set (NRH_FOUND TRUE)
endif()

if (NOT EXISTS "${CMAKE_SOURCE_DIR}/cmake/ran.h" AND NOT INTERNET_DISABLED)
  file(DOWNLOAD "https://www.astro.umd.edu/~ricotti/NEWWEB/teaching/ASTR415/NR3/code/ran.h"
    ${CMAKE_SOURCE_DIR}/cmake/ran.h
    TIMEOUT 3
    STATUS download_status
  )
  set (RANH_FOUND TRUE)
endif()

if (NOT EXISTS "${CMAKE_SOURCE_DIR}/cmake/realft.cpp" AND NOT INTERNET_DISABLED)
  file(DOWNLOAD "https://www.astro.umd.edu/~ricotti/NEWWEB/teaching/ASTR415/NR3/legacy/nr2/CPP_211/recipes/realft.cpp"
    ${CMAKE_SOURCE_DIR}/cmake/realft.cpp
    TIMEOUT 3
    STATUS download_status
  )
  execute_process(
    COMMAND git --work-tree=. --git-dir=.git apply ${CMAKE_SOURCE_DIR}/cmake/realft.patch --ignore-whitespace --whitespace=nowarn --verbose
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
    RESULT_VARIABLE error_code
  )
  set (REALFTCPP_FOUND TRUE)
endif()

if (NOT EXISTS "${CMAKE_SOURCE_DIR}/cmake/four1.cpp" AND NOT INTERNET_DISABLED)
  file(DOWNLOAD "https://www.astro.umd.edu/~ricotti/NEWWEB/teaching/ASTR415/NR3/legacy/nr2/CPP_211/recipes/four1.cpp"
    ${CMAKE_SOURCE_DIR}/cmake/four1.cpp
    TIMEOUT 3
    STATUS download_status
  )
  execute_process(
    COMMAND git --work-tree=. --git-dir=.git apply ${CMAKE_SOURCE_DIR}/cmake/four1.patch --ignore-whitespace --whitespace=nowarn --verbose
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
    RESULT_VARIABLE error_code
  )
  set (FOUR1CPP_FOUND TRUE)
endif()

if (NRH_FOUND AND RANH_FOUND AND REALFTCPP_FOUND AND REALFTCPP_FOUND AND FOUR1CPP_FOUND)
set(NR3_FOUND TRUE)
endif()

set(NR3_INCLUDE_DIR ${CMAKE_SOURCE_DIR}/cmake)
include_directories(${OPENGL_INCLUDE_DIRS} ${FLTK_INCLUDE_DIR} ${NR3_INCLUDE_DIR} ${GLUT_INCLUDE_DIR} ${Boost_INCLUDE_DIR})

add_executable(FrameLight
	${CMAKE_SOURCE_DIR}/src/FrameLight/draw.cpp
	${CMAKE_SOURCE_DIR}/src/FrameLight/draw.h
	${CMAKE_SOURCE_DIR}/src/FrameLight/form.cpp
	${CMAKE_SOURCE_DIR}/src/FrameLight/form.h
	${CMAKE_SOURCE_DIR}/src/FrameLight/Frame_1.cpp
	${CMAKE_SOURCE_DIR}/src/FrameLight/Frame_1.h
	${CMAKE_SOURCE_DIR}/src/FrameLight/Main.cpp
)

add_executable(FrameVuoto
	${CMAKE_SOURCE_DIR}/src/FrameVuoto/draw.cpp
	${CMAKE_SOURCE_DIR}/src/FrameVuoto/draw.h
	${CMAKE_SOURCE_DIR}/src/FrameVuoto/form.cpp
	${CMAKE_SOURCE_DIR}/src/FrameVuoto/form.h
	${CMAKE_SOURCE_DIR}/src/FrameVuoto/Frame.cpp
	${CMAKE_SOURCE_DIR}/src/FrameVuoto/Frame.h
	${CMAKE_SOURCE_DIR}/src/FrameVuoto/includes.h
	${CMAKE_SOURCE_DIR}/src/FrameVuoto/Main.cpp
)

add_executable(NPuntiSfera
	${CMAKE_SOURCE_DIR}/src/NPuntiSfera/avanza.cpp
	${CMAKE_SOURCE_DIR}/src/NPuntiSfera/avanza.h
	${CMAKE_SOURCE_DIR}/src/NPuntiSfera/def.h
	${CMAKE_SOURCE_DIR}/src/NPuntiSfera/draw.cpp
	${CMAKE_SOURCE_DIR}/src/NPuntiSfera/draw.h
	${CMAKE_SOURCE_DIR}/src/NPuntiSfera/form.cpp
	${CMAKE_SOURCE_DIR}/src/NPuntiSfera/form.h
	${CMAKE_SOURCE_DIR}/src/NPuntiSfera/Frame_1.cpp
	${CMAKE_SOURCE_DIR}/src/NPuntiSfera/Frame_1.h
	${CMAKE_SOURCE_DIR}/src/NPuntiSfera/Main.cpp
	${CMAKE_SOURCE_DIR}/src/NPuntiSfera/Main.h
	${CMAKE_SOURCE_DIR}/src/NPuntiSfera/messaggi.cpp
	${CMAKE_SOURCE_DIR}/src/NPuntiSfera/texture_jpg.cpp
)

add_executable(ODE_esponenziale
	${CMAKE_SOURCE_DIR}/src/ODE_esponenziale/exp.cpp
	${CMAKE_SOURCE_DIR}/src/ODE_esponenziale/includes.h
)

add_executable(ODE_oscillatore
	${CMAKE_SOURCE_DIR}/src/ODE_oscillatore/main.cpp
)

add_executable(ODE_oscillatore_3D
	${CMAKE_SOURCE_DIR}/src/ODE_oscillatore_3D/classi.cpp
	${CMAKE_SOURCE_DIR}/src/ODE_oscillatore_3D/classi.h
	${CMAKE_SOURCE_DIR}/src/ODE_oscillatore_3D/includes.h
	${CMAKE_SOURCE_DIR}/src/ODE_oscillatore_3D/main.cpp
)

add_executable(PDE_EqCalore
	${CMAKE_SOURCE_DIR}/src/PDE_EqCalore/draw.cpp
	${CMAKE_SOURCE_DIR}/src/PDE_EqCalore/draw.h
	${CMAKE_SOURCE_DIR}/src/PDE_EqCalore/EqCalore.cpp
	${CMAKE_SOURCE_DIR}/src/PDE_EqCalore/form.cpp
	${CMAKE_SOURCE_DIR}/src/PDE_EqCalore/form.h
	${CMAKE_SOURCE_DIR}/src/PDE_EqCalore/Frame.cpp
	${CMAKE_SOURCE_DIR}/src/PDE_EqCalore/Frame.h
	${CMAKE_SOURCE_DIR}/src/PDE_EqCalore/Main.cpp
)

add_executable(PDE_EqLaplace_Console
	${CMAKE_SOURCE_DIR}/src/PDE_EqLaplace/dati.h
	${CMAKE_SOURCE_DIR}/src/PDE_EqLaplace/draw.cpp
	${CMAKE_SOURCE_DIR}/src/PDE_EqLaplace/draw.h
	${CMAKE_SOURCE_DIR}/src/PDE_EqLaplace/EqLaplace.cpp
	${CMAKE_SOURCE_DIR}/src/PDE_EqLaplace/EqLaplace.h
	${CMAKE_SOURCE_DIR}/src/PDE_EqLaplace/form.cpp
	${CMAKE_SOURCE_DIR}/src/PDE_EqLaplace/form.h
	${CMAKE_SOURCE_DIR}/src/PDE_EqLaplace/Frame.cpp
	${CMAKE_SOURCE_DIR}/src/PDE_EqLaplace/Frame.h
	${CMAKE_SOURCE_DIR}/src/PDE_EqLaplace/MainConsole.cpp
)

add_executable(PDE_EqLaplace_Grafica
	${CMAKE_SOURCE_DIR}/src/PDE_EqLaplace/dati.h
	${CMAKE_SOURCE_DIR}/src/PDE_EqLaplace/draw.cpp
	${CMAKE_SOURCE_DIR}/src/PDE_EqLaplace/draw.h
	${CMAKE_SOURCE_DIR}/src/PDE_EqLaplace/EqLaplace.cpp
	${CMAKE_SOURCE_DIR}/src/PDE_EqLaplace/EqLaplace.h
	${CMAKE_SOURCE_DIR}/src/PDE_EqLaplace/form.cpp
	${CMAKE_SOURCE_DIR}/src/PDE_EqLaplace/form.h
	${CMAKE_SOURCE_DIR}/src/PDE_EqLaplace/Frame.cpp
	${CMAKE_SOURCE_DIR}/src/PDE_EqLaplace/Frame.h
	${CMAKE_SOURCE_DIR}/src/PDE_EqLaplace/MainGrafica.cpp
)

add_executable(PDE_EqOnde
	${CMAKE_SOURCE_DIR}/src/PDE_EqOnde/draw.cpp
	${CMAKE_SOURCE_DIR}/src/PDE_EqOnde/draw.h
	${CMAKE_SOURCE_DIR}/src/PDE_EqOnde/EqOnde.cpp
	${CMAKE_SOURCE_DIR}/src/PDE_EqOnde/form.cpp
	${CMAKE_SOURCE_DIR}/src/PDE_EqOnde/form.h
	${CMAKE_SOURCE_DIR}/src/PDE_EqOnde/Frame_1.cpp
	${CMAKE_SOURCE_DIR}/src/PDE_EqOnde/Frame_1.h
	${CMAKE_SOURCE_DIR}/src/PDE_EqOnde/Main.cpp
)

add_executable(PDE_Gottlieb
	${CMAKE_SOURCE_DIR}/src/PDE_Gottlieb/dati.h
	${CMAKE_SOURCE_DIR}/src/PDE_Gottlieb/draw.cpp
	${CMAKE_SOURCE_DIR}/src/PDE_Gottlieb/draw.h
	${CMAKE_SOURCE_DIR}/src/PDE_Gottlieb/EqOnde.cpp
	${CMAKE_SOURCE_DIR}/src/PDE_Gottlieb/form.cpp
	${CMAKE_SOURCE_DIR}/src/PDE_Gottlieb/form.h
	${CMAKE_SOURCE_DIR}/src/PDE_Gottlieb/Frame_1.cpp
	${CMAKE_SOURCE_DIR}/src/PDE_Gottlieb/Frame_1.h
	${CMAKE_SOURCE_DIR}/src/PDE_Gottlieb/Main.cpp
	${CMAKE_SOURCE_DIR}/src/PDE_Gottlieb/utili.cpp
	${CMAKE_SOURCE_DIR}/src/PDE_Gottlieb/utili.h
)

if (NR3_FOUND)
add_executable(PDE_KDV
    ${CMAKE_SOURCE_DIR}/src/PDE_KDV/draw.cpp
    ${CMAKE_SOURCE_DIR}/src/PDE_KDV/draw.h
    ${CMAKE_SOURCE_DIR}/src/PDE_KDV/form.cpp
    ${CMAKE_SOURCE_DIR}/src/PDE_KDV/form.h
    ${CMAKE_SOURCE_DIR}/src/PDE_KDV/Frame_1.cpp
    ${CMAKE_SOURCE_DIR}/src/PDE_KDV/Frame_1.h
    #${CMAKE_SOURCE_DIR}/src/PDE_KDV/guicon.cpp
    #${CMAKE_SOURCE_DIR}/src/PDE_KDV/guicon.h
    ${CMAKE_SOURCE_DIR}/src/PDE_KDV/KDV.cpp
    ${CMAKE_SOURCE_DIR}/src/PDE_KDV/Main.cpp
    ${CMAKE_SOURCE_DIR}/cmake/nr.h
    ${CMAKE_SOURCE_DIR}/cmake/realft.cpp
    ${CMAKE_SOURCE_DIR}/cmake/four1.cpp
)

add_executable(Robby
    ${CMAKE_SOURCE_DIR}/src/Robby/draw.cpp
    ${CMAKE_SOURCE_DIR}/src/Robby/draw.h
    ${CMAKE_SOURCE_DIR}/src/Robby/form.cpp
    ${CMAKE_SOURCE_DIR}/src/Robby/form.h
    ${CMAKE_SOURCE_DIR}/src/Robby/frame.cpp
    ${CMAKE_SOURCE_DIR}/src/Robby/frame.h
    ${CMAKE_SOURCE_DIR}/src/Robby/includes.h
    ${CMAKE_SOURCE_DIR}/src/Robby/main_grafica.cpp
    ${CMAKE_SOURCE_DIR}/src/Robby/robby.cpp
    ${CMAKE_SOURCE_DIR}/src/Robby/robby.h
    ${CMAKE_SOURCE_DIR}/cmake/nr.h
    ${CMAKE_SOURCE_DIR}/cmake/ran.h
)
endif()


target_link_libraries(FrameLight            ${FLTK_LIBRARIES} ${OPENGL_gl_LIBRARY} ${OPENGL_glu_LIBRARY} ${GLUT_LIBRARIES} ${JPEG_LIBRARIES})
target_link_libraries(FrameVuoto            ${FLTK_LIBRARIES} ${OPENGL_gl_LIBRARY} ${OPENGL_glu_LIBRARY} ${GLUT_LIBRARIES} ${JPEG_LIBRARIES})
target_link_libraries(NPuntiSfera           ${FLTK_LIBRARIES} ${OPENGL_gl_LIBRARY} ${OPENGL_glu_LIBRARY} ${GLUT_LIBRARIES} ${JPEG_LIBRARIES})
target_link_libraries(ODE_esponenziale      ${FLTK_LIBRARIES} ${OPENGL_gl_LIBRARY} ${OPENGL_glu_LIBRARY} ${GLUT_LIBRARIES} ${JPEG_LIBRARIES})
target_link_libraries(ODE_oscillatore       ${FLTK_LIBRARIES} ${OPENGL_gl_LIBRARY} ${OPENGL_glu_LIBRARY} ${GLUT_LIBRARIES} ${JPEG_LIBRARIES})
target_link_libraries(ODE_oscillatore_3D    ${FLTK_LIBRARIES} ${OPENGL_gl_LIBRARY} ${OPENGL_glu_LIBRARY} ${GLUT_LIBRARIES} ${JPEG_LIBRARIES})
target_link_libraries(PDE_EqCalore          ${FLTK_LIBRARIES} ${OPENGL_gl_LIBRARY} ${OPENGL_glu_LIBRARY} ${GLUT_LIBRARIES} ${JPEG_LIBRARIES})
target_link_libraries(PDE_EqLaplace_Console ${FLTK_LIBRARIES} ${OPENGL_gl_LIBRARY} ${OPENGL_glu_LIBRARY} ${GLUT_LIBRARIES} ${JPEG_LIBRARIES})
target_link_libraries(PDE_EqLaplace_Grafica ${FLTK_LIBRARIES} ${OPENGL_gl_LIBRARY} ${OPENGL_glu_LIBRARY} ${GLUT_LIBRARIES} ${JPEG_LIBRARIES})
target_link_libraries(PDE_EqOnde            ${FLTK_LIBRARIES} ${OPENGL_gl_LIBRARY} ${OPENGL_glu_LIBRARY} ${GLUT_LIBRARIES} ${JPEG_LIBRARIES})
target_link_libraries(PDE_Gottlieb          ${FLTK_LIBRARIES} ${OPENGL_gl_LIBRARY} ${OPENGL_glu_LIBRARY} ${GLUT_LIBRARIES} ${JPEG_LIBRARIES})
if (NR3_FOUND)
target_link_libraries(PDE_KDV               ${FLTK_LIBRARIES} ${OPENGL_gl_LIBRARY} ${OPENGL_glu_LIBRARY} ${GLUT_LIBRARIES} ${JPEG_LIBRARIES})
target_link_libraries(Robby                 ${FLTK_LIBRARIES} ${OPENGL_gl_LIBRARY} ${OPENGL_glu_LIBRARY} ${GLUT_LIBRARIES} ${JPEG_LIBRARIES})
endif()

if(UNIX)
target_link_libraries(FrameLight            ${CMAKE_DL_LIBS} )
target_link_libraries(FrameVuoto            ${CMAKE_DL_LIBS} )
target_link_libraries(NPuntiSfera           ${CMAKE_DL_LIBS} )
target_link_libraries(ODE_esponenziale      ${CMAKE_DL_LIBS} )
target_link_libraries(ODE_oscillatore       ${CMAKE_DL_LIBS} )
target_link_libraries(ODE_oscillatore_3D    ${CMAKE_DL_LIBS} )
target_link_libraries(PDE_EqCalore          ${CMAKE_DL_LIBS} )
target_link_libraries(PDE_EqLaplace_Console ${CMAKE_DL_LIBS} )
target_link_libraries(PDE_EqLaplace_Grafica ${CMAKE_DL_LIBS} )
target_link_libraries(PDE_EqOnde            ${CMAKE_DL_LIBS} )
target_link_libraries(PDE_Gottlieb          ${CMAKE_DL_LIBS} )
if (NR3_FOUND)
target_link_libraries(PDE_KDV               ${CMAKE_DL_LIBS} )
target_link_libraries(Robby                 ${CMAKE_DL_LIBS} )
endif()
endif()

install (TARGETS
	FrameLight
    FrameVuoto
    NPuntiSfera
    ODE_esponenziale
    ODE_oscillatore
    ODE_oscillatore_3D
    PDE_EqCalore
    PDE_EqLaplace_Console
    PDE_EqLaplace_Grafica
    PDE_EqOnde
    PDE_Gottlieb
    DESTINATION
    ${CMAKE_SOURCE_DIR}/bin/
)

if (NR3_FOUND)
install (TARGETS
    PDE_KDV
    Robby
    DESTINATION
    ${CMAKE_SOURCE_DIR}/bin/
)
endif()
