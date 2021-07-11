#ifndef VERTEXSHADERSIMPLE_H
#define VERTEXSHADERSIMPLE_H

const GLchar* vertexShaderSrcColorPass =
"#version 460 core\n"
"layout (location = 0) in vec3 position;\n"
"layout (location = 1) in vec3 color;\n"
"smooth out vec4 theColor;\n"
"void main()\n"
"{\n"
	"gl_Position = vec4(position.x, position.y, position.z, 1.0f);\n"
	"theColor = vec4(color.x, color.y, color.z, 1.0f);\n"
"}\0";


const GLchar* vertexShaderSrcColorPassRotation =
"#version 460 core\n"
"layout (location = 0) in vec3 position;\n"
"layout (location = 1) in vec3 color;\n"
"smooth out vec4 theColor;\n"
"uniform float loopDuration;\n"
"uniform float time;\n"
"void main()\n"
"{\n"
"float timeScale = 3.145592 * 2.0f / loopDuration;\n"
"float curTime = mod(time, loopDuration);\n"
"vec4 pos = vec4(position.x, position.y, position.z, 1.0f);\n"
"vec4 offsetPos = vec4(cos(curTime * timeScale) * 0.5f, sin(curTime * timeScale) * 0.5f, 0.f, 0.f);\n"
"gl_Position = pos + offsetPos;\n"
"theColor = vec4(color.x, color.y, color.z, 1.0f);\n"
"}\0";

const GLchar* vertexShaderSrcManualPerspective =
"#version 330\n"

"layout(location = 0) in vec4 position;"
"layout(location = 1) in vec4 color;"

"smooth out vec4 theColor;"

"uniform vec2 offset;"
"uniform mat4 cameraToClipMatrix;"

"void main()"
"{"
"vec4 cameraPos = position + vec4(offset.x, offset.y, 0.0, 0.0);"
"gl_Position = cameraToClipMatrix * cameraPos;"
"theColor = color;"
"}";

const GLchar* vertexShaderSrcModelCameraClipTransform =
"#version 460\n"

"layout (location = 0) in vec4 position;"
"layout (location = 1) in vec4 color;"

"smooth out vec4 theColor;"

"uniform mat4 modelToCameraMatrix;"
"uniform mat4 cameraToClipMatrix;"

"void main() {"
"vec4 cameraPos = modelToCameraMatrix * position;"
"gl_Position = cameraToClipMatrix * cameraPos;"
"theColor = color;"
"}";

#endif //VERTEXSHADERSIMPLE_H
