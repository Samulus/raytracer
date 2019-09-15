//
// luabinding.h
// Author: Samuel Vargas 
// Date: 09/15/2019
//

#pragma once

#include "lua.hpp" // Silence warnings when creating sol::state(…)
#include "sol2/sol.hpp"
#include "sol2/forward.hpp"

class LuaBinding {
    sol::state global;
public:
    LuaBinding();
};

