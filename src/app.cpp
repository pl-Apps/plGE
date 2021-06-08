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

void init(unsigned long background_color, unsigned long foreground_color);
void close();
void draw();
unsigned long RGB(int r, int g, int b);

struct coord {
	int x,y;
} dot;

int main()
{
	background_color_dark=RGB(40, 40, 40);
	foreground_color_dark=RGB(210, 210, 210);

	background_color_light=RGB(250, 250, 250);
	foreground_color_light=RGB(15, 10, 10);

	init(background_color_dark, foreground_color_dark);
	while(true)
	{
		XEvent event;
		XNextEvent(displ, &event);
		if(event.type==Expose && event.xexpose.count == 0) {
			draw();
		}
		char* text;
		KeySym key;
		if(event.type==KeyPress && XLookupString(&event.xkey, text, 255, &key, 0)==1) {
			cout << "Pressed: " << int(text[0]) << endl;
			int dec_key = int(text[0]);

			if(text[0]=='c')
			{
				XClearWindow(displ, win);
			}
			if(text[0]=='l')
			{
				Window oldwin = win;
				init(background_color_light, background_color_dark);
				cout << "Light mode" << endl;
				current_backgroundcolor=background_color_light;
				current_forecolor=background_color_dark;
				XDestroyWindow(displ, oldwin);
			}
			if(text[0]=='d')
			{
				Window oldwin = win;
				init(background_color_dark, foreground_color_dark);
				cout << "Dark mode" << endl;
				current_backgroundcolor=background_color_dark;
				current_forecolor=foreground_color_dark;
				XDestroyWindow(displ, oldwin);
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
			dot.x = x;
			dot.y = y;
		}
	}
	return 0;
}

void init(unsigned long background_color, unsigned long foreground_color)
{
	dot.x=800;
	dot.y=500;
	displ=XOpenDisplay((char *)0);
	screen=DefaultScreen(displ);
	black=BlackPixel(displ, screen);
	white=WhitePixel(displ, screen);
	red=RGB(255, 0, 0);
	blue=(0, 0, 255);
	current_backgroundcolor=background_color;
	current_forecolor=foreground_color;
	win=XCreateSimpleWindow(displ, DefaultRootWindow(displ), 0, 0, dot.x, dot.y, 5, foreground_color, background_color);
	XSetStandardProperties(displ, win, "plGE | Beta", "plGE | Beta", None, NULL, 0, NULL);
	XSelectInput(displ, win, ExposureMask | ButtonPressMask | KeyPressMask);
	gc=XCreateGC(displ, win, 0, 0);
	XSetBackground(displ, gc, current_backgroundcolor);
	XSetForeground(displ, gc, current_forecolor);
	//XClearWindow(displ, win);
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