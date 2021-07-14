#ifndef FRAGMENTSHADERSIMPLE_H
#define FRAGMENTSHADERSIMPLE_H

const GLchar* fragmentShaderSrcYValue =
"#version 460 core\n"
"\n"
"smooth in vec4 theColor;\n"
"out vec4 outputColor;\n"
"void main()\n"
"{\n"
"float lerpValue = gl_FragCoord.y / 500.0;\n"
"outputColor = mix(vec4(1.f, 1.0f, 1.0f, 1.0f), vec4(0.1f, 0.1f, 0.1f, 1.0f), lerpValue);\n"
"}\n";

const GLchar* fragmentShaderSrcSmoothColor =
"#version 460 core\n"
"\n"
"smooth in vec4 theColor;\n"
"out vec4 outputColor;\n"
"void main()\n"
"{\n"
"outputColor = theColor;\n"
"}\n";

const GLchar* fragmentShaderSrcSmoothColorChange =
"#version 460 core\n"
"\n"
"smooth in vec4 theColor;\n"
"out vec4 outputColor;\n"
"uniform float time;\n"
"uniform float loopDuration;\n"
"const vec4 white = vec4(1.0f, 1.f, 1.f, 1.f);\n"
"void main()\n"
"{\n"
"float curTime = mod(time, loopDuration);\n"
"float lerp = abs(curTime / loopDuration - 0.5f);\n"
"outputColor = mix(theColor, white, lerp);\n"
"}\n";

const GLchar* fragment_shader_pass_vtn =
"#version 460 core\n;"

"flat in vec2 texture_pass;"
"flat in vec3 normal_pass;"
"flat in vec4 position_pass;"
"flat in int vertex_id_pass;"

"out vec4 output_color;"

"const vec4 grey_color_1 = vec4(0.1f, 0.1f, 0.1f, 1.f);"
"const vec4 grey_color_3 = vec4(0.3f, 0.3f, 0.3f, 1.f);"
"const vec4 grey_color_5 = vec4(0.5f, 0.5f, 0.5f, 1.f);"
"const vec4 grey_color_8 = vec4(0.8f, 0.8f, 0.8f, 1.f);"

"void main() {"
"float intense = (vertex_id_pass % 8) / 10.f + 0.1f;"
"output_color = vec4(intense, intense, intense, 1.f);"
"}";
#endif //FRAGMENTSHADERSIMPLE_H
