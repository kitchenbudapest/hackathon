/* INFO **
** INFO */

/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
/* Include standard headers */
#include <stddef.h>
/*  type  : size_t */
#include <stdlib.h>
/*  func  : malloc
            calloc
            realloc */
#include <stdbool.h>
/*  type  : bool
    const : true
            false */

/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
/* Include kibu headers */
#include <kb/errors.h>
/*  type  : kb_Error
    const : kb_OKAY
            kb_SELF_IS_NULL
            kb_ARG2_IS_NULL
            kb_ARG3_IS_NULL
            kb_ALLOC_FAIL
            kb_ITEM_NOT_IN_CONTAINER */
#include <kb/utils/dense_set.h>
/*  type  : kb_utils_DenseSet
            kb_utils_DenseSetItem
            kb_utils_DenseSetIter
    func  : kb_utils_DenseSet_has */


/*----------------------------------------------------------------------------*/
kb_Error
kb_utils_DenseSetItem_ini(kb_utils_DenseSetItem *const self)
{
    /* If `self` is NULL */
    if (!self)
        return kb_SELF_IS_NULL;

    /* Set values */
    self->id = (size_t)0;

    /* If everything went fine */
    return kb_OKAY;
}


/*----------------------------------------------------------------------------*/
kb_Error
kb_utils_DenseSet_new(kb_utils_DenseSet **const self,
                      size_t                    limit)
{
    /* Local variables */
    kb_utils_DenseSet      *dense_set;
    kb_utils_DenseSetItem **items;

    /* If `self` is NULL */
    if (!self)
        return kb_SELF_IS_NULL;

    /* If something goes wrong make sure instance is NULL */
    *self = NULL;

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
        return kb_ALLOC_FAIL;
}


/* TODO: **Make DenseSet inheritable**
         Add *_ini and *_fin methods to DenseSet */


/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
kb_Error
kb_utils_DenseSet_del(kb_utils_DenseSet **const self)
{
    /* If `self` or instance is NULL */
    if (!self || !*self)
        return kb_SELF_IS_NULL;

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
    bool has;
    size_t i;
    kb_Error error;
    if ((error = kb_utils_DenseSet_has(self, item, &has)))
        return error;

    /* If item already in container */
    if (has)
        return kb_OKAY;

    /* Get local reference */
    kb_utils_DenseSetItem **items = self->items;

    /* Resize array if necessary */
    if ((self->count + 1) >= self->limit)
    {
        /* Resize memory chunk */
        if (!(items = realloc(self->items,
                              sizeof(kb_utils_DenseSetItem *)*self->limit*2)))
            return kb_ALLOC_FAIL;

        /* Zero-out newly allocated space */
        for (i=self->limit; i<(self->limit*2); i++)
            items[i] = NULL;

        /* Update internals */
        self->items = items;
        self->limit *= 2;
    }

    /* If there are holes */
    if (self->index != self->count)
        for (i=self->index; i<self->limit; i++)
            if (!self->items[i])
            {
                self->index = i;
                break;
            }

    /* Store item */
    item->id = self->index;
    self->items[self->index] = item;

    /* Increase counter and indicator */
    ++self->count;
    ++self->index;

    /* If everything went fine */
    return kb_OKAY;
}


/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
kb_Error
kb_utils_DenseSet_pull(kb_utils_DenseSet     *const self,
                       kb_utils_DenseSetItem *const item)
{
    bool has;
    kb_Error error;
    if ((error = kb_utils_DenseSet_has(self, item, &has)))
        return error;

    /* If Item object in Set object */
    if (!has)
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
kb_Error
kb_utils_DenseSet_has(kb_utils_DenseSet     *const  self,
                      kb_utils_DenseSetItem *const  item,
                      bool                         *has)
{
    /* If any of the arguments is NULL */
    if (!self)
        return kb_SELF_IS_NULL;
    else if (!item)
        return kb_ARG2_IS_NULL;
    else if (!has)
        return kb_ARG3_IS_NULL;

    /* Return if Item object is in Set object */
    *has = self->items[item->id] == item ? true : false;

    /* If everything went fine */
    return kb_OKAY;
}


/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
kb_Error
kb_utils_DenseSet_len(kb_utils_DenseSet *const  self,
                      size_t                   *length)
{
    /* If `self` is NULL */
    if (!self)
        return kb_SELF_IS_NULL;
    else if(!length)
        return kb_ARG3_IS_NULL;

    /* Return length */
    *length = self->count;

    /* If everything went fine */
    return kb_OKAY;
}



/*----------------------------------------------------------------------------*/
kb_Error
kb_utils_DenseSetIter_new(kb_utils_DenseSetIter **const self,
                          kb_utils_DenseSet      *const dense_set)
{
    /* If any of the arguments is NULL */
    if (!self)
        return kb_SELF_IS_NULL;
    else if (!dense_set)
        return kb_ARG2_IS_NULL;

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
kb_utils_DenseSetIter_del(kb_utils_DenseSetIter **const self)
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
kb_utils_DenseSetIter_next(kb_utils_DenseSetIter  *const self,
                           kb_utils_DenseSetItem **const item)
{
    /* If any of the arguments is NULL */
    if (!self)
        return kb_SELF_IS_NULL;
    else if (!item)
        return kb_ARG2_IS_NULL;

    /* Get local references */
    size_t limit = self->dense_set->limit;
    kb_utils_DenseSetItem *const *const items = self->dense_set->items;

    /* Get next item from the iterator */
    *item = NULL;
    for (size_t i=self->index; i<limit; i++)
        if ((*item = items[i]))
        {
            self->index = ++i;
            break;
        }

    /* If everything went fine */
    return kb_OKAY;
}
