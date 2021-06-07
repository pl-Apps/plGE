#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/Xos.h>

#include <stdlib.h>
#include <iostream>

using namespace std;

Display* displ;
int screen;
Window win;
GC gc;
unsigned long white, black, red, blue, current_forecolor, current_backgroundcolor, background_color_dark, foreground_color_dark, background_color_light, foreground_color_light;

void init();
void close();
void draw();
unsigned long RGB(int r, int g, int b);

struct coord {
	int x,y;
} dot;

int main()
{
	init();
	while(true)
	{
		XEvent event;
		XNextEvent(displ, &event);
		if(event.type==Expose && event.xexpose.count == 0) {
			draw();
		}
		char text[255];
		KeySym key;
		if(event.type==KeyPress && XLookupString(&event.xkey, text, 255, &key, 0)==1) {
			if(text[0]=='c')
			{
				XClearWindow(displ, win);
			}
			if(text[0]=='w')
			{
				//XFreeGC(displ, gc);
				XClearWindow(displ, win);
			}
			if(text[0]=='b')
			{
				//XFreeGC(displ, gc);
				XClearWindow(displ, win);
			}
		}
		if(event.type == ButtonPress)
		{
			int x=event.xbutton.x, y=event.xbutton.y;
			XSetForeground(displ, gc, foreground_color_dark);
			XDrawLine(displ, win, gc, dot.x, dot.y, x, y);
			XSetForeground(displ, gc, blue);
			strcpy(text, "");
			XDrawString(displ, win, gc, x, y, text, strlen(text));
			dot.x=x;
			dot.y = y;
		}
	}
	return 0;
}

void init()
{
	dot.x=800;
	dot.y=500;
	displ=XOpenDisplay((char *)0);
	screen=DefaultScreen(displ);
	black=BlackPixel(displ, screen);
	white=WhitePixel(displ, screen);
	red=RGB(255, 0, 0);
	blue=(0, 0, 255);
	background_color_dark=RGB(40, 40, 40);
	foreground_color_dark=RGB(210, 210, 210);
	background_color_light=RGB(210, 210, 210);
	foreground_color_light=RGB(40, 40, 40);
	current_backgroundcolor=background_color_dark;
	current_forecolor=foreground_color_dark;
	win=XCreateSimpleWindow(displ, DefaultRootWindow(displ), 0, 0, dot.x, dot.y, 5, background_color_dark, background_color_dark);
	XSetStandardProperties(displ, win, "plGE | Beta", "plGE | Beta", None, NULL, 0, NULL);
	XSelectInput(displ, win, ExposureMask | ButtonPressMask | KeyPressMask);
	gc=XCreateGC(displ, win, 0, 0);
	XSetBackground(displ, gc, background_color_dark);
	XSetForeground(displ, gc, background_color_dark);
	XClearWindow(displ, win);
	XMapRaised(displ, win);
}

void close()
{
	XFreeGC(displ, gc);
	XDestroyWindow(displ, win);
	XCloseDisplay(displ);
	exit(0);
}

void draw()
{
	XClearWindow(displ, win);
}

unsigned long RGB(int r, int g, int b)
{
	return b + (g<<8) + (r<<16);
}