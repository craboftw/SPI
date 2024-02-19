# Distributed under the OSI-approved MIT License.  See accompanying
# file LICENSE or https://github.com/Crascit/DownloadProject for details.

cmake_minimum_required(VERSION 2.8.2)

project(libigl-download NONE)

include(ExternalProject)
ExternalProject_Add(libigl-download
                    GIT_CONFIG advice.detachedHead=false;GIT_REPOSITORY;https://github.com/libigl/libigl.git;GIT_TAG;aea868bd1fc64f71afecd2c51e51507a99d8e3e5
                    SOURCE_DIR          "/mnt/c/Users/flopezguerrero/Scattered_Points_Interpolation-master/external/libigl"
                    BINARY_DIR          "/mnt/c/Users/flopezguerrero/Scattered_Points_Interpolation-master/buildwsl/libigl-build"
                    CONFIGURE_COMMAND   ""
                    BUILD_COMMAND       ""
                    INSTALL_COMMAND     ""
                    TEST_COMMAND        ""
)
