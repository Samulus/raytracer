//
// meshinstance.h
// Author: Samuel Vargas 
// Date: 09/01/2019
//

#pragma once

#include "geometry.h"
#include "wavefrontobj.h"
#include <memory>

class MeshInstance : public Geometry {
    std::shared_ptr<const WavefrontObj> wavefrontObj;
public:
    MeshInstance(const glm::vec3& origin, const Material& material, const std::shared_ptr<const WavefrontObj>& wavefrontObj);
    ~MeshInstance() override;
    [[nodiscard]] float getIntersectionScalarForRay(const Ray& ray) const override;
    [[nodiscard]] glm::vec3 getSurfaceNormal(const glm::vec3& intersectionPoint) const override;
};

