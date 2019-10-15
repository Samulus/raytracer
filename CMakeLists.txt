cmake_minimum_required(VERSION 3.9)
project(raytracer)
set(CMAKE_VERBOSE_MAKEFILE ON)
set (CMAKE_CXX_STANDARD 17)

# Seek out the highest versions
set(CMAKE_FIND_PACKAGE_SORT_ORDER NATURAL)
set(CMAKE_FIND_PACKAGE_SORT_DIRECTION DEC)

if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "MSVC")
        set(CMAKE_CXX_FLAGS_RELEASE "/MT")
        set(CMAKE_CXX_FLAGS_DEBUG "/MTd")
endif()

find_package(glfw3 CONFIG REQUIRED)
find_package(GLEW REQUIRED)
find_package(OpenGL REQUIRED)
find_package(tinyobjloader CONFIG REQUIRED)
find_package(spdlog CONFIG REQUIRED)
find_package(imgui CONFIG REQUIRED)
find_package(Lua REQUIRED)

add_executable(raytracer_release
        # lib
        lib/linalg/linalg.h
        lib/imgui/imgui_impl_glfw.cpp
        lib/imgui/imgui_impl_opengl3.cpp
        lib/clipp/clipp.h
        # src
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
        src/coordinateconversion.cpp
        src/coordinateconversion.h
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
        src/material.h
        src/raycollision.h
        src/wavefrontobj.h
        src/meshinstance.cpp
        src/meshinstance.h
        src/mollertrumbore.h
        src/mollertrumbore.cpp
        src/triangle.cpp
        src/triangle.h
        src/gui.cpp
        src/gui.h
        src/worldmap.cpp
        src/worldmap.h
        src/procedualvertexbuffer.cpp
        src/procedualvertexbuffer.h
        src/luabinding.cpp
        src/luabinding.h
        src/arguments.cpp
        src/arguments.h
        src/version.h
        src/universedata.h
        src/universedata.cpp
        src/filebrowserwindow.cpp
        src/filebrowserwindow.h
        src/mapwindow.cpp
        src/mapwindow.h
        src/gl_glfw.h
        src/maprenderer.cpp
        src/maprenderer.h
        src/fullscreenquad.cpp
        src/fullscreenquad.h
        src/phonglighting.cpp
        src/phonglighting.h
        src/rgbimagethreaded.cpp
        src/rgbimagethreaded.h)


# Local Libraries
target_include_directories(raytracer_release PRIVATE lib/imgui)
target_include_directories(raytracer_release PRIVATE lib/linalg)
target_include_directories(raytracer_release PRIVATE lib/sol3)
target_include_directories(raytracer_release PRIVATE lib/tinydir)
target_include_directories(raytracer_release PRIVATE lib/clipp)

# vcpkg provided libraries
target_include_directories(raytracer_release PRIVATE ${LUA_INCLUDE_DIR})
target_link_directories(raytracer_release PRIVATE ${LUA_LIBRARY}/../)

# Library options
add_compile_definitions(SOL_ALL_SAFETIES_ON=1)

# Debugging: Print all CMake Variables
#get_cmake_property(_variableNames VARIABLES)
#list (SORT _variableNames)
#foreach (_variableName ${_variableNames})
    #message(STATUS "${_variableName}=${${_variableName}}")
#endforeach()

target_link_libraries(raytracer_release PRIVATE lua)
target_link_libraries(raytracer_release PRIVATE glfw)
target_link_libraries(raytracer_release PRIVATE GLEW::GLEW)
target_link_libraries(raytracer_release PRIVATE ${OPENGL_LIBRARIES})
target_link_libraries(raytracer_release PRIVATE spdlog::spdlog)
target_link_libraries(raytracer_release PRIVATE tinyobjloader::tinyobjloader)
target_link_libraries(raytracer_release PRIVATE imgui::imgui)

# Tests
find_package(doctest CONFIG REQUIRED)
add_executable(raytracer_test
        # lib
        lib/linalg/linalg.h
        # Test Cases
        test/test.cpp
        test/testrgbimage.cpp
        test/testspaceconversion.cpp
        test/testsphere.cpp
        test/testlighttransport.cpp
        test/testdiffuselighting.cpp
        test/testplane.cpp
        test/testraytracer.cpp
        test/testmollertrumbore.cpp
        # Main Program Code
        src/geometry.cpp
        src/geometry.h
        src/rgbimage.cpp
        src/rgbimage.h
        src/coordinateconversion.cpp
        src/coordinateconversion.h
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
        src/meshinstance.h
        src/mollertrumbore.h
        src/mollertrumbore.cpp
        src/triangle.cpp
        src/triangle.h
        src/rgbimagethreaded.cpp
        src/rgbimagethreaded.h
        test/testrgbimagethreaded.cpp)

target_include_directories(raytracer_test PRIVATE src)
target_include_directories(raytracer_test PRIVATE lib/linalg/)

target_link_libraries(raytracer_test PRIVATE doctest::doctest)
target_link_libraries(raytracer_test PRIVATE glfw)
target_link_libraries(raytracer_test PRIVATE GLEW::GLEW)
target_link_libraries(raytracer_test PRIVATE spdlog::spdlog)
target_link_libraries(raytracer_test PRIVATE fmt::fmt fmt::fmt-header-only)
target_link_libraries(raytracer_test PRIVATE tinyobjloader::tinyobjloader)
