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
#include "nanoxml.h"

int main()
{
    DOM dom;
    nanoxml_load_file("..\\..\\example\\test.html", &dom);

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
}
