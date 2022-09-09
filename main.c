#include "crypt.h"
#include "interface.h"

const char *argp_program_bug_address = "boukhatem.abderraouf@gmail.com";
const char *argp_program_version = "0.0.1";

int main(int argc,char** argv) {
    print_sep();
    s_params params;
    load_params(argc,argv,&params);
    if(params.mode_chiffrement){
        chiffrer_f(&params.fp_source,&params.fp_dest,params.cle,params.size_source,params.size_cle);
    }else{
        dechiffrer_f(&params.fp_source,&params.fp_dest,params.cle,params.size_source,params.size_cle);
    }
    if(params.keep){
        printf("Fichier source gardé\n");
    }else{
        remove(params.path_source);
        printf("Fichier source supprimé\n");
    }
    print_sep();
    printf("Traitement terminé\n");
    print_sep();
    return 0;
}
