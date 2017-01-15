// Jonathan Chin
// 1/1/2017
// Beyond Guard - Antivirus in C

#include <stdio.h>

#include <database/connect.h>
#include <scanner/scan.h>
#include <util/md5.h>
#include <util/process.h>
#include <util/stack.h>
#include <unittest/testMD5.h>

// Remove this later, this is only for temporary testing of the stack
void testStack();

int main (int argc, char **argv)
{
    //testStack();
    //getProcessList();
    //printAllProcesses();
    //getFullPath(6004);

    int result = connectDB();
    if (result){
        printf("Failed to connect database, aborting...\n");
        return 1; // Can't connect to database
    }
    if (argc != 2){
        perror("Please supply a path to a folder or file.\n");
        return 1;
    }else{
        int pass = scanDirectory(argv[1]);
        if(pass){
            printf("Failed scanning directory for argument %s\n", argv[1]);
        }
    }
    int testResult = testMD5();
    if(testResult){
        printf("Failed unit test");
    }
    closeDB();

    return 0;
}

void testStack(){
    Stack s;
    stackInit(&s);
    stackPush(&s, "jon");
    stackPush(&s, "test");
    stackPush(&s, "hello");
    char *top = stackTop(&s);
    printf("Top is %s\n", top);
    stackPop(&s);
    top = stackTop(&s);
    printf("Top is %s\n", top);
    stackDestroy(&s);
}
