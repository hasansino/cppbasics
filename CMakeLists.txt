cmake_minimum_required(VERSION 3.22)

project(cppbasics VERSION 1.0)

set(CMAKE_DEBUG_POSTFIX d)

# specify the C++ standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# compiler and linked flags
set(CMAKE_CXX_STANDARD_LIBRARIES "${CMAKE_CXX_STANDARD_LIBRARIES} -static-libgcc -static-libstdc++ -lwsock32 -lws2_32")
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -Wl,-Bstatic,--whole-archive -lwinpthread -Wl,--no-whole-archive")

# define options
option(USE_CUSTOM_MATH "Use custom math library" ON)
# if present and true, this will cause all libraries
# to be built shared unless the library was explicitly
# added as a static library
option(BUILD_SHARED_LIBS "Build using shared libraries" ON)

# add internal libraries
if (USE_CUSTOM_MATH)
    add_subdirectory(lib/math)
    list(APPEND EXTRA_LIBS math)
endif ()

add_subdirectory(lib/echo)
list(APPEND EXTRA_LIBS echo)

# add external libraries
set(Boost_INCLUDE_DIR C:/lib/boost/1.84.0)
set(Boost_LIBRARY_DIR C:/lib/boost/1.84.0/libs)
find_package(Boost COMPONENTS REQUIRED)
include_directories(${Boost_INCLUDE_DIR})

# include pre-processed header
configure_file(cmake.hpp.in include/cmake.hpp)
include_directories(${PROJECT_BINARY_DIR}/include)

# cppbasics target

add_executable(
        cppbasics
        main.cpp
        myclass.hpp myclass.cpp mystruct.hpp mystruct.cpp functions.hpp functions.cpp
        std/io.cpp std/std.hpp
)

# target linking and includes
target_link_libraries(
        cppbasics
        PUBLIC ${EXTRA_LIBS}
)
target_include_directories(
        cppbasics
        PUBLIC "${PROJECT_BINARY_DIR}/include"
)
set_target_properties(
        cppbasics PROPERTIES
        DEBUG_POSTFIX ${CMAKE_DEBUG_POSTFIX}
)

# cppbasics testing
include(CTest)
add_test(NAME Runs COMMAND cppbasics)
add_test(NAME Usage COMMAND cppbasics)
set_tests_properties(Usage PROPERTIES PASS_REGULAR_EXPRESSION ".*C\\+\\+.*")

function(do_test target arg result)
    add_test(NAME Comp${arg} COMMAND ${target} ${arg})
    set_tests_properties(Comp${arg} PROPERTIES PASS_REGULAR_EXPRESSION ${result})
endfunction()

do_test(cppbasics 0 ".*C\\+\\+.*")
do_test(cppbasics 1 ".*C\\+\\+.*")
do_test(cppbasics 2 ".*C\\+\\+.*")
do_test(cppbasics 3 ".*C\\+\\+.*")
do_test(cppbasics 4 ".*C\\+\\+.*")
do_test(cppbasics 5 ".*C\\+\\+.*")
do_test(cppbasics 6 ".*C\\+\\+.*")

# installation directives
install(TARGETS cppbasics DESTINATION bin)
install(FILES "${PROJECT_BINARY_DIR}/include/cmake.hpp" DESTINATION include)

# packaging
include(InstallRequiredSystemLibraries)
set(CPACK_RESOURCE_FILE_LICENSE "${CMAKE_CURRENT_SOURCE_DIR}/LICENCE")
set(CPACK_PACKAGE_VERSION_MAJOR "${cppbasics_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${cppbasics_VERSION_MINOR}")
set(CPACK_SOURCE_GENERATOR "TGZ")
include(CPack)