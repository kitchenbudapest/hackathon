/* INFO **
** INFO */

/* Header guard */
#ifndef KBJS_KEYS_H_4727978645810375
#define KBJS_KEYS_H_4727978645810375 1

#define KBJS_NATIVE             " {/* native */}"
#define KBJS_NATIVE_OBJ(O)      "object " O KBJS_NATIVE
#define KBJS_NATIVE_FUNC(F)     "function " F "()" KBJS_NATIVE
#define KBJS_HIDDEN_KEY_PREFIX  "\xFF\xFF"
#define KBJS_INSTANCE_PTR       KBJS_HIDDEN_KEY_PREFIX "instance_ptr"

#endif /* KBJS_KEYS_H_4727978645810375 */
