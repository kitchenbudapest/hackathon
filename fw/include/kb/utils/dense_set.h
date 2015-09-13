/* INFO **
** INFO */

/* Header guard */
#ifndef __KB_UTILS_DENSE_SET_H_32497603607726133__
#define __KB_UTILS_DENSE_SET_H_32497603607726133__

/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
/* Include standard headers */
#include <stddef.h>
/*  type  : size_t */
#include <stdbool.h>
/*  type  : bool */

/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
/* Include kibu headers */
#include <kb/errors.h>
/*  type  : kb_Error */


/*----------------------------------------------------------------------------*/
#define KB_UTILS_DENSE_SET_ITEM_MEMBERS() \
    size_t id;                            \


/*----------------------------------------------------------------------------*/
typedef struct
{
    KB_UTILS_DENSE_SET_ITEM_MEMBERS()
} kb_utils_DenseSetItem;


/*----------------------------------------------------------------------------*/
typedef struct
{
    size_t                  limit;
    size_t                  count;
    size_t                  index;
    kb_utils_DenseSetItem **items;
} kb_utils_DenseSet;


/*----------------------------------------------------------------------------*/
typedef struct
{
    kb_utils_DenseSet *dense_set;
    size_t             index;
} kb_utils_DenseSetIter;


/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
/* Returns:
    kb_OKAY:
        if no error occured
    kb_SELF_IS_NULL:
        if first argument is a NULL pointer
    kb_ALLOC_FAIL:
        if allocation of internals failed */
kb_Error
kb_utils_DenseSet_new(kb_utils_DenseSet **const self,
                      size_t                    limit);
/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
/* Returns:
    kb_OKAY:
        if no error occured
    kb_SELF_IS_NULL:
        if first argument is a NULL pointer */
kb_Error
kb_utils_DenseSet_del(kb_utils_DenseSet **const self);
/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
/* Returns:
    kb_OKAY:
        if no error occured
    kb_SELF_IS_NULL:
        if first argument is a NULL pointer
    kb_ARG2_IS_NULL:
        if second argument is a NULL pointer
    kb_ALLOC_FAIL:
        if allocation of internals failed */
kb_Error
kb_utils_DenseSet_push(kb_utils_DenseSet     *const self,
                       kb_utils_DenseSetItem *const item);
/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
/* Returns:
    kb_OKAY:
        if no error occured
    kb_SELF_IS_NULL:
        if first argument is a NULL pointer
    kb_ARG2_IS_NULL:
        if second argument is a NULL pointer
    kb_ITEM_NOT_IN_CONTAINER:
        if second argument is not in first argument */
kb_Error
kb_utils_DenseSet_pull(kb_utils_DenseSet     *const self,
                       kb_utils_DenseSetItem *const item);
/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
/* Returns:
    kb_OKAY:
        if no error occured
    kb_SELF_IS_NULL:
        if first argument is a NULL pointer
    kb_ARG2_IS_NULL:
        if second argument is a NULL pointer
    kb_ARG2_IS_NULL:
        if third argument is a NULL pointer */
kb_Error
kb_utils_DenseSet_has(kb_utils_DenseSet     *const  self,
                      kb_utils_DenseSetItem *const  item,
                      bool                         *has);
/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
/* Returns:
    kb_OKAY:
        if no error occured
    kb_SELF_IS_NULL:
        if first argument is a NULL pointer
    kb_ARG2_IS_NULL:
        if second argument is a NULL pointer */
kb_Error
kb_utils_DenseSet_len(kb_utils_DenseSet *const  self,
                      size_t                   *length);
/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
/* Returns:
    kb_OKAY:
        if no error occured
    kb_SELF_IS_NULL:
        if first argument is a NULL pointer
    kb_ARG2_IS_NULL:
        if second argument is a NULL pointer
    kb_ALLOC_FAIL:
        if allocation of the new Iter object failed */
kb_Error
kb_utils_DenseSetIter_new(kb_utils_DenseSetIter **const self,
                          kb_utils_DenseSet      *const dense_set);
/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
/* Returns:
    kb_OKAY:
        if no error occured
    kb_SELF_IS_NULL:
        if first argument is a NULL pointer */
kb_Error
kb_utils_DenseSetIter_del(kb_utils_DenseSetIter **const self);
/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
/* Returns:
    kb_OKAY:
        if no error occured
    kb_SELF_IS_NULL:
        if first argument is a NULL pointer
    kb_ARG2_IS_NULL:
        if second argument is a NULL pointer */
kb_Error
kb_utils_DenseSetIter_next(kb_utils_DenseSetIter  *const self,
                           kb_utils_DenseSetItem **const item);


#endif /* __KB_UTILS_DENSE_SET_H_32497603607726133__ */
