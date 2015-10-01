/* INFO **
** INFO */

/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
/* Include python headers
   Since Python may define some pre-processor definitions which affect the
   standard headers on some systems, you must include Python.h before any
   standard headers are included */
#include <Python.h>
/*  type  : PyObject
    func  : PyCapsule_New
            PyErr_SetString
            PyModule_AddObject */

/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
/* Include kibu headers */
#include <kb/rpi2/enums.h>
/*  type  : kb_rpi2_PinId
    const : kb_rpi2_PINx
            kb_rpi2_PINS_COUNT */

/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
/* Include kbpy headers */
#include "include/errors.h"
/*  const : kbpy_OKAY
            kbpy_FAIL
    value : kbpy_rpi2_INTERNAL_ERROR */


/*----------------------------------------------------------------------------*/
typedef struct
{
    kb_rpi2_PinId  id;
    const char    *name;
} PyPinId;


/*----------------------------------------------------------------------------*/
static const PyPinId PY_PIN_IDS[] =
{
    [kb_rpi2_PIN1]  = {kb_rpi2_PIN1,  "kb.rpi2.PIN1"},
    [kb_rpi2_PIN2]  = {kb_rpi2_PIN2,  "kb.rpi2.PIN2"},
    [kb_rpi2_PIN3]  = {kb_rpi2_PIN3,  "kb.rpi2.PIN3"},
    [kb_rpi2_PIN4]  = {kb_rpi2_PIN4,  "kb.rpi2.PIN4"},
    [kb_rpi2_PIN5]  = {kb_rpi2_PIN5,  "kb.rpi2.PIN5"},
    [kb_rpi2_PIN6]  = {kb_rpi2_PIN6,  "kb.rpi2.PIN6"},
    [kb_rpi2_PIN7]  = {kb_rpi2_PIN7,  "kb.rpi2.PIN7"},
    [kb_rpi2_PIN8]  = {kb_rpi2_PIN8,  "kb.rpi2.PIN8"},
    [kb_rpi2_PIN9]  = {kb_rpi2_PIN9,  "kb.rpi2.PIN9"},
    [kb_rpi2_PIN10] = {kb_rpi2_PIN10, "kb.rpi2.PIN10"},

    [kb_rpi2_PIN11] = {kb_rpi2_PIN11, "kb.rpi2.PIN11"},
    [kb_rpi2_PIN12] = {kb_rpi2_PIN12, "kb.rpi2.PIN12"},
    [kb_rpi2_PIN13] = {kb_rpi2_PIN13, "kb.rpi2.PIN13"},
    [kb_rpi2_PIN14] = {kb_rpi2_PIN14, "kb.rpi2.PIN14"},
    [kb_rpi2_PIN15] = {kb_rpi2_PIN15, "kb.rpi2.PIN15"},
    [kb_rpi2_PIN16] = {kb_rpi2_PIN16, "kb.rpi2.PIN16"},
    [kb_rpi2_PIN17] = {kb_rpi2_PIN17, "kb.rpi2.PIN17"},
    [kb_rpi2_PIN18] = {kb_rpi2_PIN18, "kb.rpi2.PIN18"},
    [kb_rpi2_PIN19] = {kb_rpi2_PIN19, "kb.rpi2.PIN19"},
    [kb_rpi2_PIN20] = {kb_rpi2_PIN20, "kb.rpi2.PIN20"},

    [kb_rpi2_PIN21] = {kb_rpi2_PIN21, "kb.rpi2.PIN21"},
    [kb_rpi2_PIN22] = {kb_rpi2_PIN22, "kb.rpi2.PIN22"},
    [kb_rpi2_PIN23] = {kb_rpi2_PIN23, "kb.rpi2.PIN23"},
    [kb_rpi2_PIN24] = {kb_rpi2_PIN24, "kb.rpi2.PIN24"},
    [kb_rpi2_PIN25] = {kb_rpi2_PIN25, "kb.rpi2.PIN25"},
    [kb_rpi2_PIN26] = {kb_rpi2_PIN26, "kb.rpi2.PIN26"},
    [kb_rpi2_PIN27] = {kb_rpi2_PIN27, "kb.rpi2.PIN27"},
    [kb_rpi2_PIN28] = {kb_rpi2_PIN28, "kb.rpi2.PIN28"},
    [kb_rpi2_PIN29] = {kb_rpi2_PIN29, "kb.rpi2.PIN29"},
    [kb_rpi2_PIN30] = {kb_rpi2_PIN30, "kb.rpi2.PIN30"},

    [kb_rpi2_PIN31] = {kb_rpi2_PIN31, "kb.rpi2.PIN31"},
    [kb_rpi2_PIN32] = {kb_rpi2_PIN32, "kb.rpi2.PIN32"},
    [kb_rpi2_PIN33] = {kb_rpi2_PIN33, "kb.rpi2.PIN33"},
    [kb_rpi2_PIN34] = {kb_rpi2_PIN34, "kb.rpi2.PIN34"},
    [kb_rpi2_PIN35] = {kb_rpi2_PIN35, "kb.rpi2.PIN35"},
    [kb_rpi2_PIN36] = {kb_rpi2_PIN36, "kb.rpi2.PIN36"},
    [kb_rpi2_PIN37] = {kb_rpi2_PIN37, "kb.rpi2.PIN37"},
    [kb_rpi2_PIN38] = {kb_rpi2_PIN38, "kb.rpi2.PIN38"},
    [kb_rpi2_PIN39] = {kb_rpi2_PIN39, "kb.rpi2.PIN39"},
    [kb_rpi2_PIN40] = {kb_rpi2_PIN40, "kb.rpi2.PIN40"},
};


/*----------------------------------------------------------------------------*/
int
kbpy_rpi2_PyPinIds_register(PyObject *module)
{
    PyObject *pin;
    for (int i=kb_rpi2_PIN1; i<kb_rpi2_PINS_COUNT; i++)
    {
        /* Create new Capsule object */
        if (!(pin = PyCapsule_New((void *)&(PY_PIN_IDS[i].id),
                                  PY_PIN_IDS[i].name,
                                  NULL)))
        {
            PyErr_SetString(kbpy_rpi2_INTERNAL_ERROR,
                            "Could not create kb.rpi2.PINx object");
            return kbpy_FAIL;
        }

        /* Add new Capsule to module */
        if (PyModule_AddObject(module,
                               PY_PIN_IDS[i].name + sizeof("kb.rpi2"),
                               pin))
        {
            PyErr_SetString(kbpy_rpi2_INTERNAL_ERROR,
                            "Could not add kb.rpi2.PINx to module");
            return kbpy_FAIL;
        }
    }

    /* If everything went fine */
    return kbpy_OKAY;
}
