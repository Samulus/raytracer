//
// meshinstance.cpp
// Author: Samuel Vargas 
// Date: 09/01/2019
//

#include "meshinstance.h"

static const auto SURFACE_NORMAL_INTERSECTION_BIAS = 1e-4f;

MeshInstance::MeshInstance(const glm::vec3& origin, const Material& material, const std::shared_ptr<const WavefrontObj>& wavefrontObj) :
    Geometry(origin, material), wavefrontObj(wavefrontObj) {
}

MeshInstance::~MeshInstance() {
}

float MeshInstance::getIntersectionScalarForRay(const Ray& ray) const {
    float intersectingScalar = -1;
    wavefrontObj->forEachTriangle([&](const glm::vec3& v0, const glm::vec3& v1, const glm::vec3& v2, const glm::vec3 normal) -> void {
        intersectingScalar = wavefrontObj->rayIntersects(ray, v0, v1, v2);
        if (intersectingScalar > 0) {
            return;
        }
    });

    return intersectingScalar;
}


glm::vec3 MeshInstance::getSurfaceNormal(const glm::vec3& intersectionPoint) const {
    auto faceNormal = glm::vec3(0);
    wavefrontObj->forEachTriangle([&](const glm::vec3& v0, const glm::vec3& v1, const glm::vec3& v2, const glm::vec3 normal) -> void {
        auto pointInFrontOfFace =  Ray(intersectionPoint + (-normal * SURFACE_NORMAL_INTERSECTION_BIAS), normal);
        float intersectingScalar = wavefrontObj->rayIntersects(pointInFrontOfFace, v0, v1, v2);
        if (intersectingScalar > 0) {
            faceNormal = normal;
            return;
        }
    });

    return faceNormal;
}
