project(lfv)

cmake_minimum_required(VERSION 2.8)
#TODO: please change the following line to include the Qt5 path
set (CMAKE_PREFIX_PATH /opt/Qt5.7.0/5.7/gcc_64)
#set(CMAKE_PREFIX_PATH $ENV{HOME}/Qt5.7.0/5.7/gcc_64)
#TODO: please change the following line to include the OpenCV path
set (OpenCV_DIR "/usr/local/opencv3.2/share/OpenCV")

# Find OpenCV, you may need to set OpenCV_DIR variable
# to the absolute path to the directory containing OpenCVConfig.cmake file
# via the command line or GUI
find_package(OpenCV REQUIRED)

# If the package has been found, several variables will
# be set, you can find the full list with descriptions
# in the OpenCVConfig.cmake file.
# Print some message showing some of them
message(STATUS "OpenCV library status:")
message(STATUS "    version: ${OpenCV_VERSION}")
message(STATUS "    libraries: ${OpenCV_LIBS}")
message(STATUS "    include path: ${OpenCV_INCLUDE_DIRS}")

macro(use_cxx11)
  if (CMAKE_VERSION VERSION_LESS "3.1")
    if (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
      set (CMAKE_CXX_FLAGS "--std=gnu++11 ${CMAKE_CXX_FLAGS}")
    endif ()
  else ()
    set (CMAKE_CXX_STANDARD 11)
  endif ()
endmacro(use_cxx11)
use_cxx11()

find_package(Qt5Core REQUIRED)
find_package(Qt5Widgets REQUIRED)
#find_package(Qt5OpenGL REQUIRED)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)
find_package(OpenMP)
if (OPENMP_FOUND)
   set (CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${OpenMP_C_FLAGS}")
   set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS}")
endif()
file(GLOB_RECURSE SRCS "src/*.cpp")
file(GLOB_RECURSE HEADERS "src/*.h")


set (INCLUDE_DIRS "")
foreach (_header ${HEADERS})
    get_filename_component(_dir ${_header} PATH)
    list (APPEND INCLUDE_DIRS ${_dir})
endforeach()
list(REMOVE_DUPLICATES INCLUDE_DIRS)

include_directories(${INCLUDE_DIRS} ${OPENCV_INCLUDE_DIRS})
add_executable(lfv ${SRCS} ${HEADERS})
target_link_libraries(lfv  ${OpenCV_LIBS}  Qt5::Core Qt5::Widgets)# Qt5::OpenGL)
#file(COPY Resources DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
