//
// worldlighteyetuple.cpp
// Author: Samuel Vargas 
// Date: 09/17/2019
//

#include "worldlighteyetuple.h"
#include "diffuselighting.h"

WorldLightEyeTuple::WorldLightEyeTuple(
        std::unique_ptr<World>& world,
        std::unique_ptr<LightTransport>& lightTransport,
        linalg::aliases::float4x4 eyeMatrix) :
    world(std::move(world)),
    lightTransport(std::move(lightTransport)),
    eyeMatrix(eyeMatrix){
}