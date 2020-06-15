#include "senser_types.h"

enclosed void SetupPixelFormat(HDC DeviceContext)
{
    local_persist PIXELFORMATDESCRIPTOR Discriptor = {
        sizeof(PIXELFORMATDESCRIPTOR),
        1,
        PFD_DRAW_TO_WINDOW|PFD_SUPPORT_OPENGL|PFD_DOUBLEBUFFER,
        PFD_TYPE_RGBA,
        32,
        0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0,
        16, 0, 0,
        PFD_MAIN_PLANE,
        0, 0, 0, 0};
    
    s32 PixelFormat = ChoosePixelFormat(DeviceContext, &Discriptor);
    SetPixelFormat(DeviceContext, PixelFormat, &Discriptor);
}

LRESULT CALLBACK WindowCallback(HWND WindowHandle, UINT Message, WPARAM WindowMessageParam, LPARAM AdditionalMessageParam)
{
    switch(Message)
    {
        case WM_CREATE:
        {
            // Pixel format
            WindowParams.DeviceContext = GetDC(WindowHandle);
            SetupPixelFormat(WindowParams.DeviceContext);
            
            // Console
            AllocConsole();
            AttachConsole(GetCurrentProcessId());
            freopen("CON", "w", stdout);
            
            // GL
            WindowParams.RenderContext = wglCreateContext(WindowParams.DeviceContext);
            wglMakeCurrent(WindowParams.DeviceContext, WindowParams.RenderContext);
            
            InitTestTriangle();
            
            return 0;
        } break;
        case WM_CLOSE:
        {
            wglMakeCurrent(WindowParams.DeviceContext, nullptr);
            wglDeleteContext(WindowParams.RenderContext);
            
            PostQuitMessage(0);
            return 0;
        } break;
        case WM_SIZE:
        {
            
            return 0;
        } break;
        case WM_PAINT:
        {
            return 0;
        } break;
        default:
        break;
    }
    
    return DefWindowProc(WindowHandle, Message, WindowMessageParam, AdditionalMessageParam);
}

int CALLBACK WinMain(HINSTANCE AppInstance, HINSTANCE AppPrevInstance, LPSTR CommandLine, int ShowCommand)
{
    WindowParams.Class.style = CS_HREDRAW|CS_VREDRAW|CS_OWNDC;
    WindowParams.Class.lpfnWndProc = WindowCallback;
    WindowParams.Class.hInstance = AppInstance;
    WindowParams.Class.lpszClassName = "SenserWindowClass";
    
    if(RegisterClass(&WindowParams.Class))
    {
        WindowParams.Handle = CreateWindowEx(0, WindowParams.Class.lpszClassName, "Senser", WS_OVERLAPPEDWINDOW|WS_VISIBLE, CW_USEDEFAULT, CW_USEDEFAULT, 1920, 1024, 0, 0, AppInstance, 0);
        
        WindowParams.Running = WindowParams.Handle != nullptr;
        while(WindowParams.Running)
        {
            PeekMessage(&WindowParams.Message, 0, 0, 0, PM_REMOVE);
            if(WindowParams.Message.message == WM_QUIT)
            {
                WindowParams.Running = false;
                continue;
            }
            
            StartFrame();
            EndFrame();
            
            TranslateMessage(&WindowParams.Message);
            DispatchMessage(&WindowParams.Message);
            
        }
    }
    
    return WindowParams.Message.wParam;
}
