#include "process.h"

#include <stdio.h>
#include <stdlib.h>

void getProcessList(){
    system("tasklist > temp.txt");
    FILE *ifp = fopen("temp.txt", "r");
    int length = 200;
    char temp[length];

    //Image Name                     PID Session Name        Session#    Mem Usage
    //========================= ======== ================ =========== ============
    //System Idle Process              0 Services                   0          4 K
    //System                           4 Services                   0      4,732 K
    fscanf(ifp, "%s%s%s%s%s%s%s%s%s%s %s%s%s%s%s%s%s%s%s%s %s", temp, temp, temp,
           temp,temp, temp,temp, temp, temp, temp,
           temp,temp, temp, temp, temp, temp,temp,
           temp,temp, temp, temp);
    char imageName[length];
    int pid;
    char sessionName[length];
    int sessionNum;
    char memUsage[length];
    char junk[length];
    fscanf(ifp, "%s %d %s %d %s %s", imageName, &pid, sessionName, &sessionNum, memUsage, junk);
    printf("%s %d %s %d %s\n", imageName, pid, sessionName, sessionNum, memUsage);
    fscanf(ifp, "%s %d %s %d %s %s", imageName, &pid, sessionName, &sessionNum, memUsage, junk);
    printf("%s %d %s %d %s\n", imageName, pid, sessionName, sessionNum, memUsage);
    fscanf(ifp, "%s %d %s %d %s %s", imageName, &pid, sessionName, &sessionNum, memUsage, junk);
    printf("%s %d %s %d %s\n", imageName, pid, sessionName, sessionNum, memUsage);
    fclose(ifp);
}
