//
// wavefrontobj.h
// Author: Samuel Vargas 
// Date: 08/31/2019
//

#pragma once

#include <istream>
#include <sstream>
#include <vector>
#include <tiny_obj_loader.h>
#include <cassert>
#include <spdlog/spdlog.h>
#include <optional>
#include "geometry.h"

struct WavefrontObj {
    tinyobj::attrib_t attrib;
    tinyobj::shape_t shape;
    std::optional<tinyobj::material_t> material;

    explicit WavefrontObj(const char* objText) {
        std::string warn;
        std::string err;
        std::istringstream objectStream(objText);
        std::vector<tinyobj::shape_t> shapes;
        std::vector<tinyobj::material_t> materials;
        assert(tinyobj::LoadObj(&attrib, &shapes, &materials, &warn, &err, &objectStream));

        if (!warn.empty()) {
            spdlog::warn(warn);
        }

        if (!err.empty()) {
            spdlog::error(err);
            assert(false);
        }

        if (shapes.size() != 1) {
            spdlog::error("Only 1 shape per object allowed currently.");
            assert(false);
        }

        if (materials.size()  > 1) {
            spdlog::error("Only 0 or 1 material object allowed currently.");
            assert(false);
        }

        shape = shapes[0];
        material = materials.empty() ?
                std::nullopt : std::optional<tinyobj::material_t>(materials[0]);
    }

    // Adapted from: https://en.wikipedia.org/wiki/M%C3%B6ller%E2%80%93Trumbore_intersection_algorithm
    static float rayIntersects(const Ray& ray, const glm::vec3 v0, const glm::vec3 v1, const glm::vec3 v2) {
        const auto epsilon = 1e-07f;

        const auto e1 = v1 - v0;
        const auto e2 = v2 - v0;
        const auto h = glm::cross(ray.direction, e2);
        const auto a = glm::dot(e1, h);

        // Parallel Ray
        if (a > -epsilon && a < epsilon) {
            return false;
        }

        const auto f = 1.0f / a;
        const auto s = ray.origin - v0;
        const auto u = f * glm::dot(ray.direction, h);

        if (u < 0.0 || u > 1.0) {
            return false;
        }

        const auto q = glm::cross(s, e1);
        const auto v = f * glm::dot(ray.direction, q);

        if (v < 0.0 || u + v > 1.0)
            return false;

        float t = f * glm::dot(e2, q);

        return t > epsilon ? t  : -1;
    }

    void forEachTriangle(const std::function<void(const glm::vec3& v0, const glm::vec3& v1, const glm::vec3& v2, const glm::vec3& normal)>& lambda) const {
        size_t index_offset = 0;

        // for each face
        for (size_t f = 0; f < shape.mesh.num_face_vertices.size(); f++) {
            int verticesForFace = shape.mesh.num_face_vertices[f];
            assert(verticesForFace == 3);

            // v0
            tinyobj::index_t iv0 = shape.mesh.indices[index_offset + 0];
            tinyobj::real_t vx0 = attrib.vertices[3 * iv0.vertex_index + 0];
            tinyobj::real_t vy0 = attrib.vertices[3 * iv0.vertex_index + 1];
            tinyobj::real_t vz0 = attrib.vertices[3 * iv0.vertex_index + 2];
            const auto v0 = glm::vec3(vx0, vy0, vz0);

            // v1
            tinyobj::index_t iv1 = shape.mesh.indices[index_offset + 1];
            tinyobj::real_t vx1 = attrib.vertices[3 * iv1.vertex_index + 0];
            tinyobj::real_t vy1 = attrib.vertices[3 * iv1.vertex_index + 1];
            tinyobj::real_t vz1 = attrib.vertices[3 * iv1.vertex_index + 2];
            const auto v1 = glm::vec3(vx1, vy1, vz1);

            // v2
            tinyobj::index_t iv2 = shape.mesh.indices[index_offset + 2];
            tinyobj::real_t vx2 = attrib.vertices[3 * iv2.vertex_index + 0];
            tinyobj::real_t vy2 = attrib.vertices[3 * iv2.vertex_index + 1];
            tinyobj::real_t vz2 = attrib.vertices[3 * iv2.vertex_index + 2];
            const auto v2 = glm::vec3(vx2, vy2, vz2);

            assert(iv0.normal_index >= 0 && "Normal required in obj file");

            // each vertex normal should be the same, TODO: assert for this
            tinyobj::real_t nx = attrib.normals[3*iv0.normal_index+0];
            tinyobj::real_t ny = attrib.normals[3*iv0.normal_index+1];
            tinyobj::real_t nz = attrib.normals[3*iv0.normal_index+2];
            const auto n = glm::vec3(nx, ny, nz);

            lambda.operator()(v0, v1, v2, n);
            index_offset += 3;
        }
    }

    ~WavefrontObj() = default;
};

