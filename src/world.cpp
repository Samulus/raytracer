//
// world.cpp
// Author: Samuel Vargas
// Date: 08/25/2019
//

#include "world.h"
#include "sphere.h"

void World::addGeometry(const std::shared_ptr<Geometry>& item) {
    geometry.emplace_back(item);
}

const std::vector<std::shared_ptr<Geometry>>& World::getGeometry() const {
    return geometry;
}
