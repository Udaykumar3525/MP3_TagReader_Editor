#include "header.h"

//open file in read+write mode - skip header - find target frame - overwrite data
void edit_tag(const char *filename, const char *opt, const char *new_data)
{
    FILE *fp = fopen(filename, "r+");

    if(fp == NULL){
        printf("file not opened properly !\n");
        return;
    }

    fseek(fp, HEADER_SIZE, SEEK_SET);    // skip 10-byte ID3 header

    char id[5];      // allocate 5 bytes (Frame ID  4 char + 1 byte for null terminator)
    id[4] = '\0';    // make it string

    while(fread(id,1,4,fp)==4)
    {
        int size = read_frame_size(fp);

        fseek(fp,2,SEEK_CUR);   // skip flags

        long data_pos = ftell(fp);

        int match = 0;

        if(strcmp(opt,"-t")==0 && strcmp(id,"TIT2")==0) match=1;
        else if(strcmp(opt,"-a")==0 && strcmp(id,"TPE1")==0) match=1;
        else if(strcmp(opt,"-A")==0 && strcmp(id,"TALB")==0) match=1;
        else if(strcmp(opt,"-y")==0 && strcmp(id,"TYER")==0) match=1;
        else if(strcmp(opt,"-c")==0 && strcmp(id,"COMM")==0) match=1;
        else if(strcmp(opt,"-m")==0 && strcmp(id,"TCON")==0) match=1;

        if(match)
        {
            fseek(fp, data_pos, SEEK_SET);                   // go to data
            fputc(0, fp);                                   //write encoding byte first 
            fwrite(new_data, 1, strlen(new_data), fp);     //After write new text 
            int remaining = size - 1 - strlen(new_data);  //clear remaining old bytes (fill remaining space with zeros) 

            for(int i=0;i<remaining;i++)
                fputc(0, fp);

            printf("Tag updated successfully ✅  \n");

            fclose(fp);
            return;
        }

        fseek(fp, size, SEEK_CUR);
    }

    printf("Tag not found !\n");
    fclose(fp);
}
