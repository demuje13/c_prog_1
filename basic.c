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
//using posix memaligmnent 
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
int main(void){
        void *pointer ; 
        size_t size = sizeof(int) * 10 ; 
        size_t memalign_boundary = 16 ; 
        if(posix_memalign(&pointer , memalign_boundary , size) == 0){
                memset(pointer , 0 , size) ; 
                int *array = (int *)pointer ; 
                for(int i = 0 ; i < 10 ; i++){
                        array[i] = i + 10 ;
                }
                for(int i = 0 ; i < 10 ; i++){
                        printf("Array :%d of value :%d of mem addr : %p\n" , i , array[i] ,(void *)&array[i]) ; 
                }
                free(pointer) ;
        }else{
                fprintf(stderr , "Posix mem alignment failed !\n") ; 
                exit(EXIT_FAILURE) ;
        }
        return 0 ;
}
//for a single digit 
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
int main(void){
        void *ptr ; 
        size_t size_of_int = sizeof(int) ; 
        size_t alignment_bound = 16 ; 
        if(posix_memalign(&ptr , alignment_bound , size_of_int) == 0){
                memset(ptr , 0 , sizeof(int)) ; 
                int *number = (int *)ptr ; 
                *number = 10 ;
                printf("The number is :%d of mem addr :%p\n" , *number , ptr) ;
                free(ptr) ;
        }else{
                return -1 ;
        }
        return 0 ;
}
//safe , trust , use -mavx lnker 
#include <stdio.h>
#include <stdlib.h>
#include <immintrin.h>

int main() {
    void *ptr;
    size_t alignment = 32;
    size_t size = 8 * sizeof(float);
    if (posix_memalign(&ptr, alignment, size)) return 1;
    float *arr = ptr;
    for (int i = 0; i < 8; i++) arr[i] = i + 1;
    __m256 vec = _mm256_load_ps(arr);
    float result[8] __attribute__((aligned(32)));  
    _mm256_store_ps(result, vec);
    for (int i = 0; i < 8; i++) printf("%.1f ", result[i]);
    printf("\n");
    free(ptr);
    return 0;
}

-- SIMD (Single Instruction, Multiple Data)
-- AVX = Advanced Vector Extensions
