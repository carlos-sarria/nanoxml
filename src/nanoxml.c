/****************************************************************************
  @file doxygen_c.h
  @author Carlos Sarria
  @date 02 Apr 2025
  @brief File containing example of doxygen usage for quick reference.
  
  Copyright (c) 2025 Carlos Sarria
 ****************************************************************************/

#include "nanoxml.h"

char *unique_tags[] = {
    "br",
    "area",
    "base",
    "col",
    "embed",
    "hr",
    "img",
    "input",
    "keygen",
    "link",
    "meta",
    "param",
    "source",
    "track",
    "wbr",
    NULL
};

/*****************************************************************************/
/* INLINES                                                                   */
/*****************************************************************************/
static inline bool IS_EMPTY(char *s)
{
    char c;
    while (c=*s++) if (c>32) return false;
    return true;
}

static inline char* TRIM(char *s)
{
    int len = strlen(s)-1;
    while(s[len]<=32) s[len--]=0;

    len = 0;
    while (s[len++]<32);

    return (s+len);
}

static inline bool IS_UNIQUE(char *s)
{
    int tag = 0;
    char trimmed[128];

    if(s[strlen(s)-1] == '/') return true;

    while(unique_tags[tag]) {
        sscanf(s, "%[^ ]", &trimmed); /* Only until space. Ignore payload. */
        if (strcmp(unique_tags[tag],s)==0) return true;
        tag++;
    }

    return false;
}


/*****************************************************************************/
/* nanoxml_allocate_buffer                                                   */
/*****************************************************************************/
e_error nanoxml_allocate_buffer(size_t len, DOM *full_DOM)
{
    full_DOM->buffer_size = len;

    full_DOM->buffer = (char *)malloc(len*sizeof(char));

    if (full_DOM->buffer == NULL) {
        print_error(SYS_ERROR);
    }

    return SUCCESS;
}
/*****************************************************************************/
/* nanoxml_process                                                        */
/*****************************************************************************/
e_error nanoxml_process(DOM *dom)
{
    char *pos = dom->buffer;
    int count = 0;

    while ((pos-dom->buffer) < dom->buffer_size) {

            pos = strchr(pos, 0x00)+1;

            if(pos[0]=='/') {
                printf("/TAG: %s\n", pos);
            }
            else {
                if(IS_UNIQUE(pos))  printf("UNQ: %s\n", pos);
                else                printf("TAG: %s\n", pos);
            }

            pos = strchr(pos, 0x00)+1;
            if(!IS_EMPTY(pos)) printf("CONTENT: %s\n", pos);

            count++;
        }

    return SUCCESS;
}
/*****************************************************************************/
/* nanoxml_preprocess                                                        */
/*****************************************************************************/
e_error nanoxml_preprocess(DOM *full_DOM)
{
    char c;
    unsigned long len = full_DOM->buffer_size;

    while(len--) {
        c = full_DOM->buffer[len];
        if (c=='<' || c=='>') full_DOM->buffer[len] = 0;
    }

    return SUCCESS;
}
/*****************************************************************************/
/* nanoxml_load_string                                                       */
/*****************************************************************************/
e_error nanoxml_load_string(const char *string, DOM *full_DOM)
{
    nanoxml_allocate_buffer(strlen(string), full_DOM);

    memcpy(full_DOM->buffer, string, full_DOM->buffer_size);

    nanoxml_preprocess(full_DOM);
    nanoxml_process(full_DOM);

    return SUCCESS;
}
/*****************************************************************************/
/* nanoxml_load_file                                                         */
/*****************************************************************************/
e_error nanoxml_load_file(const char *filename, DOM *full_DOM)
{
    FILE *file = fopen(filename, "rb");
    if (!file) {
        print_error(ERROR,"%s %s", strerror(errno), filename);
    }
    fseek(file, 0, SEEK_END);
    size_t len = (unsigned long)ftell(file);
    fseek(file, 0, SEEK_SET);

    nanoxml_allocate_buffer(len, full_DOM);
    if(fread(full_DOM->buffer, sizeof(char), len, file) != len){
        print_error(SYS_ERROR);
    }

    fclose(file);

    nanoxml_preprocess(full_DOM);
    nanoxml_process(full_DOM);

    return SUCCESS;
}
