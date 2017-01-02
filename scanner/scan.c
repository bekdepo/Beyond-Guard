#include "scan.h"

#include <dirent.h>
#include <sys/stat.h>

// scans directory to see if any files match MD5 in database
void scanDirectory(char *searchDir){
    DIR *midir;
    struct dirent* info_archivo;
    struct stat fileStat;
    char fullpath[256];

    if ((midir=opendir(searchDir)) == NULL)
    {
        perror("Error in opendir");
        exit(-1);
    }

    while ((info_archivo = readdir(midir)) != 0)
    {
        //printf ("%s ", info_archivo->d_name);
        strcpy (fullpath, searchDir);
        strcat (fullpath, "/");
        strcat (fullpath, info_archivo->d_name);
        if (!stat(fullpath, &fileStat) && is_file(fullpath))
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
