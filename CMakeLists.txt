cmake_minimum_required(VERSION 3.0)

set(CMAKE_CXX_STANDARD 17)

project("Archiver")

add_library(archiver_lib STATIC archiver/archiver.cpp)
add_library(trie_vertex STATIC trie_vertex/trie_vertex.cpp)
add_library(reader STATIC reader/reader.cpp)
add_library(writer STATIC writer/writer.cpp)

add_executable(archiver main.cpp)

target_link_libraries(archiver archiver_lib trie_vertex reader writer)
