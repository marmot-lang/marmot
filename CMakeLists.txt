cmake_minimum_required(VERSION 3.16)
project(Marmot)

set(CMAKE_CXX_STANDARD 17)
aux_source_directory(./src DIR_SCRS)
add_executable(marmotc ${DIR_SCRS})