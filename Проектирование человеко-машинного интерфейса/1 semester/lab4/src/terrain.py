import os
import sys
import math
import bpy

argv = sys.argv[sys.argv.index('--') + 1:]
work = argv[0]
heightmap = os.path.join(work, 'heightmap.png')

bpy.ops.wm.read_factory_settings(use_empty=True)
scene = bpy.context.scene

# а) Plane
bpy.ops.mesh.primitive_plane_add(size=10)
terrain = bpy.context.active_object
terrain.name = 'Terrain'

# б) Subdivision Surface: 4 вершины -> ~263 тыс.
sub = terrain.modifiers.new('Subdivision', 'SUBSURF')
sub.subdivision_type = 'SIMPLE'
sub.levels = 9
sub.render_levels = 9

# в) Displace с текстурой — картой высот
tex = bpy.data.textures.new('HeightMap', 'IMAGE')
tex.image = bpy.data.images.load(heightmap)
tex.image.colorspace_settings.name = 'Non-Color'
tex.extension = 'EXTEND'
disp = terrain.modifiers.new('Displace', 'DISPLACE')
disp.texture = tex
disp.texture_coords = 'UV'
disp.strength = 2.2
disp.mid_level = 0.0
bpy.ops.object.shade_smooth()

# Свет и небо
bpy.ops.object.light_add(type='SUN', rotation=(math.radians(55), 0, math.radians(135)))
bpy.context.active_object.data.energy = 1.2
world = bpy.data.worlds.new('World')
scene.world = world
world.use_nodes = True
sky = world.node_tree.nodes.new('ShaderNodeTexSky')
world.node_tree.links.new(sky.outputs['Color'], world.node_tree.nodes['Background'].inputs['Color'])
world.node_tree.nodes['Background'].inputs['Strength'].default_value = 0.1

# Камеры
def add_camera(name, loc, target):
    bpy.ops.object.camera_add(location=loc)
    cam = bpy.context.active_object
    cam.name = name
    cam.data.lens = 35
    c = cam.constraints.new('TRACK_TO')
    empty = bpy.data.objects.new(name + '_target', None)
    empty.location = target
    scene.collection.objects.link(empty)
    c.target = empty
    return cam

cams = [add_camera('Camera1', (9, -9, 6), (0, 0, 0.3)),
        add_camera('Camera2', (-8, -4, 4.5), (0.5, 0.5, 0.6)),
        add_camera('CameraTop', (0, 0, 14), (0, 0, 0))]

# Параметры рендеринга: 1600x1200, JPEG
scene.render.engine = 'CYCLES'
scene.cycles.samples = 64
scene.cycles.use_denoising = True
scene.render.resolution_x = 1600
scene.render.resolution_y = 1200
scene.render.resolution_percentage = 100
scene.render.image_settings.file_format = 'JPEG'
scene.render.image_settings.quality = 95

for i, cam in enumerate(cams, 1):
    scene.camera = cam
    scene.render.filepath = os.path.join(work, f'render_{i}.jpg')
    bpy.ops.render.render(write_still=True)

bpy.ops.wm.save_as_mainfile(filepath=os.path.join(work, 'terrain.blend'))
