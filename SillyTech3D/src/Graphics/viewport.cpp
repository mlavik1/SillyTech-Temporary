#include "viewport.h"

#include "st_assert.h"

Viewport::Viewport(float arg_x, float arg_y, float arg_width, float arg_height)
{
	__AssertComment(arg_x <= 1.0f, "X must be between 0.0 - 1.0");
	__AssertComment(arg_y <= 1.0f, "Y must be between 0.0 - 1.0");
	__AssertComment(arg_width <= 1.0f, "Width must be between 0.0 - 1.0");
	__AssertComment(arg_height <= 1.0f, "Height must be between 0.0 - 1.0");

	x = arg_x;
	y = arg_y;
	w = arg_width;
	h = arg_height;
}

Viewport::~Viewport()
{

}