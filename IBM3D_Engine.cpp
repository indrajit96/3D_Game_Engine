#include "IBM3D_Engine.h"
#include "Render.h"
#pragma comment(lib,"d3dx9.lib")
#pragma comment(lib,"d3d9.lib")

IBM3D_Engine * IBM3D_Engine::_instance = 0;

IBM3D_Engine::IBM3D_Engine()
{
	Render_p = new Render();
	
	//Input_O = new Input();
}

IBM3D_Engine * IBM3D_Engine::instance()
{
	if(_instance == 0)
		_instance = new IBM3D_Engine();
	return _instance;
}

void IBM3D_Engine::updateloop(callback_function f)
{
	bool a;
	a =f();                                                           //UPDATE IS EXECUTED

}
MSG msg;
void IBM3D_Engine::start_engine()
{
	
	Render_p = new Render();
	while(TRUE)
	{ 

		  while(PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }

        if(msg.message == WM_QUIT)
            break;
		updateloop(update_loop_p);
		Render_p->render_frame_start();                                //UPDATE IS EXECUTED
		Render_p->draw_list();                                        //List is drawn with required visibility.
		Render_p->render_frame_end();
	}

}

void IBM3D_Engine::addToDraw(I_Drawable * obj)
{
	Render_p->list_to_draw.push_back(obj);
}

