--
-- SAM
-- Author: Samuel Vargas 
-- Date: 09/15/2019
--

local Albedo = Vec3f.new(0.18, 0.18, 0.18)

local Color = {
    white = Vec3f.new(1, 1, 1),
    red = Vec3f.new(1, 0, 0),
    green = Vec3f.new(0, 1, 0),
    blue = Vec3f.new(0, 0, 1)
}

local Material = {
    mirror = Material.new(Color.white, Albedo, MaterialType.Reflective, 0),
    white = Material.new(Color.white, Albedo, MaterialType.Diffuse, 0),
    red = Material.new(Color.red, Albedo, MaterialType.Diffuse, 0),
    green = Material.new(Color.green, Albedo, MaterialType.Diffuse, 0),
    blue = Material.new(Color.blue, Albedo, MaterialType.Diffuse, 0),
}

local Universe = {
    world = World.new(),
    lightTransport = DiffuseLighting.new(),
    eyeMatrix = Mat4f.new()
}

local Geometry = {
    Sphere.new(Vec3f.new(-0.3, 0, -1), 0.1, Material.green),
    Sphere.new(Vec3f.new(0, 0, -1), 0.1, Material.mirror),
    Sphere.new(Vec3f.new(0.0, 0, -2), 0.1, Material.red),
    Sphere.new(Vec3f.new(0.3, 0, -1), 0.1, Material.blue),
}

local Lighting = {
    SunLight.new(Vec3f.new(0, -1, -1), Color.white, 25),
}

for _, geo in ipairs(Geometry) do
    Universe.world:addGeometry(geo)
end

for _, light in ipairs(Lighting) do
    Universe.lightTransport:addLight(light)
end

return UniverseData.new(Universe.world, Universe.lightTransport, Universe.eyeMatrix)
--]]
