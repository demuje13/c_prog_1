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
//another simple example of alloc for 2d array 
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
int main(void){
        int row = 3 ; 
        int coll = 3 ;
        int **matrix = (int **)malloc(sizeof(int *) * row) ; 
        if(matrix == NULL){
                fprintf(stderr , "Failed to do alloc row !") ;
                return -1 ; 
        }
        for(int i = 0 ; i < row ; i++){
                matrix[i] = (int *)malloc(sizeof(int) * coll) ; 
                if(matrix[i] == NULL){
                        fprintf(stderr , "Failed to allocate matrix[i]") ; 
                        int x = 0 ; 
                        for(int x = 0 ; x < i ; x++){
                                free(matrix[x]) ;
                        }
                        free(matrix) ; 
                        exit(EXIT_FAILURE) ;
                }
        }
        int count = 0 ;
        for(int i = 0 ; i < row ; i++){
                for(int j = 0 ; j < coll ; j++){
                        matrix[i][j] = count++ ;
                }
        }

        for(int i = 0 ; i < row ; i++){
                for(int j = 0 ; j < coll ; j++){
                        printf("%d " ,matrix[i][j]) ;
                }
                printf("\n") ;
        }
        for(int i= 0 ; i < row ; i++){
                free(matrix[i]) ;
        }
        free(matrix) ;
}
