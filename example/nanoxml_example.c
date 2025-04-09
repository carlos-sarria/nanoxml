/****************************************************************************
  @file nanoxml_example.c
  @author Carlos Sarria
  @date 02 Apr 2025
  @brief Example for nanoxml library which prints out the original HTML parsed.

  Copyright (c) 2025 Carlos Sarria
 ****************************************************************************/
#include "nanoxml.h"

int main()
{
    DOM dom;
    char *xmlfile = "..\\..\\example\\test.html";
    e_error error = nanoxml_load_file(xmlfile, &dom);
    if(error != SUCCESS) {
        fprintf(stderr, "failed to process: %s", xmlfile);
        exit(EXIT_FAILURE);
    }

    CONTENT *c = dom.content_list;

    while (c){

        printf("TAGS: ");
        for(int i=0; i<c->num_tags; i++) printf("[%s] ", c->tags[i]);
        if(c->type == UNIQUE_TAG)   printf("\n UNIQUE TAG: %s\n", c->content);
        else if(c->type == COMMENT) printf("\n COMMENT: %s\n", c->content);
        else                        printf("\n CONTENT: %s\n", c->content);

        c = (CONTENT *)c->prev_node;
    }

    nanoxml_free_content(&dom);

    exit(EXIT_SUCCESS);
}
