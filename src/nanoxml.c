/****************************************************************************
  @file nanoxml.c
  @author Carlos Sarria
  @date 02 Apr 2025
  @brief Small and efficient XML browser that supports HTML constructs.
  
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
static inline int IS_EMPTY(char *s)
{
    char c;
    while (c=*s++) if (c>32) return 0;
    return 1;
}

static inline char* TRIM(char *s)
{
    int len = strlen(s)-1;
    while(s[len]<=32) s[len--]=0;

    len = 0;
    while (s[len++]<32);

    return (s+len);
}

static inline e_type GET_TYPE(char *s)
{
    int tag = 0;
    char trimmed[128];

    if(s[strlen(s)-1] == '/') return UNIQUE_TAG;

    if(s[0]=='!') return COMMENT; // HTML comment

    sscanf(s, "%[^ ]", &trimmed); /* Only until space. Ignore payload. */

    while(unique_tags[tag]) {
        if (strcmp(unique_tags[tag], trimmed)==0) return UNIQUE_TAG;
        tag++;
    }

    return TAG;
}

static inline void TAG_PUSH(char **stack, char *str, int *size)
{
    if(*size<MAX_TAGS-1) stack[*size]=str;
    (*size)++;
}

static inline void TAG_POP(char **stack, char *str, int *size)
{
    int pos = 0;
    char trimmed[128];

    sscanf(str, "%[^ ]", &trimmed); /* Only until space. Ignore payload. */

    while(stack[pos] && strcmp(trimmed,stack[pos])) pos++; // Find first match
    if(pos>*size) return; // not found
    while(stack[pos]) stack[pos-1]=stack[pos++]; // Move pointers one step up

    (*size)--;
}

/*****************************************************************************/
/* nanoxml_allocate_buffer                                                   */
/*****************************************************************************/
e_error nanoxml_allocate_buffer(size_t len, DOM *full_DOM)
{
    full_DOM->buffer_size = len;

    full_DOM->buffer = (char *)malloc(len*sizeof(char));

    if (full_DOM->buffer == NULL) {
        return ERR_OUT_OF_MEMORY;
    }

    return SUCCESS;
}

/*****************************************************************************/
/* nanoxml_create_content                                                    */
/*****************************************************************************/
e_error nanoxml_create_content(DOM *dom, char *str, char **tag_stack, int  stack_size, e_type type)
{
    static CONTENT *temp_prev = NULL;

    CONTENT *content = (CONTENT *)malloc(sizeof(CONTENT));
    if(content==NULL) return ERR_OUT_OF_MEMORY;

    content->tags = (char **)malloc(sizeof(char *)*stack_size);
    if(content->tags==NULL) return ERR_OUT_OF_MEMORY;

    memcpy(content->tags, tag_stack, sizeof(char *)*stack_size);
    content->num_tags = stack_size;
    content->content = str;
    content->type = type;
    content->prev_node = NULL;

    if(dom->content_list==NULL) dom->content_list = content; // start of linked list

    if(temp_prev) temp_prev->prev_node = content; // linked list (reversed)

    temp_prev = content;

    dom->num_contents++;

    return SUCCESS;
}

/*****************************************************************************/
/* nanoxml_free_content                                                      */
/*****************************************************************************/
void nanoxml_free_content(DOM *dom)
{
    CONTENT *content = dom->content_list;

    while (content){
        CONTENT *temp = (CONTENT *)content->prev_node;
        if(content->tags) free(content->tags);
        if(content) free(content);
        content = temp;
    }
}
/*****************************************************************************/
/* nanoxml_process                                                        */
/*****************************************************************************/
e_error nanoxml_process(DOM *dom)
{
    char *pos = dom->buffer;
    int count = 0;
    char *tag_stack[MAX_TAGS];
    int  stack_size = 0;
    e_error error;

    dom->content_list = NULL;
    dom->num_contents = 0;

    memset(tag_stack, 0, sizeof(char*)*MAX_TAGS);

    while ((pos-dom->buffer) < dom->buffer_size) {

        pos = strchr(pos, 0x00)+1;

        if(pos[0]=='/') {
            TAG_POP(tag_stack, pos+1, &stack_size);
        }
        else {
            e_type t = GET_TYPE(pos);
            if(t==TAG) {
                TAG_PUSH(tag_stack, pos, &stack_size);
            }
            else {
               error = nanoxml_create_content(dom, pos, tag_stack,stack_size, t);
               if(error != SUCCESS) return error;
            }
        }

        pos = strchr(pos, 0x00)+1;
        if(!IS_EMPTY(pos)) {
            error = nanoxml_create_content(dom, pos, tag_stack,stack_size, TEXT);
            if(error != SUCCESS) return error;
        }

        count++;
    }

    return SUCCESS;
}
/*****************************************************************************/
/* nanoxml_preprocess                                                        */
/*****************************************************************************/
void nanoxml_preprocess(DOM *full_DOM)
{
    char c;
    unsigned long len = full_DOM->buffer_size;

    while(len--) {
        c = full_DOM->buffer[len];
        if (c=='<' || c=='>') full_DOM->buffer[len] = 0;
    }
}
/*****************************************************************************/
/* nanoxml_load_string                                                       */
/*****************************************************************************/
e_error nanoxml_load_string(const char *string, DOM *dom)
{
    e_error error;

    nanoxml_allocate_buffer(strlen(string), dom);

    memcpy(dom->buffer, string, dom->buffer_size);

    nanoxml_preprocess(dom);
    error = nanoxml_process(dom);
    if(error != SUCCESS) return error;

    return SUCCESS;
}
/*****************************************************************************/
/* nanoxml_load_file                                                         */
/*****************************************************************************/
e_error nanoxml_load_file(const char *filename, DOM *full_DOM)
{
    FILE *file = fopen(filename, "rb");
    if (!file) {
        return ERR_FILE_NOT_FOUND;
    }

    fseek(file, 0, SEEK_END);
    size_t len = (unsigned long)ftell(file);
    fseek(file, 0, SEEK_SET);

    nanoxml_allocate_buffer(len, full_DOM);
    if(fread(full_DOM->buffer, sizeof(char), len, file) != len){
        return ERR_UNKNOWN;
    }

    fclose(file);

    nanoxml_preprocess(full_DOM);
    e_error error = nanoxml_process(full_DOM);
    if(error != SUCCESS) {
        return error;
    }

    return SUCCESS;
}
