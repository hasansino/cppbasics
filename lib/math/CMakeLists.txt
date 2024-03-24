add_library(
        math
        STATIC
        sqrt.cpp
        "${CMAKE_CURRENT_BINARY_DIR}/sqrt_table.hpp"
)

set_target_properties(
        math
        PROPERTIES
        VERSION "1.0.0"
        SOVERSION "1"
        RUNTIME_OUTPUT_DIRECTORY "${PROJECT_BINARY_DIR}/lib/math"
        LIBRARY_OUTPUT_DIRECTORY "${PROJECT_BINARY_DIR}/lib/math"
        ARCHIVE_OUTPUT_DIRECTORY "${PROJECT_BINARY_DIR}/lib/math"
)

target_include_directories(
        math
        INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}   # anybody linking to us sees math.hpp
        PRIVATE ${CMAKE_CURRENT_BINARY_DIR}     # only library includes sqrt_table.hpp
)

# check if ldexp/frexp functions exist without linking math.h
include(CheckSymbolExists)
check_symbol_exists(ldexp "math.h" HAVE_LDEXP)
check_symbol_exists(frexp "math.h" HAVE_FREXP)

# on some platforms, we will need to link to the m library
# if log and exp are not initially found, require the m library and try again
if (NOT (HAVE_LDEXP AND HAVE_FREXP))
    message(WARNING "ldexp/frexp capability not found")
    # remove HAVE_LDEXP and HAVE_FREXP from the cache
    unset(HAVE_LDEXP CACHE)
    unset(HAVE_FREXP CACHE)
    # a list of libraries to add to the link command
    set(CMAKE_REQUIRED_LIBRARIES "m")
    # perform check again
    check_symbol_exists(ldexp "math.h" HAVE_LDEXP)
    check_symbol_exists(frexp "math.h" HAVE_FREXP)
    message(STATUS "Trying again after linking math.h")
    if (HAVE_LDEXP AND HAVE_FREXP)
        target_link_libraries(math PRIVATE m)
    else ()
        message(WARNING "System does not have ldexp/frexp capability")
    endif ()
endif ()

# pass HAVE_LDEXP/HAVE_FREXP to compiler as defines
if (HAVE_LDEXP AND HAVE_FREXP)
    target_compile_definitions(math PRIVATE HAVE_LDEXP HAVE_FREXP)
endif ()

# table generation
add_executable(sqrt_table sqrt_table.cpp)
add_custom_command(
        COMMAND sqrt_table ${CMAKE_CURRENT_BINARY_DIR}/sqrt_table.hpp 1000
        OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/sqrt_table.hpp
        DEPENDS sqrt_table # from add_executable
)

# installation directives
install(TARGETS math DESTINATION lib)
install(FILES math.hpp DESTINATION include)