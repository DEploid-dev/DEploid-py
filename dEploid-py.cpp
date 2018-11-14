#include <Python.h>
#include "structmember.h" // fix something array have incomplete type
#include <string>  /* string */
#include <exception>
#include <stdexcept>

#include "lib/src/vcfReader.hpp"


#define MODULE_DOC \
"Low level interface for msprime"


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






PyObject* vectorToList_Double(const vector<double> &data) {
    PyObject* listObj = PyList_New( data.size() );
    if (!listObj) throw std::logic_error("Unable to allocate memory for Python list");
    for (unsigned int i = 0; i < data.size(); i++) {
        PyObject *num = PyFloat_FromDouble( (double) data[i]);
        if (!num) {
            Py_DECREF(listObj);
            throw std::logic_error("Unable to allocate memory for Python list");
        }
        PyList_SET_ITEM(listObj, i, num);
    }
    return listObj;
}


PyObject* vectorToList_Str(const vector<string> &data) {
    PyObject* listObj = PyList_New( data.size() );
    if (!listObj) throw std::logic_error("Unable to allocate memory for Python list");
    for (unsigned int i = 0; i < data.size(); i++) {
        PyObject *s = Py_BuildValue("s", data[i].c_str());
        PyList_SET_ITEM(listObj, i, s);
    }
    return listObj;
}


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
        self->vcfreader->finalize();
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
VcfReaderPy_get_vcfheader(VcfReaderPy *self)
{
    PyObject *ret = NULL;
    if (VcfReaderPy_check_state(self) != 0) {
        goto out;
    }
    ret = vectorToList_Str(self->vcfreader->headerLines);
out:
    return ret;
}


static PyObject *
VcfReaderPy_get_vqslod(VcfReaderPy *self)
{
    PyObject *ret = NULL;
    if (VcfReaderPy_check_state(self) != 0) {
        goto out;
    }
    ret = vectorToList_Double(self->vcfreader->vqslod);
out:
    return ret;
}


static PyObject *
VcfReaderPy_get_refcount(VcfReaderPy *self)
{
    PyObject *ret = NULL;
    if (VcfReaderPy_check_state(self) != 0) {
        goto out;
    }
    ret = vectorToList_Double(self->vcfreader->refCount);
out:
    return ret;
}


static PyObject *
VcfReaderPy_get_altcount(VcfReaderPy *self)
{
    PyObject *ret = NULL;
    if (VcfReaderPy_check_state(self) != 0) {
        goto out;
    }
    ret = vectorToList_Double(self->vcfreader->altCount);
out:
    return ret;
}


static PyMemberDef VcfReaderPy_members[] = {
    {NULL}  /* Sentinel */
};


static PyMethodDef VcfReaderPy_methods[] = {
    {"get_vcfheader", (PyCFunction) VcfReaderPy_get_vcfheader, METH_NOARGS,
            "Returns the VCF header as plain text." },
    {"get_refCount", (PyCFunction) VcfReaderPy_get_refcount, METH_NOARGS,
            "Returns VCF reference allele count." },
    {"get_altCount", (PyCFunction) VcfReaderPy_get_altcount, METH_NOARGS,
            "Returns VCF alternative allele count." },
    {"get_vqslod", (PyCFunction) VcfReaderPy_get_vqslod, METH_NOARGS,
            "Returns VCF SNP VQSLOD scores." },
    {NULL}  /* Sentinel */
};


static PyTypeObject Vcf = {
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
    {NULL}        /* Sentinel */
};




#if PY_MAJOR_VERSION >= 3

static struct PyModuleDef dEploidmodule = {
    PyModuleDef_HEAD_INIT,
    "_dEploid",
    MODULE_DOC,
    -1,
    dEploid_methods,
    NULL, NULL, NULL, NULL
};

#define INITERROR return NULL

PyMODINIT_FUNC
PyInit__dEploid(void)

#else
#define INITERROR return

void
init__dEploid(void)
#endif
{
#if PY_MAJOR_VERSION >= 3
    PyObject *module = PyModule_Create(&dEploidmodule);
#else
    PyObject *module = Py_InitModule3("_dEploid", dEploid_methods, MODULE_DOC);
#endif

    /* Vcf type */
    Vcf.tp_new = PyType_GenericNew;
    if (PyType_Ready(&Vcf) < 0) {
        INITERROR;
    }
    Py_INCREF(&Vcf);
    PyModule_AddObject(module, "Vcf", (PyObject *) &Vcf);


    ///* NoddyType type */
    //NoddyType.tp_new = PyType_GenericNew;
    //if (PyType_Ready(&NoddyType) < 0) {
        //INITERROR;
    //}
    //Py_INCREF(&NoddyType);
    //PyModule_AddObject(module, "NoddyType", (PyObject *) &NoddyType);

#if PY_MAJOR_VERSION >= 3
    return module;
#endif
}
