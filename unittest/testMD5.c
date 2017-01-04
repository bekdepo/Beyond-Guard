#include "testMD5.h"

#include <util/md5.h>
#include <database/connect.h>

#include <stdio.h>
#include <assert.h>

int testMD5(){
    char md5string[33];
    char *md5 = getMD5("unittest/data/eicar.com.txt", md5string);
    if(md5 != NULL){
        int result = isMD5InDB(md5);
        if(result != 1){
            return 1;
        }
    }
    md5 = getMD5("unittest/data/fake.txt", md5string);
    if(md5 != NULL){
        int result = isMD5InDB(md5);
        if(result == 1){
            return 1;
        }
    }
    return 0;
}

