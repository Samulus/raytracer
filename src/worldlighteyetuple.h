//
// worldlighteyetuple.h
// Author: Samuel Vargas 
// Date: 09/16/2019
//

#pragma once
#include "world.h"
#include "lighttransport.h"
#include "diffuselighting.h"
#include <linalg.h>

struct WorldLightEyeTuple {
   std::unique_ptr<World> world;
   std::unique_ptr<LightTransport> lightTransport;
   linalg::aliases::float4x4 eyeMatrix;
   WorldLightEyeTuple(
           std::unique_ptr<World>& world,
           std::unique_ptr<LightTransport>& lightTransport,
           linalg::aliases::float4x4 eyeMatrix
   );
};