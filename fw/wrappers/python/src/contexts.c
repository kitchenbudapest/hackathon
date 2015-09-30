/* INFO **
** INFO */

/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
/* Include python headers
   Since Python may define some pre-processor definitions which affect the
   standard headers on some systems, you must include Python.h before any
   standard headers are included */
#include <Python.h>
/*  type  : PyObject
    macro : Py_TYPE
            Py_XDECREF
            PyObject_HEAD */

/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
/* Include standard headers */
#include <stdio.h>
/*
    func  : fputs

/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
/* Include kibu headers */
#include <kb/errors.h>
/*  type  : kb_Error
    const : kb_OKAY
            kb_ALLOC_FAIL
            kb_SELF_IS_NULL */
#include <kb/rpi2/contexts.h>
/*  type  : kb_rpi2_Context
    func  :


/* Module level constants */
/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
#define PYTHON_RETURN_VALUE_SUCCESS  0
#define PYTHON_RETURN_VALUE_FAILURE -1

/*----------------------------------------------------------------------------*/
typedef struct
{
    PyObject_HEAD
    kb_rpi2_Context *context;
    PyObject        *on_start;
    PyObject        *on_stop;
    PyObject        *on_exit;
    PyObject        *on_cycle_begin;
    PyObject        *on_cycle_end;
    PyObject        *on_activate;
} kbpy_rpi2_Context;


/*----------------------------------------------------------------------------*/
kb_Error
kbpy_rpi2_Context_on_start(kb_rpi2_Context *const context,
                           kb_rpi2_Event   *const event)
{
    return kb_OKAY;
}


/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
static int
kbpy_rpi2_Context_init(kbpy_rpi2_Context *self,
                       PyObject          *args,
                       PyObject          *kwargs)
{
    (void)args;
    (void)kwargs;
    switch (kb_rpi2_Context_ini(self->context));
    {
        case kb_OKAY:
            return PYTHON_RETURN_VALUE_SUCCESS;

        case kb_ALLOC_FAIL:
            fputs("kbpy: Allocation of kb.rpi2.Context failed\n", stderr);
            return PYTHON_RETURN_VALUE_FAILURE;

        case kb_SELF_IS_NULL:
            fputs("kbpy: Initialization of kb.rpi2.Context failed", stderr);
            return PYTHON_RETURN_VALUE_FAILURE;
    }
}


/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
static void
kbpy_rpi2_Context_dealloc(kbpy_rpi2_Context *self)
{
    /* Decrease internal python object references */
    Py_XDECREF(self->on_start);
    Py_XDECREF(self->on_stop);
    Py_XDECREF(self->on_exit);
    Py_XDECREF(self->on_cycle_begin);
    Py_XDECREF(self->on_cycle_end);
    Py_XDECREF(self->on_activate);

    /* Deconstruct kibu Context object */
    kb_rpi2_Context_fin(self->context);

    /* Free self as a python object */
    Py_TYPE(self)->tp_free((PyObject *)self);
}


/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
static PyObject*
kbpy_rpi2_Context_on_start_getter(PyObject*,
                                  void*)
{

}


/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
static int
kbpy_rpi2_Context_on_start_setter(PyObject*,
                                  PyObject*,
                                  void*)
{

}


/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
// https://docs.python.org/3/c-api/typeobj.html#c.PyTypeObject.tp_getset
static PyGetSetDef kbpy_rpi2_Context_getters_setters[] =
{
    {
        .name = "on_start",
        .get  = (getter)kbpy_rpi2_Context_on_start_getter,
        .set  = (setter)kbpy_rpi2_Context_on_start_setter,
        .doc  = "Called once, before the event loop starts",
        .closure = NULL
    },
};



/*----------------------------------------------------------------------------*/
PyDoc_STRVAR(kbpy_rpi2_Context_doc,
             "kb.rpi2.Context docstring");

static PyTypeObject kbpy_rpi2_ContextType =
{
    PyObject_HEAD_INIT(NULL)
    .tp_name           = "kb.rpi2.Context",
    .tp_basicsize      = sizeof(kbpy_rpi2_Context),
    .tp_itemsize       = 0,
    .tp_dealloc        = (destructor)kbpy_rpi2_Context_dealloc,
    .tp_print          = 0,
    .tp_getattr        = 0,
    .tp_setattr        = 0,
    .tp_reserved       = 0,
    .tp_repr           = 0,
    .tp_as_number      = 0,
    .tp_as_sequence    = 0,
    .tp_as_mapping     = 0,
    .tp_hash           = 0,
    .tp_call           = 0,
    .tp_str            = 0,
    .tp_getattro       = 0,
    .tp_setattro       = 0,
    .tp_as_buffer      = 0,
    .tp_flags          = Py_TPFLAGS_DEFAULT |
                         Py_TPFLAGS_BASETYPE, /* Can be subtyped */
    .tp_doc            = kbpy_rpi2_Context_doc,
    .tp_traverse       = 0,
    .tp_clear          = 0,
    .tp_richcompare    = 0,
    .tp_weaklistoffset = 0,
    .tp_iter           = 0,
    .tp_iternext       = 0,
    .tp_methods        = 0,
    .tp_members        = 0,
    .tp_getset         = 0,
    .tp_base           = 0,
    .tp_dict           = 0,
    .tp_descr_get      = 0,
    .tp_descr_set      = 0,
    .tp_dictoffset     = 0,
    .tp_init           = (initproc)kbpy_rpi2_Context_init,
    .tp_alloc          = 0,
    .tp_new            = PyType_GenericNew,
    // .tp_free           = 0,
    // .tp_is_gc          = 0,
    // .tp_bases          = 0,
    // .tp_mro            = 0,
    // .tp_cache          = 0,
    // .tp_subclasses     = 0,
    // .tp_weaklist       = 0,
    // .tp_del            = 0,
    // .tp_version_tag    = 0,
    // .tp_finalize       = 0,
};
