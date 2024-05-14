import enum
import math

import bpy
import numpy as np

import pdb


#bpy.types.RenderSettings.use_lock_interface = True

# Check if the active object is in Pose Mode
def is_pose_mode_active():
    # Get the active object
    active_object = bpy.context.active_object
    
    return True

    # Check if the active object exists and is in Pose Mode
    # if active_object and active_object.mode == 'POSE':
    if active_object:
        return True
    else:
        return False

class BoneName(enum.Enum):
    BoneRed = "BoneRed"

class View3DPanel:
    bl_space_type = 'VIEW_3D'
    bl_region_type = 'UI'

### Operators

def main_turn(context, slice, angle, rotaxis):

    print("pose mode?", is_pose_mode_active())
    
    bpy.ops.object.mode_set(mode='OBJECT')

    #pdb.set_trace()
    
    print(slice)
    slice = slice.reshape(9,)
    root = slice[9//2]
    print(root)
    slice = np.delete(slice, 9//2)
    print(slice)
    
    o1 = context.scene.objects["Cube."+slice[0]]
    o2 = context.scene.objects["Cube."+slice[1]]
    o3 = context.scene.objects["Cube."+slice[2]]
    o4 = context.scene.objects["Cube."+slice[3]]
    o5 = context.scene.objects["Cube."+slice[4]]
    o6 = context.scene.objects["Cube."+slice[5]]
    o7 = context.scene.objects["Cube."+slice[6]]
    o8 = context.scene.objects["Cube."+slice[7]]
    
    root = context.scene.objects["Cube."+root]

    for o in (o1, o2, o3, o4, o5, o6, o7, o8):
        o.parent = root
    
    #bpy.ops.object.parent_set(type='OBJECT', keep_transform=False)
    
    #context.active_pose_bone.rotation_mode = 'XYZ'
    rotation_increment = math.radians(angle)
    breakpoint()
    #root.rotation_euler.y += rotation_increment
    #selected_bone.rotation_euler.y += rotation_increment
    ax = getattr(root.rotation_euler, rotaxis)
    ax += rotation_increment
    
    bpy.ops.object.select_all(action='DESELECT')
    
    for o in (o1, o2, o3, o4, o5, o6, o7, o8, root):
        o.select_set(True)
        #o.matrix_world = o.matrix_world @ o.matrix_world.inverted()
        bpy.ops.object.transform_apply(location=True, rotation=True, scale=True)
        bpy.ops.object.parent_clear(type='CLEAR')
        o.select_set(False)
        
    #bpy.ops.object.parent_clear(type='CLEAR')
    
    #for o in context.scene.objects:
    #    o.select_set(False)
    
class BaseRubikCubeRotator:
    """Faire tourner le rubik cube"""
    bl_idname = "object.rubik_cube_rotator"
    
    cubes = np.array((
        "004", "027", "002",
        "020", "001", "019",
        "012", "011", "010",
        "026", "025", "024",
        "018", "017", "016",
        "009", "008", "007",
        "023", "022", "021",
        "015", "014", "013",
        "006", "005", "003"
    ))
    
    print(cubes)
    cubes = cubes.reshape(3, 3, 3)
    print(cubes)
    
    
    @classmethod
    def poll(cls, context):
        return True
        return context.active_bone is not None
    
    
    def execute(self, context):
        main_turn(context)
        return {'FINISHED'}
    
class RubikCubeRotatorRedLeft(bpy.types.Operator, BaseRubikCubeRotator):

    bl_label = "Red ↰"
    bl_idname = BaseRubikCubeRotator.bl_idname + "_red_left"

    def execute(self, context):
        main_turn(context, self.cubes[2, :, :], -45, "y")
        return {'FINISHED'}
    
class RubikCubeRotatorRedRight(bpy.types.Operator, BaseRubikCubeRotator):

    bl_label = "Red ↱"
    bl_idname = BaseRubikCubeRotator.bl_idname + "_red_right"

    def execute(self, context):
        main_turn(context, self.cubes[2, :, :], 45, "y")
        return {'FINISHED'}

class RubikCubeRotatorYellowLeft(bpy.types.Operator, BaseRubikCubeRotator):

    bl_label = "Yellow ↰"
    bl_idname = BaseRubikCubeRotator.bl_idname + "_yellow_left"
    
    def execute(self, context):
        main_turn(context, self.cubes[:, :, 0], -90, "x")
        return {'FINISHED'}
    
class RubikCubeRotatorYellowRight(bpy.types.Operator, BaseRubikCubeRotator):

    bl_label = "Yellow ↱"
    bl_idname = BaseRubikCubeRotator.bl_idname + "_yellow_right"

    def execute(self, context):
        main_turn(context, self.cubes[:, :, 0], 90, "x")
        return {'FINISHED'}

class RubikCubeRotatorOrangeLeft(bpy.types.Operator, BaseRubikCubeRotator):

    bl_label = "Orange ↰"
    bl_idname = BaseRubikCubeRotator.bl_idname + "_orange_left"

    def execute(self, context):
        main_turn(context, self.cubes[0, :, :], -90, "y")
        return {'FINISHED'}

class RubikCubeRotatorOrangeRight(bpy.types.Operator, BaseRubikCubeRotator):

    bl_label = "Orange ↱"
    bl_idname = BaseRubikCubeRotator.bl_idname + "_orange_right"

    def execute(self, context):
        main_turn(context, self.cubes[0, :, :], 90, "y")
        return {'FINISHED'}

### Panel
class RotateCubePanel(View3DPanel, bpy.types.Panel):
    bl_label = "Rotate Rubik Cube"
    bl_category = "Tool"
    bl_context = ""
    
    def draw(self, context):
        layout = self.layout

        obj = context.object

        row = layout.row()
        row.label(text="Hello world!", icon='WORLD_DATA')

        row = layout.row()
        row.label(text="Active object is: " + obj.name)
        row = layout.row()
        row.prop(obj, "name")

        row = layout.row()
        row.operator("mesh.primitive_cube_add")
        
        row = layout.row()
        row.operator("object.rubik_cube_rotator_red_left")
        row.operator("object.rubik_cube_rotator_red_right")
        row = layout.row()
        row.operator("object.rubik_cube_rotator_yellow_left")
        row.operator("object.rubik_cube_rotator_yellow_right")
        row = layout.row()
        row.operator("object.rubik_cube_rotator_orange_left")
        row.operator("object.rubik_cube_rotator_orange_right")
        row = layout.row()
        row.operator("object.rubik_cube_rotator_red_left")
        row.operator("object.rubik_cube_rotator_red_left")


def bone_move_callback(scene):
    #print("bone moved !!", scene.frame_current)
    #bpy.data.objects["Cube.023"].scale[0] = 2
    # A triangle that shifts in the z direction
    zshift = scene.frame_current * 0.1
    vertices = [(-1, -1, zshift), (1, -1, zshift), (0, 1, zshift)]
    triangles = [(0, 1, 2)]

    object = bpy.data.objects["Cube.023"]
    object.data.clear_geometry()
    object.data.from_pydata(vertices, [], triangles)

def register():
    #bpy.app.handlers.frame_change_post.append(bone_move_callback)
    #bpy.app.handlers.frame_change_pre.append(bone_move_callback)
    bpy.utils.register_class(RubikCubeRotatorRedLeft)
    bpy.utils.register_class(RubikCubeRotatorRedRight)
    bpy.utils.register_class(RubikCubeRotatorYellowLeft)
    bpy.utils.register_class(RubikCubeRotatorYellowRight)
    bpy.utils.register_class(RubikCubeRotatorOrangeLeft)
    bpy.utils.register_class(RubikCubeRotatorOrangeRight)
    bpy.utils.register_class(RotateCubePanel)

def unregister():
    #bpy.app.handlers.frame_change_pre.remove(bone_move_callback)
    #bpy.app.handlers.frame_change_post.remove(bone_move_callback)
    bpy.utils.unregister_class(RotateCubePanel)
    bpy.utils.unregister_class(RubikCubeRotatorYellowRight)
    bpy.utils.unregister_class(RubikCubeRotatorYellowLeft)
    bpy.utils.unregister_class(RubikCubeRotatorRedRight)
    bpy.utils.unregister_class(RubikCubeRotatorRedLeft)
    
if __name__ == "__main__":
    register()
    #unregister()
    