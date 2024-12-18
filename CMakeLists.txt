cmake_minimum_required(VERSION 3.25 FATAL_ERROR)

project(checksum VERSION 0.0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED 20)
set(CMAKE_CXX_EXTENSIONS ON)
set(BOOST_INCLUDE_LIBRARIES system filesystem uuid algorithm program_options)

if(MSVS)
    add_compile_options(
        $<$<CONFIG:>:/MT>
        $<$<CONFIG:Debug>:/MTd>
        $<$<CONFIG:Release>:/MT>)
else()
    set(cmake_find_library_suffixes ".a")
    set(build_shared_libs off)
    set(cmake_exe_linker_flags "-static")
endif()

file(GLOB APPLICATION_SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/application/src/*.cpp)

include(cmake/UpdateGitSubmodules.cmake)

update_git_submodule(${CMAKE_CURRENT_SOURCE_DIR}/libs/boost)

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/libs/boost EXCLUDE_FROM_ALL)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/application/inc)

add_executable(${PROJECT_NAME} ${APPLICATION_SOURCES})

target_link_libraries(${PROJECT_NAME} PRIVATE
    Boost::algorithm
    Boost::filesystem
    Boost::program_options
    Boost::system
    Boost::uuid)
