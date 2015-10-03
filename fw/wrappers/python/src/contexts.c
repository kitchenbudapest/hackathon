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
    func  : kb_Error_str */
#include <kb/rpi2/contexts.h>
/*  type  : kb_rpi2_Context
    func  : kb_rpi2_Context_ini
            kb_rpi2_Context_fin */

/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
/* Include kbpy headers */
#include "include/errors.h"
/*  const : kbpy_OKAY
            kbpy_FAIL
    value : kbpy_rpi2_INTERNAL_ERROR */
#include "include/types.h"
/*  type  : kbpy_rpi2_Context
            kbpy_rpi2_PyContext
            kbpy_rpi2_Event */


/* Module level constants */
/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
#define OBJECT_NAME "kb.rpi2.Context"


/*----------------------------------------------------------------------------*/
static int
kbpy_rpi2_PyContext_init(PyObject *self,
                         PyObject *args,
                         PyObject *kwargs)
{
    /* If any arguments passed */
    if ((PyObject_Length(args) > (Py_ssize_t)1) || kwargs)
    {
            PyErr_SetString(PyExc_TypeError,
                            "__init__() takes 1 positional argument but more "
                            "were given");
            return kbpy_FAIL;
    }

    /* Create new wrapped kibu Context */
    kbpy_rpi2_Context *kb_context;
    if (!(kb_context = malloc(sizeof(kbpy_rpi2_Context))))
    {
        PyErr_SetString(kbpy_rpi2_INTERNAL_ERROR, kb_Error_str(kb_ALLOC_FAIL));
        return kbpy_FAIL;
    }

    /* Initialize instance as kibu Context */
    kb_Error error;
    switch ((error = kb_rpi2_Context_ini((kb_rpi2_Context *const)kb_context)))
    {
        case kb_OKAY:
            break;

        default:
            free(kb_context);
            PyErr_SetString(kbpy_rpi2_INTERNAL_ERROR, kb_Error_str(error));
            return kbpy_FAIL;
    }

    /* Store the C reference */
    ((kbpy_rpi2_PyContext *const)self)->kb_context = kb_context;
    /* Store the python reference */
    kb_context->py_context = (kbpy_rpi2_PyContext *const)self;

    /* Initialize callbacks */
    ((kbpy_rpi2_PyContext *const)self)->on_start       = NULL;
    ((kbpy_rpi2_PyContext *const)self)->on_stop        = NULL;
    ((kbpy_rpi2_PyContext *const)self)->on_exit        = NULL;
    ((kbpy_rpi2_PyContext *const)self)->on_cycle_begin = NULL;
    ((kbpy_rpi2_PyContext *const)self)->on_cycle_end   = NULL;
    ((kbpy_rpi2_PyContext *const)self)->on_activate    = NULL;

    /* If everything went fine */
    return kbpy_OKAY;
}


/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
static void
kbpy_rpi2_PyContext_dealloc(PyObject *self)
{
    /* Decrease internal python object references */
    Py_XDECREF(((kbpy_rpi2_PyContext *const)self)->on_start);
    Py_XDECREF(((kbpy_rpi2_PyContext *const)self)->on_stop);
    Py_XDECREF(((kbpy_rpi2_PyContext *const)self)->on_exit);
    Py_XDECREF(((kbpy_rpi2_PyContext *const)self)->on_cycle_begin);
    Py_XDECREF(((kbpy_rpi2_PyContext *const)self)->on_cycle_end);
    Py_XDECREF(((kbpy_rpi2_PyContext *const)self)->on_activate);

    /* Deconstruct kibu Context object */
    kb_rpi2_Context_fin(
        (kb_rpi2_Context *const)((kbpy_rpi2_PyContext *const)self)->kb_context);
    /* Deallocate kibu Context object */
    free(((kbpy_rpi2_PyContext *const)self)->kb_context);

    /* Free self as a python object */
    Py_TYPE(self)->tp_free(self);
}


/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
static PyObject*
kbpy_rpi2_PyContext_call(PyObject *self,
                         PyObject *args,
                         PyObject *kwargs)
{
    static char *kwlist[] = {"callback", NULL};

    /* Unpack and store arguments */
    PyObject *name,
             *callback;
    if (!PyArg_ParseTupleAndKeywords(args,
                                     kwargs,
                                     "O:__call__",
                                     kwlist,
                                     &callback))
    {
        PyErr_SetString(PyExc_AttributeError,
                        "The argument of '" OBJECT_NAME "' should be a single "
                        "object");
        return (PyObject *)NULL;
    }

    /* Try to get name attribute of the given object */
    if (!(name = PyObject_GetAttrString(callback, "__name__")))
    {
        PyErr_SetString(PyExc_AttributeError,
                        "The attributes of '" OBJECT_NAME "' object should "
                        "have a '__name__' attribute");
        return (PyObject *)NULL;
    }

    /* Try to store the given object to instance */
    if (PyObject_SetAttr(self, name, callback))
    {
        PyErr_SetString(PyExc_AttributeError, "Cannot set attribute");
        return (PyObject *)NULL;
    }

    /* If everything went fine */
    Py_INCREF(callback);
    return callback;
}


