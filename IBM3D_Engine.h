#include <windows.h>
#include <windowsx.h>
#include <d3d9.h>
#include <d3dx9.h>
#include <vector>
typedef bool (*callback_function)(void); // type for conciseness

class Render;
class Input;
class I_Drawable;
class IBM3D_Engine
{
public :
	static IBM3D_Engine *     _instance;
	Render *                  Render_p;
	int                       screen_width;
	int                       screen_height;
	HWND                      hWnd;
	callback_function         update_loop_p;
	std::vector<I_Drawable*>  list_pointer;

	static IBM3D_Engine * instance();
	IBM3D_Engine();
	void updateloop(callback_function);
	void screen_init(int,int);
	void start_engine();
	void addToDraw(I_Drawable *);
	
};

#define ENGINE IBM3D_Engine::_instance()