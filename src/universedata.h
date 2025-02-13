//
// universedata.h
// Author: Samuel Vargas 
// Date: 09/16/2019
//

#pragma once
#include "world.h"
#include "lighttransport.h"
#include "diffuselighting.h"
#include <linalg.h>

struct UniverseData {
   World world;
   LightTransport& lightTransport;
   linalg::aliases::float4x4 eyeMatrix;
   UniverseData(World& world, LightTransport& lightTransport, linalg::aliases::float4x4 eyeMatrix);
};