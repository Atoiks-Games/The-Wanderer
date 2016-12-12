cmake_minimum_required(VERSION 2.8.4)
project(THE_WANDERER)

set(CMAKE_CXX_FLAGS "-std=c++11 -Wall -O3")
set(CMAKE_EXE_LINKER_FLAGS "-Os -s -fdata-sections -ffunction-sections -Wl,--gc-sections,--strip-all")

include_directories(${THE_WANDERER_SOURCE_DIR}/header)
add_subdirectory(src/utils)
add_subdirectory(src/wanderer)

add_executable(the_wanderer main.cxx)
target_link_libraries(the_wanderer utils wanderer) 
