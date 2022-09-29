cmake_minimum_required(VERSION 3.16)
project(Marmot)
aux_source_directory(./src DIR_SCRS)
add_executable(marmotc ${DIR_SCRS})