#include <windows.h>
#include <windowsx.h>
#include <d3d9.h>
#include <d3dx9.h>
#include <vector>
#define CUSTOMFVF (D3DFVF_XYZRHW | D3DFVF_DIFFUSE)
class I_Drawable;
class IBM3D_Engine;
class Render
{
public:
 LPDIRECT3D9                 d3d;              // the pointer to Direct3D interface
 LPDIRECT3DDEVICE9           d3ddev;           // the pointer to device class
 static Render*              _instance;
 std::vector<I_Drawable *>   list_to_draw;
 IBM3D_Engine *              IBM3D_Engine_p;

 void render_frame_start();
 void render_frame_end();

 void SetCamera(float,float,float);
 void cleanD3D();
 void init_list();
 void draw_list();
 void init_light();
 Render();
 void initD3D(HWND);                           // sets up and initializes Direct3D
 static Render* instance();

};