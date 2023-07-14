#include<unistd.h> //miscellaneous functions
#include<sys/stat.h>    //constructs that facilitates getting file attributes
#include<sys/types.h>
//#define _POSIX_SOURCE
#include <fcntl.h>  //file control options, open()
#include<stdio.h>   //standard input output, printf, scanf, sscanf
#include<stdlib.h>  //standard library, calloc, atoi, itoa
#include<string.h>  //sring handling, strcmp

void manual(char* operation){     //manual followed by command name for information about particular command
    printf("%s",operation);
    if(strcmp(operation,"all")==0){
        printf("\nPlease input specific command name out of create, open, read, write, copy or info in front of \"manual\" for specific information about command.\n");
    }
    else if(strcmp(operation,"create")==0){
        printf("%s","\nCommand Name : create\n");
        printf("\n%s","Format : ./exe_file create filename mode(optional)\n");
        printf("%s","\nOutput : Creates a new empty file with the given filename and by default gives read and write to user and group.\n\n");
        printf("No. of arguments = 1/2.\n\n");
        printf("%s","The folllowing numeral constants are  required for mode:\n\n0700 user (file owner) has read, write and execute permission(S_IRWXU)\n");
        printf("0400 user (file owner) has read permission(S_IRUSR)\n");
        printf("0200 user (file owner) has write permission(S_IWUSR)\n");
        printf("0100 user (file owner) has execute permission(S_IXUSR)\n");
        printf("0070 user (group) has read, write and execute permission(S_IRWXG)\n");
        printf("0040 user (group) has read permission(S_IRGRP)\n");
        printf("0020 user (group) has write permission(S_IWGRP)\n");
        printf("0010 user (group) has execute permission(S_IXGRP)\n");
        printf("0007 user (others) have read, write and execute permission(S_IRWXO)\n");
        printf("0004 user (others) have read permission(S_IROTH)\n");
        printf("0002 user (others) have write permission(S_IWOTH)\n");
        printf("0001 user (others) have execute permission(S_IXOTH)\n");
    }
    else if(strcmp(operation,"read")==0){
        printf("%s","\nCommand Name : read\n");
        printf("\n%s","Format : ./exe_file read filename bytes(optional) offset(optional)\n");
        printf("%s","Output : Prints data read from offset of the source to console or by default prints all the content from from the beginning.\n");
        printf("No. of arguments = 1/2/3.\n\n");   
    }
    else if(strcmp(operation,"open")==0){
        printf("%s","\nCommand Name : open\n");
        printf("\n%s","Format : ./exe_file open filename flag(optional)\n");
        printf("%s","Output : Opens and prints the file descriptor if the file exists otherwise creates the file  .\n");
        printf("Flags: 0 - Read Only, 1 - Write Only, 2 - Read Write");
        printf("No. of arguments = 1/2.\n\n");   
    }
    else if(strcmp(operation,"write")==0){
        printf("%s","\nCommand Name : write\n");
        printf("\n%s","Format : ./exe_file write filename offset\n");
        printf("%s","Output : Writes data from the console to destfile at given offset and truncates the data.\n");
        printf("No. of arguments = 2.\n\n");   
    }
    else if(strcmp(operation,"stats")==0){
        printf("%s","\nCommand Name : info\n");
        printf("\n%s","Format : ./exe_file stats filename\n");
        printf("%s","Output : Displays statistical information about given filename.\n");
        printf("No. of arguments = 1.\n\n");
    }
    else if(strcmp(operation,"copy")==0){
        printf("%s","\nCommand Name : copy\n");
        printf("\n%s","Format : ./exe_file copy sfile  offset bytes dfile offset\n");
        printf("%s","Output : Copies amount of bytes data from sourcefile to destfile.\n");
        printf("No. of arguments = 5.\n\n");
    }
    else{
        printf("%s","\nNo such command.\n");
    }
}
void Create(char* fname,char *n){
    int flag=0;
    //checking for pre existence of a file
    int fd1=open(fname,O_RDONLY);
    if (fd1>0){
        printf("\nFile already exists, do you want to replace with new file (Y/N):- ");
        close(fd1);
        char ch;
        scanf("%c",&ch);
        if(ch=='Y') printf("\nCreating new file "); //Overwrites new file
        else {printf("\nPrevious file remains");flag=1;}
    
    }

    //creation of a file
    int x=0;
    sscanf(n,"%o",&x);
    if(flag==0){int fd=creat(fname,x);

    (fd>0)? printf("\nFile created successfully with file descriptor : %i\n",fd):printf("\nFile couldn't be created");

    if (fd>0){fd=close(fd);
    (fd==0)?printf("\nFile closed successfully\n"):printf("\nFile couldn't close");}}
    // unlink(fname); //to remove directory entry
}
void Open(char* path, int flag){
    int fd=open(path,flag);

    if(fd>=0) {printf("File opened with file descriptor: %i\n",fd);}

    else {printf("\nFile does not exist.Do you want to create it? (Y/N) ");
        char ch;
        scanf("%c",&ch);
        if(ch=='Y') Create(path, "0660");
        }

}
void Copy(char *fname1, int off1, int n, char *fname2, int off2)
{
    char *buffer = (char *)calloc(n, sizeof(char));
    int fd1;
   
    fd1 = open(fname1, O_RDONLY);

    int fd2 = open(fname2, O_WRONLY);

    
    if (fd1 < 0)
    {
        printf("\nCan't Open file: %s\n", fname1);
        return;
    }
    if (fd2 < 0)
    {
        printf("\nCan't Open file : %s\n", fname2);
        return;
    }
    
    
    if (fd1 != 0)
    {
        lseek(fd1, off1, SEEK_SET);
    }

    lseek(fd2, off2, SEEK_SET);

    printf("\nCopying data:\n");
    
    // reading and writing the content

    read(fd1, buffer, n);
    write(fd2, buffer, n);

    printf("Data Copied\n");
    fd1 = close(fd1);
    fd2 = close(fd2);

    if (fd1 < 0)
    {
        printf("\nCan't Close file: %s\n", fname1);
        return;
    }
    if (fd2 < 0)
    {
        printf("\nCan't Close file : %s\n", fname2);
        return;
    }
}
void Read(char* file, int n,int o){

    int fd=open(file,0);
    char buf[1024];
    if(fd<0){
        printf("\nCan't locate the file to be read.\n");
        return;
    }
    else{
        int v=lseek(fd,o,0);
        if(v==-1){ printf("\nCan't reach the given offset in file \n"); return;}

        printf("\nData read from file: \n");
        int r=read(fd,buf,n);
        write(1,buf,r);
    
        // while(r!=0){
        //     write(1,buf,r);
        //     r=read(fd,buf,n);
        // }
        printf(" \n");
    }
    printf("Data read successfully\n");

    fd=close(fd); //file closed after read
}
void Write(char *fname,int seek)
{
    //open the file
        int fd=open(fname,O_TRUNC| O_WRONLY|O_CREAT,0660);

    //error message
    if(fd<0){
        printf("\nError in opening file: %s\n",fname);
        return;
    }
    printf("\nEnter Data to write in file\n");
    char buff[512];
    int byte_read = read(0,buff,512);
    lseek(fd,seek,0);

    //reading and writing the content
    write(fd, buff,byte_read);

    printf("Write Successful!\n");
    //closing the file
    fd=close(fd);
    //error message
    if (fd<0)
    {
        printf("\nError in closing the files\n");
        return;
    }
    else{
        exit(0);
    }
}
void info(char* file){
    //fn. to read file statistics
    
    struct stat buf;
    int val = stat(file, &buf);
    if(val==-1){
        printf("%s", "\nError in collecting file stats. Returning!\n");
        return ;
    }
    
    printf("%s","\nFile Statistics :-\n");
    printf("\nFile id : %lu", buf.st_ino);
    printf("\nFile links : %lu", buf.st_nlink);
    printf("\nFile size : %ld", buf.st_size);
    printf("\nFile owner: %d", buf.st_uid);
    printf("\nFile last access time : %ld", buf.st_atime);
    printf("\nFile last modification time : %ld\n", buf.st_mtime);
                
    printf("\n\nFile permissions : %u :-\n", buf.st_mode);
    printf( (S_ISDIR(buf.st_mode)) ? "d" : "-");
    //printf("\t");
    printf( (buf.st_mode & S_IRUSR) ? "r" : "-");
    printf( (buf.st_mode & S_IWUSR) ? "w" : "-");
    printf( (buf.st_mode & S_IXUSR) ? "x" : "-");
    printf("\t");
    printf( (buf.st_mode & S_IRGRP) ? "r" : "-"); 
    printf( (buf.st_mode & S_IWGRP) ? "w" : "-");
    printf( (buf.st_mode & S_IXGRP) ? "x" : "-");
    printf("\t");
    printf( (buf.st_mode & S_IROTH) ? "r" : "-");
    printf( (buf.st_mode & S_IWOTH) ? "w" : "-");
    printf( (buf.st_mode & S_IXOTH) ? "x" : "-");
    printf("\n\n");

    return;
}

