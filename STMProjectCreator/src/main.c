#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "commands.h"
#include "file_def.h"

enum boards_e {
    Board_STM32F4XX = 0,
    Board_STM32L4XX = 1,
};

uint32_t gBoard = 0;
char gName[0x100] = {0};
char gRamSize[0x100] = "0x10000";
char gRomSize[0x100] = "0x10000";

void cmdSetName(char* cmd) {
    strcpy(gName, cmd);
}

void cmdSetRom(char* cmd) {
    strcpy(gRomSize, cmd);
}

void cmdSetRam(char* cmd) {
    strcpy(gRamSize, cmd);
}

void cmdSelectBoard(char* cmd) {
    if(strcmp(cmd, "F4") == 0) {
        gBoard = Board_STM32F4XX;
    }
    else if(strcmp(cmd, "L4") == 0) {
        gBoard = Board_STM32L4XX;
    }
}

cmd_t gCmds[] = {
    { cmdSelectBoard, "-board" },
    { cmdSetName, "-name"},
    { cmdSetRam, "-ram"},
    { cmdSetRom, "-rom"}
};

void cmdHelp(char* cmd) {
    cmd = cmd;

    printf("Commands:\n");

    for(size_t i = 0; i < sizeof(gCmds) / sizeof(cmd_t); i++) {
        printf("\t%s\n", gCmds[i].mCmd);
    }
    
    printf("\t-help\n");

    exit(0);
}

int main(int argc, char** argv) {
    cmd_t help = { cmdHelp, "-help" };

    for(int i = 0; i < argc; i++) {
        for(size_t j = 0; j < sizeof(gCmds) / sizeof(cmd_t); j++) {
            if(strcmp(argv[i], gCmds[j].mCmd) == 0) {
                gCmds[j].mCmdFn(argv[i + 1]);

                break;
            }
        }

        if(strcmp(argv[i], help.mCmd) == 0) {
            help.mCmdFn(argv[i + 1]);

            break;
        }
    }

    printf("Cpu: %s\n", gBoard == 0 || gBoard == 1 ? "m4" : "m4");
    printf("Board: STM32%sXX\n", gBoard == 0 ? "F4" : "L4");
    printf("Name: %s\n", gName);

    if(gBoard == Board_STM32F4XX) {
        void* t = strcpy(gRamSize, "128k");
        t = strcpy(gRomSize, "512k");
        // Stupid error of -Werror flag
        t = t;
    }
    else {
        void* t = strcpy(gRamSize, "128k");
        t = strcpy(gRomSize, "1024k");
        t = t;
    }

    printf("Ram: %s\n", gRamSize);
    printf("Rom: %s\n", gRomSize);

    if(gName[0] == 0) {
        printf("\t[ERROR]: No name\n");
        
        return 0;
    }

    char folder[0x120] = "mkdir ";
    void *trash = strcat(folder, gName);

    printf("Creating folder \"%s\"\n", folder);

    system(folder);

    char path[0x100];
    trash = strcpy(path, "./");
    trash = strcat(path, gName);
    trash = strcat(path, "/");

    char buffer[0x200];
    trash = strcpy(buffer, path);

    FILE* fAsm = fopen(strcat(buffer, "flash.s"), "wb+");
    printf("Creating file \"%s\"\n", buffer);
    fprintf(fAsm, gFlashAsm, gBoard == 0 || gBoard == 1 ? "m4" : "m4");
    fclose(fAsm);

    trash = memset(buffer, 0, 0x200);
    trash = strcpy(buffer, path);

    FILE* fLd = fopen(strcat(buffer, "flash.ld"), "wb+");
    printf("Creating file \"%s\"\n", buffer);
    fprintf(fLd, gFlashLd, gRomSize, gRamSize);
    fclose(fLd);

    trash = memset(buffer, 0, 0x200);
    trash = strcpy(buffer, path);

    FILE* fmain = fopen(strcat(buffer, "main.c"), "wb+");
    printf("Creating file \"%s\"\n", buffer);
    fprintf(fmain, "/*\n\tCreated with %s ", argv[0]);
    for(int i = 1; i < argc; i++) {
        fprintf(fmain, "%s ", argv[i]);
    }
    fprintf(fmain, "\n*/\n");
    fprintf(fmain, "#define STM32_%sXX\n\n", gBoard == 0 ? "F4" : "L4");
    fprintf(fmain, gMainC);
    fclose(fmain);

    trash = memset(buffer, 0, 0x200);
    trash = strcpy(buffer, path);

    FILE* fcomp = fopen(strcat(buffer, "comp.bat"), "wb+");
    printf("Creating file \"%s\"\n", buffer);
    fprintf(fcomp, gCompBat, gBoard == 0 || gBoard == 1 ? "m4" : "m4", gBoard == 0 || gBoard == 1 ? "m4" : "m4", gName, gName, gName);
    fclose(fcomp);
    
    trash = memset(buffer, 0, 0x200);
    trash = strcpy(buffer, path);

    FILE* fmk = fopen(strcat(buffer, "mk.sh"), "wb+");
    printf("Creating file \"%s\"\n", buffer);
    fprintf(fmk, gMkSh, gBoard == 0 || gBoard == 1 ? "m4" : "m4", gBoard == 0 || gBoard == 1 ? "m4" : "m4", gName, gName, gName, gName);
    fclose(fmk);

    trash = trash;

    char command[256] = "cd ./";
    trash = strcat(command, gName);

    system(command);

    return 0;
}