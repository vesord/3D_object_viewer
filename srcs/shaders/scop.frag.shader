#version 460 core

smooth in vec2 texture_pass;
smooth in vec3 normal_pass;
smooth in vec4 position_pass;
flat in int vertex_id_pass;

uniform sampler2D texture_in;
uniform int shading_type;

out vec4 output_color;

const vec4 clay_color = vec4(0.71f, 0.42f, 0.31f, 1.f);
const vec3 light_direction = normalize(vec3(-1.f, -1.f, -1.f));
const vec4 diffuse_intensity = vec4(0.85f, 0.85, 0.85, 1.f);

vec4 display_triangles()
{
    const float intense = (vertex_id_pass % 10) / 10.f + 0.1f;
    return vec4(intense, intense, intense, 1.f);
}

void main() {
    if (shading_type == 0)
        output_color = display_triangles();
    else if (shading_type == 1)
        output_color = texture(texture_in, texture_pass);
    else if (shading_type == 2)
    {
        float cos_angle_incidence = dot(normal_pass, light_direction);
        cos_angle_incidence = clamp(cos_angle_incidence, 0, 1);
        output_color = (clay_color * diffuse_intensity * cos_angle_incidence);
    }
}