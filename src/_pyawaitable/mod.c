#include <pyawaitable.h>
#include <pyawaitable/awaitableobject.h>
#include <pyawaitable/coro.h>
#include <pyawaitable/values.h>
#include <pyawaitable/genwrapper.h>
#include <pyawaitable/with.h>
#define ADD_TYPE_FROMSPEC(type, spec)                                        \
do                                                                           \
{                                                                            \
    type = (PyTypeObject *)PyType_FromSpec(&spec);                           \
    if (type == NULL) {                                                      \
        return NULL;                                                         \
    }                                                                        \
    if (PyModule_AddObject(m, #type, Py_NewRef(_PyObject_CAST(type))) < 0) { \
        Py_DECREF(&type);                                                    \
        Py_DECREF(m);                                                        \
        return NULL;                                                         \
    }                                                                        \
} while (0)

extern PyTypeObject *_PyAwaitableType = NULL;
extern PyTypeObject *_PyAwaitableGenWrapperType = NULL;

static PyModuleDef awaitable_module =
{
    PyModuleDef_HEAD_INIT,
    "_pyawaitable",
    NULL,
    -1
};

/*
 * This is the ABI definition.
 *
 * You can only append to this structure.
 * Never ever remove, move, or change the size of an existing field.
 */
static PyAwaitableABI _abi_interface =
{
    .size = sizeof(PyAwaitableABI),
    .new = pyawaitable_new_impl,
    .await = pyawaitable_await_impl,
    .cancel = pyawaitable_cancel_impl,
    .set_result = pyawaitable_set_result_impl,
    .save = pyawaitable_save_impl,
    .save_arb = pyawaitable_save_arb_impl,
    .unpack = pyawaitable_unpack_impl,
    .unpack_arb = pyawaitable_unpack_arb_impl,
    .await_function = pyawaitable_await_function_impl,
    .save_int = pyawaitable_save_int_impl,
    .unpack_int = pyawaitable_unpack_int_impl,
    .set = pyawaitable_set_impl,
    .set_arb = pyawaitable_set_arb_impl,
    .set_int = pyawaitable_set_int_impl,
    .get = pyawaitable_get_impl,
    .get_arb = pyawaitable_get_arb_impl,
    .get_int = pyawaitable_get_int_impl,
    .async_with = pyawaitable_async_with_impl,
    .defer_await = pyawaitable_defer_await_impl
};

PyMODINIT_FUNC
PyInit__pyawaitable(void)
{
    PyObject *m = PyModule_Create(&awaitable_module);
    ADD_TYPE_FROMSPEC(_PyAwaitableType, _PyAwaitable_Spec);
    ADD_TYPE_FROMSPEC(_PyAwaitableGenWrapperType, _PyAwaitableGenWrapper_Spec);
    _abi_interface.PyAwaitableType = _PyAwaitableType;
    PyObject *capsule = PyCapsule_New(
        &_abi_interface,
        "_pyawaitable.abi_v1",
        NULL
    );

    if (!capsule)
    {
        Py_DECREF(m);
        return NULL;
    }

    if (PyModule_AddObject(m, "abi_v1", capsule) < 0)
    {
        Py_DECREF(m);
        Py_DECREF(capsule);
        return NULL;
    }

    return m;
}
