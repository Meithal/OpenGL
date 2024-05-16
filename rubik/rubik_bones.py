import enum
import math

import bpy
import numpy as np

import pdb

bl_info = {
    "name": "Rubiks Cube",
    "blender": (2, 80, 0),
    "category": "Object",
}

#bpy.types.RenderSettings.use_lock_interface = True
in_rot = False

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

def ShowMessageBox(message = "", title = "Message Box", icon = 'INFO'):

    def draw(self, context):
        self.layout.label(text=message)

    bpy.context.window_manager.popup_menu(draw, title = title, icon = icon)

### Operators

def main_turn(context, slice, angle, rotaxis):
    rotidx = ["x", "y", "z"].index(rotaxis)

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

    #for o in (o1, o2, o3, o4, o5, o6, o7, o8):
    #    o.parent = root
    
    #bpy.ops.object.parent_set(type='OBJECT', keep_transform=False)
    
    #context.active_pose_bone.rotation_mode = 'XYZ'
    rotation_increment = math.radians(angle)
    #breakpoint()
    #root.rotation_euler.y += rotation_increment
    #selected_bone.rotation_euler.y += rotation_increment
    #return
    #root.rotation_euler[rotidx] += rotation_increment
    #return
    #ax = getattr(root.rotation_euler, rotaxis)
    #ax += rotation_increment
    
    #return
    bpy.ops.object.select_all(action='DESELECT')
    
    
    for o in (o1, o2, o3, o4, o5, o6, o7, o8, root):
        o.select_set(True)
        #o.matrix_world = o.matrix_world @ o.matrix_world.inverted()
        o.rotation_euler[rotidx] += rotation_increment
        bpy.ops.object.transform_apply(location=True, rotation=True, scale=True)
        #bpy.ops.object.parent_clear(type='CLEAR')
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
    
    win_cubes = np.copy(cubes)
    
    print(cubes)
    cubes = cubes.reshape(3, 3, 3)
    win_cubes = np.copy(cubes)
    print(cubes)
    
    
    @classmethod
    def poll(cls, context):
        return True
        return context.active_bone is not None
    
    
    def check_win(self):
        #main_turn(context)
        if np.array_equal(self.win_cubes, self.cubes):
            ShowMessageBox("Bravo") 
        return {'FINISHED'}
    
class RubikCubeRotatorRedLeft(bpy.types.Operator, BaseRubikCubeRotator):

    bl_label = "Red ↰"
    bl_idname = BaseRubikCubeRotator.bl_idname + "_red_left"

    def execute(self, context):
        main_turn(context, self.cubes[2, :, :], -90, "y")
        self.cubes[2, :, :] = np.rot90(self.cubes[2, :, :], -1)
        super().check_win()
        return {'FINISHED'}
    
class RubikCubeRotatorRedRight(bpy.types.Operator, BaseRubikCubeRotator):

    bl_label = "Red ↱"
    bl_idname = BaseRubikCubeRotator.bl_idname + "_red_right"

    def execute(self, context):
        main_turn(context, self.cubes[2, :, :], 90, "y")
        self.cubes[2, :, :] = np.rot90(self.cubes[2, :, :], 1)
        super().check_win()
        return {'FINISHED'}

class RubikCubeRotatorYellowLeft(bpy.types.Operator, BaseRubikCubeRotator):

    bl_label = "Yellow ↰"
    bl_idname = BaseRubikCubeRotator.bl_idname + "_yellow_left"
    
    def execute(self, context):
        main_turn(context, self.cubes[:, :, 0], 90, "x")
        self.cubes[:, :, 0] = np.rot90(self.cubes[:, :, 0], 1)
        super().check_win()
        return {'FINISHED'}
    
class RubikCubeRotatorYellowRight(bpy.types.Operator, BaseRubikCubeRotator):

    bl_label = "Yellow ↱"
    bl_idname = BaseRubikCubeRotator.bl_idname + "_yellow_right"

    def execute(self, context):
        main_turn(context, self.cubes[:, :, 0], -90, "x")
        self.cubes[:, :, 0] = np.rot90(self.cubes[:, :, 0], -1)
        super().check_win()
        return {'FINISHED'}

class RubikCubeRotatorOrangeLeft(bpy.types.Operator, BaseRubikCubeRotator):

    bl_label = "Orange ↰"
    bl_idname = BaseRubikCubeRotator.bl_idname + "_orange_left"

    def execute(self, context):
        main_turn(context, self.cubes[0, :, :], 90, "y")
        self.cubes[0, :, :] = np.rot90(self.cubes[0, :, :], 1)
        super().check_win()
        return {'FINISHED'}

class RubikCubeRotatorOrangeRight(bpy.types.Operator, BaseRubikCubeRotator):

    bl_label = "Orange ↱"
    bl_idname = BaseRubikCubeRotator.bl_idname + "_orange_right"

    def execute(self, context):
        main_turn(context, self.cubes[0, :, :], -90, "y")
        self.cubes[0, :, :] = np.rot90(self.cubes[0, :, :], -1)
        super().check_win()
        return {'FINISHED'}


