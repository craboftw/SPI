# Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
# file Copyright.txt or https://cmake.org/licensing for details.

cmake_minimum_required(VERSION 3.5)

file(MAKE_DIRECTORY
  "C:/Users/flopezguerrero/Scattered_Points_Interpolation-master/external/libigl"
  "C:/Users/flopezguerrero/Scattered_Points_Interpolation-master/cmake-build-debug/libigl-build"
  "C:/Users/flopezguerrero/Scattered_Points_Interpolation-master/external/.cache/libigl/libigl-download-prefix"
  "C:/Users/flopezguerrero/Scattered_Points_Interpolation-master/external/.cache/libigl/libigl-download-prefix/tmp"
  "C:/Users/flopezguerrero/Scattered_Points_Interpolation-master/external/.cache/libigl/libigl-download-prefix/src/libigl-download-stamp"
  "C:/Users/flopezguerrero/Scattered_Points_Interpolation-master/external/.cache/libigl/libigl-download-prefix/src"
  "C:/Users/flopezguerrero/Scattered_Points_Interpolation-master/external/.cache/libigl/libigl-download-prefix/src/libigl-download-stamp"
)

set(configSubDirs )
foreach(subDir IN LISTS configSubDirs)
    file(MAKE_DIRECTORY "C:/Users/flopezguerrero/Scattered_Points_Interpolation-master/external/.cache/libigl/libigl-download-prefix/src/libigl-download-stamp/${subDir}")
endforeach()
if(cfgdir)
  file(MAKE_DIRECTORY "C:/Users/flopezguerrero/Scattered_Points_Interpolation-master/external/.cache/libigl/libigl-download-prefix/src/libigl-download-stamp${cfgdir}") # cfgdir has leading slash
endif()
