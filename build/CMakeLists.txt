cmake_minimum_required(VERSION 3.10)
project(Vesper)

find_package(LLVM REQUIRED CONFIG)
message(STATUS "Found LLVM ${LLVM_PACKAGE_VERSION}")
message(STATUS "LLVM dir: ${LLVM_DIR}")

include_directories(${LLVM_INCLUDE_DIRS} include)
add_definitions(${LLVM_DEFINITIONS})

file(GLOB SOURCES "src/*.cpp")

add_executable(vesper ${SOURCES})

llvm_map_components_to_libnames(llvm_libs support core irreader native)
target_link_libraries(vesper ${llvm_libs})

install(TARGETS vesper DESTINATION bin)
