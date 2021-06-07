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
unsigned long black, white, red, blue;

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
	while(1)
	{
		XEvent event;
		XNextEvent(displ, &event);
		if(event.type==Expose && event.xexpose.count == 0) {
			draw();
		}
		char text[255];
		KeySym key;
		if(event.type==KeyPress && XLookupString(&event.xkey, text, 255, &key, 0)==1) {
			if(text[0]=='q')
			{
				close();
			}
		}
		if(event.type == ButtonPress)
		{
			int x=event.xbutton.x, y=event.xbutton.y;
			XSetForeground(displ, gc, red);
			XDrawLine(displ, win, gc, dot.x, dot.y, x, y);
			XSetForeground(displ, gc, blue);
			strcpy(text, ".");
			XDrawString(displ, win, gc, x, y, text, strlen(text));
			dot.x=x;
			dot.y = y;
		}
	}
	return 0;
}

void init()
{
	dot.x=100;
	dot.y=100;
	displ=XOpenDisplay((char *)0);
	screen=DefaultScreen(displ);
	black=BlackPixel(displ, screen);
	white=WhitePixel(displ, screen);
	red=RGB(255, 0, 0);
	blue=(0, 0, 255);
	win=XCreateSimpleWindow(displ, DefaultRootWindow(displ), 0, 0, 300, 300, 5, white, black);
	XSetStandardProperties(displ, win, "plGE | Beta", "plGE | Beta", None, NULL, 0, NULL);
	XSelectInput(displ, win, ExposureMask | ButtonPressMask | KeyPressMask);
	gc=XCreateGC(displ, win, 0, 0);
	XSetBackground(displ, gc, white);
	XSetForeground(displ, gc, black);
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