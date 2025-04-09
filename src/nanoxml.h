/****************************************************************************
  @file nanoxml.h
  @author Carlos Sarria
  @date 02 Apr 2025
  @brief Small and efficient XML browser that supports HTML constructs.

  Copyright (c) 2025 Carlos Sarria
 ****************************************************************************/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_TAGS 128

typedef enum {
    SUCCESS,
    ERR_UNKNOWN,
    ERR_OUT_OF_MEMORY,
    ERR_FILE_NOT_FOUND,
} e_error;

typedef enum {
    TAG,
    TEXT,
    UNIQUE_TAG,
    COMMENT,
} e_type;

typedef struct {
    char **tags;
    int num_tags;
    char *content;
    void *prev_node;
    e_type type;
} CONTENT;

typedef struct {
    CONTENT *content_list; // Linked-list of content with all own tags
    int  num_contents;
    char *buffer;
    size_t buffer_size;
} DOM;


e_error nanoxml_load_string (const char *string, DOM *full_DOM);
e_error nanoxml_load_file   (const char *filename, DOM *full_DOM);
