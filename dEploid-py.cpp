#include <Python.h>
#include <string>  /* string */
#include <exception>

#include "lib/src/vcfReader.hpp"

//typedef struct {
    //PyObject_HEAD
    //tree_sequence_t *tree_sequence;
//} TreeSequence;

static void
handle_library_error(int err)
{
    //if (msp_is_kas_error(err)) {
        //PyErr_SetString(MsprimeFileFormatError, msp_strerror(err));
    //} else {
        //switch (err) {
            //case MSP_ERR_FILE_VERSION_TOO_NEW:
                //PyErr_SetString(MsprimeVersionTooNewError, msp_strerror(err));
                //break;
            //case MSP_ERR_FILE_VERSION_TOO_OLD:
                //PyErr_SetString(MsprimeVersionTooOldError, msp_strerror(err));
                //break;
            //case MSP_ERR_FILE_FORMAT:
                //PyErr_SetString(MsprimeFileFormatError, msp_strerror(err));
                //break;
            //case MSP_ERR_OUT_OF_BOUNDS:
                //PyErr_SetString(PyExc_IndexError, msp_strerror(err));
                //break;
            //default:
                //PyErr_SetString(MsprimeLibraryError, msp_strerror(err));
        //}
    //}
    //PyErr_SetString(MsprimeFileFormatError, msp_strerror(err));
}


typedef struct {
    PyObject_HEAD
    bool locked;
    VcfReader *vcfreader;
} VcfReaderPy;


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

static PyObject *
extractCoverageFromVcf(PyObject *args)
{
    PyObject *ret = NULL;
    //size_t num_tracked_samples;
    int err;
    err = 0;
    //if (SparseTree_get_node_argument(self, args, &node) != 0) {
        //goto out;
    //}
    //err = sparse_tree_get_num_tracked_samples(self->sparse_tree, (node_id_t) node,
            //&num_tracked_samples);

    //if (err != 0) {
        //handle_library_error(err);
        //goto out;
    //}
    ////ret = Py_BuildValue("I", (unsigned int) num_tracked_samples);
//out:
    if ( err != 0 ){
        handle_library_error(err);
    }

    return ret;
}





static PyMethodDef dEploid_extractCoverageFromVcf[] = {
    {"extractCoverageFromVcf", (PyCFunction) extractCoverageFromVcf,
            METH_VARARGS,
            "Extract vcf ..." },
    {NULL, NULL, 0, NULL}   /* sentinel */
};


static PyTypeObject EmptyType = {
    PyVarObject_HEAD_INIT(NULL, 0)
    "_dEploid.EmptyType",             /* tp_name */
    0,             /* tp_basicsize */
    0,                         /* tp_itemsize */
    0, /* tp_dealloc */
    0,                         /* tp_print */
    0,                         /* tp_getattr */
    0,                         /* tp_setattr */
    0,                         /* tp_reserved */
    0,                         /* tp_repr */
    0,                         /* tp_as_number */
    0,                         /* tp_as_sequence */
    0,                         /* tp_as_mapping */
    0,                         /* tp_hash  */
    0,                         /* tp_call */
    0,                         /* tp_str */
    0,                         /* tp_getattro */
    0,                         /* tp_setattro */
    0,                         /* tp_as_buffer */
    0,        /* tp_flags */
    0,           /* tp_doc */
    0,                     /* tp_traverse */
    0,                     /* tp_clear */
    0,                     /* tp_richcompare */
    0,                     /* tp_weaklistoffset */
    0,                     /* tp_iter */
    0,                     /* tp_iternext */
    0,             /* tp_methods */
    0,             /* tp_members */
    0,                         /* tp_getset */
    0,                         /* tp_base */
    0,                         /* tp_dict */
    0,                         /* tp_descr_get */
    0,                         /* tp_descr_set */
    0,                         /* tp_dictoffset */
    0,      /* tp_init */
};


static PyObject *
dEploid_getProgramVertionStr(PyObject *self)
{
    return Py_BuildValue("s", VERSION);
}


static PyObject *
dEploid_getLibraryVertionStr(PyObject *self)
{
    return Py_BuildValue("s", DEPLOIDVERSION);
}


static PyObject *
dEploid_getLassoLibraryVertionStr(PyObject *self)
{
    return Py_BuildValue("s", LASSOVERSION);
}

static PyObject *
dEploid_getCompileTimeStr(PyObject *self)
{
    return Py_BuildValue("s", COMPILEDATE);
}


static PyMethodDef dEploid_methods[] = {
    {"add", (PyCFunction) dEploid_add, METH_VARARGS,
         "Print a lovely skit to standard output."},
    {"getLibraryVertionStr", (PyCFunction) dEploid_getLibraryVertionStr,
            METH_NOARGS, "Returns the version of the dEploid git version." },
    {"getLassoLibraryVertionStr", (PyCFunction) dEploid_getLassoLibraryVertionStr,
            METH_NOARGS, "Returns the version of the lasso git version." },
    {"getProgramVertionStr", (PyCFunction) dEploid_getProgramVertionStr,
            METH_NOARGS, "Returns the version of the dEploid C++ library." },
    {"getCompileTimeStr", (PyCFunction) dEploid_getCompileTimeStr,
            METH_NOARGS, "Returns the compilation time." },
    {NULL, NULL, 0, NULL}   /* sentinel */
};


static struct PyModuleDef dEploidmodule = {
    PyModuleDef_HEAD_INIT,
    "dEploid",
    NULL,
    -1,
    dEploid_methods,
};

PyMODINIT_FUNC
PyInit_dEploid(void)
{
    PyObject *module = PyModule_Create(&dEploidmodule);
    //Py_INCREF(&EmptyType);
    //PyModule_AddObject(module, "EmptyType", (PyObject *) &EmptyType);
    return module;
}
