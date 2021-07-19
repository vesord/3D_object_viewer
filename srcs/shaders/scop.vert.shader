#version 460 core

layout (location = 0) in vec4 position;
layout (location = 1) in vec2 texture;
layout (location = 2) in vec3 normal;

smooth out vec3 normal_pass;
smooth out vec2 texture_pass;
smooth out vec4 position_pass;
flat out int vertex_id_pass;


uniform mat4 camera_to_clip_matrix;
uniform mat4 model_to_camera_matrix;

void main() {
    vec4 camera_pos = model_to_camera_matrix * position;
    gl_Position = camera_to_clip_matrix * camera_pos;
    normal_pass = (normalize(model_to_camera_matrix * vec4(normal, 0.f))).xyz;
    texture_pass = texture;
    position_pass = gl_Position;
    vertex_id_pass = gl_VertexID;
}