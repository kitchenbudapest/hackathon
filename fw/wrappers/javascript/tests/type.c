/* INFO **
** INFO */

/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
/* Include standard headers */
#include <stddef.h>
/*  type  : size_t */
#include <stdlib.h>
/*  func  : malloc
            free */
#include <string.h>
/*  func  : strncpy */

/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
/* Include project headers */
#include "type.h"
/*  macro : JS_TYPE_NAME_SIZE
    type  : T
            E
    func  : T_new
            T_del
            T_str */

/*----------------------------------------------------------------------------*/
E
T_new(T          **const self,
      const char  *const name)
{
    static size_t id = 0;

    if (!self)
        return SELF_IS_NULL;

    *self = NULL;

    T *t;
    if (!(t = malloc(sizeof(T))))
        return ALLOC_FAIL;

    t->id = id++;
    strncpy(t->name, name, JS_TYPE_NAME_SIZE);

    *self = t;
    return OKAY;
}


/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
E
T_del(T **const self)
{
    if (!self || !*self)
        return SELF_IS_NULL;

    free(*self);
    *self = NULL;

    return OKAY;
}


/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
E
T_str(T     *const self,
      char **const repr)
{
    if (!self)
        return SELF_IS_NULL;
    else if (!repr)
        return ARG2_IS_NULL;

    *repr = self->name;
    return OKAY;
}
