#include "crypt.h"
#include "interface.h"


void chiffrer(char* text_clair,char* perroquet,char* text_crypt,int l_text,int l_perroquet){
     for(int i=0;i<l_text;i++){
        text_crypt[i]=text_clair[i]-perroquet[i%l_perroquet];
    }
}
void dechiffrer(char* text_crypt,char* perroquet,char* text_clair,int l_text,int l_perroquet){
    for(int i=0;i<l_text;i++){
        text_clair[i]=text_crypt[i]+perroquet[i%l_perroquet];
    }
}

void chiffrer_f(FILE **f_input,FILE **f_output,char* perroquet,int l_text,int l_perroquet){
    char buffer_in[TAILLE_MAX_BUFFER],buffer_out[TAILLE_MAX_BUFFER];
    int nb_read=0,nb_write=0;
    int nb_iterations=l_text/TAILLE_MAX_BUFFER;
    int nb_rest=l_text%TAILLE_MAX_BUFFER;
    fseek(*f_input, 0, SEEK_SET);
    fseek(*f_output, 0, SEEK_SET);
    for(int i=0;i<nb_iterations;i++){
        nb_read+=fread(buffer_in, sizeof(char), TAILLE_MAX_BUFFER, *f_input);
        chiffrer(buffer_in,perroquet,buffer_out,TAILLE_MAX_BUFFER,l_perroquet);
        nb_write+=fwrite(buffer_out, sizeof(char), TAILLE_MAX_BUFFER, *f_output);
    }
    nb_read+=fread(buffer_in, sizeof(char), nb_rest, *f_input);
    chiffrer(buffer_in,perroquet,buffer_out,nb_rest,l_perroquet);
    nb_write+=fwrite(buffer_out, sizeof(char), nb_rest, *f_output);
    fclose(*f_input);
    fclose(*f_output);
}

void dechiffrer_f(FILE **f_input,FILE **f_output,char* perroquet,int l_text,int l_perroquet){
    char buffer_in[TAILLE_MAX_BUFFER],buffer_out[TAILLE_MAX_BUFFER];
    int nb_read=0,nb_write=0;
    int nb_iterations=l_text/TAILLE_MAX_BUFFER;
    int nb_rest=l_text%TAILLE_MAX_BUFFER;
    fseek(*f_input, 0, SEEK_SET);
    fseek(*f_output, 0, SEEK_SET);
    for(int i=0;i<nb_iterations;i++){
        nb_read+=fread(buffer_in, sizeof(char), TAILLE_MAX_BUFFER, *f_input);
        dechiffrer(buffer_in,perroquet,buffer_out,TAILLE_MAX_BUFFER,l_perroquet);
        nb_write+=fwrite(buffer_out, sizeof(char), TAILLE_MAX_BUFFER, *f_output);
    }
    nb_read+=fread(buffer_in, sizeof(char), nb_rest, *f_input);
    dechiffrer(buffer_in,perroquet,buffer_out,nb_rest,l_perroquet);
    nb_write+=fwrite(buffer_out, sizeof(char), nb_rest, *f_output);
    fclose(*f_input);
    fclose(*f_output);
}