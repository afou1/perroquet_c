#ifndef PROJETC_ASTEK_CRYPT_H
#define PROJETC_ASTEK_CRYPT_H

#include <string.h>
#include <stdio.h>
#include <stdlib.h>

//! Fonction de dechiffrement qui prend deux tableaux, selon la cle donné dans perroquet
//! \param text_clair tableau de char qui represente une partie de fichier à chiffrer
//! \param perroquet tableau de char qui represente la cle de chiffrement
//! \param text_crypt tableau ou on va mettre le resultat du chiffrement, la fonction fait la supposition
//! qu'il a la meme taille que text_clair
//! \param l_text taille du tableau text_clair et text_crypt, je le passe en argument car j'essaie de prendre en consideration
//! le cas ou on a un tableau qui contient la valeur ascii \0 avant la fin
//! \param l_perroquet taille de la clé
void chiffrer(char* text_clair,char* perroquet,char* text_crypt,int l_text,int l_perroquet);
//!  Fonction de dechiffrement qui prend deux tableaux, cette fonction ne peux pas prendre des tableaux trop volumineux
//!  donc on l'appelle dans dechiffrer_f pour iterer sur un fichier avec un buffer de taille fix.
//! \param text_crypt tableau de char qui represente une partie de fichier à dechiffrer
//! \param perroquet tableau de char qui represente la cle de chiffrement
//! \param text_clair ableau ou on va mettre le resultat du dechiffrement, la fonction fait la meme supposition que chiffrer()
//! \param l_text taille du tableau text_clair et text_crypt
//! \param l_perroquet taille de la clé
void dechiffrer(char* text_crypt,char* perroquet,char* text_clair,int l_text,int l_perroquet);
//! Fonction de chiffrement qui prend deux flux de fichier ouverts, et qui va chiffrer selon la cle qui est donné dans perroquet
//! \param f_input double pointeur vers le fichier en clair, je prend un double pointeur pour eviter les erreurs avec ftell et fseek
//! \param f_output double pointeur vers le fichier destination apres chiffrement
//! \param perroquet tableau de char qui represente la cle de chiffrement
//! \param l_text taille du tableau text_clair et text_crypt
//! \param l_perroquet taille de la clé
void chiffrer_f(FILE **f_input,FILE **f_output,char* perroquet,int l_text,int l_perroquet);
//! Fonction de dechifrement qui prend deux flux de fichier ouverts, et qui va dechiffrer selon la cle qui est donné dans perroquet
//! \param f_input double pointeur vers le fichier de chiffrement
//! \param f_output double pointeur vers le fichier destination apres dechiffrement
//! \param perroquet tableau de char qui represente la cle de chiffrement
//! \param l_text taille du tableau text_clair et text_crypt
//! \param l_perroquet taille de la clé
void dechiffrer_f(FILE **f_input,FILE **f_output,char* perroquet,int l_text,int l_perroquet);



#endif //PROJETC_ASTEK_CRYPT_H
