#ifndef PYAWAITABLE_GENWRAPPER_H
#define PYAWAITABLE_GENWRAPPER_H

#include <Python.h>
#include <pyawaitable/awaitableobject.h>

extern PyType_Spec _PyAwaitableGenWrapper_Spec;
extern PyTypeObject *_PyAwaitableGenWrapperType;

typedef struct _GenWrapperObject
{
    PyObject_HEAD
    PyAwaitableObject *gw_aw;
    PyObject *gw_current_await;
} GenWrapperObject;

PyObject *
genwrapper_next(PyObject *self);

int genwrapper_fire_err_callback(
    PyObject *self,
    awaitcallback_err err_callback
);

PyObject *
genwrapper_new(PyAwaitableObject *aw);

#endif
