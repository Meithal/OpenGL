cmake_minimum_required(VERSION 3.14)
set(CMAKE_CXX_STANDARD 14)

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
target_link_libraries(soil_lib OpenGL::GL GLUT::GLUT)

add_executable(quat
    main.cpp
)

target_link_libraries(quat OpenGL::GL GLUT::GLUT)
target_include_directories(quat PUBLIC include)

add_executable(soil
    soil.cpp
)

target_link_libraries(soil soil_lib)

add_executable(cours_soil
    exemples_SOIL/main.cpp
    exemples_SOIL/Camera.cpp
    exemples_SOIL/Map.cpp
    exemples_SOIL/Block.cpp
    exemples_SOIL/include/Block.hpp
    exemples_SOIL/include/Camera.hpp
    exemples_SOIL/include/Map.hpp
    exemples_SOIL/include/Skybox.hpp
)
target_link_libraries(cours_soil soil_lib)
target_include_directories(cours_soil PRIVATE exemples_SOIL/include)

add_custom_target(copy-runtime-files ALL
    COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_SOURCE_DIR}/exemples_SOIL/img ${CMAKE_BINARY_DIR}/img
    DEPENDS cours_soil)

add_executable(tests_quats
    exemples_SOIL/tests.cpp
    exemples_SOIL/include/Quaternion.hpp
    exemples_SOIL/Quaternion.cpp
)
target_include_directories(tests_quats PRIVATE exemples_SOIL/include)