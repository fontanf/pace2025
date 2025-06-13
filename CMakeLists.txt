cmake_minimum_required(VERSION 3.28.0)

project(Pace2025 LANGUAGES CXX)

# Avoid FetchContent warning.
cmake_policy(SET CMP0135 NEW)

# Require C++14.
set(CMAKE_CXX_STANDARD 14)

# Enable output of compile commands during generation.
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Set MSVC_RUNTIME_LIBRARY.
set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")

# Enable FetchContent.
include(FetchContent)

# Fetch fontanf/setcoveringsolver.
FetchContent_Declare(
    setcoveringsolver
    GIT_REPOSITORY https://github.com/fontanf/setcoveringsolver.git
    GIT_TAG bd3fbbfb2d7afca41a14b446d94974851ee28d96
    #SOURCE_DIR "${PROJECT_SOURCE_DIR}/../setcoveringsolver/"
    EXCLUDE_FROM_ALL)
FetchContent_MakeAvailable(setcoveringsolver)

add_executable(Pace2025_pace2025_hs_heuristic_main)
target_sources(Pace2025_pace2025_hs_heuristic_main PRIVATE
    pace2025_hs_heuristic_main.cpp)
target_link_libraries(Pace2025_pace2025_hs_heuristic_main PUBLIC
    SetCoveringSolver_local_search_row_weighting
    SetCoveringSolver_large_neighborhood_search
    SetCoveringSolver_trivial_bound
    Boost::program_options)
set_target_properties(Pace2025_pace2025_hs_heuristic_main PROPERTIES OUTPUT_NAME "pace2025_hs_heuristic")
install(TARGETS Pace2025_pace2025_hs_heuristic_main)

add_executable(Pace2025_pace2025_ds_heuristic_main)
target_sources(Pace2025_pace2025_ds_heuristic_main PRIVATE
    pace2025_ds_heuristic_main.cpp)
target_link_libraries(Pace2025_pace2025_ds_heuristic_main PUBLIC
    SetCoveringSolver_local_search_row_weighting
    SetCoveringSolver_large_neighborhood_search
    SetCoveringSolver_trivial_bound
    Boost::program_options)
set_target_properties(Pace2025_pace2025_ds_heuristic_main PROPERTIES OUTPUT_NAME "pace2025_ds_heuristic")
install(TARGETS Pace2025_pace2025_ds_heuristic_main)
