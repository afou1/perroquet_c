#include "interface.h"



void print_sep(){
    printf("==================================\n");
}


int load_file(char* path,FILE** fp){
    if((*fp= fopen(path,"rb"))){
        fseek(*fp, 0, SEEK_END);    // Go to end
        int length = ftell(*fp);
        fseek(*fp, 0, SEEK_SET);
        return length;
    }else{
        return -1;
    }
}

int read_file(FILE** fp,char *out,int len){
    int nb_read=0,pos=0;
    int nb_iterations=len/TAILLE_MAX_BUFFER;
    int nb_rest=len%TAILLE_MAX_BUFFER;
    for(int i=0;i<nb_iterations;i++){
        pos= ftell(*fp);
        nb_read+=fread(out+pos, sizeof(char), TAILLE_MAX_BUFFER, *fp);
    }
    pos= ftell(*fp);
    nb_read+=fread(out+pos, sizeof(char), nb_rest, *fp);
    fclose(*fp);
    return nb_read;
}

int save_file(char* text_crypt,int len,FILE** fp_out){
    int nb_ecrit= fwrite(text_crypt,sizeof(char),len,*fp_out);
    fclose(*fp_out);
    if(nb_ecrit==len){
        return 0;
    }
    return nb_ecrit;
}

void init_params(s_params *params){
    params->size_source=-1;
    params->size_cle=-1;
    params->fp_dest=NULL;
    params->fp_source=NULL;
    params->mode_chiffrement=-1;
    params->keep=0;
    params->b_dest=0;
    params->b_overwrite=0;
}

void loop_err_file(char* path,char* filename,char *mode){
    FILE* fp=NULL;

    while(!(fp= fopen(path,mode))){
        printf("Impossible de lire le fichier %s:  %s\n",filename,path);
        printf("Message system: %s\n",strerror(errno));
        printf("Veuillez reessayer:");
        __fpurge(stdin);
        scanf("%s",path);
    }
    if(fp) fclose(fp);
}

void loop_err_dest(char* path,int b_overwrite){
    FILE* fp=NULL;
    int exist_wfile=(access(path,W_OK)==0);
    while( exist_wfile || ((fp= fopen(path,"wb"))==0)){
        if(exist_wfile){
            if(b_overwrite){
                break;
            }else{
                printf("Argument ignoré. Fichier deja existant,\n--help pour voir l'argument necessaire\n");
                print_sep();
            }
        }else{
            printf("Impossible de lire le fichier destination:  %s\n",path);
            printf("Message system: %s\n",strerror(errno));
        }
        printf("Veuillez reessayer:");
        __fpurge(stdin);
        scanf("%s",path);
        exist_wfile=(access(path,W_OK)==0);
    }
    if(fp) fclose(fp);
}

void close_everything(s_params *params){
    if(params->fp_dest){
        fclose(params->fp_dest);
    }
    if(params->fp_source){
        fclose(params->fp_source);
    }
}

//! Fonction requise par la fonction arge_parse. Elle va etre appeler pour chaque argument, elle va ensuite changer les valeurs des parametres du programme selon ce que l'utilisateur entre comme arguments

//! \param key la clé de l'argument, la definition des clés pour chaque argument est faite dans load_params
//! \param arg valeur passé à l'argument
//! \param state structure qui contient un ensemble d'information sur l'etat du traitement des parameteres, elle permet aussi de passer nos propres données à parse_opt, avec la structure params
//! \return retourne une valeur qui indique le bon traitement de l'argument, ou un code d'erreur
static int parse_opt (int key, char *arg,struct argp_state *state){
    s_params *params = state->input;
    FILE* fp=NULL;
    switch (key){
        case 'f':
            if(!access(arg,R_OK)){
                strcpy(params->path_source,arg);
                params->size_source=0;
            }else{
                printf("Argument ignoré. Impossible de lire le fichier: %s\n",arg);
                printf("Message systeme: %s\n",strerror(errno));
                print_sep();
            }
            break;
        case 'o':
            if (access(arg,W_OK)==0){
                strcpy(params->path_destination,arg);
                if(params->b_overwrite){
                    params->b_dest=2;
                }else{
                    params->b_dest=3;
                }
            }else if(access(arg,F_OK) && (fp=fopen(arg,"wb"))){
                strcpy(params->path_destination,arg);
                params->b_dest=1;
                fclose(fp);
                remove(arg);
            }else{
                printf("Argument ignoré. Impossible d'ecrire le fichier: %s\n",arg);
                printf("Message systeme: %s\n",strerror(errno));
                print_sep();
            }
            break;
        case 'p':
            strcpy(params->cle,arg);
            params->size_cle= strlen(params->cle);
            break;
        case 'k':
            params->keep=1;
            break;
        case 684:
            params->b_overwrite=1;
            break;
        default:
            if(arg && strcmp("crypt",arg) && strcmp("decrypt",arg)){
                fprintf(stderr,"Argument non reconnu:  %s\n",arg);
                print_sep();
                int del_dest=(params->fp_dest!=NULL);
                close_everything(params);
                if(del_dest==1){
                    remove(params->path_destination);
                }
                exit(EXIT_FAILURE);
            }
    }
    return 0;
}

