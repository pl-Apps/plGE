#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/Xos.h>

#include <stdlib.h>
#include <iostream>

#include <unistd.h>

#include <math.h>

#include <thread>
#include <pthread.h>

#include "err.h"

using namespace std;

float clamp(float start_value, float min, float max)
{
    float ret = start_value;
    if(ret > max)
    {
        ret = max;
    }
    if(ret < min)
    {
        ret = min;
    }
    return ret;
}

class vector2
{
    public:
        float x, y;
    void assing(float x_value, float y_value)
    {
        x = x_value;
        y = y_value;
        return;
    };
};

class vector3
{
    public:
        float x, y, z;
    void assing(float x_value, float y_value, float z_value)
    {
        x = x_value;
        y = y_value;
        z = z_value;
        return;
    };
};

void create_3D_object(Display* _display, vector2 vector)
{
    return;
}

void create_3D_object(Display* _display, vector3 vector)
{
    return;
}