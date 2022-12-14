cmake_minimum_required(VERSION 3.16)
project(Marmot)

set(CMAKE_CXX_STANDARD 20)

find_package(LLVM REQUIRED CONFIG)

message(STATUS "Found LLVM ${LLVM_PACKAGE_VERSION}")
message(STATUS "Using LLVMConfig.cmake in: ${LLVM_DIR}")
message(STATUS "LLVM include directory: ${LLVM_INCLUDE_DIRS}")

include_directories(${LLVM_INCLUDE_DIRS})
add_definitions(${LLVM_DEFINITIONS})

aux_source_directory(./src DIR_SCRS)
add_executable(marmotc ${DIR_SCRS})

llvm_map_components_to_libnames(llvm_libs support core irreader executionengine interpreter)

message(STATUS "Using llvm libs: ${llvm_libs}")

target_link_libraries(marmotc ${llvm_libs})