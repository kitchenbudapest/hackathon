/* INFO **
** INFO */

/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
/* Include standard headers */
#include <stddef.h>
/*  type  : size_t */

/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
/* Include kbjs headers */
#include "include/types.h"
/*  value : KBJS_TYPES_STASH_KEY */


/*----------------------------------------------------------------------------*/
static size_t STASH_KEY = (size_t)0;


/*----------------------------------------------------------------------------*/
int
kbjs_get_stash_key(size_t  length,
                   char   *buffer)
{
    return snprintf(buffer, length - (size_t)1, "%zu", STASH_KEY++);
}
