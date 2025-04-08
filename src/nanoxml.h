/****************************************************************************
  @file doxygen_c.h
  @author Carlos Sarria
  @date 02 Apr 2025
  @brief File containing example of doxygen usage for quick reference.
  
  Copyright (c) 2025 Carlos Sarria 
 ****************************************************************************
  MIT License

  Permission is hereby granted, free of charge, to any person obtaining a copy
  of this software and associated documentation files (the "Software"), to deal
  in the Software without restriction, including without limitation the rights
  to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
  copies of the Software, and to permit persons to whom the Software is
  furnished to do so, subject to the following conditions:

  The above copyright notice and this permission notice shall be included in all
  copies or substantial portions of the Software.

  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
  SOFTWARE.
 ****************************************************************************/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#include "error.h"

#define MAX_TAGS 128

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
