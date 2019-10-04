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
    global.new_enum("MaterialType",
        "Reflective", MaterialType::Reflective,
        "Diffuse", MaterialType::Diffuse
    );

    auto material = global.new_usertype<Material>(
            "Material", sol::constructors<Material(float3, float3, MaterialType, float)>());


    // Light Types
    auto light = global.new_usertype<Light>("Light");

    auto sunLight = global.new_usertype<SunLight>("SunLight",
        sol::constructors<SunLight(float3, float3, float)>(),
        sol::base_classes, sol::bases<Light>()
    );

    auto pointLight = global.new_usertype<SunLight>("PointLight",
        sol::constructors<PointLight(float3, float3, float)>(),
        sol::base_classes, sol::bases<Light>()
    );

    // Light Transport Algorithms
    auto diffuseLighting = global.new_usertype<DiffuseLighting>("DiffuseLighting",
        sol::constructors<DiffuseLighting()>(),
        "addLight", [](DiffuseLighting& diffuseLighting, Light& light) {
            auto* sunLight = dynamic_cast<SunLight*>(&light);
            if (sunLight != nullptr) {
                std::unique_ptr<Light> tmp = std::make_unique<SunLight>(*sunLight);
                diffuseLighting.addLight(tmp);
                return;
            }

            auto* pointLight = dynamic_cast<PointLight*>(&light);
            if (pointLight != nullptr) {
                std::unique_ptr<Light> tmp = std::make_unique<PointLight>(*pointLight);
                diffuseLighting.addLight(tmp);
                return;
            }

            throw std::runtime_error("Unknown light.");
        },
        sol::base_classes, sol::bases<LightTransport>()
    );

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

    auto plane = global.new_usertype<Plane>("Plane",
        sol::constructors<Plane(float3, float3, Material)>(),
        sol::base_classes, sol::bases<Geometry>()
    );

    // Universe Data
    auto universeData = global.new_usertype<UniverseData>("UniverseData",
        sol::constructors<UniverseData(World, LightTransport&, float4x4)>()
    );
}

UniverseData LuaBinding::loadUniverseFromScript(const std::filesystem::path& luaFile) {
    sol::optional<UniverseData> result = global.safe_script_file(luaFile);

    if (!result) {
        throw std::runtime_error("Lua program bad, see pfr");
    }

    return result.value();
}