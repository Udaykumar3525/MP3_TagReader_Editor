#include "header.h"

void view_tags(const char *filename)
{
    FILE *fp = fopen(filename, "r"); // open file in read mode
    if(fp == NULL){
        printf("file not opened properly !\n");
        return;
    }

    Tag tag = {0};  // structure to store metadata

    //read first 10 bytes (ID3 header)
    unsigned char header[10];
    fread(header, 1, 10, fp);

    /* Here header is binary data without null terminator. 
       strcmp needs a null-terminated string, 
       so I used strncmp to compare only the first 3 bytes safely */
    if(strncmp((char*)header, "ID3", 3) != 0)    // check first 3 bytes must be "ID3"
    {
        printf("No ID3 tag found\n");
        fclose(fp);
        return;
    }

    int tag_size = 0;    //calculate metadata size = total bytes occupied by all frames
    //Why start from 6 - ID3 header stores metadata size in bytes 6 to 9 (extract size only from those 4 bytes)
    for(int i=6;i<10;i++)                          // ID3 uses syncsafe int (7-bit shift)
        tag_size = (tag_size<<7) | header[i];

    read_frames(fp, &tag, tag_size);    // Function call to read frames

    display(tag);     // Function call to display the frames

    fclose(fp);
}

/* Loop through all frames inside metadata block
    For each frame:
        read ID, read size, read data
        and store into struct                */

void read_frames(FILE *fp, Tag *tag, int tag_size)
{
    int bytes_read = 0;

    while(bytes_read < tag_size)   //Runs until tag size only to avoid going into audio data 
    {
        char id[5];
        id[4] = '\0';

        if(fread(id,1,4,fp)!=4)    // read frame id (Ex: TIT2, TPE1 etc)
            break;

        int size = read_frame_size(fp);   // read current frame size

        fseek(fp,2,SEEK_CUR);      // skip flags (2 bytes)

        bytes_read += 10 + size;

        if(size <= 0) break;

        char *buffer = malloc(size+1);    // dynamically allocataing  memory for frame data
        if(buffer == NULL) break;
        fread(buffer,1,size,fp);
        buffer[size] = '\0';       //making null terminator

        char *text = buffer + 1;       // skip encoding byte (ex: 00)

        //matching the frame id
        if(strcmp(id,"TIT2")==0) strcpy(tag->title,text);
        else if(strcmp(id,"TPE1")==0) strcpy(tag->artist,text);
        else if(strcmp(id,"TALB")==0) strcpy(tag->album,text);
        else if(strcmp(id,"TYER")==0) strcpy(tag->year,text);
        else if(strcmp(id,"COMM")==0) strcpy(tag->comment,text);
        else if(strcmp(id,"TCON")==0) strcpy(tag->genre, text);

        
        //APIC = Album Picture frame - It stores: [ encoding ][ mime type ][ picture type ][ description ][ image bytes ]
        // index (0 - )
        else if(strcmp(id,"APIC")==0)   
        {
            int pos = 0;

            pos++;  // skip encoding byte (1 byte)

            while(buffer[pos] != '\0') pos++;  //mime type string (null terminated) - "image/jpeg\0"
             
            pos++;   //skip the null terminator

            pos++;  // skip picture type (1 byte)

            while(buffer[pos] != '\0') pos++;   //description string (null terminated) - "Cover\0"

            pos++;  //skip the null terminator

            int img_size = size - pos;   //remaining bytes = real image , actual image binary data

            FILE *img = fopen("cover.jpg","w");

            if(img){
                fwrite(buffer+pos,1,img_size,img);
                fclose(img);
                printf(YELLOW "\nAlbum art Also extracted (APIC) -> cover.jpg\n" RESET);
            }
        }
        free(buffer);
    }
}

//Reads 4 bytes from file - Converts them into integer- Because frame tells how many bytes belong to it.
int read_frame_size(FILE *fp)
{
    unsigned char s[4];

    fread(s,1,4,fp);    // read 4 bytes

    int size = 0;

    for(int i=0;i<4;i++)          //running loop for 4bytes times
        size = size*256 + s[i];     // combine bytes using base-256 math

    return size;
}


void display(Tag tag)   //Printing final metadata 
{
    printf("\n------------>" MAGENTA " MP3 METADATA " RESET "<-----------\n" RESET);

    printf("Title   : " GREEN "%s\n" RESET, tag.title);
    printf("Artist  : " GREEN "%s\n" RESET, tag.artist);
    printf("Album   : " GREEN "%s\n" RESET, tag.album);
    printf("Year    : " GREEN "%s\n" RESET, tag.year);
    printf("Comment : " GREEN "%s\n" RESET, tag.comment);
    printf("Genre   : " GREEN "%s\n" RESET, tag.genre);
    
    printf("----------------------------------------\n\n");
}



