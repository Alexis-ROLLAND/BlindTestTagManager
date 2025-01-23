cmake_minimum_required(VERSION 3.15)		# never set less 3.12 min version
project(bttManager)

set(CMAKE_CXX_STANDARD 23)  # We're using C++23 standard :)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)  # Désactiver les extensions spécifiques au compilateur

# Build type is debug by default
# call cmake .. -DCMAKE_BUILD_TYPE=Release to change to relase
# call cmake .. -DCMAKE_BUILD_TYPE=Debug to revert to debug
if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Debug CACHE STRING "Build type (Debug, Release, etc.)" FORCE)
endif()

add_compile_options(-Wshadow -Wnon-virtual-dtor -Wold-style-cast)

# Définir des options de compilation pour tous les compilateurs
add_compile_options(-Wall -Wextra -Wpedantic)

# Ajout de flags spécifiques pour GCC/Clang
if(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
  set(SANITIZE_FLAGS "-fsanitize=address,undefined") # Choisissez vos sanitizers ici
  if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    add_compile_options(${SANITIZE_FLAGS} -fno-omit-frame-pointer -g)
    add_link_options(${SANITIZE_FLAGS})
  endif()
endif()

set(CMAKE_CXX_FLAGS_DEBUG "-Og -g")             # Debug : Optimisation légère pour le débogage
set(CMAKE_CXX_FLAGS_RELEASE "-O3 -DNDEBUG")     # Release : Optimisation maximale sans symboles de debug

message(STATUS "Build type: ${CMAKE_BUILD_TYPE}")

find_package(ZLIB)
find_package(TagLib 2.0.0 REQUIRED)

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

# main executable test : cmake --build . -t test_bttManager     /!\ Not Working /!\ -> Link error
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



