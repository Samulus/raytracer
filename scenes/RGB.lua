--
-- RGB.lua
-- Author: Samuel Vargas 
-- Date: 09/15/2019
--

local Albedo = Vec3f(0.18, 0.18, 0.18)

local Color = {
    white = Vec3f(1, 1, 1),
    red = Vec3f(1, 0, 0),
    green = Vec3f(0, 1, 0),
    blue = Vec3f(0, 0, 1)
}

local Material = {
    mirror = Material(Color.white, Albedo, MaterialType.Reflective, 0),
    white = Material(Color.white, Albedo, MaterialType.Diffuse, 0),
    red = Material(Color.red, Albedo, MaterialType.Diffuse, 0),
    green = Material(Color.green, Albedo, MaterialType.Diffuse, 0),
    blue = Material(Color.blue, Albedo, MaterialType.Diffuse, 0),
}

local Universe = {
    world = World(),
    lightTransport = DiffuseLighting(),
    eyeMatrix = Mat4f()
}

local Geometry = {
    Sphere(Vec3f(-0.3, 0.1, -1), 0.1, Material.red),
    Sphere(Vec3f(0.0, 0.1, -1), 0.1, Material.green),
    Sphere(Vec3f(0.3, 0.1, -1), 0.1, Material.blue),
    Plane(Vec3f(0.0, -0.05, 0.1), Vec3f(0, 1, 0), Material.white),
}

local Lighting = {
    SunLight(Vec3f(0, -1, -1), Color.white, 25),
}

for _, geo in ipairs(Geometry) do
    Universe.world:addGeometry(geo)
end

for _, light in ipairs(Lighting) do
    Universe.lightTransport:addLight(light)
end

return UniverseData(Universe.world, Universe.lightTransport, Universe.eyeMatrix)
