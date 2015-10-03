/* INFO **
** INFO */

/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
/* Include python headers
   Since Python may define some pre-processor definitions which affect the
   standard headers on some systems, you must include Python.h before any
   standard headers are included */
#include <Python.h>
/*  macro : Py_INCREF
            Py_XDECREF
            PyDoc_STRVAR
            PyModuleDef_HEAD_INIT
    const : PYTHON_MODULE_CAN_BE_REINITIALISED
    type  : PyObject
            PyModuleDef
            PyMODINIT_FUNC
    func  : PyModule_Create
            PyType_Ready */

/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
/* Include kibu headers */
#include <kb/rpi2/enums.h>
/*  const : kb_rpi2_PIN1
            kb_rpi2_PINS_COUNT */

/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
/* Include kbpy headers */
#include "include/errors.h"
/*  value : kbpy_rpi2_INTERNAL_ERROR */
#include "include/pin_ids.h"
/*  value : kbpy_rpi2_PY_PIN_IDS */
#include "include/contexts.h"
/*  value : kbpy_rpi2_PyContextType */
#include "include/events.h"
/*  value : kbpy_rpi2_PyEventType */


/*----------------------------------------------------------------------------*/
PyDoc_STRVAR(kbpy_module_doc,
             "kbpy is a python wrapper implemented via the Python C API around "
             "the libkb library. libkb is a very high level, context based, "
             "event driven framework to work with SBC's GPIO pins connected "
             "sensors.");

static struct PyModuleDef kbpy_module =
{
    PyModuleDef_HEAD_INIT,
    .m_name     = "rpi2",
    .m_doc      = kbpy_module_doc,
    .m_size     = 1, /* module can be reinitialized */
    .m_methods  = NULL,

    // .m_slots    = NULL, // py3.5
    // .m_reload   = NULL, // py3.4

    // .m_traverse = NULL,
    // .m_clear    = NULL,
    // .m_free     = NULL,
};


/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
PyMODINIT_FUNC
PyInit_rpi2(void)
{
    PyObject *module;

    /* Create python module */
    if (!(module = PyModule_Create(&kbpy_module)))
        goto Create_Error;

    /* Create exceptions */
    kbpy_rpi2_INTERNAL_ERROR = PyErr_NewException("kb.rpi2.InternalError",
                                                  NULL,
                                                  NULL);
    /* Add exception to the module */
    Py_INCREF(kbpy_rpi2_INTERNAL_ERROR);
    if (PyModule_AddObject(module,
                           "InternalError",
                           kbpy_rpi2_INTERNAL_ERROR))
        goto Add_Object_Error;

    /* Finalize Context class */
    if (PyType_Ready(&kbpy_rpi2_PyContextType))
        goto Type_Ready_Error;

    /* Add PinId enums */
    PyObject *pin;
    for (int i=kb_rpi2_PIN1; i<kb_rpi2_PINS_COUNT; i++)
    {
        /* Create new Capsule object */
        if (!(pin = PyCapsule_New((void *)&(kbpy_rpi2_PY_PIN_IDS[i].id),
                                  kbpy_rpi2_PY_PIN_IDS[i].name,
                                  NULL)))
        {
            PyErr_SetString(kbpy_rpi2_INTERNAL_ERROR,
                            "Could not create kb.rpi2.PINx object");
            goto Register_Object_Error;
        }

        /* Add new Capsule to module */
        if (PyModule_AddObject(module,
                               kbpy_rpi2_PY_PIN_IDS[i].name + sizeof("kb.rpi2"),
                               pin))
        {
            PyErr_SetString(kbpy_rpi2_INTERNAL_ERROR,
                            "Could not add kb.rpi2.PINx to module");
            goto Register_Object_Error;
        }
    }

    /* Add Context class-object to the module */
    Py_INCREF((PyObject *)&kbpy_rpi2_PyContextType);
    if (PyModule_AddObject(module,
                           "Context",
                           (PyObject *)&kbpy_rpi2_PyContextType))
    {
        Py_XDECREF((PyObject *)&kbpy_rpi2_PyContextType);
        goto Add_Object_Error;
    }

    /* Finalize Event class */
    if (PyType_Ready(&kbpy_rpi2_PyEventType))
        goto Type_Ready_Error;

    /* Add Event class-object to the module */
    Py_INCREF((PyObject *)&kbpy_rpi2_PyEventType);
    if (PyModule_AddObject(module,
                           "Event",
                           (PyObject *)&kbpy_rpi2_PyEventType))
    {
        Py_XDECREF((PyObject *)&kbpy_rpi2_PyEventType);
        goto Add_Object_Error;
    }

    /* If everything went fine */
    return module;

    /* If there was any problem */
    Type_Ready_Error:
    Add_Object_Error:
    Register_Object_Error:
        Py_XDECREF(module);
    Create_Error:
        return NULL;
}
