//
// worldlighteyetuple.cpp
// Author: Samuel Vargas 
// Date: 09/17/2019
//

#include "universedata.h"
#include "diffuselighting.h"

UniverseData::UniverseData(World& world, LightTransport& lightTransport, linalg::aliases::float4x4 eyeMatrix) :
    world(world), lightTransport(lightTransport), eyeMatrix(eyeMatrix) {
}