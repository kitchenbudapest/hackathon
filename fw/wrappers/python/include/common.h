/* INFO **
** INFO */

/* Header guard */
#ifndef KBPY_RPI2_SENSORS_COMMON_H_4548327730281795
#define KBPY_RPI2_SENSORS_COMMON_H_4548327730281795 1

/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
/* Include python headers
   Since Python may define some pre-processor definitions which affect the
   standard headers on some systems, you must include Python.h before any
   standard headers are included */
#include <Python.h>
/*  type  : PyObject */


/*----------------------------------------------------------------------------*/
#define KBPY_RPI2_SENSORS_COMMON_TYPE(C_STRUCT,                                \
                                      C_NAME,                                  \
                                      C_MACRO,                                 \
                                      CALLBACKS)                               \
    /*-----------------------------------------------------------------------*/\
    /* Forward declarations to avoid circular dependencies */                  \
    struct kbpy_rpi2_sensors_##C_STRUCT;                                       \
    struct kbpy_rpi2_sensors_py_##C_STRUCT;                                    \
                                                                               \
    /*-----------------------------------------------------------------------*/\
    typedef struct kbpy_rpi2_sensors_##C_STRUCT                                \
    {                                                                          \
        KB_RPI2_SENSORS_##C_MACRO##_MEMBERS()                                  \
        struct kbpy_rpi2_sensors_py_##C_STRUCT *py_sensor;                     \
    } kbpy_rpi2_sensors_##C_NAME;                                              \
    /*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -*/\
    typedef struct kbpy_rpi2_sensors_py_##C_STRUCT                             \
    {                                                                          \
        PyObject_HEAD                                                          \
        struct kbpy_rpi2_sensors_##C_STRUCT *kb_sensor;                        \
        PyObject                            *on_enable;                        \
        PyObject                            *on_disable;                       \
        CALLBACKS                                                              \
    } kbpy_rpi2_sensors_Py##C_NAME;


