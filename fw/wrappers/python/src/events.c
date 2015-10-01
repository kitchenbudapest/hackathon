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
            Py_XDECREF */

/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
/* Include standard headers */
#include <stdlib.h>
/*  func  : malloc
            free */

/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
/* Include jemalloc headers */
#include <jemalloc/jemalloc.h>

/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
/* Include kibu headers */
#include <kb/errors.h>
/*  type  : kb_Error
    const : kb_OKAY
            kb_ALLOC_FAIL
    func  : kb_Error_str */
#include <kb/rpi2/events.h>
/*  type  : kb_rpi2_Event
    func  : kb_rpi2_Event_ini
            kb_rpi2_Event_fin
            kb_rpi2_Event_active */

/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
/* Include kbpy headers */
#include "include/errors.h"
/*  const : kbpy_OKAY
            kbpy_FAIL
    value : kbpy_rpi2_INTERNAL_ERROR */
#include "include/types.h"
/*  type  : kbpy_rpi2_Event
            kbpy_rpi2_PyEvent
            kbpy_rpi2_Context
            kbpy_rpi2_PyContext */
#include "include/contexts.h"
/*  value : kbpy_rpi2_PyContextType */


/* Module level constants */
/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
#define OBJECT_NAME "kb.rpi2.Event"


/*----------------------------------------------------------------------------*/
static int
kbpy_rpi2_PyEvent_init(PyObject *self,
                       PyObject *args,
                       PyObject *kwargs)
{
    static char *kwlist[] = {"context", NULL};

    /* Unpack and store arguments */
    PyObject *py_context;
    if (!PyArg_ParseTupleAndKeywords(args,
                                     kwargs,
                                     "O:__init__",
                                     kwlist,
                                     &py_context))
        return kbpy_FAIL;

    /* If the given object is not a Context one */
    if (!PyObject_IsInstance(py_context, (PyObject *)&kbpy_rpi2_PyContextType))
    {
        PyErr_SetString(PyExc_TypeError,
                        "'" OBJECT_NAME ".__init__' first argument should be a "
                        "kb.rpi2.Context");
        return kbpy_FAIL;
    }

    /* Create new wrapped kibu Event */
    kbpy_rpi2_Event *kb_event;
    if (!(kb_event = malloc(sizeof(kbpy_rpi2_Event))))
    {
        PyErr_SetString(kbpy_rpi2_INTERNAL_ERROR, kb_Error_str(kb_ALLOC_FAIL));
        return kbpy_FAIL;
    }

    /* Initialize instamce as kibu Event */
    kb_Error error;
    switch ((error =
        kb_rpi2_Event_ini(
            (kb_rpi2_Event *const)kb_event,
            (kb_rpi2_Context *const)((kbpy_rpi2_PyContext *const)py_context)->kb_context)))
    {
        case kb_OKAY:
            break;

        default:
            free(kb_event);
            PyErr_SetString(kbpy_rpi2_INTERNAL_ERROR, kb_Error_str(error));
            return kbpy_FAIL;
    }

    /* Increase reference counter */
    Py_INCREF(py_context);

    /* Store the C reference */
    ((kbpy_rpi2_PyEvent *const)self)->kb_event = kb_event;
    /* Store the python reference */
    kb_event->py_event = (kbpy_rpi2_PyEvent *const)self;

    /* If everything went fine */
    return kbpy_OKAY;
}


/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
static void
kbpy_rpi2_PyEvent_dealloc(PyObject *self)
{
    /* Deconstruct kibu Event object */
    kb_rpi2_Event_fin(
        (kb_rpi2_Event *const)((kbpy_rpi2_PyEvent *const)self)->kb_event);
    /* Deallocate kibu Event object */
    free(((kbpy_rpi2_PyEvent *const)self)->kb_event);

    /* Free self as a python object */
    Py_TYPE(self)->tp_free(self);
}


/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
static PyObject*
kbpy_rpi2_PyEvent_activate(PyObject *self,
                           PyObject *args)
{
    Py_XDECREF(args);

    /* Call the original C function */
    kb_Error error;
    switch (
        (error = kb_rpi2_Event_activate(
            (kb_rpi2_Event *const)((kbpy_rpi2_PyEvent *const)self)->kb_event)))
    {
        /* If everything went fine */
        case kb_OKAY:
            Py_INCREF(Py_None);
            return Py_None;

        /* If there was a problem */
        default:
            PyErr_SetString(kbpy_rpi2_INTERNAL_ERROR, kb_Error_str(error));
            return (PyObject *)NULL;
    }
}


/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
static PyMethodDef kbpy_rpi2_PyEvent_methods[] =
{
    {
        .ml_name  = "activate",
        .ml_meth  = kbpy_rpi2_PyEvent_activate,
        .ml_flags = METH_NOARGS,
        .ml_doc   = "Deactivates previously activated Event object in Context "
                    "and activates this as current one. The activation is only "
                    "scheduled, will be fullfilled in the nearest cycle's end"
    },
    {NULL, NULL, 0, NULL},
};


/*----------------------------------------------------------------------------*/
PyDoc_STRVAR(kbpy_rpi2_PyEvent_doc,
             OBJECT_NAME " manages the kb.rpi2.Sensor objects and other "
             "internal values (such as pin usages, etc.)");

PyTypeObject kbpy_rpi2_PyEventType =
{
    PyObject_HEAD_INIT(NULL)
    .tp_name           = OBJECT_NAME,
    .tp_basicsize      = sizeof(kbpy_rpi2_PyEvent),
    .tp_itemsize       = 0,
    .tp_dealloc        = kbpy_rpi2_PyEvent_dealloc,
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
    .tp_doc            = kbpy_rpi2_PyEvent_doc,
    .tp_traverse       = 0,
    .tp_clear          = 0,
    .tp_richcompare    = 0,
    .tp_weaklistoffset = 0,
    .tp_iter           = 0,
    .tp_iternext       = 0,
    .tp_methods        = kbpy_rpi2_PyEvent_methods,
    .tp_members        = 0,
    .tp_getset         = 0,
    .tp_base           = 0,
    .tp_dict           = 0,
    .tp_descr_get      = 0,
    .tp_descr_set      = 0,
    .tp_dictoffset     = 0,
    .tp_init           = kbpy_rpi2_PyEvent_init,
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
