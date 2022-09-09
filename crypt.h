#ifndef PROJETC_ASTEK_CRYPT_H
#define PROJETC_ASTEK_CRYPT_H

#include <string.h>
#include <stdio.h>
#include <stdlib.h>

void chiffrer(char* text_clair,char* perroquet,char* text_crypt,int l_text,int l_perroquet);
void dechiffrer(char* text_crypt,char* perroquet,char* text_clair,int l_text,int l_perroquet);



#endif //PROJETC_ASTEK_CRYPT_H
