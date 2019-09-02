//
// world.h
// Author: Samuel Vargas
// Date: 08/25/2019
//

#pragma once
#include <glm/glm.hpp>
#include <vector>
#include "sphere.h"
#include "light.h"
#include <functional>
#include <memory>

class World {
private:
    std::vector<std::shared_ptr<Geometry>> geometry;

public:
    explicit World() = default;
    void addGeometry(const std::shared_ptr<Geometry>& geometry);
    const std::vector<std::shared_ptr<Geometry>>& getGeometry() const;
};
