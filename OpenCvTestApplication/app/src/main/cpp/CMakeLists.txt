# For more information about using CMake with Android Studio, read the
# documentation: https://d.android.com/studio/projects/add-native-code.html

# Sets the minimum version of CMake required to build the native library.

cmake_minimum_required(VERSION 3.4.1)
add_library(
        native-lib
        SHARED
        native-lib.cpp utils.cpp)
include_directories(include)

#添加OpenCv库
add_library(opencv-lib
        SHARED
        IMPORTED)
#设置添加的动态库的地址
set_target_properties(opencv-lib
              PROPERTIES
              IMPORTED_LOCATION ${CMAKE_SOURCE_DIR}/../jniLibs/${ANDROID_ABI}/libopencv_java4.so)
find_library(
        log-lib
        log)
find_library(
        jnigraphics-lib jnigraphics
)
target_link_libraries(
        native-lib
        ${log-lib}
        ${jnigraphics-lib}
        opencv-lib)