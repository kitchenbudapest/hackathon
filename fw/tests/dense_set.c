/* INFO **
** INFO */

/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
/* Include standard headers */
#include <stdio.h>
/*  func  : puts */
#include <stdlib.h>
/*  const : EXIT_SUCCESS */

/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
/* Include kibu headers */
#include "kb/errors.h"
/*  type  : kb_Error */
#include "kb/utils/dense_set.h"
/**/

/*----------------------------------------------------------------------------*/
typedef struct
{
    KB_UTILS_DENSE_SET_ITEM_MEMBERS()
    char *value;
} Item;


/*----------------------------------------------------------------------------*/
kb_Error
stringify(kb_utils_DenseSet *dense_set)
{
    kb_utils_DenseSetIter *iter;
    kb_utils_DenseSetItem *item;

    kb_Error error;
    if ((error = kb_utils_DenseSetIter_new(&iter, dense_set)) ||
        (error = kb_utils_DenseSetIter_next(iter, &item)))
            return error;

    printf("<kb_utils_DenseSet[");
    for (size_t i=0; item; i++)
    {
        if (i)
            printf(", ");
        printf("%s", ((Item *)item)->value);
        kb_utils_DenseSetIter_next(iter, &item);
    }
    printf("]>\n");

    if ((error = kb_utils_DenseSetIter_del(&iter)))
        return error;

    return kb_OKAY;
}


/*----------------------------------------------------------------------------*/
int
main(void)
{
    kb_utils_DenseSet *dense_set;

    Item a, b, c, d, e, f, g;
    a.id    = (size_t)0;
    a.value = "Item('a')";
    b.id    = (size_t)0;
    b.value = "Item('b')";
    c.id    = (size_t)0;
    c.value = "Item('c')";
    d.id    = (size_t)0;
    d.value = "Item('d')";
    e.id    = (size_t)0;
    e.value = "Item('e')";
    f.id    = (size_t)0;
    f.value = "Item('f')";
    g.id    = (size_t)0;
    g.value = "Item('g')";

    switch (kb_utils_DenseSet_new(&dense_set, (size_t)32))
    {
        case kb_SELF_IS_NULL:
            puts("DenseSet: self is NULL");
            break;

        case kb_ALLOC_FAIL:
            puts("DenseSet: internal allocation failed");
            break;

        default:
            break;
    }

    kb_utils_DenseSet_push(dense_set, (kb_utils_DenseSetItem *)&a);
    kb_utils_DenseSet_push(dense_set, (kb_utils_DenseSetItem *)&b);
    kb_utils_DenseSet_push(dense_set, (kb_utils_DenseSetItem *)&c);
    kb_utils_DenseSet_push(dense_set, (kb_utils_DenseSetItem *)&d);
    kb_utils_DenseSet_push(dense_set, (kb_utils_DenseSetItem *)&e);
    kb_utils_DenseSet_push(dense_set, (kb_utils_DenseSetItem *)&f);
    kb_utils_DenseSet_push(dense_set, (kb_utils_DenseSetItem *)&g);

    size_t l;
    kb_utils_DenseSet_len(dense_set, &l);
    printf("DenseSet: length = %zu\n", l);

    stringify(dense_set);

    kb_utils_DenseSet_pull(dense_set, (kb_utils_DenseSetItem *)&a);
    kb_utils_DenseSet_pull(dense_set, (kb_utils_DenseSetItem *)&c);
    kb_utils_DenseSet_pull(dense_set, (kb_utils_DenseSetItem *)&d);
    kb_utils_DenseSet_pull(dense_set, (kb_utils_DenseSetItem *)&g);

    stringify(dense_set);

    kb_utils_DenseSet_push(dense_set, (kb_utils_DenseSetItem *)&g);
    kb_utils_DenseSet_push(dense_set, (kb_utils_DenseSetItem *)&d);
    kb_utils_DenseSet_push(dense_set, (kb_utils_DenseSetItem *)&c);
    kb_utils_DenseSet_push(dense_set, (kb_utils_DenseSetItem *)&a);

    stringify(dense_set);

    kb_utils_DenseSet_del(&dense_set);
    return EXIT_SUCCESS;
}
