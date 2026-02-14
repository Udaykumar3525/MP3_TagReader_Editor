----------------> 🎵 MP3 TAG READER & EDITOR (ID3v2) <----------------
Author  : Udaykumar Upputuri  
Language: C 
-----------------------------------------------------------------------

## ▶ INTRODUCTION :
MP3 tag reader is a software which will read and display MP3 (ID3) tag
information from MP3 files. The software will be desktop based and not web
based.  
It will be useful to individuals who wish to view and collect
mp3 tag data. This project can be extended to implement a tag editor, 
where in users can modify mp3 tag information.

## 📌 PROJECT OVERVIEW :
This project is a command-line based MP3 Tag Reader and Editor
implemented completely in C.  
It reads and edits MP3 metadata stored using the ID3v2 format.  
The program extracts information like:  
• Title  
• Artist  
• Album  
• Year  
• Comment  
• Genre  
• Album Art (Cover Image)  

It can also modify these tags directly inside the MP3 file.  

## 📂 WHAT IS ID3? :  
ID3 is a metadata container used in MP3 files.  
-> MP3 file structure:  

| ID3 Header (10 bytes) |  
| Metadata Frames      |  
| Audio Data           |  

Each metadata item is stored inside frames like:  

TIT2  - Title  
TPE1  - Artist  
TALB  - Album  
TYER  - Year  
COMM  - Comment  
TCON  - Genre  
APIC  - Album Art  
and so on....  

-> ID3 HEADER STRUCTURE (10 Bytes)   
Bytes 0–2  - "ID3" signature  
Byte 3     - Version  
Byte 4     - Revision  
Byte 5     - Flags  
Bytes 6–9  - Metadata size (syncsafe integer)  

-> FRAME STRUCTURE (Every tag uses this format)  
Frame ID                - 4B  
Size                    - 4B   
Flags                   - 2B  
Frame Data (variable)   -  n bytes    

Ex: TIT2 | 0005  | 00   | 00 U d a y --> 00 encoding, uday is title txt  
FRAME DATA STRUCTURE --  encoding (1B) + text string(n bytes)  

-> APIC (ALBUM ART) FRAME STRUCTURE  
Encoding    - 1B  
Mime type   - string\0  
pic type    - 1B  
Description - string\0  
Image data  - Raw data  

## ⚙️ FEATURES IMPLEMENTED  
-> View metadata from MP3  
-> Edit metadata fields  

🚀 HOW THE PROGRAM WORKS :  
-----> VIEW MODE (-v)  
Steps:  
1. Open MP3 file in binary mode  
2. Read first 10 bytes (ID3 header)  
3. Validate "ID3" signature  
4. Extract metadata size (syncsafe integer)  
5. Loop through frames until metadata ends (metadata size)  
6. For each frame:  
      -> read frame ID  
      -> read frame size  
      -> read frame data  
      -> store into structure  
7. Print all tags  

Example: ./a.out -v sample.mp3  

-----> EDIT MODE (-e)  
Steps:  
1. Open file in read+write mode  
2. Skip 10-byte header  
3. Search target frame  
4. Overwrite new text data  
5. Save changes  

Example: ./a.out -e -t "My Song" sample.mp3  

## 🖥️ USAGE :  
View tags: ./a.out -v [mp3file]  

Edit tags:  
    ./a.out -e -t [title]   [file]  
    ./a.out -e -a [artist]  [file]  
    ./a.out -e -A [album]   [file]  
    ./a.out -e -y [year]    [file]  
    ./a.out -e -c [comment] [file]  

Example:  
    ./a.out -v rajasaab.mp3  
    ./a.out -e -y 2024 rajasaab.mp3  

## 📁 PROJECT FILES :  
main.c     -> handles CLI arguments  
view.c     -> reads & displays tags  
edit.c     -> modifies tags  
header.h   -> structure + prototypes  
README.txt -> project explanation  

## 🧠 CONCEPTS USED :  
• fopen / fread / fwrite / fseek  
• Binary file parsing  
• Structures  
• Pointers  
• Dynamic memory allocation (malloc/free)  
• String handling (ex: strncmp, strcmp, strcpy)  
• Byte manipulation  
• Syncsafe integer decoding  
• Frame-based parsing  

🔗 References  
1. Wikipedia article on ID3 tag - http://en.wikipedia.org/wiki/ID3  
2. ID3 tag standard website - http://id3.org  
3. ID3 tag version 2.3 standard - http://id3.org/id3v2.3.0  

📸 SAMPLE OUTPUT :   

```
Album art Also extracted (APIC) -> cover.jpg

------------> MP3 METADATA <-----------
Title   : Rebel Saab :: SenSongsMp3.Com
Artist  : Sanjith Hegde, Blaaze
Album   : The Raja Saab (2025)
Year    : 2024
Comment : Releasing_at_9th_j
Genre   : Telugu

----------------------------------------
```