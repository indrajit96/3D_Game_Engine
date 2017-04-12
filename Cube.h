#include "Render.h"
#include "I_Drawable.h"
#define CUSTOMFVF (D3DFVF_XYZ | D3DFVF_NORMAL)
struct CUSTOMVERTEX {FLOAT X, Y, Z; D3DVECTOR NORMAL;};
class Cube : public I_Drawable
{
public:
	LPDIRECT3DVERTEXBUFFER9 v_buffer;
 	LPDIRECT3DINDEXBUFFER9 i_buffer;
	D3DXMATRIX matTranslate;
	D3DXMATRIX matScale;
	D3DXMATRIX matRotateX;

	float base_x;
	float base_y;
	float length;
	

	void init_object();
	void draw();
	Cube(float,float,float);
	void scale(float,float,float);
	void translate(float,float,float);
	void rotate(float,float,float);
	void clean_object();
	CUSTOMVERTEX * vertices;              
	short * indices;
	Render * render_p;
	void set_visible();
	void unset_visible();
};
