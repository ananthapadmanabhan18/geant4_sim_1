cmake_minimum_required(VERSION 3.16...3.28)
project(GEANT4 CXX)


# Find Geant4 package
find_package(Geant4 REQUIRED ui_all vis_all)
include(${Geant4_USE_FILE})
include_directories(${PROJECT_SOURCE_DIR}/include)


# Find ROOT package
find_package(ROOT REQUIRED COMPONENTS RIO Net)
include(${ROOT_USE_FILE})

# Setting the source and header files
file(GLOB sources ${PROJECT_SOURCE_DIR}/src/*.cc)
file(GLOB headers ${PROJECT_SOURCE_DIR}/include/*.hh)
file(GLOB headers ${PROJECT_SOURCE_DIR}/include/*.h)



# Add the executable, and link it to the Geant4 libraries
add_executable(simulation simulation.cc ${sources} ${headers})
target_link_libraries(simulation PRIVATE ${Geant4_LIBRARIES} ${ROOT_LIBRARIES})


# Setting the name of the scripts
set(SIMULATION_SCRIPTS
  init_vis.mac
  run.mac
  vis.mac
  )


# Copy the scripts to the build directory if on Windows
if(WIN32)
  foreach(_script ${SIMULATION_SCRIPTS})
    configure_file(
      ${PROJECT_SOURCE_DIR}/macros/${_script}
      ${PROJECT_BINARY_DIR}/Release/${_script}
      COPYONLY
      )
  endforeach()
endif()


# Copy the scripts to the build directory if on UNIX
if(UNIX)
  foreach(_script ${SIMULATION_SCRIPTS})
    configure_file(
      ${PROJECT_SOURCE_DIR}/macros/${_script}
      ${PROJECT_BINARY_DIR}/${_script}
      COPYONLY
      )
  endforeach()
endif()


# Add a custom target to run the simulation
add_custom_target(GEANT4 DEPENDS simulation)

# Install the executable
install(TARGETS simulation DESTINATION bin)
