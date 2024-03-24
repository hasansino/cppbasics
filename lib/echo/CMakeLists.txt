add_library(
        echo
        SHARED
        echo.cpp
)

set_target_properties(
        echo PROPERTIES
        VERSION "1.0.0"
        SOVERSION "1"
        RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}
        LIBRARY_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}
        ARCHIVE_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}
)

target_include_directories(
        echo
        INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}   # anybody linking to us sees echo.hpp
)

# define the symbol stating we are using the
# declspec(dllexport) when building on windows
target_compile_definitions(echo PRIVATE "EXPORTING_ECHO")

# installation directives
install(TARGETS echo DESTINATION lib)
install(FILES echo.hpp DESTINATION include)