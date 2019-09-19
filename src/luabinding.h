//
// luabinding.h
// Author: Samuel Vargas 
// Date: 09/15/2019
//

#pragma once

#include "lua.hpp"

#define SOL_ALL_SAFETIES_ON 1
#define SOL_CHECK_ARGUMENTS 1
#define SOL_SAFE_USERTYPES 1
#include "sol/sol.hpp"
#include "sol/forward.hpp"
#include "world.h"
#include "worldlighteyetuple.h"

class LuaBinding {
    sol::state global;
public:
    LuaBinding();
    std::unique_ptr<WorldLightEyeTuple> loadWorldFromScript(const char* luaSource);
};