class RubikCubeRotatorWhiteLeft(bpy.types.Operator, BaseRubikCubeRotator):

    bl_label = "White ↰"
    bl_idname = BaseRubikCubeRotator.bl_idname + "_white_left"

    def execute(self, context):
        main_turn(context, self.cubes[:, :, 2], -90, "x")
        self.cubes[:, :, 2] = np.rot90(self.cubes[:, :, 2], -1)
        super().check_win()
        return {'FINISHED'}

class RubikCubeRotatorWhiteRight(bpy.types.Operator, BaseRubikCubeRotator):

    bl_label = "White ↱"
    bl_idname = BaseRubikCubeRotator.bl_idname + "_white_right"

    def execute(self, context):
        main_turn(context, self.cubes[:, :, 2], 90, "x")
        self.cubes[:, :, 2] = np.rot90(self.cubes[:, :, 2], 1)
        super().check_win()
        return {'FINISHED'}


class RubikCubeRotatorBlueLeft(bpy.types.Operator, BaseRubikCubeRotator):

    bl_label = "Blue ↰"
    bl_idname = BaseRubikCubeRotator.bl_idname + "_blue_left"

    def execute(self, context):
        main_turn(context, self.cubes[:, 0, :], 90, "z")
        self.cubes[:, 0, :] = np.rot90(self.cubes[:, 0, :], 1)
        super().check_win()
        return {'FINISHED'}

class RubikCubeRotatorBlueRight(bpy.types.Operator, BaseRubikCubeRotator):

    bl_label = "Blue ↱"
    bl_idname = BaseRubikCubeRotator.bl_idname + "_blue_right"

    def execute(self, context):
        main_turn(context, self.cubes[:, 0, :], -90, "z")
        self.cubes[:, 0, :] = np.rot90(self.cubes[:, 0, :], -1)
        super().check_win()
        return {'FINISHED'}

class RubikCubeRotatorGreenLeft(bpy.types.Operator, BaseRubikCubeRotator):

    bl_label = "Green ↰"
    bl_idname = BaseRubikCubeRotator.bl_idname + "_green_left"

    def execute(self, context):
        main_turn(context, self.cubes[:, 2, :], -90, "z")
        self.cubes[:, 2, :] = np.rot90(self.cubes[:, 2, :], -1)
        super().check_win()
        return {'FINISHED'}

class RubikCubeRotatorGreenRight(bpy.types.Operator, BaseRubikCubeRotator):

    bl_label = "Green ↱"
    bl_idname = BaseRubikCubeRotator.bl_idname + "_green_right"

    def execute(self, context):
        main_turn(context, self.cubes[:, 2, :], 90, "z")
        
        self.cubes[:, 2, :] = np.rot90(self.cubes[:, 2, :], 1)
        super().check_win()
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
        row.operator("object.rubik_cube_rotator_white_left")
        row.operator("object.rubik_cube_rotator_white_right")
        row = layout.row()
        row.operator("object.rubik_cube_rotator_blue_left")
        row.operator("object.rubik_cube_rotator_blue_right")
        row = layout.row()
        row.operator("object.rubik_cube_rotator_green_left")
        row.operator("object.rubik_cube_rotator_green_right")


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
    bpy.utils.register_class(RubikCubeRotatorWhiteLeft)
    bpy.utils.register_class(RubikCubeRotatorWhiteRight)
    bpy.utils.register_class(RubikCubeRotatorBlueLeft)
    bpy.utils.register_class(RubikCubeRotatorBlueRight)
    bpy.utils.register_class(RubikCubeRotatorGreenLeft)
    bpy.utils.register_class(RubikCubeRotatorGreenRight)
    bpy.utils.register_class(RotateCubePanel)

def unregister():
    #bpy.app.handlers.frame_change_pre.remove(bone_move_callback)
    #bpy.app.handlers.frame_change_post.remove(bone_move_callback)
    bpy.utils.unregister_class(RotateCubePanel)
    bpy.utils.unregister_class(RubikCubeRotatorYellowRight)
    bpy.utils.unregister_class(RubikCubeRotatorYellowLeft)
    bpy.utils.unregister_class(RubikCubeRotatorRedRight)
    bpy.utils.unregister_class(RubikCubeRotatorRedLeft)
    
    bpy.utils.register_class(RubikCubeRotatorOrangeLeft)
    bpy.utils.register_class(RubikCubeRotatorOrangeRight)
    bpy.utils.register_class(RubikCubeRotatorWhiteLeft)
    bpy.utils.register_class(RubikCubeRotatorWhiteRight)
    
    bpy.utils.register_class(RubikCubeRotatorBlueLeft)
    bpy.utils.register_class(RubikCubeRotatorBlueRight)
    
    
    bpy.utils.register_class(RubikCubeRotatorGreenLeft)
    bpy.utils.register_class(RubikCubeRotatorGreenRight)
    
if __name__ == "__main__":
    register()
    #unregister()
    