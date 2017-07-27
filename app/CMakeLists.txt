# For more information about using CMake with Android Studio, read the
# documentation: https://d.android.com/studio/projects/add-native-code.html

# Sets the minimum version of CMake required to build the native library.

cmake_minimum_required(VERSION 3.4.1)

# Creates and names a library, sets it as either STATIC
# or SHARED, and provides the relative paths to its source code.
# You can define multiple libraries, and CMake builds them for you.
# Gradle automatically packages shared libraries with your APK.

add_library( # Sets the name of the library.
             h265decoder

             # Sets the library as a shared library.
             SHARED

             # Provides a relative path to your source file(s).
             src/main/cpp/source/AndroidH265Decoder.cpp )

# Searches for a specified prebuilt library and stores the path as a
# variable. Because CMake includes system libraries in the search path by
# default, you only need to specify the name of the public NDK library
# you want to add. CMake verifies that the library exists before
# completing its build.
include_directories(${PROJECT_SOURCE_DIR}/src/main/cpp/include)
set(LINK_DIR "${PROJECT_SOURCE_DIR}/src/main/jniLibs/${ANDROID_ABI}")


add_library( x265-lib
             SHARED
             IMPORTED )

set_target_properties( # Specifies the target library.
                       x265-lib

                       # Specifies the parameter you want to define.
                       PROPERTIES IMPORTED_LOCATION

                       # Provides the path to the library you want to import.
                       ${LINK_DIR}/libx265.so )


add_library( avutil-lib
             SHARED
             IMPORTED )

set_target_properties( # Specifies the target library.
                       avutil-lib

                       # Specifies the parameter you want to define.
                       PROPERTIES IMPORTED_LOCATION

                       # Provides the path to the library you want to import.
                       ${LINK_DIR}/libavutil-55.so )

add_library( swscale-lib
             SHARED
             IMPORTED )

set_target_properties( # Specifies the target library.
                       swscale-lib

                       # Specifies the parameter you want to define.
                       PROPERTIES IMPORTED_LOCATION

                       # Provides the path to the library you want to import.
                       ${LINK_DIR}/libswscale-4.so )

add_library( swresample-lib
             SHARED
             IMPORTED )

set_target_properties( # Specifies the target library.
                       swresample-lib

                       # Specifies the parameter you want to define.
                       PROPERTIES IMPORTED_LOCATION

                       # Provides the path to the library you want to import.
                       ${LINK_DIR}/libswresample-2.so )


add_library( avcodec-lib
             SHARED
             IMPORTED )

set_target_properties( # Specifies the target library.
                       avcodec-lib

                       # Specifies the parameter you want to define.
                       PROPERTIES IMPORTED_LOCATION

                       # Provides the path to the library you want to import.
                       ${LINK_DIR}/libavcodec-57.so )

add_library( avformat-lib
             SHARED
             IMPORTED )

set_target_properties( # Specifies the target library.
                       avformat-lib

                       # Specifies the parameter you want to define.
                       PROPERTIES IMPORTED_LOCATION

                       # Provides the path to the library you want to import.
                       ${LINK_DIR}/libavformat-57.so )

add_library( avfilter-lib
             SHARED
             IMPORTED )

set_target_properties( # Specifies the target library.
                       avfilter-lib

                       # Specifies the parameter you want to define.
                       PROPERTIES IMPORTED_LOCATION

                       # Provides the path to the library you want to import.
                       ${LINK_DIR}/libavfilter-6.so )

find_library( # Sets the name of the path variable.
              log-lib

              # Specifies the name of the NDK library that
              # you want CMake to locate.
              log )

# Specifies libraries CMake should link to your target library. You
# can link multiple libraries, such as libraries you define in this
# build script, prebuilt third-party libraries, or system libraries.

target_link_libraries( # Specifies the target library.
                       h265decoder

                       # Links the target library to the log library
                       # included in the NDK.
                       ${log-lib}
                       x265-lib
                       avutil-lib
                       swscale-lib
                       swresample-lib
                       avcodec-lib
                       avformat-lib
                       avfilter-lib)