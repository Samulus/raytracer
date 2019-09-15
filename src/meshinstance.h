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
    MeshInstance(const linalg::vec<float,3>& origin, const Material& material, const std::shared_ptr<const WavefrontObj>& wavefrontObj);
    ~MeshInstance() override;
    [[nodiscard]] float getIntersectionScalarForRay(const Ray& ray) const override;
    [[nodiscard]] linalg::vec<float,3> getSurfaceNormal(const linalg::vec<float,3>& intersectionPoint) const override;
};

