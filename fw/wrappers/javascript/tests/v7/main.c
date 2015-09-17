/* INFO **
** INFO */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "external/include/v7.h"

#include "js_type.h"
/*  func  : create_T */

#define CHUNK_SIZE (size_t)8

int
main(void)
{
    FILE *js_file = fopen("main.js", "r");
    if (!js_file)
    {
        puts("Unable to open file");
        return EXIT_FAILURE;
    }

    char   *js_code;
    char    js_code_buf[CHUNK_SIZE];
    size_t  js_code_idx = (size_t)0;
    size_t  js_code_len = CHUNK_SIZE;
    if (!(js_code = malloc(sizeof(char)*(js_code_len + (size_t)1))))
    {
        puts("Allocation failed");
        return EXIT_FAILURE;
    }

    size_t read_len;
    while ((read_len = fread(js_code_buf,
                             sizeof(char),
                             CHUNK_SIZE,
                             js_file)) > 0)
    {
        strncpy(js_code + js_code_idx, js_code_buf, read_len);

        if ((js_code_idx += read_len) >= js_code_len)
        {
            if (!(js_code = realloc(js_code,
                                    sizeof(char)*((js_code_len*=2) + (size_t)1))))
            {
                puts("Reallocation failed");
                free(js_code);
                fclose(js_file);
                return EXIT_FAILURE;
            }
        }
    }

    if (ferror(js_file))
    {
        puts("Unable to read file");
        free(js_code);
        fclose(js_file);
        return EXIT_FAILURE;
    }

    fclose(js_file);
    js_code[js_code_idx] = '\0';

    v7_val_t result;
    struct v7 *v7 = v7_create();

    create_T(v7);


    switch(v7_exec(v7, &result, js_code))
    {
        case V7_OK:
            break;

        case V7_SYNTAX_ERROR:
            puts("SyntaxError");
            break;

        case V7_EXEC_EXCEPTION:
            puts("Exception");
            v7_println(v7, result);
            break;

        case V7_AST_TOO_LARGE:
            puts("AST segment longer than 16bit");
            break;

        case V7_STACK_OVERFLOW:
            puts("StackOverflowError");
            break;
    }
    v7_destroy(v7);

    free(js_code);
    return EXIT_SUCCESS;
}
