/* senser_gl.h : June 14th 2020 5:39 pm */

#if !defined(SENSER_GL_H)

#include "glew/glew.h"
#include "gl/gl.h"

enclosed const char* VertexShaderSource = "#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"uniform mat4 Model; \n"
"uniform mat4 View; \n"
"uniform mat4 Projection; \n"
"void main()\n"
"{\n"
"   gl_Position = Projection * View * Model * vec4(aPos, 1.0);\n"
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
    
    v3 Position;
    v3 Rotation;
    v3 Scale;
};

#define WORLD_UP V3(0.f, 1.f, 0.f)
#define NEAR_PLANE 0.01f
#define FAR_PLANE 1000.f

#define ROLL V3(1.f, 0.f, 0.f)
#define PITCH V3(0.f, 1.f, 0.f)
#define YAW V3(0.f, 0.f, -1.f)

struct camera
{
    v3 Position;
    v3 Rotation;
    v3 Front;
    v3 Right;
    v3 Up;
    m4 View;
    m4 Projection;
};

global_variable camera Camera;

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
