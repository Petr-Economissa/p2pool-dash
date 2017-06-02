#include <Python.h>

#include "gvidon.h"

static PyObject *gvidon_getpowhash(PyObject *self, PyObject *args)
{
    char *output;
    PyObject *value;
#if PY_MAJOR_VERSION >= 3
    PyBytesObject *input;
#else
    PyStringObject *input;
#endif
    if (!PyArg_ParseTuple(args, "S", &input))
        return NULL;
    Py_INCREF(input);
    output = PyMem_Malloc(32);

#if PY_MAJOR_VERSION >= 3
    gvidon_hash((char *)PyBytes_AsString((PyObject*) input), output);
#else
    gvidon_hash((char *)PyString_AsString((PyObject*) input), output);
#endif
    Py_DECREF(input);
#if PY_MAJOR_VERSION >= 3
    value = Py_BuildValue("y#", output, 32);
#else
    value = Py_BuildValue("s#", output, 32);
#endif
    PyMem_Free(output);
    return value;
}

static PyMethodDef GvidonMethods[] = {
    { "getPoWHash", gvidon_getpowhash, METH_VARARGS, "Returns the proof of work hash using gvidon hash" },
    { NULL, NULL, 0, NULL }
};

#if PY_MAJOR_VERSION >= 3
static struct PyModuleDef GvidonModule = {
    PyModuleDef_HEAD_INIT,
    "gvidon_hash",
    "...",
    -1,
    GvidonMethods
};

PyMODINIT_FUNC PyInit_gvidon_hash(void) {
    return PyModule_Create(&GvidonModule);
}

#else

PyMODINIT_FUNC initgvidon_hash(void) {
    (void) Py_InitModule("gvidon_hash", GvidonMethods);
}
#endif
