#include <Python.h>
#include "structmember.h" // fix something array have incomplete type
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



/*===================================================================
 * VcfReaderPy
 *===================================================================
 */

typedef struct {
    PyObject_HEAD
    bool locked;
    VcfReader *vcfreader;
} VcfReaderPy;


static int
VcfReaderPy_check_state(VcfReaderPy *self)
{
    int ret = 0;
    if (self->vcfreader == NULL) {
        PyErr_SetString(PyExc_SystemError, "VcfReaderPy not initialised");
        ret = -1;
    }
    return ret;
}

static void
VcfReaderPy_dealloc(VcfReaderPy* self)
{
    if (self->vcfreader != NULL) {
        //delete self->vcfreader;
        PyMem_Free(self->vcfreader);
        self->vcfreader = NULL;
    }
    Py_XDECREF(self->vcfreader);
    Py_TYPE(self)->tp_free((PyObject*)self);
}

static int
VcfReaderPy_init(VcfReaderPy *self, PyObject *args)
{
    int ret = -1;
    int err;

    int ok;
    char *s;
    ok = PyArg_ParseTuple(args, "s", &s);
    std::string filename(s);
    if (filename.size() > 0){
        self->vcfreader = new VcfReader(filename);
    }
    //static char *kwlist[] = {"tree_sequence", "ploidy", "contig_id", NULL};
    //unsigned int ploidy = 1;
    //const char *contig_id = "1";
    //TreeSequence *tree_sequence;

    //self->vcf_converter = NULL;
    //self->tree_sequence = NULL;
    //if (!PyArg_ParseTupleAndKeywords(args, kwds, "O!|Is", kwlist,
            //&TreeSequenceType, &tree_sequence, &ploidy, &contig_id)) {
        //goto out;
    //}
    //self->tree_sequence = tree_sequence;
    //Py_INCREF(self->tree_sequence);
    //if (TreeSequence_check_tree_sequence(self->tree_sequence) != 0) {
        //goto out;
    //}
    //if (ploidy < 1) {
        //PyErr_SetString(PyExc_ValueError, "Ploidy must be >= 1");
        //goto out;
    //}
    //if (strlen(contig_id) == 0) {
        //PyErr_SetString(PyExc_ValueError, "contig_id cannot be the empty string");
        //goto out;
    //}
    //self->vcf_converter = PyMem_Malloc(sizeof(vcf_converter_t));
    //if (self->vcf_converter == NULL) {
        //PyErr_NoMemory();
        //goto out;
    //}
    //err = vcf_converter_alloc(self->vcf_converter,
            //self->tree_sequence->tree_sequence, ploidy, contig_id);
    //if (err != 0) {
        //handle_library_error(err);
        //goto out;
    //}
    ret = 0;
//out:
    return ret;
}


static PyObject *
VcfReaderPy_get_header(VcfReaderPy *self)
{
    PyObject *ret = NULL;
    int err;
    char *header;

    if (VcfReaderPy_check_state(self) != 0) {
        goto out;
    }
    //err = vcf_converter_get_header(self->vcf_converter, &header);
    //if (err != 0) {
        //handle_library_error(err);
        //goto out;
    //}
    ret = Py_BuildValue("s", header);
out:
    return ret;
}


static PyMemberDef VcfReaderPy_members[] = {
    {NULL}  /* Sentinel */
};


static PyMethodDef VcfReaderPy_methods[] = {
    {"get_header", (PyCFunction) VcfReaderPy_get_header, METH_NOARGS,
            "Returns the VCF header as plain text." },
    {NULL}  /* Sentinel */
};

static PyTypeObject VcfReaderPyType = {
    PyVarObject_HEAD_INIT(NULL, 0)
    "_msprime.VcfReaderPy",             /* tp_name */
    sizeof(VcfReaderPy),             /* tp_basicsize */
    0,                         /* tp_itemsize */
    (destructor)VcfReaderPy_dealloc, /* tp_dealloc */
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
    Py_TPFLAGS_DEFAULT,        /* tp_flags */
    "VcfReaderPy objects",           /* tp_doc */
    0,                     /* tp_traverse */
    0,                     /* tp_clear */
    0,                     /* tp_richcompare */
    0,                     /* tp_weaklistoffset */
    0,                    /* tp_iter */
    0, /* tp_iternext */
    VcfReaderPy_methods,             /* tp_methods */
    VcfReaderPy_members,             /* tp_members */
    0,                         /* tp_getset */
    0,                         /* tp_base */
    0,                         /* tp_dict */
    0,                         /* tp_descr_get */
    0,                         /* tp_descr_set */
    0,                         /* tp_dictoffset */
    (initproc)VcfReaderPy_init,      /* tp_init */
    //0,                         /* tp_alloc */
    //Noddy_new,                 /* tp_new */
};













/*===================================================================
 * NoddyType
 *===================================================================
 */



typedef struct {
    PyObject_HEAD
    PyObject *first;
    PyObject *last;
    int number;
} Noddy;

static int
Noddy_traverse(Noddy *self, visitproc visit, void *arg)
{
    int vret;

    if (self->first) {
        vret = visit(self->first, arg);
        if (vret != 0)
            return vret;
    }
    if (self->last) {
        vret = visit(self->last, arg);
        if (vret != 0)
            return vret;
    }

    return 0;
}

