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
    
    QuadPositionsAllocationSize = (GRID_COUNT_X * GRID_COUNT_Y) * sizeof(quad_position);
    QuadPositions = (quad_position*)Allocate(QuadPositionsAllocationSize);
    
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
    
    glGenTextures(1, &Quad.Texture.ID);
    glBindTexture(GL_TEXTURE_2D, Quad.Texture.ID);
    
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    
    u8* Data = (u8*)stbi_load("D:\\senser\\content\\D_Editor.tga", &Quad.Texture.Params.X, &Quad.Texture.Params.Y, &Quad.Texture.Params.Z, 0);
    if(Data != nullptr)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, Quad.Texture.Params.X, Quad.Texture.Params.Y, 0, GL_RGB, GL_UNSIGNED_BYTE, Data);
        glGenerateMipmap(GL_TEXTURE_2D);
        stbi_image_free(Data);
    }
    
    const r32 VertPositionConst = GRID_SIZE / 2.f;
    r32 Vertices[] = 
    {
        // positions          // colors           // texture coords
        VertPositionConst,  VertPositionConst, 0.0f,   1.0f, 1.0f, 1.0f,   1.0f, 1.0f,   // top right
        VertPositionConst, -VertPositionConst, 0.0f,   1.0f, 1.0f, 1.0f,   1.0f, 0.0f,   // bottom right
        -VertPositionConst, -VertPositionConst, 0.0f,  1.0f, 1.0f, 1.0f,   0.0f, 0.0f,   // bottom left
        -VertPositionConst,  VertPositionConst, 0.0f,  1.0f, 1.0f, 1.0f,   0.0f, 1.0f    // top left 
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
    
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(r32), (void*)0);
    glEnableVertexAttribArray(0);
    
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(r32), (void*)(3 * sizeof(r32)));
    glEnableVertexAttribArray(1);
    
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(r32), (void*)(6 * sizeof(r32)));
    glEnableVertexAttribArray(2);
    
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
    
    Quad.Layer = DL_Front;
    Quad.Position = V2i(0, 0);
    Quad.Scale = V2i(1, 1);
}

enclosed void TestTriangle()
{
    glBindTexture(GL_TEXTURE_2D, Quad.Texture.ID);
    glUseProgram(QuadShader.ProgramID);
    
    for(s32 Index = 0; Index < QuadPositionsAllocationSize / sizeof(quad_position); ++Index)
    {
        quad_position* Position = &QuadPositions[Index];
        if(Position->Used)
        {
            m4 Model = M4Translate(V3((r32)Position->Position.X, (r32)Position->Position.Y, (r32)-Quad.Layer)) ;
            Model = Model * M4Rotate((r32)Quad.Rotation, YAW);
            Model = Model * M4Scale(V3((r32)Quad.Scale.X, (r32)Quad.Scale.Y, 1.f));
            
            glUniformMatrix4fv(glGetUniformLocation(QuadShader.ProgramID, "Projection"), 1, GL_FALSE, Camera.Projection.Components[0]);
            glUniformMatrix4fv(glGetUniformLocation(QuadShader.ProgramID, "View"), 1, GL_FALSE, Camera.View.Components[0]);
            glUniformMatrix4fv(glGetUniformLocation(QuadShader.ProgramID, "Model"), 1, GL_FALSE, Model.Components[0]);
            
            glBindVertexArray(Quad.VAO);
            glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        }
    }
}

enclosed void AddToQuadPositions(const v2i NewPosition)
{
    const s32 X = NewPosition.X / GRID_SIZE;
    const s32 Y = NewPosition.Y / GRID_SIZE;
    
    const s32 Index = ((WindowParams.Dimensions.Width / GRID_SIZE) * (Y - 1)) + X;
    
    if(QuadPositions[Index].Used)
    {
        QuadPositions[Index].Used = false;
    }
    else
    {
        QuadPositions[Index].Position = V2i(NewPosition.X, NewPosition.Y);
        QuadPositions[Index].Used = true;
    }
}

enclosed void StartFrame()
{
    glEnable(GL_DEPTH_TEST);
    glClearColor(0.5f, 0.5f, 0.5f, 1.f);
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    
    // Default Direction
    Camera.Rotation.Yaw = -90.f;
    
    Camera.Projection = Orthographic(0.f, (r32)WindowParams.Dimensions.Width, 0.f, (r32)WindowParams.Dimensions.Height, NEAR_PLANE, FAR_PLANE);
    
    Camera.Front.X = cos(Radians(Camera.Rotation.Yaw)) * cos(Radians(Camera.Rotation.Pitch));
    Camera.Front.Y = sin(Radians(Camera.Rotation.Pitch));
    Camera.Front.Z = sin(Radians(Camera.Rotation.Yaw)) * cos(Radians(Camera.Rotation.Pitch));
    
    Camera.Front = NormalizeV3(Camera.Front);
    Camera.Right = NormalizeV3(Cross(Camera.Front, WORLD_UP));
    Camera.Up = NormalizeV3(Cross(Camera.Right, Camera.Front));
    
    Camera.View = LookAt(Camera.Position, AddV3(Camera.Position, Camera.Front), Camera.Up);
    
    TestTriangle();
    
    if(App.bEditorActive)
    {
        UpdateImGui();
    }
}

enclosed void EndFrame()
{
    SwapBuffers(WindowParams.DeviceContext);
}

