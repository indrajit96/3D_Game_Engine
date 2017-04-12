class I_Drawable
{
public:
	
	virtual void init_object() = 0;
	virtual void draw() = 0;
	virtual void scale(float,float,float) = 0;
	virtual void rotate(float,float,float) = 0;
	virtual void translate(float,float,float) = 0;
	virtual void clean_object() = 0;
	virtual void set_visible() = 0;
	virtual void unset_visible() = 0;
	int visible;
	
};