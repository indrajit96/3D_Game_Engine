#include"Render.h"
#include"IBM3D_Engine.h"
#include"I_Drawable.h"
#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600
#pragma comment(lib,"d3dx9.lib")
#pragma comment(lib,"d3d9.lib")

Render::Render()
{

}
void Render::initD3D(HWND hWnd)                                
{
	IBM3D_Engine *IBM3D_Engine_p = IBM3D_Engine::instance();
	Render * r1 = Render::instance();
	r1->d3d = Direct3DCreate9(D3D_SDK_VERSION);                                                   // create the Direct3D interface

    D3DPRESENT_PARAMETERS d3dpp;                                                              // create a struct to hold various device information

    ZeroMemory(&d3dpp, sizeof(d3dpp));                                                        // clear out the struct for use
    d3dpp.Windowed = TRUE;
    d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
    d3dpp.hDeviceWindow = hWnd;
    d3dpp.BackBufferFormat = D3DFMT_X8R8G8B8;
    d3dpp.BackBufferWidth = SCREEN_WIDTH;
    d3dpp.BackBufferHeight = SCREEN_HEIGHT;
    d3dpp.EnableAutoDepthStencil = TRUE;
    d3dpp.AutoDepthStencilFormat = D3DFMT_D16;

    // create a device class using this information and the info from the d3dpp stuct
    d3d->CreateDevice(D3DADAPTER_DEFAULT,
                      D3DDEVTYPE_HAL,
                      hWnd,
                      D3DCREATE_SOFTWARE_VERTEXPROCESSING,
                      &d3dpp,
                      &d3ddev);

        // call the function to initialize the cube
    init_light();    // call the function to initialize the light and material

    d3ddev->SetRenderState(D3DRS_LIGHTING, TRUE);    // turn on the 3D lighting
    d3ddev->SetRenderState(D3DRS_ZENABLE, TRUE);    // turn on the z-buffer
    d3ddev->SetRenderState(D3DRS_AMBIENT, D3DCOLOR_XRGB(50, 50, 50));    // ambient light
}

Render * Render::_instance = 0;

Render * Render::instance()
{
	if(_instance == 0)
		_instance = new Render();
	return _instance;
}

void Render::init_list()
{
	int i =0;
	for(i=0;i<list_to_draw.size();i++)
	{
		if(list_to_draw.at(i)->visible)
		list_to_draw.at(i)->init_object();
	}
}
void Render::draw_list()
{
	unsigned i;
	for(i=0;i<list_to_draw.size();i++)
	{
		list_to_draw.at(i)->draw();
	}
}
void Render::render_frame_start()
{
	d3ddev->Clear(0, NULL, D3DCLEAR_TARGET, D3DCOLOR_XRGB(0, 0, 0), 1.0f, 0);
    d3ddev->Clear(0, NULL, D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB(0, 0, 0), 1.0f, 0);

    d3ddev->BeginScene();

    // select which vertex format we are using
    d3ddev->SetFVF(CUSTOMFVF);
	SetCamera(1.0,1.0,1.0);


}

void Render::render_frame_end()
{
	d3ddev->EndScene(); 

    d3ddev->Present(NULL, NULL, NULL, NULL);
}

void Render::SetCamera(float x,float y,float z)
{
	  d3ddev->SetFVF(CUSTOMFVF);

    // set the view transform
    D3DXMATRIX matView;
    D3DXMatrixLookAtLH(&matView,
    &D3DXVECTOR3 (1.0f, 18.0f, -25.0f),    // the camera position
    &D3DXVECTOR3 (0.0f, 0.0f, 0.0f),      // the look-at position
    &D3DXVECTOR3 (0.0f, 2.0f, 8.0f));    // the up direction
    d3ddev->SetTransform(D3DTS_VIEW, &matView);

    // set the projection transform
    D3DXMATRIX matProjection;
    D3DXMatrixPerspectiveFovLH(&matProjection,
                               D3DXToRadian(45),
                               (FLOAT)SCREEN_WIDTH / (FLOAT)SCREEN_HEIGHT,
                               1.0f,    // the near view-plane
                               100.0f);    // the far view-plane
    d3ddev->SetTransform(D3DTS_PROJECTION, &matProjection);
}

void Render::init_light()
{
	D3DLIGHT9 light;    // create the light struct
    D3DMATERIAL9 material;    // create the material struct

    ZeroMemory(&light, sizeof(light));    // clear out the light struct for use
    light.Type = D3DLIGHT_DIRECTIONAL;    // make the light type 'directional light'
    light.Diffuse = D3DXCOLOR(0.5f, 0.5f, 0.5f, 1.0f);    // set the light's color
    light.Direction = D3DXVECTOR3(0.0f, -1.3f, -0.3f);

    d3ddev->SetLight(0, &light);    // send the light struct properties to light #0
    d3ddev->LightEnable(0, TRUE);    // turn on light #0

    ZeroMemory(&material, sizeof(D3DMATERIAL9));    // clear out the struct for use
    material.Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);    // set diffuse color to white
    material.Ambient = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);    // set ambient color to white

    d3ddev->SetMaterial(&material);    // set the globably-used material to &material
}
void Render::cleanD3D()
{
	d3ddev->Release();
    d3d->Release();
}