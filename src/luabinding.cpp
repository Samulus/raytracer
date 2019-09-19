//
// luabinding.cpp
// Author: Samuel Vargas 
// Date: 09/15/2019
//

#include <linalg.h>

#include "diffuselighting.h"
#include "light.h"
#include "luabinding.h"
#include "worldlighteyetuple.h"
#include "sphere.h"

LuaBinding::LuaBinding() : global(sol::state()){
    global.open_libraries(
            sol::lib::base,
            sol::lib::package,
            sol::lib::math
    );

    using namespace linalg::aliases;

    // Math
    auto vec1f = global.new_usertype<float1>("Vec1f", sol::constructors<float1(), float1(float)>());
    auto vec2f = global.new_usertype<float2>("Vec2f", sol::constructors<float2(), float2(float, float)>());
    auto vec3f = global.new_usertype<float3>("Vec3f", sol::constructors<float3(), float3(float, float, float)>());
    auto vec4f = global.new_usertype<float4>("Vec4f", sol::constructors<float4(), float4(float, float, float, float)>());
    auto mat4f = global.new_usertype<float4x4>("Mat4f", sol::constructors<float4x4()>());

    // Material
    global.new_enum<MaterialType>("MaterialType", {
        {"Reflective", MaterialType::Reflective},
        {"Diffuse", MaterialType::Diffuse}
    });

    auto material = global.new_usertype<Material>("Material", sol::constructors<Material(float3, float3, MaterialType, float)>());

    // Light Transport Algorithms
    auto diffuseLighting = global.new_usertype<DiffuseLighting>("DiffuseLighting", sol::constructors<DiffuseLighting()>());

    // Light Types
    auto sunLight = global.new_usertype<SunLight>("SunLight", sol::constructors<SunLight(float3, float3, float)>());
    auto pointLight = global.new_usertype<SunLight>("PointLight", sol::constructors<PointLight(float3, float3, float)>());

    // Geometry
    auto sphere = global.new_usertype<Sphere>("Sphere", sol::constructors<Sphere(float3, float, Material)>());
}

std::unique_ptr<WorldLightEyeTuple> LuaBinding::loadWorldFromScript(const char* luaSource) {
    auto result = global.safe_script(luaSource, [](lua_State* L, sol::protected_function_result pfr) {
        return pfr;
    });

    if (!result.valid()) {
        throw std::runtime_error("Lua program bad, see pfr");
    }

    auto world = std::make_unique<World>();
    std::unique_ptr<LightTransport> diffuseLighting = std::make_unique<DiffuseLighting>();
    auto eye = linalg::aliases::float4x4();

    return std::make_unique<WorldLightEyeTuple>(WorldLightEyeTuple(world, diffuseLighting, eye));
}