int main(int argc,char * argv[]){ //char *argv[] is an array of pointers to string

    // (==)operator does not work in C for comparing strings

    if(!strcmp(argv[1],"create")){
        if (argc>=3 && argc<5){
            if(argc==4){Create(argv[2], argv[3]);} 
            else 
            Create(argv[2], "0660"); // default permissions are read and write to user and group
            }
        else printf("\nToo many arguments"); //Error handled for correct input
        return 0;
    }
    else if(!strcmp(argv[1],"read")){
        // read argv[2] argv[3](optional) argv[4](optional)
        //by default shows full content of file
        if(argc==3) Read(argv[2],1024,0);
        else if(argc==4) Read(argv[2],atoi(argv[3]),0);
        else if(argc==5) Read(argv[2],atoi(argv[3]),atoi(argv[4]));
        else printf("Please input filename, number of bytes(optional) to read and offset(optional)\n");
        return 0;
    }
    else if(!strcmp(argv[1],"copy")){          
        //argv[2]=source filename , argv[3]=offset of source file , argv[4]=no of bytes to copy , argv[5]=destination file , argv[6]=offset to copy to    
        Copy(argv[2],atoi(argv[3]),atoi(argv[4]),argv[5],atoi(argv[6]));
        return 0;
    }
    else if(!strcmp(argv[1],"open")){
        int mode=0;//default read
        if(argc>3 && argc<5){
            mode=atoi(argv[3]);//0-Read 1-Write 2-ReadWrite
        }
        Open(argv[2],mode);
        return 0;
    }
    else if(!strcmp(argv[1],"write")){               
        Write(argv[2],atoi(argv[3]));       //truncates current content of file
        return 0;
    }
    else if(!strcmp(argv[1],"info")){
        if(argc==3){
            //exe_file stats filename
            //argv[0] argv[1] argv[2]

            info(argv[2]);
        }
        else{
            printf("%s","\nNeed a filename for info\n");
            return 0;
        }
    }
    else if(!strcmp(argv[1],"manual")){
        //exe_file manual command_name
        //argv[0] argv[1] argv[2]
        manual(argv[2]);
        return 0;
    }
    else printf("Enter a valid operation from create, open, read, write, copy and info please :)\n"); //Commands allowed in program
   
    return 0;
}