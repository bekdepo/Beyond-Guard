#include "md5.h"

#include <stdio.h>
#include <stdlib.h>
#include <openssl/md5.h>

char *getMD5(char *filename, char *md5string){
    unsigned char digest[MD5_DIGEST_LENGTH];
    int i;
    FILE *inFile = fopen (filename, "rb");
    MD5_CTX mdContext;
    int bytes;
    unsigned char data[1024];

    if (inFile == NULL) {
        printf ("%s can't be opened.\n", filename);
        return NULL;
    }

    MD5_Init (&mdContext);
    while ((bytes = fread (data, 1, 1024, inFile)) != 0){
        MD5_Update (&mdContext, data, bytes);
    }
    fclose (inFile);
    MD5_Final (digest,&mdContext);

    for(i = 0; i < MD5_DIGEST_LENGTH; i++) {
        sprintf(&md5string[i*2], "%02x", (unsigned int)digest[i]);
        //printf("%02x", digest[i]);
    }
    //printf ("%s\n", filename);
    return md5string;
}
