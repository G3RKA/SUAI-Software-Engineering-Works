import os
import sys
import math
import bpy

argv = sys.argv[sys.argv.index('--') + 1:]
work, heightmap = argv[0], argv[1]
scale = int(argv[2]) if len(argv) > 2 else 100

bpy.ops.wm.read_factory_settings(use_empty=True)
scene = bpy.context.scene

# Рельеф из ЛР4
bpy.ops.mesh.primitive_plane_add(size=10)
terrain = bpy.context.active_object
terrain.name = 'Terrain'
sub = terrain.modifiers.new('Subdivision', 'SUBSURF')
sub.subdivision_type = 'SIMPLE'
sub.levels = sub.render_levels = 8
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

# Анимируемый объект — шар
bpy.ops.mesh.primitive_uv_sphere_add(radius=0.35, segments=48, ring_count=24)
ball = bpy.context.active_object
ball.name = 'Ball'
bpy.ops.object.shade_smooth()

# Ключевые кадры: положение и масштаб
keys = [
    (1,   (-4.0, -3.5, 1.0), 1.0),
    (30,  (-1.5, -0.5, 3.2), 1.6),
    (60,  (1.5, 1.0, 2.6), 0.8),
    (90,  (3.5, -2.0, 2.8), 1.4),
    (120, (-0.5, -3.0, 1.2), 1.0),
]
for frame, loc, s in keys:
    ball.location = loc
    ball.scale = (s, s, s)
    ball.keyframe_insert('location', frame=frame)
    ball.keyframe_insert('scale', frame=frame)

# Сглаживание графиков F-Curve (IPO Curve): Bezier с автоматическими ручками
from bpy_extras import anim_utils
ad = ball.animation_data
channelbag = anim_utils.action_get_channelbag_for_slot(ad.action, ad.action_slot)
for fc in channelbag.fcurves:
    for kp in fc.keyframe_points:
        kp.interpolation = 'BEZIER'
        kp.handle_left_type = kp.handle_right_type = 'AUTO_CLAMPED'
    fc.update()

# Свет, небо, камера
bpy.ops.object.light_add(type='SUN', rotation=(math.radians(50), 0, math.radians(140)))
bpy.context.active_object.data.energy = 1.2
world = bpy.data.worlds.new('World')
scene.world = world
world.use_nodes = True
sky = world.node_tree.nodes.new('ShaderNodeTexSky')
world.node_tree.links.new(sky.outputs['Color'], world.node_tree.nodes['Background'].inputs['Color'])
world.node_tree.nodes['Background'].inputs['Strength'].default_value = 0.1

bpy.ops.object.camera_add(location=(9, -10, 7))
cam = bpy.context.active_object
cam.data.lens = 32
target = bpy.data.objects.new('CamTarget', None)
target.location = (0, 0, 0.8)
scene.collection.objects.link(target)
cam.constraints.new('TRACK_TO').target = target
scene.camera = cam

# Параметры видеоряда и рендеринга
scene.frame_start, scene.frame_end = 1, 120
scene.render.fps = 24
scene.render.engine = 'BLENDER_EEVEE'
scene.render.resolution_x = 1280
scene.render.resolution_y = 720
scene.render.resolution_percentage = scale

# Кадры-иллюстрации в ключевых точках
scene.render.image_settings.media_type = 'IMAGE'
scene.render.image_settings.file_format = 'JPEG'
for frame, _, _ in keys[:4]:
    scene.frame_set(frame)
    scene.render.filepath = os.path.join(work, f'frame_{frame:03d}.jpg')
    bpy.ops.render.render(write_still=True)

# Значения кривой Z для графика: Bezier и линейная интерполяция
with open(os.path.join(work, 'fcurve_z.csv'), 'w') as f:
    f.write('frame,bezier,linear\n')
    for frame in range(1, 121):
        scene.frame_set(frame)
        z = ball.location.z
        for (f0, l0, _), (f1, l1, _) in zip(keys, keys[1:]):
            if f0 <= frame <= f1:
                lin = l0[2] + (l1[2] - l0[2]) * (frame - f0) / (f1 - f0)
                break
        f.write(f'{frame},{z:.4f},{lin:.4f}\n')

# Видеоролик: MPEG-4, кодек H.264, высокое качество
scene.render.image_settings.media_type = 'VIDEO'
scene.render.image_settings.file_format = 'FFMPEG'
scene.render.ffmpeg.format = 'MPEG4'
scene.render.ffmpeg.codec = 'H264'
scene.render.ffmpeg.constant_rate_factor = 'HIGH'
scene.render.ffmpeg.ffmpeg_preset = 'GOOD'
scene.render.filepath = os.path.join(work, 'animation.mp4')
bpy.ops.render.render(animation=True)

bpy.ops.wm.save_as_mainfile(filepath=os.path.join(work, 'lr6.blend'))
