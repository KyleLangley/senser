/* senser_imgui.h : July 11th 2020 8:33 pm */

#if !defined(SENSER_IMGUI_H)

#define IMGUI_IMPL_OPENGL_LOADER_GLEW
#include "imgui/imgui.h"
#include "imgui/examples/imgui_impl_win32.h"
#include "imgui/examples/imgui_impl_opengl3.h"

enclosed void InitImGUI(void* Hwnd);
enclosed void CloseImGui();
enclosed void UpdateImGui();

#define SENSER_IMGUI_H
#endif
