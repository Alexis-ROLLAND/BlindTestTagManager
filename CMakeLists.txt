cmake_minimum_required(VERSION 3.12)		# never set less 3.12 min version
project(bttManager)

# Build type is debug by default
# call cmake .. -DCMAKE_BUILD_TYPE=Release to change to relase
# call cmake .. -DCMAKE_BUILD_TYPE=Debug to revert to debug
if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Debug)
endif()

set(CMAKE_CXX_STANDARD 23)  # We're using C++23 standard :)

set(CMAKE_CXX_FLAGS "-Wall -Wextra -Wpedantic")
set(CMAKE_CXX_FLAGS_DEBUG "-Og -g")
set(CMAKE_CXX_FLAGS_RELEASE "-O3")

find_package(ZLIB)
find_package(TagLib 2.0.0 REQUIRED)

message(STATUS "Build type: ${CMAKE_BUILD_TYPE}")

include_directories(include)

# Choose wich executable will be build : cmake --build . -t  

# main executable : cmake --build . -t bttManager
add_executable(bttManager src/bttManager_main.cpp
                          src/lib_bttManager.cpp
                          src/bttParser.cpp
                          src/tagManager.cpp)
target_link_libraries(bttManager TagLib::tag)

# test app for tagManager class
# cmake --build . -t test_tagManager
add_executable(test_tagManager  src/test_tagManager.cpp
                                src/tagManager.cpp) 
target_link_libraries(test_tagManager TagLib::tag)

# main executable test : cmake --build . -t test_bttManager
add_executable(test_bttManager  src/test_bttManager.cpp
                                src/bttParser.cpp
                                src/tagManager.cpp)
target_link_libraries(test_bttManager TagLib::tag)

# Simple tag checking app
add_executable(checkTags  src/checkTags.cpp
                          src/tagManager.cpp) 
target_link_libraries(checkTags TagLib::tag)  

# Simple tag preparation (init) app
add_executable(prepareTags  src/prepareTags.cpp
                            src/tagManager.cpp) 
target_link_libraries(prepareTags TagLib::tag)  

# Very simple app listing the tags & values
# cmake --build . -t dumpTags
add_executable(dumpTags src/dumpTags.cpp
                        src/tagManager.cpp) 
target_link_libraries(dumpTags TagLib::tag)      



