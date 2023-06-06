cmake_minimum_required(VERSION 3.21)
project(EX_04 C)

set(CMAKE_C_STANDARD 99)

add_executable(EX_04 main.c Hist.c TestHist.c TestHist.h Set.c LinkedList.c)