/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
#define CALLBACK_SETTER_GETTER_WRAPPER(C_NAME, PY_NAME)                        \
    static kb_Error                                                            \
    kbpy_rpi2_PyContext_##C_NAME(kb_rpi2_Context *const context,               \
                                 kb_rpi2_Event   *const event)                 \
    {                                                                          \
        PyObject *args,                                                        \
                 *result;                                                      \
                                                                               \
        /* Build arguments for the callback function */                        \
        args = Py_BuildValue("(OO)",                                           \
                             ((kbpy_rpi2_Context *const)context)->py_context,  \
                             ((kbpy_rpi2_Event   *const)event)->py_event);     \
                                                                               \
        /* Invoke callback function and check its return value */              \
        result =                                                               \
            PyObject_CallObject(                                               \
                ((kbpy_rpi2_Context *const)context)->py_context->C_NAME,       \
                args);                                                         \
        if (PyObject_IsTrue(result))                                           \
            return kb_FAIL;                                                    \
        /* If everything went fine */                                          \
        return kb_OKAY;                                                        \
    }                                                                          \
    /*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -*/\
    static PyObject*                                                           \
    kbpy_rpi2_PyContext_##C_NAME##_getter(PyObject *self,                      \
                                          void     *closure)                   \
    {                                                                          \
        (void)closure;                                                         \
                                                                               \
        /* If instance does not have an `C_NAME` callback */                   \
        if (!((kbpy_rpi2_PyContext *const)self)->C_NAME)                       \
        {                                                                      \
            PyErr_SetString(PyExc_AttributeError,                              \
                            "'" OBJECT_NAME "' object has no attribute "       \
                            "'" PY_NAME "'");                                  \
            return (PyObject *)NULL;                                           \
        }                                                                      \
        /* If instance has an `C_NAME` callback */                             \
        Py_INCREF(((kbpy_rpi2_PyContext *const)self)->C_NAME);                 \
        return ((kbpy_rpi2_PyContext *const)self)->C_NAME;                     \
    }                                                                          \
    /*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -*/\
    static int                                                                 \
    kbpy_rpi2_PyContext_##C_NAME##_setter(PyObject *self,                      \
                                          PyObject *C_NAME,                    \
                                          void     *closure)                   \
    {                                                                          \
        (void)closure;                                                         \
                                                                               \
        /* If the given object is not a function-like one */                   \
        if (!PyCallable_Check(C_NAME))                                         \
        {                                                                      \
            Py_INCREF(PyExc_TypeError);                                        \
            PyErr_SetString(PyExc_TypeError,                                   \
                            "'" OBJECT_NAME "."                                \
                            PY_NAME "' has to be callable");                   \
            return kbpy_FAIL;                                                  \
        }                                                                      \
        /* If the given object is a function-like one */                       \
        Py_XDECREF(((kbpy_rpi2_PyContext *const)self)->C_NAME);                \
        Py_INCREF(C_NAME);                                                     \
        ((kbpy_rpi2_PyContext *const)self)->C_NAME = C_NAME;                   \
                                                                               \
        /* Bind C wrappered python function to kibu Context */                 \
        kb_rpi2_Context_bind_##C_NAME(                                         \
            (kb_rpi2_Context *const)(                                          \
                (kbpy_rpi2_PyContext *const)self)->kb_context,                 \
            kbpy_rpi2_PyContext_##C_NAME);                                     \
                                                                               \
        /* If everything went fine */                                          \
        return kbpy_OKAY;                                                      \
    }
/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
CALLBACK_SETTER_GETTER_WRAPPER(on_start      , "on_start")
CALLBACK_SETTER_GETTER_WRAPPER(on_stop       , "on_stop")
CALLBACK_SETTER_GETTER_WRAPPER(on_cycle_begin, "on_cycle_begin")
CALLBACK_SETTER_GETTER_WRAPPER(on_cycle_end  , "on_cycle_end")
CALLBACK_SETTER_GETTER_WRAPPER(on_exit       , "on_exit")
#undef CALLBACK_SETTER_GETTER_WRAPPER


/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
#define CALLBACK_SETTER_GETTER_WRAPPER_DEF(C_NAME, PY_NAME, PY_DOC)            \
    {                                                                          \
        .name    = PY_NAME,                                                    \
        .get     = (getter)kbpy_rpi2_PyContext_##C_NAME##_getter,              \
        .set     = (setter)kbpy_rpi2_PyContext_##C_NAME##_setter,              \
        .doc     = PY_DOC,                                                     \
        .closure = NULL                                                        \
    }
