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
    if (!PyObject_IsInstance(py_event, (PyObject *)&kbpy_rpi2_PyEventType))
    {
        PyErr_SetString(PyExc_TypeError,
                        "First argument of '" OBJECT_NAME ".__init__' should be "
                        "a kb.rpi2.Event");
        return kbpy_FAIL;
    }

    /* If the given ojbect is not a PyCapsule */
    kb_rpi2_PinId *pin_id;
    if (!(pin_id = PyCapsule_GetContext(py_pin_id)))
    {
        PyErr_SetString(PyExc_TypeError,
                        "Second aargument of '" OBJECT_NAME ".__init__' should"
                        "be a kb.rpi2.PINx");
        return kbpy_FAIL;
    }

    /* Check if object is one of the PIN enums */
    bool not_found = true;
    for (int i=kb_rpi2_PIN1; i<kb_rpi2_PINS_COUNT; i++)
        if (&(kbpy_rpi2_PY_PIN_IDS[i].id) == pin_id)
        {
            not_found = false;
            break;
        }
    /* If object is not a PIN enum */
    if (not_found)
    {
        PyErr_SetString(PyExc_TypeError,
                        "Second aargument of '" OBJECT_NAME ".__init__' should"
                        "be a kb.rpi2.PINx");
        return kbpy_FAIL;
    }

    /* Create new wrapped kibu LED */
    kbpy_rpi2_sensors_LED *kb_sensor;
    if (!(kb_sensor = malloc(sizeof(kbpy_rpi2_sensors_PyLED))))
    {
        PyErr_SetString(kbpy_rpi2_INTERNAL_ERROR, kb_Error_str(kb_ALLOC_FAIL));
        return kbpy_FAIL;
    }

    /* Initialize instance as kibu LED */
    kb_Error error;
    switch ((error = kb_rpi2_sensors_LED_ini((kb_rpi2_sensors_LED *const)kb_sensor)))
    {
        case kb_OKAY:
            break;

        default:
            PyErr_SetString(kbpy_rpi2_INTERNAL_ERROR,
                            "");
            return kbpy_FAIL;
    }

    /* Store the C reference */
    ((kbpy_rpi2s_sensors_PyLED *const)self)->kb_sensor = kb_sensor;
    /* Store the python reference */
    kb_sensor->py_sensor = (kbpy_rpi2_sensors_PyLED *const)self;

    /* Initialize callbacks */
    ((kbpy_rpi2_sensors_PyLED *const)self)->on_on  = NULL;
    ((kbpy_rpi2_sensors_PyLED *const)self)->on_off = NULL;

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
        on_on ,
        "on_on",
         NULL),
    KBPY_RPI2_SENSORS_COMMON_CALLBACK_SETTER_GETTER_WRAPPER_DEF(
        on_off,
        "on_off",
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
KBPY_RPI2_SENSORS_COMMON_PY_TYPE(LED, kbpy_rpi2_sensors_PyLED_methods)
