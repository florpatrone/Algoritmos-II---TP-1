#include <stdlib.h>
#include <string.h>

char *substr(const char *str, size_t n){
    char* sub_str = malloc(sizeof(char)*n+1);
 
    if (sub_str == NULL) return NULL;
 
    strncpy(sub_str,str,n);
    sub_str[n] = '\0';
    return sub_str;
}

char *join(char **strv, char sep){
    int x = 0;
    int tam = 0;
    
    while (strv[x]){
        tam += strlen(strv[x])+1;
        x++;
    }

    if (tam == 0) tam = 1;

    char* str_final = malloc(sizeof(char)*tam);

    int i = 0;
    int k = 0;

    while(strv[i]){
        int j = 0;
        while(strv[i][j] != '\0'){
            str_final[k] = strv[i][j];
            j++;
            k++;
        }
        str_final[k] = sep;
        i++;
        k++;
    }
    str_final[tam-1] = '\0';

    return str_final;
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