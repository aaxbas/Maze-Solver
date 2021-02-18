cmake_minimum_required(VERSION 3.7)

project(MAZESOLVER)

include_directories(src src/solvers)
file(GLOB_RECURSE SRC_FILES
  src/*.cpp
  src/*.hpp
)

include_directories(include include/solvers)
file(GLOB_RECURSE INC_FILES
  include/*.hpp
  include/solvers/*.hpp
)

file(GLOB_RECURSE SOLV_FILES
  src/solvers/*.cpp
)

INCLUDE(FindPkgConfig)
PKG_SEARCH_MODULE(SDL2 REQUIRED sdl2)

#INCLUDE_DIRECTORIES(${SDL2_INCLUDE_DIRS})
#TARGET_LINK_LIBRARIES(${PROJECT_NAME} ${SDL2_LIBRARIES})

add_executable(MAZESOLVER src/main.cpp src/Map.cpp src/Screen.cpp ${SOLV_FILES} ${INC_FILES} ${SDL2_INCLUDE_DIRS})
target_link_libraries(${PROJECT_NAME} ${INC_FILES} ${SDL2_LIBRARIES}) 

add_executable(MAZEBUILDER src/mapBuilder.cpp src/Map.cpp src/Screen.cpp ${INC_FILES}  ${SDL2_INCLUDE_DIRS})
target_link_libraries(MAZEBUILDER ${INC_FILES} ${SDL2_LIBRARIES})

