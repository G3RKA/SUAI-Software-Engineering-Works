import os
import sys
import math
import bpy

argv = sys.argv[sys.argv.index('--') + 1:]
work, heightmap = argv[0], argv[1]
scale = int(argv[2]) if len(argv) > 2 else 100
only = argv[3].split(',') if len(argv) > 3 else None

bpy.ops.wm.read_factory_settings(use_empty=True)
scene = bpy.context.scene

# Рельеф из ЛР4: Plane + Subdivision Surface + Displace с картой высот
bpy.ops.mesh.primitive_plane_add(size=120)
terrain = bpy.context.active_object
terrain.name = 'Terrain'
sub = terrain.modifiers.new('Subdivision', 'SUBSURF')
sub.subdivision_type = 'SIMPLE'
sub.levels = sub.render_levels = 10
tex = bpy.data.textures.new('HeightMap', 'IMAGE')
tex.image = bpy.data.images.load(heightmap)
tex.image.colorspace_settings.name = 'Non-Color'
# карта высот занимает центр плоскости, вокруг ровная земля
tex.extension = 'CLIP'
tex.crop_min_x = tex.crop_min_y = -1.0
tex.crop_max_x = tex.crop_max_y = 2.0
disp = terrain.modifiers.new('Displace', 'DISPLACE')
disp.texture = tex
disp.texture_coords = 'UV'
disp.strength = 7.0
disp.mid_level = 0.0
bpy.ops.object.shade_smooth()

# Камера у края рельефа смотрит на горы
bpy.ops.object.camera_add(location=(0, -30, 1.0), rotation=(math.radians(97), 0, 0))
cam = bpy.context.active_object
cam.data.lens = 40
scene.camera = cam

# Источник света Sun
bpy.ops.object.light_add(type='SUN')
sun = bpy.context.active_object
sun.data.angle = math.radians(0.6)

# Мир: физическое небо (с солнечным диском) и ночное небо со звёздами
day = bpy.data.worlds.new('Day')
day.use_nodes = True
dn = day.node_tree.nodes
sky = dn.new('ShaderNodeTexSky')
sky.sky_type = 'MULTIPLE_SCATTERING'
sky.sun_disc = True
sky.sun_size = math.radians(2.5)
sky.sun_rotation = 0.0
day.node_tree.links.new(sky.outputs['Color'], dn['Background'].inputs['Color'])
bg = dn['Background']

night = bpy.data.worlds.new('Night')
night.use_nodes = True
nn = night.node_tree.nodes
nbg = nn['Background']
vor = nn.new('ShaderNodeTexVoronoi')
vor.feature = 'F1'
vor.inputs['Scale'].default_value = 70
coord = nn.new('ShaderNodeTexCoord')
night.node_tree.links.new(coord.outputs['Generated'], vor.inputs['Vector'])
ramp = nn.new('ShaderNodeValToRGB')
ramp.color_ramp.elements[0].position = 0.0
ramp.color_ramp.elements[0].color = (1, 1, 1, 1)
ramp.color_ramp.elements[1].position = 0.045
ramp.color_ramp.elements[1].color = (0.006, 0.02, 0.07, 1)
night.node_tree.links.new(vor.outputs['Distance'], ramp.inputs['Fac'])
night.node_tree.links.new(ramp.outputs['Color'], nbg.inputs['Color'])
nbg.inputs['Strength'].default_value = 1.0
# звёзды видны только камере, горы ночью не подсвечиваются
lp = nn.new('ShaderNodeLightPath')
dark = nn.new('ShaderNodeBackground')
dark.inputs['Strength'].default_value = 0.0
mix = nn.new('ShaderNodeMixShader')
night.node_tree.links.new(lp.outputs['Is Camera Ray'], mix.inputs['Fac'])
night.node_tree.links.new(dark.outputs['Background'], mix.inputs[1])
night.node_tree.links.new(nbg.outputs['Background'], mix.inputs[2])
night.node_tree.links.new(mix.outputs['Shader'], nn['World Output'].inputs['Surface'])


def set_sun(elev_deg, azim_deg, energy, strength, color=(1, 1, 1)):
    scene.world = day
    e, a = math.radians(elev_deg), math.radians(azim_deg)
    sky.sun_elevation = e
    sky.sun_rotation = a
    bg.inputs['Strength'].default_value = strength
    # направление лампы совпадает с солнцем на небе
    sun.rotation_euler = (math.pi / 2 - e, 0, math.pi - a)
    sun.data.energy = energy
    sun.data.color = color
    sun.hide_render = False


scene.render.engine = 'CYCLES'
scene.cycles.samples = 48
scene.cycles.use_denoising = True
scene.render.resolution_x = 1600
scene.render.resolution_y = 1200
scene.render.resolution_percentage = scale
scene.render.image_settings.file_format = 'JPEG'
scene.render.image_settings.quality = 95

shots = {
    'sunrise': lambda: set_sun(1.0, -15, 1.0, 0.15, (1.0, 0.7, 0.4)),
    'sundisc': lambda: set_sun(14, -5, 1.5, 0.12, (1.0, 0.92, 0.8)),
    'day':     lambda: set_sun(45, 20, 1.5, 0.08),
    'sunset':  lambda: set_sun(0.4, -30, 2.0, 0.35, (1.0, 0.3, 0.1)),
}

for name, setup in shots.items():
    if only and name not in only:
        continue
    setup()
    scene.render.filepath = os.path.join(work, f'{name}.jpg')
    bpy.ops.render.render(write_still=True)

if not only or 'night' in only:
    scene.world = night
    sun.hide_render = True
    scene.render.filepath = os.path.join(work, 'night.jpg')
    bpy.ops.render.render(write_still=True)

bpy.ops.wm.save_as_mainfile(filepath=os.path.join(work, 'lr5.blend'))
