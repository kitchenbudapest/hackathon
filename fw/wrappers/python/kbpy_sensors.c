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
/* Include kbpy headers */
#include "include/sensors/leds.h"
/*  value : kbpy_rpi2_sensors_PyLEDType */


/*----------------------------------------------------------------------------*/
PyDoc_STRVAR(module_sensors_doc,
             "kb.rpi2.sensors module include the hardware specific objects.");

static struct PyModuleDef module_sensors =
{
    PyModuleDef_HEAD_INIT,
    .m_name     = "sensors",
    .m_doc      = module_sensors_doc,
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
PyInit_libsensors(void)
{
    PyObject *module;

    /* Create python module */
    if (!(module = PyModule_Create(&module_sensors)))
        goto Create_Error;

    #define ADD_OBJECT(C_NAME)                                                 \
        /* Finalize Event class */                                             \
        if (PyType_Ready(&kbpy_rpi2_sensors_Py##C_NAME##Type))                 \
            goto Type_Ready_Error;                                             \
                                                                               \
        /* Add C_NAME class-object to the module */                            \
        Py_INCREF((PyObject *)&kbpy_rpi2_sensors_Py##C_NAME##Type);            \
        if (PyModule_AddObject(                                                \
                module,                                                        \
                #C_NAME,                                                       \
                (PyObject *)&kbpy_rpi2_sensors_Py##C_NAME##Type))              \
        {                                                                      \
            Py_XDECREF((PyObject *)&kbpy_rpi2_sensors_Py##C_NAME##Type);       \
            goto Add_Object_Error;                                             \
        }

    /* Add objects */
    ADD_OBJECT(LED)
    #undef ADD_OBJECT

    /* If everything went fine */
    return module;

    /* If there was any problem */
    Type_Ready_Error:
    Add_Object_Error:
        Py_XDECREF(module);
    Create_Error:
        return NULL;
}
