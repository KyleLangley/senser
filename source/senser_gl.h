/* senser_gl.h : June 14th 2020 5:39 pm */

#if !defined(SENSER_GL_H)

#include "glew/glew.h"
#include "gl/gl.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb/stb_image.h"

enclosed const char* VertexShaderSource = "#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"layout (location = 1) in vec3 aColor;\n"
"layout (location = 2) in vec2 aTexCoord;\n"
"out vec3 Color;\n"
"out vec2 TexCoord;\n"
"uniform mat4 Model; \n"
"uniform mat4 View; \n"
"uniform mat4 Projection; \n"
"void main()\n"
"{\n"
"   gl_Position = Projection * View * Model * vec4(aPos, 1.0);\n"
"   Color = aColor;\n"
"   TexCoord = vec2(aTexCoord.x, aTexCoord.y);\n"
"}\0";

enclosed const char* FragmentShaderSource = "#version 330 core\n"
"out vec4 FragColor;\n"
"in vec3 Color;\n"
"in vec2 TexCoord;\n"
"uniform sampler2D texture_one;\n"
"void main()\n"
"{\n"
"   FragColor = texture(texture_one, TexCoord) * vec4(Color, 1.0);\n"
"}\n\0";

enum draw_layer
{
    DL_Front = 1,
    DL_Middle = 2,
    DL_Back = 3,
};

struct quad_shader
{
    s32 VertexID;
    s32 FragmentID;
    s32 ProgramID;
};

struct texture
{
    u32 ID;
    v3i Params;
};

struct quad
{
    u32 VBO;
    u32 VAO;
    u32 EBO;
    texture Texture;
    
    draw_layer Layer;
    v2i Position;
    s32 Rotation;
    v2i Scale;
};

struct quad_position
{
    v2i Position;
    u8 Used;
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

enclosed quad_position* QuadPositions;
enclosed s32 QuadPositionsAllocationSize;

enclosed void InitTestTriangle();
enclosed void TestTriangle();

enclosed void AddToQuadPositions(const v2i NewPosition);
enclosed void CheckShader(const s32 ID);
enclosed void CheckProgram(const s32 ID);

enclosed void StartFrame();
enclosed void EndFrame();

#define SENSER_GL_H
#endif
