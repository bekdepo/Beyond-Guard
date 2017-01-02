#include "file.h"

#include <sys/stat.h>

//returns non-zero if the path is a file
int is_file(const char *path){
    struct stat path_stat;
    stat(path, &path_stat);
    return S_ISREG(path_stat.st_mode);
}

// returns non-zero if the path is a directory
int isDirectory(const char *path) {
    struct stat statbuf;
    if (stat(path, &statbuf) != 0){
        return 0;
    }

   return S_ISDIR(statbuf.st_mode);
}
