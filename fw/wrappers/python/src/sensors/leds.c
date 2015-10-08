/* INFO **
** INFO */

/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
/* Include python headers
   Since Python may define some pre-processor definitions which affect the
   standard headers on some systems, you must include Python.h before any
   standard headers are included */
#include <Python.h>
/*  type  : PyObject */

/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
/* Include standard headers */
#include <stdbool.h>
/*  type  : bool
    const : true
            false */

/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
/* Include kibu headers */
#include <kb/rpi2/sensors/leds.h>
/*  macro : KB_RPI2_SENSORS_LED_MEMBERS
    type  : kb_rpi2_sensors_LED */

/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
/* Include kbpy headers */
#include "include/errors.h"
/*  const : kbpy_OKAY
            kbpy_FAIL
    value : kbpy_rpi2_INTERNAL_ERROR */
#include "include/types.h"
/*  type  : kbpy_rpi2_Context
            kbpy_rpi2_PyContext
            kbpy_rpi2_Event
            kbpy_rpi2_PyEvent */
#include "include/events.h"
/*  type  : kbpy_rpi2_PyEventType */
#include "include/pin_ids.h"
/*  type  : kbpy_rpi2_PyPinId
    value : kbpy_rpi2_PY_PIN_IDS */
#include "include/sensors/common.h"
/*  macro : KBPY_RPI2_SENSORS_COMMON_TYPE
            KBPY_RPI2_SENSORS_COMMON_INIT_IS_EVENT
            KBPY_RPI2_SENSORS_COMMON_INIT_IS_CAPSULE
            KBPY_RPI2_SENSORS_COMMON_INIT_IS_PIN_ID
            KBPY_RPI2_SENSORS_COMMON_INIT_ALLOC
            KBPY_RPI2_SENSORS_COMMON_INIT_MUTUAL_REF
            KBPY_RPI2_SENSORS_COMMON_INIT_CALLBACK
            KBPY_RPI2_SENSORS_COMMON_DEALLOC
            KBPY_RPI2_SENSORS_COMMON_CALL
            KBPY_RPI2_SENSORS_COMMON_CALLBACK_SETTER_GETTER_WRAPPER
            KBPY_RPI2_SENSORS_COMMON_CALLBACK_SETTER_GETTER_WRAPPER_DEF
            KBPY_RPI2_SENSORS_COMMON_SIMPLE_METHOD
            KBPY_RPI2_SENSORS_COMMON_SIMPLE_METHOD_DEF
            KBPY_RPI2_SENSORS_COMMON_PY_TYPE */


/* Module level constants */
/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
#define OBJECT_NAME "kb.rpi2.sensors.LED"


/*----------------------------------------------------------------------------*/
/* kbpy_rpi2_sensors_LED
   kbpy_rpi2_sensors_PyLED */
KBPY_RPI2_SENSORS_COMMON_TYPE(led,
                              LED,
                              LED,
                              PyObject *on_on;
                              PyObject *on_off;)

/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
static int
kbpy_rpi2_sensors_PyLED_init(PyObject *self,
                             PyObject *args,
                             PyObject *kwargs)
{
    static char *kwlist[] = {"event", "pin", NULL};

    /* Unpack and store arguments */
    PyObject *py_event,
             *py_pin_id;
    if (!PyArg_ParseTupleAndKeywords(args,
                                     kwargs,
                                     "OO:__init__",
                                     kwlist,
                                     &py_event,
                                     &py_pin_id))
        return kbpy_FAIL;

    /* If the given object is not a Context one */
    KBPY_RPI2_SENSORS_COMMON_INIT_IS_EVENT(py_event)

    /* If the given ojbect is not a PyCapsule */
    kb_rpi2_PinId *pin_id;
    KBPY_RPI2_SENSORS_COMMON_INIT_IS_CAPSULE(py_pin_id, pin_id)

    /* Check if object is one of the PIN enums */
    KBPY_RPI2_SENSORS_COMMON_INIT_IS_PIN_ID(pin_id)

    /* Create new wrapped kibu LED */
    KBPY_RPI2_SENSORS_COMMON_INIT_ALLOC(LED)

    /* Initialize instance as kibu LED */
    kb_Error error;
    switch ((error = kb_rpi2_sensors_LED_ini(
        (kb_rpi2_sensors_LED *const)kb_sensor,
        (kb_rpi2_Event *const)((kbpy_rpi2_PyEvent *const)py_event)->kb_event,
        *pin_id)))
    {
        case kb_OKAY:
            break;

        default:
            PyErr_SetString(kbpy_rpi2_INTERNAL_ERROR,
                            kb_Error_str(error));
            return kbpy_FAIL;
    }

    /* Link kibu and python object */
    KBPY_RPI2_SENSORS_COMMON_INIT_MUTUAL_REF(LED)

    /* Initialize callbacks */
    KBPY_RPI2_SENSORS_COMMON_INIT_CALLBACK(LED, on_on)
    KBPY_RPI2_SENSORS_COMMON_INIT_CALLBACK(LED, on_off)

    /* If everything went fine */
    return kbpy_OKAY;
}


/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
/* kbpy_rpi2_sensors_LED_dealloc */
KBPY_RPI2_SENSORS_COMMON_DEALLOC(
    LED,
    KBPY_RPI2_SENSORS_XDECREF_CALLBACK_MEMBER(LED, on_on);
    KBPY_RPI2_SENSORS_XDECREF_CALLBACK_MEMBER(LED, on_off);)

/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
/* kbpy_rpi2_sensors_LED_call */
KBPY_RPI2_SENSORS_COMMON_CALL(LED)

/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
/* kbpy_rpi2_sensors_LED_on_on
   kbpy_rpi2_sensors_LED_on_on_setter
   kbpy_rpi2_sensors_LED_on_on_getter */
KBPY_RPI2_SENSORS_COMMON_CALLBACK_SETTER_GETTER_WRAPPER(LED, on_on)
/* kbpy_rpi2_sensors_LED_on_off
   kbpy_rpi2_sensors_LED_on_off_setter
   kbpy_rpi2_sensors_LED_on_off_getter */
KBPY_RPI2_SENSORS_COMMON_CALLBACK_SETTER_GETTER_WRAPPER(LED, on_off)

/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
static PyGetSetDef kbpy_rpi2_sensors_PyLED_getters_setters[] =
{
    KBPY_RPI2_SENSORS_COMMON_CALLBACK_SETTER_GETTER_WRAPPER_DEF(
        LED,
        on_on,
        NULL),
    KBPY_RPI2_SENSORS_COMMON_CALLBACK_SETTER_GETTER_WRAPPER_DEF(
        LED,
        on_off,
        NULL),
    {NULL, NULL, NULL, NULL, NULL},
};


/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
/* kbpy_rpi2_sensors_PyLED_on */
KBPY_RPI2_SENSORS_COMMON_SIMPLE_METHOD(LED, on)
/* kbpy_rpi2_sensors_PyLED_off */
KBPY_RPI2_SENSORS_COMMON_SIMPLE_METHOD(LED, off)

/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
static PyMethodDef kbpy_rpi2_sensors_PyLED_methods[] =
{
    KBPY_RPI2_SENSORS_COMMON_SIMPLE_METHOD_DEF(LED, on,  NULL),
    KBPY_RPI2_SENSORS_COMMON_SIMPLE_METHOD_DEF(LED, off, NULL),
    {NULL, NULL, 0, NULL}
};

/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
/* kbpy_rpi2_sensors_PyLEDType */
KBPY_RPI2_SENSORS_COMMON_PY_TYPE_C(LED, kbpy_rpi2_sensors_PyLED_methods)
