#include <stdio.h>
#include <string.h>       //used for string operations
#include "header.h"

//controller - handles command line and decides view or edit
//argc = number of inputs, or Arguments count, argv = actual inputs
int main(int argc, char *argv[])
{
    FILE *fp;

    // If user gives no arguments - show usage
    if (argc < 2)  
    {
        printf(RED "\nInvalid usage !\n" RESET);

        printf(CYAN "-------------------------------------------------------------\n" RESET);
        printf(MAGENTA  "Usage:\n" RESET);

        printf("  View MP3 metadata   →   " GREEN "./a.out -v <mp3file>\n" RESET);
        printf("  Edit metadata       →   " GREEN "./a.out -e -<option> <data> <file>\n" RESET);
        printf("  Help menu           →   " GREEN "./a.out -help\n" RESET);

        printf(CYAN "-------------------------------------------------------------\n\n" RESET);

        return 0;
    }

    // Display help/usage menu
    if (strcmp(argv[1], "-help") == 0)
    {
        printf("\n-------------> MP3 TAG READER HELP <-------------\n");

        printf(MAGENTA "\nAvailable Commands:\n\n" RESET);

        printf("View MP3 metadata  : " GREEN "./a.out -v <mp3filename>\n" RESET);

        printf("Edit Title         : " GREEN "./a.out -e -t <data> <file>\n" RESET);
        printf("Edit Artist        : " GREEN "./a.out -e -a <data> <file>\n" RESET);
        printf("Edit Album         : " GREEN "./a.out -e -A <data> <file>\n" RESET);
        printf("Edit Year          : " GREEN "./a.out -e -y <data> <file>\n" RESET);
        printf("Edit Genre         : " GREEN "./a.out -e -m <data> <file>\n" RESET);
        printf("Edit Comment       : " GREEN "./a.out -e -c <data> <file>\n" RESET);

        printf("--------------------------------------------------\n\n");
        return 0;
    }

    if(strcmp(argv[1], "-v") == 0)     //View mode
    {
        //Must pass 3 argumnets - ./a.out -v file_name
        view_tags(argv[2]);
    }

    else if(strcmp(argv[1], "-e") == 0)   //Edit mode
    {
        //Must pass 5 argumnets - ./a.out -e option content_toupdate file_name
        edit_tag(argv[4], argv[2], argv[3]);
    }

    else{
        printf(RED "Invalid option ! \n" RESET);
    }

    return 0;
}