/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
static PyGetSetDef kbpy_rpi2_PyContext_getters_setters[] =
{
    CALLBACK_SETTER_GETTER_WRAPPER_DEF(
        on_start,
        "on_start",
        "Called once, right before the event loop starts"),
    CALLBACK_SETTER_GETTER_WRAPPER_DEF(
        on_stop,
        "on_stop",
        "Called once, right after the event loop stops"),
    CALLBACK_SETTER_GETTER_WRAPPER_DEF(
        on_cycle_begin,
        "on_cycle_begin",
        "Called at the beginning of every cycle of the event loop"),
    CALLBACK_SETTER_GETTER_WRAPPER_DEF(
        on_cycle_end,
        "on_cycle_end",
        "Called at the end of every cycle of the event loop"),
    CALLBACK_SETTER_GETTER_WRAPPER_DEF(
        on_exit,
        "on_exit",
        "Called before the program terminates"),
    {NULL, NULL, NULL, NULL, NULL},
};
#undef CALLBACK_SETTER_GETTER_WRAPPER_DEF


/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
#define METHOD(C_NAME)                                                         \
    static PyObject*                                                           \
    kbpy_rpi2_PyContext_##C_NAME(PyObject *self,                               \
                                 PyObject *args)                               \
    {                                                                          \
        Py_XDECREF(args);                                                      \
                                                                               \
        /* Call the original C function */                                     \
        kb_Error error;                                                        \
        switch (                                                               \
            (error = kb_rpi2_Context_##C_NAME(                                 \
                (kb_rpi2_Context *const)(                                      \
                    (kbpy_rpi2_PyContext *const)self)->kb_context)))           \
        {                                                                      \
            /* If everything went fine */                                      \
            case kb_OKAY:                                                      \
                Py_INCREF(Py_None);                                            \
                return Py_None;                                                \
                                                                               \
            /* If there was a problem */                                       \
            default:                                                           \
                PyErr_SetString(kbpy_rpi2_INTERNAL_ERROR, kb_Error_str(error));\
                return (PyObject *)NULL;                                       \
        }                                                                      \
    }
/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
METHOD(start)
METHOD(stop)
METHOD(exit)
#undef METHOD


/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
#define METHOD_DEF(C_NAME, PY_NAME, PY_DOC)                                    \
    {                                                                          \
        .ml_name  = PY_NAME,                                                   \
        .ml_meth  = kbpy_rpi2_PyContext_##C_NAME,                              \
        .ml_flags = METH_NOARGS,                                               \
        .ml_doc   = PY_DOC                                                     \
    }
/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
static PyMethodDef kbpy_rpi2_PyContext_methods[] =
{
    METHOD_DEF(
        start,
        "start",
        "Enters event loop. This function only returns when kb.rpi2.Context."
        "stop or kb.rpi2.Context.exit methods called directly or any of the "
        "callbacks return an object which boolean value is True"),
    METHOD_DEF(
        stop,
        "stop",
        "Schedule a stop at the end of the nearest cycle's end"),
    METHOD_DEF(
        exit,
        "exit",
        "Schedule program termination at the end of the nearest cycle's end"),
    {NULL, NULL, 0, NULL}
};
#undef METHOD_DEF


/*----------------------------------------------------------------------------*/
PyDoc_STRVAR(kbpy_rpi2_PyContext_doc,
             OBJECT_NAME " manages the kb.rpi2.Event objects and handles the"
             " event loop.");

PyTypeObject kbpy_rpi2_PyContextType =
{
    PyObject_HEAD_INIT(NULL)
    .tp_name           = OBJECT_NAME,
    .tp_basicsize      = sizeof(kbpy_rpi2_PyContext),
    .tp_itemsize       = 0,
    .tp_dealloc        = kbpy_rpi2_PyContext_dealloc,
    .tp_print          = 0,
    .tp_getattr        = 0,
    .tp_setattr        = 0,
    .tp_as_async       = 0, // tp_reserved in python3.4
    .tp_repr           = 0,
    .tp_as_number      = 0,
    .tp_as_sequence    = 0,
    .tp_as_mapping     = 0,
    .tp_hash           = 0,
    .tp_call           = kbpy_rpi2_PyContext_call,
    .tp_str            = 0,
    .tp_getattro       = 0,
    .tp_setattro       = 0,
    .tp_as_buffer      = 0,
    .tp_flags          = Py_TPFLAGS_DEFAULT |
                         Py_TPFLAGS_BASETYPE, /* Can be subtyped */
    .tp_doc            = kbpy_rpi2_PyContext_doc,
    .tp_traverse       = 0,
    .tp_clear          = 0,
    .tp_richcompare    = 0,
    .tp_weaklistoffset = 0,
    .tp_iter           = 0,
    .tp_iternext       = 0,
    .tp_methods        = kbpy_rpi2_PyContext_methods,
    .tp_members        = 0,
    .tp_getset         = kbpy_rpi2_PyContext_getters_setters,
    .tp_base           = 0,
    .tp_dict           = 0,
    .tp_descr_get      = 0,
    .tp_descr_set      = 0,
    .tp_dictoffset     = 0,
    .tp_init           = kbpy_rpi2_PyContext_init,
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
