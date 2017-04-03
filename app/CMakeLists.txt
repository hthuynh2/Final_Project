set(pathToProject /Users/hthieu/Desktop/Spring2017/ECE420/Final_Project)

set(pathToOpenCv /Users/hthieu/Desktop/NDK_OpenCv/OpenCV-android-sdk)
cmake_minimum_required(VERSION 3.4.1)


set(CMAKE_VERBOSE_MAKEFILE on)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=gnu++11")

include_directories(${pathToOpenCv}/sdk/native/jni/include)

add_library(    native-lib
                SHARED
                src/main/cpp/native-lib.cpp
                src/main/cpp/sift_main.cpp
                src/main/cpp/image.cpp
                src/main/cpp/sift.cpp
                src/main/cpp/constant.cpp
                src/main/cpp/octave.cpp
                src/main/cpp/key.cpp
                )

add_library( lib_opencv SHARED IMPORTED )

set_target_properties(lib_opencv PROPERTIES IMPORTED_LOCATION ${pathToProject}/app/src/main/jniLibs/${ANDROID_ABI}/libopencv_java3.so)


find_library( # Sets the name of the path variable.
              log-lib

              # Specifies the name of the NDK library that
              # you want CMake to locate.
              log )

target_link_libraries( # Specifies the target library.
                       native-lib

                       # Links the target library to the log library
                       # included in the NDK.
                       ${log-lib}
                       lib_opencv
                       )