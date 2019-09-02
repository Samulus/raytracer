cmake_minimum_required(VERSION 3.9)
set(CMAKE_VERBOSE_MAKEFILE ON)
set (CMAKE_CXX_STANDARD 17)
project(raytracer VERSION 0.0.0
        DESCRIPTION "Simple raytracer"
        LANGUAGES CXX)

find_package(glfw3 CONFIG REQUIRED)
find_package(GLEW REQUIRED)
find_package(OpenGL REQUIRED)
find_package(glm CONFIG REQUIRED)
find_package(tinyobjloader CONFIG REQUIRED)
find_package(spdlog CONFIG REQUIRED)

add_executable(raytracer_release
        src/main.cc
        src/window.cpp
        src/window.h
        src/shader.cpp
        src/shader.h
        src/world.cpp
        src/world.h
        src/rgbimage.cpp
        src/rgbimage.h
        src/raytracer.cpp
        src/raytracer.h
        src/lerp.cpp
        src/lerp.h
        src/sphere.h
        src/ray.cpp
        src/ray.h
        src/spaceconversion.cpp
        src/spaceconversion.h
        src/geometry.h
        src/sphere.cpp
        src/sphere.h
        src/geometry.cpp
        src/plane.cpp
        src/plane.h
        src/light.h
        src/lighttransport.h
        src/lighttransport.cpp
        src/facingratiolighttransport.cpp
        src/facingratiolighttransport.h
        src/diffuselighting.cpp
        src/diffuselighting.h
        src/glfwmanager.cpp
        src/glfwmanager.h
        src/pi.h
        src/albedo.h
        src/color.h
        src/universe.h
        src/scenes.h
        src/material.h
        src/raycollision.h
        src/wavefrontobj.h
        src/meshinstance.cpp src/meshinstance.h)

target_link_libraries(raytracer_release PRIVATE glfw)
target_link_libraries(raytracer_release PRIVATE GLEW::GLEW)
target_link_libraries(raytracer_release PRIVATE ${OPENGL_LIBRARIES})
target_link_libraries(raytracer_release PRIVATE glm)
target_link_libraries(raytracer_release PRIVATE spdlog::spdlog)
target_link_libraries(raytracer_release PRIVATE tinyobjloader::tinyobjloader)


# Tests
find_package(doctest CONFIG REQUIRED)
add_executable(raytracer_test
        # Test Cases
        test/test.cpp
        test/testrgbimage.cpp
        test/testspaceconversion.cpp
        test/testsphere.cpp
        test/testlighttransport.cpp
        test/testdiffuselighting.cpp
        test/testplane.cpp
        test/testraytracer.cpp
        test/testwavefrontobj.cpp
        # Main Program Code
        src/geometry.cpp
        src/geometry.h
        src/rgbimage.cpp
        src/rgbimage.h
        src/spaceconversion.cpp
        src/spaceconversion.h
        src/ray.cpp
        src/ray.h
        src/plane.cpp
        src/plane.h
        src/sphere.h
        src/sphere.cpp
        src/diffuselighting.cpp
        src/diffuselighting.h
        src/lighttransport.cpp
        src/lighttransport.h
        src/world.cpp
        src/world.h 
        src/raytracer.cpp
        src/raytracer.h
        src/lerp.cpp
        src/lerp.h
        src/material.h
        src/wavefrontobj.h
        src/meshinstance.cpp
        src/meshinstance.h)

target_include_directories(raytracer_test PRIVATE src)
target_link_libraries(raytracer_test PRIVATE doctest::doctest)
target_link_libraries(raytracer_test PRIVATE glfw)
target_link_libraries(raytracer_test PRIVATE GLEW::GLEW)
target_link_libraries(raytracer_test PRIVATE glm)
target_link_libraries(raytracer_test PRIVATE spdlog::spdlog)
target_link_libraries(raytracer_test PRIVATE fmt::fmt fmt::fmt-header-only)
target_link_libraries(raytracer_test PRIVATE tinyobjloader::tinyobjloader)
