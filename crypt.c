#include "crypt.h"



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