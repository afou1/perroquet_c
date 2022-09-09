#ifndef PROJETC_ASTEK_INTERFACE_H
#define PROJETC_ASTEK_INTERFACE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <argp.h>
#include <argz.h>

// Je voulais utiliser des macros pour remplacer les parties qui dependent de linux, mais je n'ai pas eu le temps de tester.
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


//! Structure qui contient toutes les infromations pour definir le fonctionnement du programme
typedef struct{
    FILE* fp_source; /**< pointeur pour le fichier source */
    int size_source; /**< Taille du fichier source en octets */
    char path_source[FILENAME_MAX]; /**< chemin du fichier source, on prend la taille max definie dans stdio_lim.h*/
    FILE* fp_dest; /**< pointeur pour le fichier destination */
    char path_destination[FILENAME_MAX]; /**< chemin du fichier destination */
    int b_dest; /**< flag que j'utilise que l'etat de la valeur du fichier de sortie (si le fichier existe deja vs on peut le creer par exemple) */
    char cle[TAILLE_MAX_CLE]; /**< la cle de chiffrement, on prend la taille max defini dans interface.h */
    int size_cle; /**< la taille de la chaine apres lecture de l'input de l'utilisateur (en utilsant strlen dans ce cas la) */
    int mode_chiffrement; /**< valeur qui me permet de savoir si l'utilisateur essaie de chiffrer ou déchiffrer le fichier en input */
    int keep; /**< valeur qui me permet de savoir si je dois supprimer le fichier source */
    int b_overwrite; /**< valeur qui devrait me permettre de savoir si l'utilisateur est d'accord pour écraser un fichier deja existant et le remplacer par le résultat de notre traitement */
}s_params;


//! Fonction qui me serre a separer l'affichage des differents traitements
void print_sep();
//! Fonction qui va charger un fichier à partir d'un chemin

//! \param path tableau de char qui représente l'emplacement du fichier
//! \param fp double pointeur vers le fichier, on a besoin du double pointeur pour changer ca valeur avec fopen
//! \return si on a pu ouvrir le fichier, une valeur positive qui représente la taille du fichier en octets <br> sinon -1
int load_file(char* path,FILE** fp);
//! Fonction qui va lire la une taille fix de caractères à partir du fichier, et va la mettre dans out

//! \param fp double pointeur vers le fichier, car on appele fclose à l'intérieur
//! \param out tableau qui va recevoir le résultat de la lecture
//! \param len le nombre de caractères qu'on voudrait lire
//! \return le nombre de caractères qu'on a pu lire (pas forcement égal à len)
int read_file(FILE** fp,char *out,int len);
//! Fonction qui permet de sauvegarder un tableau de char dans un fichier

//! \param text_crypt tableau à enregistrer
//! \param len taille du tableau
//! \param fp_out double pointeur vers le fichier. On ferme le fichier apres traitement
//! \return 0 si l'écriture est réussie, sinon le nombre de caractères qu'on a pu écrire.
int save_file(char* text_crypt,int len,FILE** fp_out);
//! initialise les paramètres/fonctionnement par default du programme.

//! /! \param params
void init_params(s_params *params);
//! Fonction qui prend l'input d'un utilisateur et qui va boucler tant qu'on a pas un chemin utilisable pour la lecture d'un fichier source

//! \param path la premiere valeur entrée par l'utilisateur
//! \param filename valeur qui devait me permettre de traiter le fichier source et destination dans la meme fonction
//! \param mode chaine de caracteres qui va etre passé à fopen ("rb"/"wb")
void loop_err_file(char* path,char* filename,char *mode);
//! Fonction qui prend l'input d'un utilisateur et qui va boucler tant qu'on a pas un chemin utilisable pour la lecture d'un fichier source <br>Cette fonction qui devrait etre remplacé par loop_err_file dans le futur

//! \param path la premiere valeure passé par l'utilisateur
//! \param b_overwrite parametre qui va nous permettre de savoir si on peut ecraser un fichier deja existant ou non
void loop_err_dest(char* path,int b_overwrite);
//! Fonction d'entré pour l'interface,  elle va charger tout les parameteres necessaire à l'execution du programme, en lisant les arguments passés et en interagissant avec l'utilisateur

//! \param argc nobmre d'arguments passés au programme
//! \param argv tableau de chaines de caracteres, qui contient tous les arguments passés
//! \param params structure qui va contenir tout les parameteres qu'on utilise dans le programme
void load_params(int argc,char **argv, s_params *params);
//! Fonction qui devrait permettre de fermer les fichier dans le cas d'une sortie soudaine à cause d'une erreure

//! \param params Les parametres du programme
void close_everything(s_params *params);


//! Fonction qui permet juste de voir si le premier argument passer est la definition du mode d'execution (crypt/decrypt)

//! \param arg le premier argument passé à notre porgramme, apres son nom
//! \param params les parametres de notre programme
void check_mode(char* arg,s_params *params);
//! Fonction pour le chargement du fichier source, dans le cas ou il n'a pas ete passé en argument

//! \param params parameteres du programme
void load_source(s_params *params);
//! Fonction pour le chargement du fichier de mot de passe, ou lecture direct en entrée

//! \param params parameteres du programme
void load_pass(s_params *params);
//! Fonction pour le chargement du fichier destination, dans le cas ou il n'a pas ete passé en argument

//! \param params parameteres du programme
void load_dest(s_params *params);
//! Fonction pour le selection du mode d'execution (crypt/decrypt) selon les arguments, ou en demandant directement en entrée

//! \param params parameteres du programme
void load_mode(s_params *params);
#endif //PROJETC_ASTEK_INTERFACE_H
