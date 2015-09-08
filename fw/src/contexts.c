/* INFO **
** INFO */

/*----------------------------------------------------------------------------*/
typedef struct
{
    kb_rpi2_Pin *pins[kb_rpi2_PIN_COUNT];
} kb_rpi2_Context;


/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
kb_Error
kb_rpi2_Context_new(kb_rpi2_Context **self)
{
    kb_rpi2_Context *context;
    if (!(context = malloc(sizeof(kb_rpi2_Context))))
        return kb_ALLOC_FAIL;

    /* If everything went fine */
    return kb_OKAY;
}
