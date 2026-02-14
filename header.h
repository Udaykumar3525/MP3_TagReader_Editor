//Prevents- multiple inclusion errors, Compiler includes file only once.
// HEADER FILE: This file contains: Libraries, Structure definitions, Function declarations
#ifndef HEADER_H
#define HEADER_H

//Standard libraries
#include <stdio.h>     
#include <stdlib.h>       //malloc, free
#include <string.h>      //strcmp, strcpy

#define HEADER_SIZE 10
//Because - ID3v2 header is always 10 bytes, So we skipping header in edit/view

// Colors 
#define RED     "\033[31m"
#define GREEN   "\033[32m"
#define YELLOW  "\033[33m"
#define BLUE    "\033[34m"
#define CYAN    "\033[36m"
#define MAGENTA  "\033[35m"
#define RESET   "\033[0m"


//Structure to store all extracted tags - Each frame's content will be copied here
typedef struct           //Thnk like This is our metadata container 
{
    char title[100];
    char artist[100];
    char album[100];
    char year[10];
    char comment[200];
    
    char genre[50];
} Tag;


//Function declarations - Just tells compiler: this function exists somewhere
//VIEW FUNCTIONS
void view_tags(const char *filename);                     // open file and extract metadata
void read_frames(FILE *fp, Tag *tag, int tag_size);      // read all frames one by one
void display(Tag tag);                                  // display final metadata

int read_frame_size(FILE *fp);       //Convert 4 size bytes -> integer

//EDIT FUNCTIONS - edit a specific frame content
void edit_tag(const char *filename, const char *opt, const char *new_data);

#endif
