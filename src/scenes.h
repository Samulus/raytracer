//
// scenes.h
// Author: Samuel Vargas
// Date: 08/23/2019
//

#pragma once

#include "world.h"
#include "diffuselighting.h"
#include "color.h"
#include "albedo.h"
#include "plane.h"
#include "meshinstance.h"
#include "triangle.h"

static const auto mirror = Material(WHITE, AVERAGE_ALBEDO, MaterialType::Reflective, 0.8);
static const auto OPAQUE_WHITE = Material(WHITE, AVERAGE_ALBEDO, MaterialType::Diffuse, 0);
static const auto OPAQUE_RED = Material(RED, AVERAGE_ALBEDO, MaterialType::Diffuse, 0);
static const auto OPAQUE_GREEN = Material(GREEN, AVERAGE_ALBEDO, MaterialType::Diffuse, 0);
static const auto OPAQUE_BLUE = Material(BLUE, AVERAGE_ALBEDO, MaterialType::Diffuse, 0);
static const auto OPAQUE_YELLOW = Material(YELLOW, AVERAGE_ALBEDO, MaterialType::Diffuse, 0);
static const auto OPAQUE_ORANGE = Material(ORANGE, AVERAGE_ALBEDO, MaterialType::Diffuse, 0);

// Models
static const char* RINGS_DATA =
#include "cube.obj"
;

static const std::shared_ptr<WavefrontObj> RINGS_MESH = std::make_shared<WavefrontObj>(WavefrontObj(RINGS_DATA));

namespace Scene {
    void ballsHoveringAboveGlobe(World& world, DiffuseLighting& lightTransport) {
        lightTransport.addLight(std::make_unique<SunLight>(SunLight(glm::vec3(0, -1, 0), WHITE, 20.0f)));
        //lightTransport.addLight(std::make_unique<PointLight>(PointLight(glm::vec3(0, 1.5, 0), WHITE, 75.0f)));

        const auto v0 = glm::vec3(0, 1.35, 0);
        const auto v1 = glm::vec3(-0.2, 1.1, 0);
        const auto v2 = glm::vec3(0.2, 1.1, 0);

        world.addGeometry(std::make_shared<Sphere>(Sphere(glm::vec3(0.5, 1.2, 0), 0.1, OPAQUE_GREEN)));
        world.addGeometry(std::make_shared<Sphere>(Sphere(glm::vec3(0.0, 1.2, 0), 0.1, mirror)));
        //world.addGeometry(std::make_shared<Triangle>(Triangle(v0, v1, v2, OPAQUE_RED))); // black
        world.addGeometry(std::make_shared<Sphere>(Sphere(glm::vec3(-0.5, 1.2, 0), 0.1, OPAQUE_BLUE)));

        // Floor Triangle
        const auto f0 = glm::vec3(0, 0, 100);
        const auto f1 = glm::vec3(-100, 0, 0);
        const auto f2 = glm::vec3(+100, 0, 0);
        //world.addGeometry(std::make_shared<Triangle>(Triangle(f1, f0, f2, OPAQUE_WHITE))); // black

        // Cornell Box
        //world.addGeometry(std::make_shared<Plane>(Plane(glm::vec3(0, 0, 100), glm::vec3(0, 1, 0), OPAQUE_WHITE)));
    }

    void simpleSunTest(World& world, DiffuseLighting& lightTransport) {
        // Lighting
        lightTransport.addLight(std::make_unique<SunLight>(SunLight(glm::vec3(0, -1, 0), WHITE, 100.0f)));

        // Spheres
        //world.addGeometry(std::make_shared<Sphere>(Sphere(glm::vec3(0, Universe::HumanEyeLevel, -1), 0.1, OPAQUE_GREEN)));

        // Rings
        const auto meshInstance = std::make_shared<MeshInstance>(MeshInstance(glm::vec3(0, 0, -1), OPAQUE_BLUE, RINGS_MESH));

        world.addGeometry(meshInstance);


        // Floor
        world.addGeometry(std::make_shared<Plane>(Plane(glm::vec3(0, 0, 0), glm::vec3(0, 1, 0), OPAQUE_WHITE)));
    }

    //
    // Shadow Tests
    //

    void sphereCastingShadowOnTriangle(World& world, DiffuseLighting& diffuseLighting) {
        //diffuseLighting.addLight(std::make_unique<SunLight>(SunLight(glm::vec3(0, -1, 0), WHITE, 25.0f)));

        diffuseLighting.addLight(std::make_unique<PointLight>(PointLight(glm::vec3(0, 1, -0.5), WHITE, 500.0f)));

        /*
        const glm::vec3 v0 = glm::vec3(0, -0.2, -9);
        const glm::vec3 v1 = glm::vec3(-1.3, -0.2, -1.5);
        const glm::vec3 v2 = glm::vec3(1.3, -0.2, -1.5);
         */

        // Blank? (pointy part closest to screen)
        //const glm::vec3 v0 = glm::vec3(0, -0.1, -0.1);
        //const glm::vec3 v1 = glm::vec3(-1.3, -0.1, -2);
        //const glm::vec3 v2 = glm::vec3(1.3, -0.1, -2);
        //const glm::vec3 normal = glm::vec3(0, 1, 0);

        // Visible  (pointy part furthest from screen)
        const glm::vec3 v0 = glm::vec3(-1.3, -0.1, -0.1);
        const glm::vec3 v1 = glm::vec3(1.3, -0.1, -0.1);
        const glm::vec3 v2 = glm::vec3(0, -0.1, -10);
        const glm::vec3 normal = glm::vec3(0, 1, 0);

        // Vertical Wall
        //const glm::vec3 v0 = glm::vec3(-0.5, -0.1, -1);
        //const glm::vec3 v1 = glm::vec3(0.5, -0.1, -1);
        //const glm::vec3 v2 = glm::vec3(0, 1, -1);
        //const glm::vec3 normal = glm::vec3(0, 0, 1);

        //world.addGeometry(std::make_shared<Sphere>(Sphere(glm::vec3(0, 0.1, -0.5), 0.05, OPAQUE_RED)));
        //world.addGeometry(std::make_shared<Sphere>(Sphere(glm::vec3(0, -0.2, -0.5), 0.1, OPAQUE_WHITE)));
        world.addGeometry(std::make_shared<Triangle>(Triangle(v0, v1, v2, normal, OPAQUE_WHITE)));
    }


}

