#include <Python.h>
#include <string>  /* string */
#include <exception>

#include "DEploid/src/vcfReader.hpp"


static PyObject *
dEploid_add(PyObject *self, PyObject *args)
{
    PyObject *ret = NULL;
    double x, y, result;

    if (!PyArg_ParseTuple(args, "dd", &x, &y)) {
        goto out;
    }
    result = x + y;
    ret = Py_BuildValue("d", result);
out:
    return ret;
}

static PyMethodDef dEploid_methods[] = {
    {"add", (PyCFunction) dEploid_add, METH_VARARGS,
         "Print a lovely skit to standard output."},
    {NULL, NULL, 0, NULL}   /* sentinel */
};

static struct PyModuleDef dEploidmodule = {
    PyModuleDef_HEAD_INIT,
    "dEploid",
    NULL,
    -1,
    dEploid_methods
};

PyMODINIT_FUNC
PyInit_dEploid(void)
{
    return PyModule_Create(&dEploidmodule);
}