/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
/* Has to be the second argument of DEALLOC macro */
#define KBPY_RPI2_SENSORS_XDECREF_CALLBACK_MEMBER(C_NAME, C_FUNC)              \
    Py_XDECREF(((kbpy_rpi2_sensors_Py##C_NAME *const)self)->C_FUNC)


/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
#define KBPY_RPI2_SENSORS_COMMON_DEALLOC(C_NAME,                               \
                                         XDECREF_MEMBERS)                      \
    static void                                                                \
    kbpy_rpi2_sensors_Py##C_NAME##_dealloc(PyObject *self)                     \
    {                                                                          \
        /* Decrease internal python object references */                       \
        XDECREF_MEMBERS                                                        \
                                                                               \
        /* Deconstruct kibu LED object */                                      \
        kb_rpi2_sensors_##C_NAME##_fin(                                        \
            (kb_rpi2_sensors_##C_NAME *const)(                                 \
                (kbpy_rpi2_sensors_Py##C_NAME *const)self)->kb_sensor);        \
        /* Deallocate kibu LED object */                                       \
        free(((kbpy_rpi2_sensors_Py##C_NAME *const)self)->kb_sensor);          \
                                                                               \
        /* Free self as a python object */                                     \
        Py_TYPE(self)->tp_free(self);                                          \
    }


/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
#define KBPY_RPI2_SENSORS_COMMON_CALL(C_NAME)                                  \
    static PyObject*                                                           \
    kbpy_rpi2_sensors_Py##C_NAME##_call(PyObject *self,                        \
                                        PyObject *args,                        \
                                        PyObject *kwargs)                      \
    {                                                                          \
        static char *kwlist[] = {"callback", NULL};                            \
                                                                               \
        /* Unpack and store arguments */                                       \
        PyObject *name,                                                        \
                 *callback;                                                    \
        if (!PyArg_ParseTupleAndKeywords(args,                                 \
                                         kwargs,                               \
                                         "O:__call__",                         \
                                         kwlist,                               \
                                         &callback))                           \
        {                                                                      \
            PyErr_SetString(PyExc_AttributeError,                              \
                            "The argument of 'kb.rpi2.sensors." #C_NAME        \
                            "' should be a single object");                    \
            return (PyObject *)NULL;                                           \
        }                                                                      \
                                                                               \
        /* Try to get name attribute of the given object */                    \
        if (!(name = PyObject_GetAttrString(callback, "__name__")))            \
        {                                                                      \
            PyErr_SetString(PyExc_AttributeError,                              \
                            "The attributes of 'kb.rpi2.sensors." #C_NAME      \
                            "' object should have a '__name__' attribute");    \
            return (PyObject *)NULL;                                           \
        }                                                                      \
                                                                               \
        /* Try to store the given object to instance */                        \
        if (PyObject_SetAttr(self, name, callback))                            \
        {                                                                      \
            PyErr_SetString(PyExc_AttributeError, "Cannot set attribute");     \
            return (PyObject *)NULL;                                           \
        }                                                                      \
                                                                               \
        /* If everything went fine */                                          \
        Py_INCREF(callback);                                                   \
        return callback;                                                       \
    }

/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
#define KBPY_RPI2_SENSORS_COMMON_CALLBACK_SETTER_GETTER_WRAPPER(C_NAME,        \
                                                                C_FUNC)        \
    static kb_Error                                                            \
    kbpy_rpi2_sensors_Py##C_NAME##_##C_FUNC(kb_rpi2_Sensor  *const sensor,     \
                                            kb_rpi2_Event   *const event,      \
                                            kb_rpi2_Context *const context)    \
    {                                                                          \
        PyObject *args,                                                        \
                 *result;                                                      \
                                                                               \
        /* Build arguments for the callback function */                        \
        args = Py_BuildValue(                                                  \
            "(OOO)",                                                           \
            ((kbpy_rpi2_sensors_##C_NAME *const)sensor)->py_sensor,            \
            ((kbpy_rpi2_Event *const)event)->py_event,                         \
            ((kbpy_rpi2_Context *const)context)->py_context);                  \
                                                                               \
        /* Invoke callback function and check its return value */              \
        result =                                                               \
            PyObject_CallObject(                                               \
                ((kbpy_rpi2_sensors_#C_NAME *const)sensor)->py_sensor->C_FUNC, \
                args);                                                         \
        if (PyObject_IsTrue(result))                                           \
            return kb_FAIL;                                                    \
        /* If everything went fine */                                          \
        return kb_OKAY;                                                        \
    }                                                                          \
    /*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -*/\
    static PyObject*                                                           \
    kbpy_rpi2_sensors_Py##C_NAME##_##C_FUNC##_getter(PyObject *self,           \
                                                     void     *closure)        \
    {                                                                          \
        (void)closure;                                                         \
                                                                               \
        /* If instance does not have an `C_NAME` callback */                   \
        if (!((kbpy_rpi2_sensors_Py##C_NAME *const)self)->C_FUNC)              \
        {                                                                      \
            PyErr_SetString(PyExc_AttributeError,                              \
                            "'kb.rpi2.sensors." #C_NAME "' object has no "     \
                            "attribute '" #C_FUNC "'");                        \
            return (PyObject *)NULL;                                           \
        }                                                                      \
        /* If instance has an `C_FUNC` callback */                             \
        Py_INCREF(((kbpy_rpi2_sensors_Py##C_NAME *const)self)->C_FUNC);        \
        return ((kbpy_rpi2_sensors_Py##C_NAME *const)self)->C_FUNC;            \
    }                                                                          \
    /*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -*/\
    static int                                                                 \
    kbpy_rpi2_sensors_Py##C_NAME##_##C_FUNC##_setter(PyObject *self,           \
                                                     PyObject *C_FUNC,         \
                                                     void     *closure)        \
    {                                                                          \
        (void)closure;                                                         \
                                                                               \
        /* If the given object is not a function-like one */                   \
        if (!PyCallable_Check(C_FUNC))                                         \
        {                                                                      \
            Py_INCREF(PyExc_TypeError);                                        \
            PyErr_SetString(PyExc_TypeError,                                   \
                            "'" OBJECT_NAME "."                                \
                            PY_NAME "' has to be callable");                   \
            return kbpy_FAIL;                                                  \
        }                                                                      \
        /* If the given object is a function-like one */                       \
        Py_XDECREF(((kbpy_rpi2_sensors_Py##C_NAME *const)self)->C_FUNC);       \
        Py_INCREF(C_FUNC);                                                     \
        ((kbpy_rpi2_sensors_Py##C_NAME *const)self)->C_FUNC = C_FUNC;          \
                                                                               \
        /* Bind C wrappered python function to kibu Context */                 \
        kb_rpi2_sensors_##C_NAME##_bind_##C_FUNC(                              \
            (kb_rpi2_sensors_##C_NAME *const)(                                 \
                (kbpy_rpi2_sensors_Py##C_NAME *const)self)->kb_sensor,         \
            kbpy_rpi2_sensors_Py##C_NAME##_##C_FUNC);                          \
                                                                               \
        /* If everything went fine */                                          \
        return kbpy_OKAY;                                                      \
    }


/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
#define KBPY_RPI2_SENSORS_COMMON_CALLBACK_SETTER_GETTER_WRAPPER_DEF(C_NAME,    \
                                                                    C_FUNC,    \
                                                                    PY_DOC)    \
    {                                                                          \
        .name    = #C_FUNC,                                                    \
        .get     = kbpy_rpi2_sensors_Py##C_NAME##_##C_FUNC##_getter,           \
        .set     = kbpy_rpi2_sensors_Py##C_NAME##_##C_FUNC##_setter,           \
        .doc     = PY_DOC,                                                     \
        .closure = NULL                                                        \
    }


/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
#define KBPY_RPI2_SENSORS_COMMON_SIMPLE_METHOD(C_NAME,                         \
                                               C_FUNC)                         \
    static PyObject*                                                           \
    kbpy_rpi2_sensors_Py##C_NAME##_##C_NAME(PyObject *self,                    \
                                            PyObject *args)                    \
    {                                                                          \
        Py_XDECREF(args);                                                      \
                                                                               \
        /* Call the original C function */                                     \
        kb_Error error;                                                        \
        switch (                                                               \
            (error = kb_rpi2_sensors_Py##C_NAME##_##C_FUNC(                    \
                (kb_rpi2_Context *const)(                                      \
                    (kbpy_rpi2_sensors_Py##C_NAME *const)self)->kb_sensor)))   \
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
#define KBPY_RPI2_SENSORS_COMMON_SIMPLE_METHOD_DEF(C_NAME,                     \
                                                   C_FUNC,                     \
                                                   PY_DOC)                     \
    {                                                                          \
        .ml_name  = #C_FUNC,                                                   \
        .ml_meth  = kbpy_rpi2_sensors_Py##C_NAME##_##C_FUNC,                   \
        .ml_flags = METH_NOARGS,                                               \
        .ml_doc   = PY_DOC                                                     \
    }


/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
#define KBPY_RPI2_SENSORS_COMMON_PY_TYPE_H(C_NAME)                             \
    extern PyTypeObject kbpy_rpi2_sensors_Py##C_NAME##Type;
#define KBPY_RPI2_SENSORS_COMMON_PY_TYPE_C(C_NAME,                             \
                                           METHODS)                            \
    PyDoc_STRVAR(kbpy_rpi2_sensors_Py##C_NAME##_doc, NULL);                    \
    PyTypeObject kbpy_rpi2_sensors_Py##C_NAME##Type =                          \
    {                                                                          \
        PyObject_HEAD_INIT(NULL)                                               \
        .tp_name           = "kb.rpi2.sensors." #C_NAME,                       \
        .tp_basicsize      = sizeof(kbpy_rpi2_sensors_Py##C_NAME),             \
        .tp_itemsize       = 0,                                                \
        .tp_dealloc        = kbpy_rpi2_sensors_Py##C_NAME##_dealloc,           \
        .tp_print          = 0,                                                \
        .tp_getattr        = 0,                                                \
        .tp_setattr        = 0,                                                \
        .tp_as_async       = 0, /* tp_reserved in python3.4 */                 \
        .tp_repr           = 0,                                                \
        .tp_as_number      = 0,                                                \
        .tp_as_sequence    = 0,                                                \
        .tp_as_mapping     = 0,                                                \
        .tp_hash           = 0,                                                \
        .tp_call           = kbpy_rpi2_sensors_Py##C_NAME##_call,              \
        .tp_str            = 0,                                                \
        .tp_getattro       = 0,                                                \
        .tp_setattro       = 0,                                                \
        .tp_as_buffer      = 0,                                                \
        .tp_flags          = Py_TPFLAGS_DEFAULT |                              \
                             Py_TPFLAGS_BASETYPE, /* Can be subtyped */        \
        .tp_doc            = kbpy_rpi2_sensors_Py##C_NAME##_doc,               \
        .tp_traverse       = 0,                                                \
        .tp_clear          = 0,                                                \
        .tp_richcompare    = 0,                                                \
        .tp_weaklistoffset = 0,                                                \
        .tp_iter           = 0,                                                \
        .tp_iternext       = 0,                                                \
        .tp_methods        = METHODS,                                          \
        .tp_members        = 0,                                                \
        .tp_getset         = kbpy_rpi2_sensors_Py##C_NAME##_getters_setters,   \
        .tp_base           = 0,                                                \
        .tp_dict           = 0,                                                \
        .tp_descr_get      = 0,                                                \
        .tp_descr_set      = 0,                                                \
        .tp_dictoffset     = 0,                                                \
        .tp_init           = kbpy_rpi2_sensors_Py##C_NAME##_init,              \
        .tp_alloc          = 0,                                                \
        .tp_new            = PyType_GenericNew,                                \
    };


#endif /* KBPY_RPI2_SENSORS_COMMON_H_4548327730281795 */
