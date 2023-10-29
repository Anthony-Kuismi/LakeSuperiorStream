cmake_minimum_required(VERSION 3.22)
project(LakeSuperiorStream)

set(CMAKE_CXX_STANDARD 17)

if ((CMAKE_CXX_COMPILER_ID MATCHES "Clang") OR ((CMAKE_CXX_COMPILER_ID STREQUAL "GNU") AND NOT (MINGW)))
    # using GCC or CLANG

    # this check also watches to see if the GNU compiler is MinGW-based (sanitizers aren't working great on
    # that at the moment so will not enable sanitizer if that's the case if the compiler is a MinGW GNU compiler)

    # Both, GCC and Clang support the same option set
    # We first turn on Warnings
    # --> https://gcc.gnu.org/onlinedocs/gcc/Warning-Options.html
    #
    # -Wall stands for All Warnings
    # -Wextra pushes that a bit further
    # -pedantic sets the compiler to use strict ISO C++
    # -Werror treats all warnings as errors so you have to fix them
    #    this last option has been commented out to make things a little easier
    add_compile_options(-Wall -Wextra -pedantic) # -Werror)

    # Sanitizer options
    # The following will turn on Debugging (-g flag) and the Address Sanitizer
    # which is turned on with the -fsanitize=address option to the compiler.
    add_compile_options(-g -fsanitize=address,undefined)

    # When we turn on the sanitizer, you also need to instruct the linker that it
    # will be used which happens with the following link option command.
    add_link_options(-g -fsanitize=address,undefined)

elseif (CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
    # using Visual Studio C++
    # MSVC uses a different warning flags
    add_compile_options(/W4)
    add_compile_options(/fsanitize=address /MTd)

endif()

# gui stuff
find_package(OpenGL REQUIRED)
link_libraries (${OPENGL_LIBRARY})

# To be able to include the GLFW header from your code, you need to tell the compiler where to find it.
add_subdirectory(${PROJECT_SOURCE_DIR}/lib/glfw-master)

# Once GLFW has been added to the project, the GLFW_LIBRARIES cache variable contains all link-time dependencies of GLFW
# as it is currently configured. To link against GLFW, link against them and the glfw target.
include_directories(${PROJECT_SOURCE_DIR}/lib/glfw-master/include)
message(STATUS "${GLFW_LIBRARIES}")
set(GLFW_STATIC_LIBRARIES "${GLFW_LIBRARIES}")

add_subdirectory(lib/Catch2-devel)

add_library(src
        CSVReader.cpp
        CSVReader.h
        DataField.h
        IReader.h
        ISample.h
        ResearcherSample.cpp
        ResearcherSample.h
        SampleType.h
        SensorSample.cpp
        SensorSample.h
        Time.cpp
        Time.h
        Searcher.h
        Searcher.cpp
        Stream.cpp
        Stream.h
        lib/imgui/imgui.cpp
        lib/imgui/imgui.h
        lib/imgui/imconfig.h
        lib/imgui/imgui_demo.cpp
        lib/imgui/imgui_draw.cpp
        lib/imgui/imgui_tables.cpp
        lib/imgui/imgui_widgets.cpp
        lib/imgui/imgui_impl_glfw.cpp
        lib/imgui/imgui_impl_glfw.h
        lib/imgui/imgui_impl_opengl3.cpp
        lib/imgui/imgui_impl_opengl3.h

        StreamGUI.cpp
        StreamGUI.h
)

add_executable(SearcherTest tests/searcher_test.cpp)
target_link_libraries(SearcherTest PRIVATE Catch2::Catch2WithMain src)

add_executable(sample_test tests/sample_test.cpp)
target_link_libraries(sample_test PRIVATE Catch2::Catch2WithMain src)

add_executable(reader_test tests/reader_test.cpp)
target_link_libraries(reader_test PRIVATE Catch2::Catch2WithMain src)

add_executable(Time_Test tests/Time_Test.cpp)
target_link_libraries(Time_Test PRIVATE Catch2::Catch2WithMain src)

add_executable(stream_test tests/stream_test.cpp)
target_link_libraries(stream_test PRIVATE Catch2::Catch2WithMain src)

add_executable(LakeSuperiorStream main.cpp)
target_link_libraries (LakeSuperiorStream ${GLEW_LIBRARIES} src)
target_link_libraries (LakeSuperiorStream glfw ${GLFW_STATIC_LIBRARIES})

add_custom_command(TARGET LakeSuperiorStream POST_BUILD
                   COMMAND ${CMAKE_COMMAND} -E copy
                   ${CMAKE_CURRENT_SOURCE_DIR}/fonts/JetBrainsMono-Regular.ttf
                   ${CMAKE_CURRENT_BINARY_DIR}/JetBrainsMono-Regular.ttf)

