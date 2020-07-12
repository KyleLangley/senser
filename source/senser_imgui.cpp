/* senser_imgui.cpp : July 11th 2020 8:33 pm */

extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

enclosed ImGuiIO* GetIO()
{
    return &ImGui::GetIO();
}

enclosed void InitImGUI(void* Hwnd)
{
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    
    ImGui::StyleColorsDark();
    
    ImGui_ImplWin32_Init(Hwnd);
    ImGui_ImplOpenGL3_Init("#version 130");
}

enclosed void CloseImGui()
{
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplWin32_Shutdown();
    ImGui::DestroyContext();
}

enclosed void UpdateImGui()
{
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplWin32_NewFrame();
    ImGui::NewFrame();
    
    bool bShowDemo = true;
    ImGui::ShowDemoWindow(&bShowDemo);
    
    ImGui::Render();
    if(ImGuiIO* IO = GetIO())
    {
        glViewport(0, 0, (int)IO->DisplaySize.x, (int)IO->DisplaySize.y);
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
    }
    
}