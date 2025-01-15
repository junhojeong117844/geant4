cmake_minimum_required(VERSION 2.6 FATAL_ERROR)

project(DAMSA_sim)

set(useROOT true)

option(WITH_GEANT4_UIVIS "Build example with Geant4 UI and Vis drivers" ON)
if(WITH_GEANT4_UIVIS)
  find_package(Geant4 REQUIRED ui_all vis_all)
else()
  find_package(Geant4 REQUIRED)
endif()

if(useROOT)
  list(APPEND OT_SOURCE_DIRECTORIES)
  list(APPEND OT_EXECUTABLES)
endif(useROOT)

if(useROOT)
  EXECUTE_PROCESS(COMMAND root-config --cflags OUTPUT_VARIABLE ROOT_CXX_FLAGS OUTPUT_STRIP_TRAILING_WHITESPACE)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${ROOT_CXX_FLAGS}")
endif(useROOT)

if(useROOT)
  EXECUTE_PROCESS(COMMAND root-config --libs OUTPUT_VARIABLE ROOT_LD_FLAGS OUTPUT_STRIP_TRAILING_WHITESPACE)
  set(CMAKE_EXE_LINKER_FLAGS ${ROOT_LD_FLAGS})
endif(useROOT)

find_package(Geant4 REQUIRED ui_all vis_all)

include(${Geant4_USE_FILE})

include_directories(${PROJECT_SOURCE_DIR}/include
					${Geant4_INCLUDE_DIR}
					)

file(GLOB sources ${PROJECT_SOURCE_DIR}/src/*.cc)
file(GLOB headers ${PROJECT_SOURCE_DIR}/include/*.hh)

file(GLOB MACRO_FILES "*.mac")

file(COPY ${MACRO_FILES} DESTINATION ${PROJECT_BINARY_DIR})

add_executable(DAMSA main.cc ${sources} ${headers})
target_link_libraries(DAMSA ${Geant4_LIBRARIES})

add_custom_target(DAMSA_sim DEPENDS DAMSA)
