#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

#include "error.h"


char *error_str[] = {
    "SUCCESS",
    "ERR_UNKNOWN",
    "ERR_WRONG_PARAMETER",
    "ERR_OUT_OF_BOUNDS",
    "ERR_NULL_POINTER",
    "ERR_WRONG_POINTER",
    "ERR_OUT_OF_MEMORY"
};

char *get_error (e_error e)
{
    return error_str[e];
}

void print_error (e_error_type e, char *file, int line, const char *text, ...)
{
   va_list list;

   fprintf(stderr, (e==ERR_WARNING)?"WARNING: ":"ERROR: ");
   va_start(list, text);
   fprintf(stderr, "%s:%d: ", file, line);
   vfprintf(stderr, text, list);
   fprintf(stderr, "\n");
   va_end(list);

   if(e == ERR_FATAL) exit(errno);
}
