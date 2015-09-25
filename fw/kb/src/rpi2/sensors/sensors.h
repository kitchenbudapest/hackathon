/* INFO **
** INFO */

/* Header guard */
#ifndef KBJS_SENSORS_SENSORS_H_1331567805515832
#define KBJS_SENSORS_SENSORS_H_1331567805515832 1

#define KBJS_COMMON_SENSORS_CALLBACK_WRAPPER()
    ...

#define KBJS_COMMON_SENSORS_METHODS_WRAPPER()
    ...

/*----------------------------------------------------------------------------*/
#define KBJS_COMMON_SENSORS_REGISTER_WRAPPER(C_NAME, JS_NAME)                  \
    void                                                                       \
    kbjs_register_##C_NAME(duk_context *context)                               \
    {                                                                          \
        /* Get kb.rpi2.sensors object */                                       \
        /* STACK: [global] */                                                  \
        duk_push_global_object(context);                                       \
        /* STACK: [global, kb] */                                              \
        duk_get_prop_string(context, (duk_idx_t)-1, "kb");                     \
        /* STACK: [global, kb, rpi] */                                         \
        duk_get_prop_string(context, (duk_idx_t)-1, "rpi2");                   \
        /* STACK: [global, kb, rpi, sensors, sensors] */                       \
        duk_get_prop_string(context, (duk_idx_t)-1, "sensors");                \
                                                                               \
        /* Create kb.rpi2.sensors.JS_NAME constructor */                       \
        /* STACK: [global, kb, rpi, sensors, "JS_NAME"] */                     \
        duk_push_string(context, JS_NAME);                                     \
        /* STACK: [global, kb, rpi, sensors, "JS_NAME", f()] */                \
        duk_push_c_function(context, C_NAME##_new, (duk_idx_t)2);              \
                                                                               \
        /* Create kb.rpi2.Context.toString */                                  \
        /* STACK: [global, kb, rpi, sensors, "JS_NAME", f(), ""] */            \
        duk_push_string(context, "toString");                                  \
        /* STACK: [global, kb, rpi, sensors, "JS_NAME", f(), "", f()] */       \
        duk_push_c_function(context, C_NAME##_type_str, (duk_idx_t)0);         \
        /* STACK: [global, kb, rpi, sensors, "JS_NAME", f()] */                \
        duk_put_prop(context, (duk_idx_t)-3);                                  \
                                                                               \
        /* Create kb.rpi2.Context.prototype */                                 \
        /* STACK: [global, kb, rpi, sensors, "JS_NAME", f(), ""] */            \
        duk_push_string(context, "prototype");                                 \
        /* STACK: [global, kb, rpi, sensors, "JS_NAME", f(), "", {}] */        \
        duk_push_object(context);                                              \
        /* STACK: [global, kb, rpi, sensors, "JS_NAME", f(), "", {f...}] */    \
        duk_put_function_list(context, (duk_idx_t)-1, C_NAME##_methods);       \
                                                                               \
        /* Set prototype */                                                    \
        /* STACK: [global, kb, rpi, sensors, "JS_NAME", f()] */                \
        duk_put_prop(context, (duk_idx_t)-3);                                  \
        /* Set constructor */                                                  \
        /* STACK: [global, kb, rpi, sensors] */                                \
        duk_put_prop(context, (duk_idx_t)-3);                                  \
                                                                               \
        /* Clean up */                                                         \
        /* STACK: [] */                                                        \
        duk_pop_n(context, (duk_idx_t)4);                                      \
    }


#endif /* KBJS_SENSORS_SENSORS_H_1331567805515832 */
