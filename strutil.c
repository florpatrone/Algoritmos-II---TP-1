#include <stdlib.h>
#include <string.h>

char *substr(const char *str, size_t n){
    char* sub_str = malloc(sizeof(char)*n+1);
 
    if (sub_str == NULL) return NULL;
 
    strncpy(sub_str,str,n);
    sub_str[n] = '\0';
    return sub_str;
}

