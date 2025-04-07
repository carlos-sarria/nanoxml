#ifndef __ERROR_H__
#define __ERROR_H__

typedef enum {
    SUCCESS = 0,
    ERR_UNKNOWN = 1,
    ERR_WRONG_PARAMETER = 2,
    ERR_OUT_OF_BOUNDS = 3,
    ERR_NULL_POINTER = 4,
    ERR_WRONG_POINTER = 5,
    ERR_OUT_OF_MEMORY = 6,
    ERR_FILE_NOT_FOUND = 7,
} e_error;

char *get_error (e_error e);

typedef enum {
    ERR_ERROR,
    ERR_WARNING,
    ERR_FATAL
} e_error_type;

#define ERROR ERR_ERROR, __FILE__, __LINE__
#define WARNING ERR_WARNING, __FILE__, __LINE__
#define SYS_ERROR ERR_FATAL, __FILE__, __LINE__, strerror(errno)

/* Use as:
 * print_error(ERROR, "Out of bunds (%d), size);     // Will ouput the message and quit.
 * print_error(WARNING, "Close to limit (%d), size); // Will ouput the message and continue.
 * print_error(SYS_ERROR);                           // Will output the system error and quit.
 * */
void print_error (e_error_type e, char *file, int line, const char *text, ...);

#endif
