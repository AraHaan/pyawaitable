#ifndef PYAWAITABLE_CORO_H
#define PYAWAITABLE_CORO_H

#include <Python.h>

#if PY_MINOR_VERSION > 9
PySendResult
awaitable_am_send(PyObject *self, PyObject *arg, PyObject **presult);
#endif

extern PyMethodDef pyawaitable_methods[];

#endif
