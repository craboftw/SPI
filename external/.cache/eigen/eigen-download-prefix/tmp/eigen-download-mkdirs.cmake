# Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
# file Copyright.txt or https://cmake.org/licensing for details.

cmake_minimum_required(VERSION 3.5)

file(MAKE_DIRECTORY
  "C:/Users/flopezguerrero/Scattered_Points_Interpolation-master/external/eigen"
  "C:/Users/flopezguerrero/Scattered_Points_Interpolation-master/cmake-build-debug/eigen-build"
  "C:/Users/flopezguerrero/Scattered_Points_Interpolation-master/external/.cache/eigen/eigen-download-prefix"
  "C:/Users/flopezguerrero/Scattered_Points_Interpolation-master/external/.cache/eigen/eigen-download-prefix/tmp"
  "C:/Users/flopezguerrero/Scattered_Points_Interpolation-master/external/.cache/eigen/eigen-download-prefix/src/eigen-download-stamp"
  "C:/Users/flopezguerrero/Scattered_Points_Interpolation-master/external/.cache/eigen/eigen-download-prefix/src"
  "C:/Users/flopezguerrero/Scattered_Points_Interpolation-master/external/.cache/eigen/eigen-download-prefix/src/eigen-download-stamp"
)

set(configSubDirs )
foreach(subDir IN LISTS configSubDirs)
    file(MAKE_DIRECTORY "C:/Users/flopezguerrero/Scattered_Points_Interpolation-master/external/.cache/eigen/eigen-download-prefix/src/eigen-download-stamp/${subDir}")
endforeach()
if(cfgdir)
  file(MAKE_DIRECTORY "C:/Users/flopezguerrero/Scattered_Points_Interpolation-master/external/.cache/eigen/eigen-download-prefix/src/eigen-download-stamp${cfgdir}") # cfgdir has leading slash
endif()
