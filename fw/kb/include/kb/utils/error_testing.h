/* INFO **
** INFO **/

/* Header guard */
#ifndef KB_UTILS_ERROR_HANDLING_H_1961672676435921
#define KB_UTILS_ERROR_HANDLING_H_1961672676435921 1

/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
/* Include standard headers */
#include <stdio.h>
/*  const : stderr
    func  : fputs */

/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
/* Include kibu headers */
#include <kb/errors.h>
/*  type  : kb_Error
    func  : kb_Error_str */


/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
#ifndef KB_ERROR_TESTING
    #define KB_ERROR_TRY(EXPR) EXPR
#else
    #define KB_ERROR_STR__(V) #V
    #define KB_ERROR_STR_(V)  KB_ERROR_STR__(V)
    #define KB_ERROR_TRY(E)                                                    \
        do                                                                     \
        {                                                                      \
            kb_Error error;                                                    \
            if ((error = E))                                                   \
            {                                                                  \
                fputs("\x1b[31m", stderr);                                     \
                fputs(kb_Error_str(error), stderr);                            \
                fputs(":\x1b[0m ", stderr);                                    \
                fputs("in file: \x1b[1m", stderr);                             \
                fputs(KB_ERROR_STR_(__FILE__), stderr);                        \
                fputs("\x1b[0m, at line: \x1b[1m", stderr);                    \
                fputs(KB_ERROR_STR_(__LINE__), stderr);                        \
                fputs("\x1b[0m, in expression: \x1b[1m", stderr);              \
                fputs(KB_ERROR_STR_(E) "\x1b[0m\n", stderr);                   \
                                                                               \
            }                                                                  \
        }                                                                      \
        while (0)
#endif /* KB_ERROR_TESTING */

#endif /* KB_UTILS_ERROR_HANDLING_H_1961672676435921 */
