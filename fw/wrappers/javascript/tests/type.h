/* INFO **
** INFO */

/* Header guard */
#ifndef __JS_TYPE_H_12784139653875715__
#define __JS_TYPE_H_12784139653875715__

#define JS_TYPE_NAME_SIZE (size_t)128

/*----------------------------------------------------------------------------*/
typedef struct
{
    size_t id;
    char   name[JS_TYPE_NAME_SIZE];
} T;


/*----------------------------------------------------------------------------*/
typedef enum
{
    OKAY,
    FAIL,
    SELF_IS_NULL,
    ARG2_IS_NULL,
    ALLOC_FAIL,
} E;

/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
/* Returns:
    OKAY
    SELF_IS_NULL
    ALLOC_FAIL */
E
T_new(T          **const self,
      const char  *const name);
/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
/* Returns:
    OKAY
    SELF_IS_NULL */
E
T_del(T **const self);
/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
/* Returns:
    OKAY
    SELF_IS_NULL
    ARG2_IS_NULL */
E
T_str(T     *const self,
      char **const repr);


#endif /* __JS_TYPE_H_12784139653875715__ */
