/* Bermuda Triangle - action adventure game
   Copyright (C) 2004 Christian Zeller <chrizel@gmx.net>

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 2 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA */

#include <Python.h>
#include "python.h"

@implementation Python

static PyObject* bt_exit(PyObject *self, PyObject *args)
{
    exit(0);
}

static PyMethodDef btMethods[] = {
    {"exit", bt_exit, METH_NOARGS,
     "Exits Bermuda Triangle."},
    {NULL, NULL, 0, NULL}
};

- init
{
    printf("Init python...");
    Py_Initialize();
    Py_InitModule("bt", btMethods);
    
    // Import our module here...
    PyRun_SimpleString("import bt");

    puts("ok");
    return self;
}

- evalString:(char *)str
{
    PyRun_SimpleString(str);
}

- free
{
    printf("Finalize python...");
    Py_Finalize();
    puts("ok");
    [super free];
}

@end

