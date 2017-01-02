// Jonathan Chin
// 1/1/2017
// Beyond Guard - Antivirus in C

#include <stdio.h>

#include <database/connect.h>
#include <scanner/scan.h>
#include <util/md5.h>

int main (int argc, char **argv)
{
    int result = connectDB();
    if (result){
        return 1; // Can't connect to database
    }
    if (argc != 2){
        perror("Please supply a folder name\n");
        return 1;
    }else{
        //scanDirectory(argv[1]);
    }


    return 0;
}
