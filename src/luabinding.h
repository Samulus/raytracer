//
// luabinding.h
// Author: Samuel Vargas 
// Date: 09/15/2019
//

#pragma once

#include "lua.hpp"

#include "geometry.h"
#include "sphere.h"
#define SOL_PRINT_ERRORS 1
#define SOL_ALL_SAFETIES_ON 1
#include "sol.hpp"
#include "world.h"
#include "universedata.h"

class LuaBinding {
    sol::state global;
public:
    LuaBinding();
    UniverseData loadUniverseFromScript(const std::filesystem::path& luaFile);
};

