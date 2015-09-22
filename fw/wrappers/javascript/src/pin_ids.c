/* INFO **
** INFO */

/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
/* Include standard headers */
#include <stdio.h>
/*  func  : snprintf */

/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
/* Include kibu headers */
#include <kb/rpi2/enums.h>
/*  type  : kb_rpi2_PinId
    const : kb_rpi2_PIN*
            kb_rpi2_PINS_COUNT */

/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
/* Include kbjs headers */
#include "include/keys.h"
/*  macro : KBJS_INSTANCE_PTR */
#include "include/types.h"
/*  macro : KBJS_TYPES_STASH_KEY_LENGTH
    type  : kbjs_Context
            kbjs_Event
            kbjs_PinId
            kbjs_LED
    func  : kbjs_get_stash_key */


/*----------------------------------------------------------------------------*/
static kbjs_PinId kbjs_PIN_IDS[kb_rpi2_PINS_COUNT];


/*----------------------------------------------------------------------------*/
static duk_ret_t
kbjs_PinId_str(duk_context *context)
{
    /* STACK: [this] */
    duk_push_this(context);

    /* STACK: [this, void*] */
    duk_get_prop_string(context, (duk_idx_t)-1, KBJS_INSTANCE_PTR);
    kbjs_PinId *pin_id = duk_get_pointer(context, (duk_idx_t)-1);
    /* STACK: [] */
    duk_pop_2(context);

    /* STACK: ["PIN*"] */
    duk_push_string(context, pin_id->str);

    /* Return string */
    return (duk_ret_t)1;
}


/*----------------------------------------------------------------------------*/
void
kbjs_register_PinIds(duk_context *context)
{
    /* Get kb.rpi2 object */
    /* STACK: [global] */
    duk_push_global_object(context);
    /* STACK: [global, kb] */
    duk_get_prop_string(context, (duk_idx_t)-1, "kb");
    /* STACK: [global, kb, rpi] */
    duk_get_prop_string(context, (duk_idx_t)-1, "rpi2");

    /* Create PinId enums */
    #define CREATE_ENUM_(INDEX)                                                \
        kbjs_PIN_IDS[kb_rpi2_PIN##INDEX] =                                     \
        (kbjs_PinId){                                                          \
            kb_rpi2_PIN##INDEX,                                                \
            "kb.rpi2.PIN" #INDEX,                                              \
            context,                                                           \
            ""                                                                 \
        };                                                                     \
        kbjs_get_stash_key(KBJS_TYPES_STASH_KEY_LENGTH,                        \
                           kbjs_PIN_IDS[kb_rpi2_PIN##INDEX].js_stash_key);     \
        /* STACK: [global, kb, rpi, "PIN*"] */                                 \
        duk_push_string(context, "PIN" #INDEX);                                \
        /* STACK: [global, kb, rpi, "PIN*", {}] */                             \
        duk_push_object(context);                                              \
        /* STACK: [global, kb, rpi, "PIN*", {}, "instance_ptr"] */             \
        duk_push_string(context, KBJS_INSTANCE_PTR);                           \
        /* STACK: [global, kb, rpi, "PIN*", {}, "instance_ptr", void*] */      \
        duk_push_pointer(context, kbjs_PIN_IDS + kb_rpi2_PIN##INDEX);          \
        /* STACK: [global, kb, rpi, "PIN*", {}] */                             \
        duk_put_prop(context, (duk_idx_t)-3);                                  \
        /* STACK: [global, kb, rpi, "PIN*", {}, "toString"] */                 \
        duk_push_string(context, "toString");                                  \
        /* STACK: [global, kb, rpi, "PIN*", {}, "toString", function] */       \
        duk_push_c_function(context, kbjs_PinId_str, (duk_idx_t)0);            \
        /* STACK: [global, kb, rpi, "PIN*", {}] */                             \
        duk_put_prop(context, (duk_idx_t)-3);                                  \
        /* STACK: [global, kb, rpi] */                                         \
        duk_put_prop(context, (duk_idx_t)-3);
    #define CREATE_ENUM(PREFIX1, PREFIX2)                                      \
        CREATE_ENUM_(PREFIX1##1)                                               \
        CREATE_ENUM_(PREFIX1##2)                                               \
        CREATE_ENUM_(PREFIX1##3)                                               \
        CREATE_ENUM_(PREFIX1##4)                                               \
        CREATE_ENUM_(PREFIX1##5)                                               \
        CREATE_ENUM_(PREFIX1##6)                                               \
        CREATE_ENUM_(PREFIX1##7)                                               \
        CREATE_ENUM_(PREFIX1##8)                                               \
        CREATE_ENUM_(PREFIX1##9)                                               \
        CREATE_ENUM_(PREFIX2##0)
    CREATE_ENUM( , 1)
    CREATE_ENUM(1, 2)
    CREATE_ENUM(2, 3)
    CREATE_ENUM(3, 4)
    #undef CREATE_ENUM_
    #undef CREATE_ENUM

    /* Clean up */
    /* STACK: [] */
    duk_pop_3(context);
}
