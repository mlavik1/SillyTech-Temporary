#ifndef VIEWPORT_H
#define VIEWPORT_H

class Viewport
{
public:
	Viewport(float arg_x, float arg_y, float arg_width, float arg_height);
	~Viewport();



public:
	float x;
	float y;
	float w;
	float h;

};

#endif