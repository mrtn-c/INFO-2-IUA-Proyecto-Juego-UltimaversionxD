cmake_minimum_required(VERSION 3.12.0)
project(proyectoSnake)

set(CMAKE_CXX_STANDARD 17)
find_package(SFML 2.5 COMPONENTS system window graphics)
add_executable(proyectoSnake main.cpp vibora.cpp vibora.h comida.cpp comida.h vida.cpp vida.h Nodo.h score.cpp score.h textos.cpp textos.h menu.cpp menu.h)
target_link_libraries(proyectoSnake sfml-system sfml-graphics sfml-window )

file(GLOB IMAGENES "IMAGENES/*")
file(COPY ${IMAGENES} DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/IMAGENES)
file(GLOB TEXTOS "textos/*")
file(COPY ${TEXTOS} DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/textos)