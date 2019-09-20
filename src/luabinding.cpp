//
// luabinding.cpp
// Author: Samuel Vargas 
// Date: 09/15/2019
//

#include <linalg.h>
#include <filesystem>
#include "diffuselighting.h"
#include "light.h"
#include "luabinding.h"
#include "universedata.h"
#include "sphere.h"
#include "plane.h"
#include "triangle.h"

LuaBinding::LuaBinding() : global(sol::state()){
    global.open_libraries(
            sol::lib::base,
            sol::lib::package,
            sol::lib::math
    );

    using namespace linalg::aliases;
    using namespace linalg::ostream_overloads;

    // Math
    auto vec1f = global.new_usertype<float1>("Vec1f",
        sol::constructors<float1(), float1(float)>(),
        sol::meta_function::to_string, [] (const float1& v) { std::ostringstream output; output << v; return output.str();
    });

    auto vec2f = global.new_usertype<float2>("Vec2f",
        sol::constructors<float2(), float2(float, float)>(),
        sol::meta_function::to_string, [] (const float2& v) { std::ostringstream output; output << v; return output.str();
    });

    auto vec3f = global.new_usertype<float3>("Vec3f",
        sol::constructors<float3(), float3(float, float, float)>(),
        sol::meta_function::to_string, [] (const float3& v) { std::ostringstream output; output << v; return output.str();
    });

    auto vec4f = global.new_usertype<float4>("Vec4f",
        sol::constructors<float4(), float4(float, float, float, float)>(),
        sol::meta_function::to_string, [] (const float4& v) { std::ostringstream output; output << v; return output.str();
    });

    auto mat4f = global.new_usertype<float4x4>("Mat4f",
        sol::constructors<float4x4()>(),
        sol::meta_function::to_string, [] (const float4x4& m) { std::ostringstream output; output << m; return output.str();
    });

    // Material
    global.new_enum<MaterialType>("MaterialType", {
        {"Reflective", MaterialType::Reflective},
        {"Diffuse", MaterialType::Diffuse}
    });

    auto material = global.new_usertype<Material>(
            "Material", sol::constructors<Material(float3, float3, MaterialType, float)>());

    // Light Transport Algorithms
    auto diffuseLighting = global.new_usertype<DiffuseLighting>(
            "DiffuseLighting", sol::constructors<DiffuseLighting()>());

    // Light Types
    auto sunLight = global.new_usertype<SunLight>(
            "SunLight", sol::constructors<SunLight(float3, float3, float)>());

    auto pointLight = global.new_usertype<SunLight>(
            "PointLight", sol::constructors<PointLight(float3, float3, float)>());

    // World
    auto world = global.new_usertype<World>(
        "World", sol::constructors<World()>(),
        "addGeometry", [] (World& world, Geometry& geometry) {
            auto* sphere = dynamic_cast<Sphere*>(&geometry);
            if (sphere != nullptr) {
                world.addGeometry(std::make_shared<Sphere>(*sphere));
                return;
            }

            auto* triangle = dynamic_cast<Triangle*>(&geometry);
            if (triangle != nullptr) {
                world.addGeometry(std::make_shared<Triangle>(*triangle));
                return;
            }

            auto* plane = dynamic_cast<Plane*>(&geometry);
            if (plane != nullptr) {
                world.addGeometry(std::make_shared<Plane>(*plane));
                return;
            }

            throw std::runtime_error("Unknown geometry.");
        }
    );

    // Geometry
    auto geometry = global.new_usertype<Geometry>("Geometry");

    auto sphere = global.new_usertype<Sphere>("Sphere",
        sol::constructors<Sphere(float3, float, Material)>(),
        sol::base_classes, sol::bases<Geometry>()
    );
}

UniverseData LuaBinding::loadUniverseFromScript(const std::filesystem::path& luaFile) {
    auto result = global.safe_script_file(luaFile);

    global.collect_garbage();

    if (!result.valid()) {
        throw std::runtime_error("Lua program bad, see pfr");
    }

    auto world = World();
    auto diffuseLighting = DiffuseLighting();
    auto eye = linalg::aliases::float4x4();
    return UniverseData(world, diffuseLighting, eye);
}