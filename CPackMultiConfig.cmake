# https://cmake.org/cmake/help/latest/guide/tutorial/Packaging%20Debug%20and%20Release.html
include("cmake-build-release/CPackConfig.cmake")

set(
        CPACK_INSTALL_CMAKE_PROJECTS
        "cmake-build-debug;cppbasics;ALL;/"
        "cmake-build-release;cppbasics;ALL;/"
)