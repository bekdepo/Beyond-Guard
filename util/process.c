#include "process.h"

#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <tchar.h>
#include <psapi.h>

void PrintProcessNameAndID(DWORD processID);

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

void PrintProcessNameAndID( DWORD processID ){
    TCHAR szProcessName[MAX_PATH] = TEXT("<unknown>");

    // Get a handle to the process.
    HANDLE hProcess = OpenProcess( PROCESS_QUERY_INFORMATION |
                                   PROCESS_VM_READ,
                                   FALSE, processID );

    // Get the process name.
    if (NULL != hProcess )
    {
        HMODULE hMod;
        DWORD cbNeeded;

        if ( EnumProcessModules( hProcess, &hMod, sizeof(hMod),
             &cbNeeded) )
        {
            GetModuleBaseName( hProcess, hMod, szProcessName,
                               sizeof(szProcessName)/sizeof(TCHAR) );
        }
    }

    // Print the process name and identifier.
    _tprintf( TEXT("%s  (PID: %u)\n"), szProcessName, processID );

    // Release the handle to the process.
    CloseHandle( hProcess );
}

int printAllProcesses(){
     // Get the list of process identifiers.

    DWORD aProcesses[1024], cbNeeded, cProcesses;
    unsigned int i;

    if ( !EnumProcesses( aProcesses, sizeof(aProcesses), &cbNeeded ) )
    {
        return 1;
    }

    // Calculate how many process identifiers were returned.
    cProcesses = cbNeeded / sizeof(DWORD);
    // Print the name and process identifier for each process.

    for ( i = 0; i < cProcesses; i++ )
    {
        if( aProcesses[i] != 0 )
        {
            PrintProcessNameAndID( aProcesses[i] );
        }
    }
    return 0;
}

// gets full path to executable of process based on pid
void getFullPath(int pid){
    HANDLE processHandle = NULL;
    TCHAR filename[MAX_PATH];

    processHandle = OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_VM_READ, FALSE, pid);
    if (processHandle != NULL) {
        if (GetModuleFileNameEx(processHandle, NULL, filename, MAX_PATH) == 0) {
            printf("Failed to get module filename.\n");
        } else {
            printf("Module filename is: %s\n", filename);
        }
        CloseHandle(processHandle);
    } else {
        printf("Failed to open process.\n");
    }
}
