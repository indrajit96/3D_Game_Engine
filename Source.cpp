#include"IBM3D_Engine.h"
#include"Cube.h"

#pragma comment(lib,"d3dx9.lib")
#pragma comment(lib,"d3d9.lib")

LRESULT CALLBACK WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
Cube *c;
bool update_f()
{
	c->set_visible();
	return TRUE;
}

int WINAPI WinMain(HINSTANCE hInstance,
                   HINSTANCE hPrevInstance,
                   LPSTR lpCmdLine,
                   int nCmdShow)
{


	WNDCLASSEX wc;

	IBM3D_Engine * m = IBM3D_Engine::instance();
	m->update_loop_p = &update_f;
	
    ZeroMemory(&wc, sizeof(WNDCLASSEX));

    wc.cbSize = sizeof(WNDCLASSEX);
    wc.style = CS_HREDRAW | CS_VREDRAW;
    wc.lpfnWndProc = WindowProc;
    wc.hInstance = hInstance;
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);
    wc.hbrBackground = (HBRUSH)COLOR_WINDOW;
    wc.lpszClassName = L"WindowClass";

    RegisterClassEx(&wc);

    m->hWnd = CreateWindowEx(NULL,
                          L"WindowClass",
                          L"Our First Direct3D Program",
                          WS_OVERLAPPEDWINDOW,
                          100, 100,
                          800, 600,
                          NULL,
                          NULL,
                          hInstance,
                          NULL);

    ShowWindow(m->hWnd, nCmdShow);

	

	                                                                                                   //Create a CUBE
	c = new Cube(1.0,1.0,1.0); 
	m->addToDraw(c);


	m->Render_p->initD3D(m->hWnd);                                                                             //Init The screen and 3D Devices
	m->start_engine();
	
	return 0;
}


LRESULT CALLBACK WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch(message)
    {
        case WM_DESTROY:
            {
                PostQuitMessage(0);
                return 0;
            } break;
    }

    return DefWindowProc (hWnd, message, wParam, lParam);
}
