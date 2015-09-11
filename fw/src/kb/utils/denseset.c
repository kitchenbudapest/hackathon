/* INFO **
** INFO */

#include <kb/errors.h> /*
    type  : kb_Error
*/

/*----------------------------------------------------------------------------*/
#define KB_UTILS_DENSE_SET_ITEM_MEMBERS() \
    size_t id;


/*----------------------------------------------------------------------------*/
typedef struct
{
    KB_UTILS_DENSE_SET_ITEM_MEMBERS()
} kb_utils_DenseSetItem;


/*----------------------------------------------------------------------------*/
typedef struct
{
    size_t                 limit;
    size_t                 count;
    size_t                 index;
    kb_utils_DenseSetItem *items;
} kb_utils_DenseSet;


/*----------------------------------------------------------------------------*/
typedef struct
{
    kb_utils_DenseSet *const dense_set;
    size_t                   index;
} kb_utils_DenseSetIter;


/*----------------------------------------------------------------------------*/
kb_Error
kb_utils_DenseSet_new(kb_utils_DenseSet *const *self,
                      size_t                    limit)
{
    /* Local variables */
    kb_utils_DenseSet     *dense_set;
    kb_utils_DenseSetItem *items;

    /* Create new Set object */
    if (!(dense_set = malloc(sizeof(kb_utils_DenseSet))))
        goto Self_Alloc_Failed;

    /* Create Items array */
    if (!(items = calloc(limit, sizeof(kb_utils_DenseSetItem *))))
        goto Item_Alloc_Failed;

    /* Set values */
    dense_set->count = 0;
    dense_set->index = 0;
    dense_set->limit = limit;
    dense_set->items = items;

    /* Return new Set object */
    *self = dense_set;

    /* If everything went fine */
    return kb_OKAY;

    /* If there was any problem */
    Item_Alloc_Failed:
        free(dense_set);
    Self_Alloc_Failed:
        *self = NULL;
        return kb_ALLOC_FAIL;
}


/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
kb_Error
kb_utils_DenseSet_del(kb_utils_DenseSet *const *self)
{
    /* Deallocate objects */
    free((*self)->items);
    free(*self);

    /* Redirect self */
    *self = NULL;

    /* If everything went fine */
    return kb_OKAY;
}


/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
kb_Error
kb_utils_DenseSet_push(kb_utils_DenseSet     *const self,
                       kb_utils_DenseSetItem *const item)
{
    if (kb_utils_DenseSet_has(self, item))
        return kb_OKAY;

    /* If everything went fine */
    return kb_OKAY;
}


/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
kb_Error
kb_utils_DenseSet_pull(kb_utils_DenseSet     *const self,
                       kb_utils_DenseSetItem *const item)
{
    if (!kb_utils_DenseSet_has(self, item))
        return kb_ITEM_NOT_IN_CONTAINER;

    /* Remove item from Set */
    self->items[item->id] = NULL;

    /* Update index if removed item is before the current hole */
    if (item->id < self->index)
        self->index = item->id;

    /* Decrease item count */
    --self->count;

    /* If everything went fine */
    return kb_OKAY;
}


/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
bool
kb_utils_DenseSet_has(kb_utils_DenseSet     *const self,
                      kb_utils_DenseSetItem *const item)
{
    /* If `self` is not NULL and
       `item` is not NULL and
       `item` is in this DenseSet */
    if (self &&
        item &&
        self->items[item->id] == item)
            return true;
    /* If `self` or `item` is not valid or
       `item` is not in `self` */
    return false;
}


/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
size_t
kb_utils_DenseSet_len(kb_utils_DenseSet *const self)
{
    if (!self)
        return (size_t)0;
    else
        return self->count;
}



/*----------------------------------------------------------------------------*/
kb_Error
kb_utils_DenseSetIter_new(kb_utils_DenseSetIter *const *self,
                          kb_utils_DenseSet     *const  dense_set)
{
    /* Create new Iter object */
    kb_utils_DenseSetIter *dense_set_iter;
    if (!(dense_set_iter = malloc(sizeof(kb_utils_DenseSetIter))))
        return kb_ALLOC_FAIL;

    /* Set values */
    dense_set_iter->dense_set = dense_set;
    dense_set_iter->index     = 0;

    /* Return new Iter object */
    *self = dense_set_iter;

    /* If everything went fine */
    return kb_OKAY;
}


/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
kb_Error
kb_utils_DenseSetIter_del(kb_utils_DenseSetIter *const *self)
{
    /* If `self` is NULL */
    if (!self)
        return kb_SELF_IS_NULL;

    /* Deallocate memory for Set */
    free(*self);

    /* Redirect `self` */
    *self = NULL;

    /* If everything went fine */
    return kb_OKAY;
}


/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
kb_Error
kb_utils_DenseSetIter_next(kb_utils_DenseSetIter *const  self,
                           kb_utils_DenseSetItem *const *item)
{
    /* If any of the arguments is NULL */
    if (!self)
        return kb_SELF_IS_NULL;
    else if (!item)
        return kb_ARG2_IS_NULL;

    /* Get next item from the iterator */
    *item = NULL;
    for (size_t i=self->index; i<self->dense_set->limit; i++)
        if (!(*item = self->dense_set->items[i]))
            break;

    /* If everything went fine */
    return kb_OKAY;
}
