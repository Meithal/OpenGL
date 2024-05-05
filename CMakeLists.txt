cmake_minimum_required(VERSION 3.14)

add_compile_definitions(GL_SILENCE_DEPRECATION)

project(quats)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}")

find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)
#find_package(SOIL REQUIRED)

add_library(
    soil_lib STATIC
    tp/SOIL/src/image_helper.c
    tp/SOIL/src/stb_image_aug.c
    tp/SOIL/src/image_DXT.c
    tp/SOIL/src/SOIL.c
)
target_include_directories(soil_lib PUBLIC tp/SOIL/include)

add_executable(quat
    main.cpp
)

target_link_libraries(quat OpenGL::GL GLUT::GLUT)
target_include_directories(quat PUBLIC include)

add_executable(soil
    soil.cpp
)

target_link_libraries(soil soil_lib)
target_link_libraries(soil_lib OpenGL::GL GLUT::GLUT)

add_executable(cours_soil
    exemples_SOIL/main.cpp
    exemples_SOIL/Camera.cpp
    exemples_SOIL/Map.cpp
    exemples_SOIL/Block.cpp
)
target_link_libraries(cours_soil soil_lib)
target_include_directories(cours_soil PRIVATE exemples_SOIL/include)

target_link_libraries(soil soil_lib)

