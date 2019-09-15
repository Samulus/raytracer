//
// luabinding.cpp
// Author: Samuel Vargas 
// Date: 09/15/2019
//

#include <linalg.h>
#include "luabinding.h"

LuaBinding::LuaBinding() : global(sol::state()){
    global.open_libraries(sol::lib::base, sol::lib::package);

    using namespace linalg::aliases;

    // Math
    auto vec1f = global.new_usertype<float1>("vec1f", sol::constructors<float1(), float1(float)>());
    auto vec2f = global.new_usertype<float2>("vec2f", sol::constructors<float2(), float2(float, float)>());
    auto vec3f = global.new_usertype<float3>("vec3f", sol::constructors<float3(), float3(float, float, float)>());
    auto vec4f = global.new_usertype<float4>("vec4f", sol::constructors<float4(), float4(float, float, float, float)>());

    // Shapes

}
