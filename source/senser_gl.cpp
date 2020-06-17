/* senser_gl.cpp : June 14th 2020 5:39 pm */

enclosed void CheckShader(const s32 ID)
{
    s32 Success = 0;
    char InfoLog[512];
    glGetShaderiv(ID, GL_COMPILE_STATUS, &Success);
    if (!Success)
    {
        glGetShaderInfoLog(ID, 512, nullptr, InfoLog);
        printf("Error with shader %s", &InfoLog[0]);
    }
}

enclosed void CheckProgram(const s32 ID)
{
    s32 Success = 0;
    char InfoLog[512];
    glGetProgramiv(ID, GL_LINK_STATUS, &Success);
    if (!Success) 
    {
        glGetProgramInfoLog(ID, 512, nullptr, InfoLog);
        printf("Error with shader program %s", &InfoLog[0]);
    }
}

enclosed void InitTestTriangle()
{
    glewExperimental = GL_TRUE;
    GLenum Error = glewInit();
    
    QuadShader.VertexID = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(QuadShader.VertexID, 1, &VertexShaderSource, nullptr);
    glCompileShader(QuadShader.VertexID);
    
    CheckShader(QuadShader.VertexID);
    
    QuadShader.FragmentID = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(QuadShader.FragmentID, 1, &FragmentShaderSource, nullptr);
    glCompileShader(QuadShader.FragmentID);
    
    CheckShader(QuadShader.FragmentID);
    
    QuadShader.ProgramID = glCreateProgram();
    glAttachShader(QuadShader.ProgramID, QuadShader.VertexID);
    glAttachShader(QuadShader.ProgramID, QuadShader.FragmentID);
    glLinkProgram(QuadShader.ProgramID);
    
    CheckProgram(QuadShader.ProgramID);
    
    glDeleteShader(QuadShader.VertexID);
    glDeleteShader(QuadShader.FragmentID);
    
    r32 Vertices[] = 
    {
        128.f,  128.f, 0.0f,
        128.f, -128.f, 0.0f,
        -128.f, -128.f, 0.0f,
        -128.f,  128.f, 0.0f 
    };
    
    u32 Indices[] = 
    { 
        0, 1, 3,
        1, 2, 3
    };
    
    glGenVertexArrays(1, &Quad.VAO);
    glGenBuffers(1, &Quad.VBO);
    glGenBuffers(1, &Quad.EBO);
    
    glBindVertexArray(Quad.VAO);
    
    glBindBuffer(GL_ARRAY_BUFFER, Quad.VAO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(Vertices), Vertices, GL_STATIC_DRAW);
    
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, Quad.EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(Indices), Indices, GL_STATIC_DRAW);
    
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(r32), (void*)0);
    glEnableVertexAttribArray(0);
    
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
    
    Quad.Position = V3(1920/2+64, 1080/2+64, -1);
    
    Quad.Scale = V3(1.f, 1.f, 1.f);
}

enclosed void TestTriangle()
{
    glUseProgram(QuadShader.ProgramID);
    
    m4 Model = M4Translate(Quad.Position);
    Model = Model * M4Rotate(Quad.Rotation.Pitch, PITCH);
    Model = Model * M4Rotate(Quad.Rotation.Yaw, YAW);
    Model = Model * M4Rotate(Quad.Rotation.Roll, ROLL);
    Model = Model * M4Scale(Quad.Scale);
    
    Quad.Rotation.Yaw += Timing.DeltaTime * 128.f;
    Quad.Position.Y = 1080/2+64;
    Quad.Position.Y += sin(Timing.GameSeconds * PI * 1.f) * 128.f;
    
    glUniformMatrix4fv(glGetUniformLocation(QuadShader.ProgramID, "Projection"), 1, GL_FALSE, Camera.Projection.Components[0]);
    glUniformMatrix4fv(glGetUniformLocation(QuadShader.ProgramID, "View"), 1, GL_FALSE, Camera.View.Components[0]);
    glUniformMatrix4fv(glGetUniformLocation(QuadShader.ProgramID, "Model"), 1, GL_FALSE, Model.Components[0]);
    
    glBindVertexArray(Quad.VAO);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}

enclosed void StartFrame()
{
    glEnable(GL_DEPTH_TEST);
    glClearColor(0.5f, 0.5f, 0.5f, 1.f);
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    
    // Default Direction
    Camera.Rotation.Yaw = -90.f;
    
    Camera.Projection = Orthographic(0.f, (r32)1920, 0.f, (r32)1080, NEAR_PLANE, FAR_PLANE);
    
    Camera.Front.X = cos(Radians(Camera.Rotation.Yaw)) * cos(Radians(Camera.Rotation.Pitch));
    Camera.Front.Y = sin(Radians(Camera.Rotation.Pitch));
    Camera.Front.Z = sin(Radians(Camera.Rotation.Yaw)) * cos(Radians(Camera.Rotation.Pitch));
    Camera.Front = NormalizeV3(Camera.Front);
    
    Camera.Right = NormalizeV3(Cross(Camera.Front, WORLD_UP));
    Camera.Up = NormalizeV3(Cross(Camera.Right, Camera.Front));
    
    Camera.View = LookAt(Camera.Position, AddV3(Camera.Position, Camera.Front), Camera.Up);
    
    
    TestTriangle();
}

enclosed void EndFrame()
{
    SwapBuffers(WindowParams.DeviceContext);
}

