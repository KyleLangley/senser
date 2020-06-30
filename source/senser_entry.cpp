#include "senser_types.h"

enclosed r64 GetSecondsElapsed(LARGE_INTEGER Start, LARGE_INTEGER End)
{
    return ((r64)(End.QuadPart - Start.QuadPart) / (r64)TimingParams.Frequency.QuadPart); 
}

enclosed LARGE_INTEGER GetQueryPerformanceCounter()
{
    LARGE_INTEGER Result;
    QueryPerformanceCounter(&Result);
    return Result;
}

enclosed void FrameSleep()
{
    r64 SecondsElapsed = GetSecondsElapsed(TimingParams.EndTime, TimingParams.StartTime);
    
    if(SecondsElapsed < FRAME_UPDATE_RATE)
    {
        while(SecondsElapsed < FRAME_UPDATE_RATE)
        {
            if(Timing.SleepIsGranular)
            {
                DWORD SleepTime = (DWORD)(1000.f * (FRAME_UPDATE_RATE - SecondsElapsed));
                if(SleepTime > 0)
                {
                    Sleep(SleepTime);
                }
            }
            
            SecondsElapsed = GetSecondsElapsed(TimingParams.EndTime, GetQueryPerformanceCounter());
        }
    }
    
    TimingParams.EndTime = GetQueryPerformanceCounter();
    
    Timing.DeltaTime = GetSecondsElapsed(TimingParams.StartTime, TimingParams.EndTime);
    Timing.GameSeconds += Timing.DeltaTime;
    Timing.FPS = 1.f / Timing.DeltaTime;
}

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
            
            // Timing
            QueryPerformanceFrequency(&TimingParams.Frequency);
            TimingParams.StartTime = GetQueryPerformanceCounter();
            TimingParams.EndTime = TimingParams.StartTime;
            Timing.SleepIsGranular = timeBeginPeriod(1) == TIMERR_NOERROR;
            
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
        case WM_LBUTTONDOWN:
        {
            s32 X = SnapToGrid(LOWORD(AdditionalMessageParam), false);
            s32 Y = SnapToGrid(WindowParams.Dimensions.Y - HIWORD(AdditionalMessageParam), true);
            
            AddToQuadPositions(V2i(X, Y));
        } break;
        case WM_RBUTTONDOWN:
        {
            printf("Right mouse button down at %d %d\n", WindowParams.CursorPoint.x, WindowParams.CursorPoint.y);
        } break;
        case WM_KEYDOWN:
        {
            switch(WindowMessageParam)
            {
                case VK_F1:
                {
                    WriteMapFile("Testing.test", QuadPositions, QuadPositionsAllocationSize / sizeof(quad_position));
                } break;
            }
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
    WindowParams.Class.hCursor = LoadCursor(AppInstance, IDC_ARROW);
    WindowParams.Class.hInstance = AppInstance;
    WindowParams.Class.lpszClassName = "SenserWindowClass";
    
    if(RegisterClass(&WindowParams.Class))
    {
        WindowParams.Dimensions = V2i(1920, 1080);
        GRID_SIZE = WindowParams.Dimensions.Width / GRID_COUNT_X;
        
        WindowParams.Handle = CreateWindowEx(0, WindowParams.Class.lpszClassName, "Senser", WS_OVERLAPPEDWINDOW|WS_VISIBLE, CW_USEDEFAULT, CW_USEDEFAULT, WindowParams.Dimensions.Width, WindowParams.Dimensions.Height, 0, 0, AppInstance, 0);
        
        WindowParams.Running = WindowParams.Handle != nullptr;
        while(WindowParams.Running)
        {
            PeekMessage(&WindowParams.Message, 0, 0, 0, PM_REMOVE);
            if(WindowParams.Message.message == WM_QUIT)
            {
                WindowParams.Running = false;
                continue;
            }
            
            GetCursorPos(&WindowParams.CursorPoint);
            
            TimingParams.StartTime = GetQueryPerformanceCounter();
            
            StartFrame();
            EndFrame();
            
            TranslateMessage(&WindowParams.Message);
            DispatchMessage(&WindowParams.Message);
            
            FrameSleep();
        }
    }
    
    return WindowParams.Message.wParam;
}
