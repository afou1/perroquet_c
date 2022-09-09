#ifndef PROJETC_ASTEK_INTERFACE_H
#define PROJETC_ASTEK_INTERFACE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <argp.h>
#include <argz.h>


#ifndef __unix__
#define __fpurge fflush
#define access _access
#include <io.h>
#else
#include <unistd.h>
#include <stdio_ext.h>
#endif
#define TAILLE_MAX_CLE 256
#define TAILLE_MAX_BUFFER 100000

typedef struct{
    FILE* fp_source;
    int size_source;
    char path_source[FILENAME_MAX];
    FILE* fp_dest;
    char path_destination[FILENAME_MAX];
    int b_dest;
    char cle[TAILLE_MAX_CLE];
    int size_cle;
    int mode_chiffrement;
    int keep;

}s_params;



void print_sep();
int load_file(char* path,FILE** fp);
int read_file(FILE** fp,char *out,int len);
int save_file(char* text_crypt,int len,FILE** fp_out);
void init_params(s_params *params);
void loop_err_file(char* path,char* filename,char *mode);
void load_params(int argc,char **argv, s_params *params);
void close_everything(s_params *params);
#endif //PROJETC_ASTEK_INTERFACE_H
