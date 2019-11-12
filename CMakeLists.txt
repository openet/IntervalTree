cmake_minimum_required(VERSION 3.11)

project(interval_tree)

set(Source_Dir ${PROJECT_SOURCE_DIR}/src)

add_library(interval_trie ${Source_Dir}/IntervalTree.cc)

add_subdirectory(gtest)
