#include "Cube.h"

Cube::Cube(float x,float y,float w)
{
	base_x = x;
	base_y = y;
	length = w;

	CUSTOMVERTEX vertices1[] =
    {
        { -3.0f, -3.0f, 3.0f, 0.0f, 0.0f, 1.0f, },    // side 1
        { 3.0f, -3.0f, 3.0f, 0.0f, 0.0f, 1.0f, },
        { -3.0f, 3.0f, 3.0f, 0.0f, 0.0f, 1.0f, },
        { 3.0f, 3.0f, 3.0f, 0.0f, 0.0f, 1.0f, },

        { -3.0f, -3.0f, -3.0f, 0.0f, 0.0f, -1.0f, },    // side 2
        { -3.0f, 3.0f, -3.0f, 0.0f, 0.0f, -1.0f, },
        { 3.0f, -3.0f, -3.0f, 0.0f, 0.0f, -1.0f, },
        { 3.0f, 3.0f, -3.0f, 0.0f, 0.0f, -1.0f, },

        { -3.0f, 3.0f, -3.0f, 0.0f, 1.0f, 0.0f, },    // side 3
        { -3.0f, 3.0f, 3.0f, 0.0f, 1.0f, 0.0f, },
        { 3.0f, 3.0f, -3.0f, 0.0f, 1.0f, 0.0f, },
        { 3.0f, 3.0f, 3.0f, 0.0f, 1.0f, 0.0f, },

        { -3.0f, -3.0f, -3.0f, 0.0f, -1.0f, 0.0f, },    // side 4
        { 3.0f, -3.0f, -3.0f, 0.0f, -1.0f, 0.0f, },
        { -3.0f, -3.0f, 3.0f, 0.0f, -1.0f, 0.0f, },
        { 3.0f, -3.0f, 3.0f, 0.0f, -1.0f, 0.0f, },

        { 3.0f, -3.0f, -3.0f, 1.0f, 0.0f, 0.0f, },    // side 5
        { 3.0f, 3.0f, -3.0f, 1.0f, 0.0f, 0.0f, },
        { 3.0f, -3.0f, 3.0f, 1.0f, 0.0f, 0.0f, },
        { 3.0f, 3.0f, 3.0f, 1.0f, 0.0f, 0.0f, },

        { -3.0f, -3.0f, -3.0f, -1.0f, 0.0f, 0.0f, },    // side 6
        { -3.0f, -3.0f, 3.0f, -1.0f, 0.0f, 0.0f, },
        { -3.0f, 3.0f, -3.0f, -1.0f, 0.0f, 0.0f, },
        { -3.0f, 3.0f, 3.0f, -1.0f, 0.0f, 0.0f, },
    };

	 short indices1[] =
    {
        0, 1, 2,    // side 1
        2, 1, 3,
        4, 5, 6,    // side 2
        6, 5, 7,
        8, 9, 10,    // side 3
        10, 9, 11,
        12, 13, 14,    // side 4
        14, 13, 15,
        16, 17, 18,    // side 5
        18, 17, 19,
        20, 21, 22,    // side 6
        22, 21, 23,
    };
	

	vertices = vertices1;
	indices = indices1;

	render_p->d3ddev->CreateVertexBuffer(24*sizeof(CUSTOMVERTEX),
                               0,
                               CUSTOMFVF,
                               D3DPOOL_MANAGED,
                               &v_buffer,
                               NULL);
	  VOID* pVoid;    // a void pointer

    // lock v_buffer and load the vertices into it
    v_buffer->Lock(0, 0, (void**)&pVoid, 0);
	
	memcpy(pVoid, vertices, sizeof(vertices));
	
	v_buffer->Unlock();

	 render_p->d3ddev->CreateIndexBuffer(36*sizeof(short),
                              0,
                              D3DFMT_INDEX16,
                              D3DPOOL_MANAGED,
                              &i_buffer,
                              NULL);
	  i_buffer->Lock(0, 0, (void**)&pVoid, 0);
    memcpy(pVoid, indices, sizeof(indices));
    i_buffer->Unlock();
	

}
void Cube::init_object()
{

}
void Cube::scale(float x,float y,float z)
{
	D3DXMatrixScaling(&matScale, 1.0f, -5.0f, 0.0f);
	render_p->d3ddev->SetTransform(D3DTS_WORLD, &matScale);
}
void Cube::translate(float x,float y,float z)
{
	D3DXMatrixScaling(&matTranslate, 1.0f, -5.0f, 0.0f);
	render_p->d3ddev->SetTransform(D3DTS_WORLD, &matTranslate);
}
void Cube::rotate(float x,float y,float z)
{
	D3DXMatrixScaling(&matRotateX, 1.0f, -5.0f, 0.0f);
	render_p->d3ddev->SetTransform(D3DTS_WORLD, &matRotateX);
}

void Cube::draw()
{
	 render_p->d3ddev->SetStreamSource(0, v_buffer, 0, sizeof(CUSTOMVERTEX));
	render_p->d3ddev->SetIndices(i_buffer);

    // draw the cube
    render_p->d3ddev->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, 24, 0, 12); 
    // select the vertex and index buffers to use


}
void Cube::clean_object()
{
	v_buffer->Release();
	i_buffer->Release();
}
void Cube::set_visible()
{
	visible = 1;
}
void Cube::unset_visible()
{
	visible = 0;
}