void check_mode(char* arg,s_params *params){
    if(!strcmp("crypt",arg)){
        params->mode_chiffrement=1;
    }else if(!strcmp("decrypt",arg)){
        params->mode_chiffrement=0;
    }
}

void load_source(s_params *params){
    if(params->size_source<0){
        printf("Fichier source:");
        __fpurge(stdin);
        scanf("%s",params->path_source);
        loop_err_file(params->path_source,"source","rb");
    }
    params->size_source= load_file(params->path_source,&params->fp_source);
    printf("Fichier source charge: %s\n",params->path_source);
    print_sep();
}

void load_pass(s_params *params){
    char* path_cle="peroq.def";
    FILE* fp=NULL;
    if (params->size_cle<0){
        printf("Cle:");
        __fpurge(stdin);
        scanf("%s",params->cle);
    }
    params->size_cle= strlen(params->cle);
    printf("Cle de chiffrement lu: %s\n",params->cle);
    print_sep();
    if(params->mode_chiffrement==1){
        if((fp=fopen(path_cle,"wb"))){
            save_file(params->cle,params->size_cle,&fp);
            printf("Sauvegarde de la cle dans le fichier: %s\n",path_cle);
        }else{
            printf("Erreur sauvgarde de la clé %s\n",path_cle);
        }
        print_sep();
    }else if (params->mode_chiffrement==0){
        int l_read= load_file(path_cle,&fp);
        if(l_read>0){
            char cle_existante[l_read+1];
            read_file(&fp,cle_existante,l_read);
            cle_existante[l_read]='\0';
            if(strcmp(cle_existante,params->cle)!=0){
                fprintf(stderr,"Cle ne correspant pas à celle sauvegardé dans le fichier %s\n",path_cle);
                print_sep();
                int del_dest=(params->fp_dest!=NULL);
                close_everything(params);
                if(del_dest){
                    remove(params->path_destination);
                }
                exit(EXIT_FAILURE);
            }
        }else{
            printf("Impossible de lire le fichier %s.\n",path_cle);
            print_sep();
        }
    }

}

void load_dest(s_params *params){
    if((params->b_dest==3) && (params->b_overwrite==0)){
        printf("Argument ignoré. Fichier deja existant,\n--help pour voir l'argument necessaire\n");
        print_sep();
        params->b_dest=0;
    }
    if (params->b_dest==0){
        printf("Fichier destination:");
        __fpurge(stdin);
        scanf("%s",params->path_destination);
        loop_err_dest(params->path_destination,params->b_overwrite);
    }
    params->fp_dest= fopen(params->path_destination,"wb");
    printf("Fichier destination charge: %s\n",params->path_destination);
    print_sep();
}

void load_mode(s_params *params){
    if(params->mode_chiffrement<0){
        char mode = '3';
        printf("1- Chiffrement\n2- Dechiffrement\n");
        printf("Votre choix (1/2) :");
        __fpurge(stdin);
        scanf("%c", &mode);
        while ((mode != '1') && (mode != '2')) {
            printf("Valeur incomprise,veuillez reessayer\n");
            printf("1- Chiffrement\n2- Dechiffrement\n");
            printf("Votre choix (1/2) :");
            __fpurge(stdin);
            scanf("%c", &mode);
        }
        params->mode_chiffrement = (mode == '1');
    }
    printf("Execution en mode %s.\n", params->mode_chiffrement ? "chiffrement" : "dechiffrement");
    print_sep();
}

void load_params(int argc,char **argv, s_params *params){
    init_params(params);
    struct argp_option options[] ={
                    {0,0,0,0,"Options entrees",2} ,
                    { "file", 'f', "CHEMIN", 0, "Chemin du fichier source",2},
                    { "output", 'o', "CHEMIN", 0, "Chemin du fichier destination",2},
                    { "pass", 'p', "CLE", 0, "Passer CLE comme clé de cryptage",2},
                    { "keep", 'k', 0, 0, "Le fichier source n'est pas supprimé",2},
                    { "overwrite", 684, 0, 0, "Si le fichier destination existe deja, il sera ecrasé",2},
                    {0,0,0,0,"Options mode d'execution",1} ,
                    { "crypt", 1024, 0, OPTION_DOC, "Mode chiffrement",1},
                    { "decrypt", 1025, 0, OPTION_DOC, "Mode dechiffrement",1},
                    {0,0,0,0,"Options d'aide",-1},
            { 0 }};
    struct argp argp = { options, parse_opt,"[crypt|decrypt]...[OPTIONS...]",
            "Permet de faire un chiffrement/dechiffrement simple d'un fichier text\n" };
    if(argc>=2){
        check_mode(argv[1],params);
        argp_parse (&argp, argc, argv, 0, 0, params);
    }else{
        printf("Aucun arguments passes. Essayez: \"%s --help\" pour plus d'aide\n",argv[0]);
        print_sep();
    }
    load_mode(params);
    load_pass(params);
    load_source(params);
    load_dest(params);
}