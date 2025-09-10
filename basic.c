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
//A sfe and clean code
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
int main(void){
        const char message[] = "Hello world" ;
        char *src = (char *)malloc(sizeof(message)) ; 
        if(!src) return -1 ;
        strncpy(src , message , sizeof(message) - 1) ;
        src[sizeof(message) - 1] = '\0' ;

        char *dst = (char *)malloc(sizeof(message)) ;
        if(dst == NULL) {
                perror("Failed to allocate dst !") ; 
                free(src) ; 
                return -1 ;
        }
        strncpy(dst , src , sizeof(message) - 1) ;
        dst[sizeof(message) - 1] = '\0' ; 
        printf("Src is :%s \n" , src) ;
        printf("dst is :%s\n" , dst) ;
        printf("Addr of src :%p\n" , (void *)src) ; 
        printf("Addr of dst :%p\n" , (void *)dst) ;
        free(src) ; free(dst) ; 
        return 0 ;
}
