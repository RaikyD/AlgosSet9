cmake_minimum_required(VERSION 3.27)
project(Set9)

set(CMAKE_CXX_STANDARD 23)

add_executable(Set9 main.cpp
        StringGenerator.cpp
        StringSortTester.cpp
        MsdRadixSort.cpp
        MsdRadixQuickSort.cpp
        StringUtils.h
        MsdRadixSort.h
        StringGenerator.h
        StringSortTester.h
        StringMergeSort.h
        StringQuickSort.h
        MsdRadixQuickSort.h
        StringMergeSort.cpp
        StringQuickSort.cpp)
