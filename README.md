# .obj Viewer


## Preview

<img src="https://github.com/vesord/HeavyStuffForOtherRepos/blob/master/obj_viewer/agalia.gif" width="200" height="200" />

More examples [bellow this page](#more-examples)

## Install and launch

`make`

`./scop`

You can also build project with CMake.

### Notes for linux

To compile GLFW for X11, you need to have the X11 packages installed, as well as the basic development tools like GCC and make. For example, on Ubuntu and other distributions based on Debian GNU/Linux, you need to install the xorg-dev package, which pulls in all X.org header packages.

`sudo apt-install libxrandr-dev libxinerama-dev libxcursor-dev`


## How to use

### CLI

.obj viewer provides CLI

`h` - shows help

`m /path/to/model.obj`  - opens .obj model

`t /path/to/texture.bmp`  - opens .bmp (only .bmp texture format is supported)


#### Controls

- `mouse move with left button pushed` : model rotation
- `mouse wheel` : zoom in/out
- `W` `A` `S` `D` `LShift` `LCtrl` : navigation
- `R` : shading as triangles
- `T` : shading as texture
- `Y` : shading with light (normals required)
- `U` : shading with light and texture (normals required)
- `I` : render as dots
- `O` : render as lines
- `P` : render as triangles
- `1`, `2` : increase/decrease zoom speed
- `3`, `4` : increase/decrease ambient light
- `SPACE` : stop/resume rotation

## More examples

<table>
  <tr>
    <td> <img src="https://github.com/vesord/HeavyStuffForOtherRepos/blob/master/obj_viewer/42.gif" width="200" height="200" /> </td>
    <td> <img src="https://github.com/vesord/HeavyStuffForOtherRepos/blob/master/obj_viewer/m249.gif" width="200" height="200" /> </td>
    <td> <img src="https://github.com/vesord/HeavyStuffForOtherRepos/blob/master/obj_viewer/teapot.gif" width="200" height="200" /> </td>
  </tr>
</table>
