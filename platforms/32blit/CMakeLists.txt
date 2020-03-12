cmake_minimum_required(VERSION 3.9)
project(blit_wasm)

set(target ${CMAKE_PROJECT_NAME})

set(32BLIT_PATH "../" CACHE PATH "Path to 32blit.cmake")
include(${32BLIT_PATH}/32blit.cmake)

add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/../../source ${CMAKE_BINARY_DIR}/m3)

blit_executable(${target} main.cpp)
blit_assets_yaml(${target} assets.yml)

add_subdirectory(wasm3_cpp)
target_link_libraries(${target} m3 wasm3_cpp)

target_compile_options(m3 PUBLIC -Dd_m3LogOutput=0 -Wno-error=double-promotion)