static int
Noddy_clear(Noddy *self)
{
    PyObject *tmp;

    tmp = self->first;
    self->first = NULL;
    Py_XDECREF(tmp);

    tmp = self->last;
    self->last = NULL;
    Py_XDECREF(tmp);

    return 0;
}

static void
Noddy_dealloc(Noddy* self)
{
    Noddy_clear(self);
    Py_TYPE(self)->tp_free((PyObject*)self);
}

static PyObject *
Noddy_new(PyTypeObject *type, PyObject *args, PyObject *kwds)
{
    Noddy *self;

    self = (Noddy *)type->tp_alloc(type, 0);
    if (self != NULL) {
        self->first = PyUnicode_FromString("");
        if (self->first == NULL)
          {
            Py_DECREF(self);
            return NULL;
          }

        self->last = PyUnicode_FromString("");
        if (self->last == NULL)
          {
            Py_DECREF(self);
            return NULL;
          }

        self->number = 0;
    }

    return (PyObject *)self;
}

static int
Noddy_init(Noddy *self, PyObject *args, PyObject *kwds)
{
    PyObject *first=NULL, *last=NULL, *tmp;

    static char *kwlist[] = {"first", "last", "number", NULL};

    if (! PyArg_ParseTupleAndKeywords(args, kwds, "|OOi", kwlist,
                                      &first, &last,
                                      &self->number))
        return -1;

    if (first) {
        tmp = self->first;
        Py_INCREF(first);
        self->first = first;
        Py_XDECREF(tmp);
    }

    if (last) {
        tmp = self->last;
        Py_INCREF(last);
        self->last = last;
        Py_XDECREF(tmp);
    }

    return 0;
}


static PyMemberDef Noddy_members[] = {
    {"first", T_OBJECT_EX, offsetof(Noddy, first), 0,
     "first name"},
    {"last", T_OBJECT_EX, offsetof(Noddy, last), 0,
     "last name"},
    {"number", T_INT, offsetof(Noddy, number), 0,
     "noddy number"},
    {NULL}  /* Sentinel */
};

static PyObject *
Noddy_name(Noddy* self)
{
    static PyObject *format = NULL;
    PyObject *args, *result;

    if (format == NULL) {
        format = PyUnicode_FromString("%s %s");
        if (format == NULL)
            return NULL;
    }

    if (self->first == NULL) {
        PyErr_SetString(PyExc_AttributeError, "first");
        return NULL;
    }

    if (self->last == NULL) {
        PyErr_SetString(PyExc_AttributeError, "last");
        return NULL;
    }

    args = Py_BuildValue("OO", self->first, self->last);
    if (args == NULL)
        return NULL;

    result = PyUnicode_Format(format, args);
    Py_DECREF(args);

    return result;
}

static PyMethodDef Noddy_methods[] = {
    {"name", (PyCFunction)Noddy_name, METH_NOARGS,
     "Return the name, combining the first and last name"
    },
    {NULL}  /* Sentinel */
};

static PyTypeObject NoddyType = {
    PyObject_HEAD_INIT(NULL)
    "noddy.Noddy",             /* tp_name */
    sizeof(Noddy),             /* tp_basicsize */
    0,                         /* tp_itemsize */
    (destructor)Noddy_dealloc, /* tp_dealloc */
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
    Py_TPFLAGS_DEFAULT |
        Py_TPFLAGS_BASETYPE |
        Py_TPFLAGS_HAVE_GC,    /* tp_flags */
    "Noddy objects",           /* tp_doc */
    (traverseproc)Noddy_traverse,   /* tp_traverse */
    (inquiry)Noddy_clear,           /* tp_clear */
    0,		               /* tp_richcompare */
    0,		               /* tp_weaklistoffset */
    0,		               /* tp_iter */
    0,		               /* tp_iternext */
    Noddy_methods,             /* tp_methods */
    Noddy_members,             /* tp_members */
    0,                         /* tp_getset */
    0,                         /* tp_base */
    0,                         /* tp_dict */
    0,                         /* tp_descr_get */
    0,                         /* tp_descr_set */
    0,                         /* tp_dictoffset */
    (initproc)Noddy_init,      /* tp_init */
    0,                         /* tp_alloc */
    Noddy_new,                 /* tp_new */
};






/*
 * dEploid_methods initialization
 */

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



#if PY_MAJOR_VERSION >= 3
#define INITERROR return NULL
#else
#define INITERROR return
#endif

PyMODINIT_FUNC
PyInit_dEploid(void)
{
    PyObject *module = PyModule_Create(&dEploidmodule);

    /* VcfReaderPyType type */
    VcfReaderPyType.tp_new = PyType_GenericNew;
    if (PyType_Ready(&VcfReaderPyType) < 0) {
        INITERROR;
    }
    Py_INCREF(&VcfReaderPyType);
    PyModule_AddObject(module, "VcfReaderPyType", (PyObject *) &VcfReaderPyType);


    /* NoddyType type */
    NoddyType.tp_new = PyType_GenericNew;
    if (PyType_Ready(&NoddyType) < 0) {
        INITERROR;
    }
    Py_INCREF(&NoddyType);
    PyModule_AddObject(module, "NoddyType", (PyObject *) &NoddyType);

    return module;
}
