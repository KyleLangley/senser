/* senser_gl.h : June 14th 2020 5:39 pm */

#if !defined(SENSER_GL_H)

#include "glew/glew.h"
#include "gl/gl.h"

enclosed const char* VertexShaderSource = "#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"void main()\n"
"{\n"
"   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
"}\0";

enclosed const char* FragmentShaderSource = "#version 330 core\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
"   FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
"}\n\0";

struct quad_shader
{
    s32 VertexID;
    s32 FragmentID;
    s32 ProgramID;
};

struct quad
{
    u32 VBO;
    u32 VAO;
    u32 EBO;
};

global_variable quad_shader QuadShader;
global_variable quad Quad;

enclosed void InitTestTriangle();
enclosed void TestTriangle();

enclosed void CheckShader(const s32 ID);
enclosed void CheckProgram(const s32 ID);

enclosed void StartFrame();
enclosed void EndFrame();

#define SENSER_GL_H
#endif
