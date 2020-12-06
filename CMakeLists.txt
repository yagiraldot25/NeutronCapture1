#----------------------------------------------------------------------------
# Setup the project
#
cmake_minimum_required(VERSION 2.6 FATAL_ERROR)
project(neutron-capture-1)

# ROOT
include(FindROOT.cmake)

set(INCLUDE_DIRECTORIES
${ROOT_INCLUDE_DIR} 
)
include_directories( ${INCLUDE_DIRECTORIES})
set(LINK_DIRECTORIES
${ROOT_LIBRARY_DIR}
)
link_directories( ${LINK_DIRECTORIES})

#----------------------------------------------------------------------------
# Find Geant4 package, activating all available UI and Vis drivers by default
# You can set WITH_GEANT4_UIVIS to OFF via the command line or ccmake/cmake-gui
# to build a batch mode only executable
#
option(WITH_GEANT4_UIVIS "Build example with Geant4 UI and Vis drivers" ON)
if(WITH_GEANT4_UIVIS)
  find_package(Geant4 REQUIRED ui_all vis_all)
else()
  find_package(Geant4 REQUIRED)
endif()

#----------------------------------------------------------------------------
# Setup Geant4 include directories and compile definitions
# Setup include directory for this project
#
include(${Geant4_USE_FILE})
include_directories(${PROJECT_SOURCE_DIR}/include)

#----------------------------------------------------------------------------
# Locate sources and headers for this project
# NB: headers are included so they will show up in IDEs
#
include_directories(${PROJECT_SOURCE_DIR}/include)
file(GLOB sources ${PROJECT_SOURCE_DIR}/src/*.cc)
file(GLOB headers ${PROJECT_SOURCE_DIR}/include/*.hh)

#----------------------------------------------------------------------------
# Get examples sources from common and shared
#
#list(APPEND sources 
#  ${PROJECT_SOURCE_DIR}/../SciFW1/src/geometry/AcceleratorClinac2100.cc)

#----------------------------------------------------------------------------
# Add the executable, and link it to the Geant4 libraries
#
add_executable(neutron-capture-1 neutron-capture-1.cc ${sources} ${headers})
target_link_libraries(neutron-capture-1 ${Geant4_LIBRARIES} ${ROOT_LIBRARIES})

#----------------------------------------------------------------------------
# Copy all scripts to the build directory, i.e. the directory in which we
# build neutron_capture. This is so that we can run the executable directly because it
# relies on these scripts being in the current working directory.
#
set(neutron-capture-1_SCRIPTS
  mac/vis1.mac
  mac/vis2.mac
  mac/init.mac
  beam/conical-beam.mac
  beam/fast-neutron.mac
  beam/fast-neutron-therapy-spectrum-by-standard-target.dat
  beam/thermal-neutron.mac
  beam/thermal-neutron-therapy-spectrum.dat
  analysis/data/total-dose-mesuared.dat
  analysis/data/total-dose-mesuared-2.dat
  analysis/data/boron-dose-mesuared.dat
  analysis/data/boron-dose-mesuared-2.dat
  analysis/data/boron-boost-ratio-2.dat
  analysis/Plot_01.C
  )

foreach(_script ${neutron-capture-1_SCRIPTS})
  configure_file(
    ${PROJECT_SOURCE_DIR}/${_script}
    ${PROJECT_BINARY_DIR}/${_script}
    COPYONLY
    )
endforeach()

#----------------------------------------------------------------------------
# For internal Geant4 use - but has no effect if you build this
# example standalone
#
#add_custom_target(neutron-capture-1 DEPENDS neutron-capture-1)

#----------------------------------------------------------------------------
# Install the executable to 'bin' directory under CMAKE_INSTALL_PREFIX
#
install(TARGETS neutron-capture-1 DESTINATION bin)


