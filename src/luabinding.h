//
// luabinding.h
// Author: Samuel Vargas 
// Date: 09/15/2019
//

#pragma once

#include "lua.hpp"

#include "geometry.h"
#include "sphere.h"

//SOL_DERIVED_CLASSES(Geometry, Sphere);
//SOL_DERIVED_CLASSES(Geometry, Plane);


#include <sol/sol.hpp>
#include <sol/forward.hpp>
SOL_BASE_CLASSES(Sphere, Geometry);

#include "world.h"
#include "universedata.h"

class LuaBinding {
    sol::state global;
public:
    LuaBinding();
    UniverseData loadUniverseFromScript(const std::filesystem::path& luaFile);
};

