#include <stdlib.h>
#include <string.h>

char *substr(const char *str, size_t n){
    char* sub_str = malloc(sizeof(char)*n+1);
 
    if (sub_str == NULL) return NULL;
 
    strncpy(sub_str,str,n);
    sub_str[n] = '\0';
    return sub_str;
}

char **split(const char *str, char sep){
    int i = 0;
    int cont_s = 0;
    int cont_c = 0;

    char* vector_est[strlen(str)+1];

    while (1){

        if ((str[i] != sep) && (str[i] != '\0')){
            cont_c++;
            
        }else{
            cont_s++;
            char* n_str = malloc(sizeof(char)*cont_c+1);
            strncpy(n_str,str+(i-cont_c),cont_c);
            n_str[cont_c] = '\0';
            vector_est[cont_s-1] = n_str;

            if (str[i] == '\0') break;
            cont_c = 0;
        }        
        i++;
    }

    char** vector_din = malloc(sizeof(char*)*cont_s+1);

    for (int j = 0; j < cont_s; j++){
        vector_din[j] = vector_est[j];
    }

    vector_din[cont_s] = NULL;

    return vector_din;

}

char *join(char **strv, char sep){
    int x = 0;
    int tam = 0;
    
    while (strv[x]){
        tam += strlen(strv[x])+1;
        x++;
    }

    if (tam == 0) tam = 1;

    char* jstr = malloc(sizeof(char)*tam);

    int pos_arreglo = 0;
    int pos_jstr = 0;

    while(strv[pos_arreglo]){
        int pos_str = 0;
        while(strv[pos_arreglo][pos_str] != '\0'){
            str_final[pos_jstr] = strv[pos_arreglo][pos_str];
            pos_str++;
            pos_jstr++;
        }
        jstr[pos_jstr] = sep;
        pos_arreglo++;
        pos_jstr++;
    }
    jstr[tam-1] = '\0';

    return jstr;
}
 
void free_strv(char *strv[]){
    int i = 0;
    char* str = strv[i];

    while (str){
        free(str);
        i++;
    }
    free(strv);
}