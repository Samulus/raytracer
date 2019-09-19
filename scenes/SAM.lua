--
-- SAM
-- Author: Samuel Vargas 
-- Date: 09/15/2019
--

local Albedo = Vec3f.new(0.18, 0.18, 0.18)

local Color = {
    white = Vec3f.new(1, 1, 1),
    red = Vec3f.new(1, 0, 0)
}

local Material = {
    opaqueWhite = Material.new(Color.white, Albedo, MaterialType.Diffuse, 0),
    opaqueRed = Material.new(Color.red, Albedo, MaterialType.Diffuse, 0)
}
local Universe = {
    world = World.new(),
    lightTransport = DiffuseLighting.new(),
    eyeMatrix = Mat4f.new()
}

local Geometry = {
    Sphere.new(Vec3f.new(0, 0.2, 0), 0.1, Color.white)
}

local Lighting = {
    SunLight.new(Vec3f.new(0, -1, 0), Color.white, 25),
}

for _, geo in ipairs(Geometry) do
    Universe.world:addGeometry(geo)
end

for _, light in ipairs(Lighting) do
    Universe.lightTransport:addLight(light)
end

return WorldLightEyeTuple
--]]
