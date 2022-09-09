#include "crypt.h"
#include "interface.h"

const char *argp_program_bug_address = "boukhatem.abderraouf@gmail.com";
const char *argp_program_version = "0.0.1";

int main(int argc,char** argv) {
    s_params params;
    load_params(argc,argv,&params);
    char tab_in[params.size_source], tab_out[params.size_source];
    read_file(&params.fp_source,tab_in,params.size_source);
    if(params.mode_chiffrement){
        chiffrer(tab_in,params.cle,tab_out,params.size_source,params.size_cle);
    }else{
        dechiffrer(tab_in,params.cle,tab_out,params.size_source,params.size_cle);
    }

    if(params.keep){
        printf("Fichier source gardé\n");
    }else{
        remove(params.path_source);
        printf("Fichier source supprimé\n");
    }
    save_file(tab_out,params.size_source,&params.fp_dest);
    print_sep();
    printf("Traitement terminé\n");
    print_sep();
    return 0;
}
