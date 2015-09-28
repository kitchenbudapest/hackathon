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
