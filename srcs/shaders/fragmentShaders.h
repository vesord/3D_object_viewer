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

"out vec4 output_color;"

"void main() {"
"if (normal_pass == vec3(0.f, 0.f, 0.f) ) "
"output_color = vec4(0.8f, 0.1f, 0.8f, 1.f);"
" else "
"output_color = abs(vec4(normal_pass, 1.f));"
"}";
#endif //FRAGMENTSHADERSIMPLE_H
