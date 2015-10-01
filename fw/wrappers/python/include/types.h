/* INFO **
** INFO */

/* Header guard */
#ifndef KBPY_TYPES_H_9888933778787067
#define KBPY_TYPES_H_9888933778787067 1

/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
/* Include python headers
   Since Python may define some pre-processor definitions which affect the
   standard headers on some systems, you must include Python.h before any
   standard headers are included */
#include <Python.h>
/*  type  : PyObject
    macro : PyObject_HEAD */

/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
/* Include kibu headers */
#include <kb/rpi2/types.h>
/*  macro : KB_RPI2_CONTEXT_MEMBERS
            KB_RPI2_EVENT_MEMBERS */


/*----------------------------------------------------------------------------*/
/* Forward declarations to avoid circular dependencies */
struct kbpy_rpi2_context;
struct kbpy_rpi2_py_context;
struct kbpy_rpi2_event;
struct kbpy_rpi2_py_event;


/*----------------------------------------------------------------------------*/
typedef struct kbpy_rpi2_context
{
    KB_RPI2_CONTEXT_MEMBERS()
    struct kbpy_rpi2_py_context *py_context;
} kbpy_rpi2_Context;
/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
typedef struct kbpy_rpi2_py_context
{
    PyObject_HEAD
    struct kbpy_rpi2_context *kb_context;
    PyObject                 *on_start;
    PyObject                 *on_stop;
    PyObject                 *on_exit;
    PyObject                 *on_cycle_begin;
    PyObject                 *on_cycle_end;
    PyObject                 *on_activate;
} kbpy_rpi2_PyContext;


/*----------------------------------------------------------------------------*/
typedef struct kbpy_rpi2_event
{
    KB_RPI2_EVENT_MEMBERS()
    struct kbpy_rpi2_py_event *py_event;
} kbpy_rpi2_Event;
/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
typedef struct kbpy_rpi2_py_event
{
    PyObject_HEAD
    struct kbpy_rpi2_event *kb_event;
} kbpy_rpi2_PyEvent;


#endif /* KBPY_TYPES_H_9888933778787067 */
