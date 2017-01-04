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
        strcpy (fullpath, searchDir);
        strcat (fullpath, "/");
        if(strcmp(info_archivo->d_name, ".") ==0  || strcmp(info_archivo->d_name, "..") == 0){
            //skip current directory and moving up a directory
            continue;
        }
        strcat (fullpath, info_archivo->d_name);
        if(isDirectory(fullpath)){
            scanDirectory(fullpath);
        }else if (!stat(fullpath, &fileStat) && isFile(fullpath)){

            char md5string[33];
            char *md5 = getMD5(fullpath, md5string);
            if(md5 != NULL){
                int result = isMD5InDB(md5);
                if(result == 1){
                    printf("%s located at %s is possibly a virus!\n", info_archivo->d_name, fullpath);
                }else{
                    printf("%s is not a virus.\n", info_archivo->d_name);
                }
            }
        }
    }
    closedir(midir);
    return 0;
}
