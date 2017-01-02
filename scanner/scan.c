#include "scan.h"

#include <dirent.h>
#include <stdio.h>
#include <sys/stat.h>

#include <database/connect.h>
#include <util/file.h>
#include <util/md5.h>

// scans directory to see if any files match MD5 in database
// TODO: Make it recurse through each folder
int scanDirectory(char *searchDir){
    DIR *midir;
    struct dirent* info_archivo;
    struct stat fileStat;
    char fullpath[256];

    if ((midir=opendir(searchDir)) == NULL)
    {
        perror("Error in opendir");
        return 1;
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
            char md5string[33];
            char *md5 = getMD5(fullpath, md5string);
            if(md5 != NULL){
                int result = isMD5InDB(md5);
                if(result == 1){
                    printf("%s located at %s is possibly a virus!\n", info_archivo->d_name, fullpath);
                }
            }
        }
        //printf("\n");
    }
    closedir(midir);
    return 0;
}
