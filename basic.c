//copy string
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
int main(void){
        char src[] = "Dark Boy !" ; 
        char dst[30] ; 
        strncpy(dst , src , sizeof(dst) - 1) ; 
        dst[sizeof(dst) - 1] = '\0' ; 
        printf("Src is :%s\n" , src) ; 
        printf("Dst is :%s\n" , dst) ; 
        return 0 ;
}
