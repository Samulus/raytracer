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

        world.addGeometry(std::make_shared<Sphere>(Sphere(glm::vec3(0.5, 1, 0), 0.1, OPAQUE_GREEN)));
        world.addGeometry(std::make_shared<Sphere>(Sphere(glm::vec3(0, 1, 0), 0.1, OPAQUE_RED)));
        world.addGeometry(std::make_shared<Sphere>(Sphere(glm::vec3(-0.5, 1, 0), 0.1, OPAQUE_BLUE)));

        // Cornell Box
        world.addGeometry(std::make_shared<Plane>(Plane(glm::vec3(0, 0, -100), glm::vec3(0, 1, 0), OPAQUE_WHITE)));
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
}

