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
#include "bt.h"

@implementation Python

static PyObject* bt_exit(PyObject *self, PyObject *args)
{
    exit(0);
}

static PyObject* bt_exec_code(PyObject *self, PyObject *args)
{
    char *code;
    if (!PyArg_ParseTuple(args, "s", &code))
	return NULL;
    PyRun_SimpleString(code);
    return Py_None;
}

static PyObject* bt_open_map(PyObject *self, PyObject *args)
{
    char *filename;
    printf("1\n");
    if (!PyArg_ParseTuple(args, "s", &filename))
	return NULL;
    printf("2\n");
    [[bt getMap] open:filename];
    printf("3\n");
    return Py_None;
}

static PyObject* bt_save_map(PyObject *self, PyObject *args)
{
    char *filename;
    if (!PyArg_ParseTuple(args, "s", &filename))
	return NULL;
    [[bt getMap] save:filename];
    return Py_None;
}

static PyMethodDef btMethods[] = {
    {"exit", bt_exit, METH_NOARGS,
     "Exits Bermuda Triangle."},
    {"exec_code", bt_exec_code, METH_VARARGS,
     "Executes the python code in the string argument."},
    {"open_map", bt_open_map, METH_VARARGS,
     "Opens a new map."},
    {"save_map", bt_save_map, METH_VARARGS,
     "Saves the current map to a file."},
    {NULL, NULL, 0, NULL}
};

- init
{
    printf("Init python...");
    Py_Initialize();
    PySys_SetArgv(bt_argc, bt_argv);
    Py_InitModule("bt", btMethods);
    
    // Import our module here...
    PyRun_SimpleString("import bt");

    // And call init.py
    PyRun_SimpleString("from init import *");

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

