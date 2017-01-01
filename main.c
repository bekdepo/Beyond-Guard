#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/stat.h>
#include <string.h>
#include <openssl/md5.h>
#include <mysql.h>

void getMD5(char *filename);
int is_regular_file(const char *path);
int isDirectory(const char *path);

int main (int argc, char **argv)
{
    DIR *midir;
    struct dirent* info_archivo;
    struct stat fileStat;
    char fullpath[256];

    printf("MySQL client version: %s\n", mysql_get_client_info());

    if (argc != 2)
    {
        perror("Please supply a folder name\n");
        exit(-1);
    }

    if ((midir=opendir(argv[1])) == NULL)
    {
        perror("Error in opendir");
        exit(-1);
    }

    while ((info_archivo = readdir(midir)) != 0)
    {
        //printf ("%s ", info_archivo->d_name);
        strcpy (fullpath, argv[1]);
        strcat (fullpath, "/");
        strcat (fullpath, info_archivo->d_name);
        if (!stat(fullpath, &fileStat) && is_regular_file(fullpath))
        {
            /*
            printf((S_ISDIR(fileStat.st_mode))  ? "d" : "-");
            printf((fileStat.st_mode & S_IRUSR) ? "r" : "-");
            printf((fileStat.st_mode & S_IWUSR) ? "w" : "-");
            printf((fileStat.st_mode & S_IXUSR) ? "x" : "-");
            printf((fileStat.st_mode & S_IRGRP) ? "r" : "-");
            printf((fileStat.st_mode & S_IWGRP) ? "w" : "-");
            printf((fileStat.st_mode & S_IXGRP) ? "x" : "-");
            printf((fileStat.st_mode & S_IROTH) ? "r" : "-");
            printf((fileStat.st_mode & S_IWOTH) ? "w" : "-");
            printf((fileStat.st_mode & S_IXOTH) ? "x" : "-");
            */
            getMD5(fullpath);
        }
        //printf("\n");
    }
    closedir(midir);
}


void getMD5(char *filename){
    unsigned char c[MD5_DIGEST_LENGTH];
    int i;
    FILE *inFile = fopen (filename, "rb");
    MD5_CTX mdContext;
    int bytes;
    unsigned char data[1024];

    if (inFile == NULL) {
        printf ("%s can't be opened.\n", filename);
        return;
    }

    MD5_Init (&mdContext);
    while ((bytes = fread (data, 1, 1024, inFile)) != 0){
        MD5_Update (&mdContext, data, bytes);
    }
    MD5_Final (c,&mdContext);
    for(i = 0; i < MD5_DIGEST_LENGTH; i++) {
        printf("%02x", c[i]);
    }
    printf (" %s\n", filename);
    fclose (inFile);
}

//returns non-zero if the file is a regular file
int is_regular_file(const char *path){
    struct stat path_stat;
    stat(path, &path_stat);
    return S_ISREG(path_stat.st_mode);
}

//
int isDirectory(const char *path) {
    struct stat statbuf;
    if (stat(path, &statbuf) != 0){
        return 0;
    }

   return S_ISDIR(statbuf.st_mode);
}
