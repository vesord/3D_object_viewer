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


#endif //FRAGMENTSHADERSIMPLE_H
