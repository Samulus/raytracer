//
// ray.h
// Author: Samuel Vargas
// Date: 08/11/2019
//

#pragma once
#include <linalg.h>
#include <iostream>

class Ray {
public:
    linalg::vec<float,3> origin;
    linalg::vec<float,3> direction;
    ~Ray();
    unsigned int depth;
    Ray(const linalg::vec<float,3>& origin, const linalg::vec<float,3>& direction, unsigned int depth);
    Ray(const linalg::vec<float,3>& origin, const linalg::vec<float,3>& direction);
    Ray& operator=(const Ray& other);
    [[nodiscard]] linalg::vec<float,3> pointWithScalar(float t) const;

    friend std::ostream& operator<<(std::ostream& out, const Ray& ray);
};
