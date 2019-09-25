//
// luabinding.h
// Author: Samuel Vargas 
// Date: 09/15/2019
//

#pragma once

#include "lua.hpp"

#include "geometry.h"
#include "sphere.h"
#include <sol/sol.hpp>
#include "world.h"
#include "universedata.h"

class LuaBinding {
    sol::state global;
public:
    LuaBinding();
    UniverseData loadUniverseFromScript(const std::filesystem::path& luaFile);
};

