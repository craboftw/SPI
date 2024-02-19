# Distributed under the OSI-approved MIT License.  See accompanying
# file LICENSE or https://github.com/Crascit/DownloadProject for details.

cmake_minimum_required(VERSION 2.8.2)

project(eigen-download NONE)

include(ExternalProject)
ExternalProject_Add(eigen-download
                    GIT_CONFIG advice.detachedHead=false;GIT_REPOSITORY;https://gitlab.com/libeigen/eigen.git;GIT_TAG;3.3.7
                    SOURCE_DIR          "C:/Users/flopezguerrero/Scattered_Points_Interpolation-master/external/eigen"
                    BINARY_DIR          "C:/Users/flopezguerrero/Scattered_Points_Interpolation-master/cmake-build-debug/eigen-build"
                    CONFIGURE_COMMAND   ""
                    BUILD_COMMAND       ""
                    INSTALL_COMMAND     ""
                    TEST_COMMAND        ""
)
