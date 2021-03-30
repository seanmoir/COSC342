cmake_minimum_required(VERSION 3.1)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

project(Shapes)
add_executable(Shapes
  shapesMain.cpp
  Shape.h
  Shape.cpp
  Rectangle.h
  Rectangle.cpp
  Image.h
  Image.cpp
  Pixel.h
  stb_image.h
  stb_image_write.h
)