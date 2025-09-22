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
-- simple avx 
//this code does the same as previous ...but it it for unsigned int and the previous was for float 
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<immintrin.h>
#include<string.h>
int main(void){
        void *ptr ; 
        size_t value_size = sizeof(unsigned int) * 8  ; 
        size_t bound = 32 ; 
        if(posix_memalign(&ptr , bound , value_size) == 0){
                memset(ptr , 0 , sizeof(unsigned int) * 8) ; 
                unsigned int *array = (unsigned int *)ptr ; 
                for(int i = 0 ; i < 8 ; i++){
                        array[i] = (unsigned int)(i * 10u) ;
                }
                unsigned int result[8] __attribute__((aligned(32))) ; 
                __m256i vector = _mm256_load_si256((__m256i *)array) ;
                _mm256_store_si256((__m256i*)result , vector) ; 
                for(int i = 0 ; i < 8 ; i++){
                        printf("%d\n" , array[i]) ;
                }
                free(ptr) ;
        }else{
                fprintf(stderr , "Posix memalign failed \n") ;
                exit(EXIT_FAILURE) ;
        }
        return 0 ;
}
//another c code 
#include<stdio.h>
#include<stdlib.h>
typedef struct {
    int date , month , year ;
}Date ; 

typedef struct {
   char  book_name[20] ; 
   Date release ;
}Book ; 
int main(void){
    Book b1 = {"How to fuck enemy" , {20 , 8 , 2025}} ; 
    printf("The book name :%s\n release time :%d : %d :%d\n" ,b1.book_name , b1.release.date , b1.release.month , b1.release.year); 
}

//another simple example of struct and node 
#include<stdio.h>
#include<stdlib.h>
typedef struct {
    int data ; 
    struct Node *next ;
}Node ; 
int main(void){
    Node *number = malloc(sizeof(Node)) ;
    if(number == NULL){
        fprintf(stderr , "failed to alloc for Node !\n") ; 
        return -1;
    }
    number->data = 120 ; 
    number->next = NULL ; 
    printf("The value of data is :%d and the asddress is :%p\n" , number->data , (void *)number);
    printf("The next node addr is :%p\n " , number->next) ;
    free(number) ;
}
//another code for struct and pointer 
#include<stdio.h>
#include<stdlib.h>
typedef struct {
    int x ; 
    int y ;
}Point ; 
typedef Point *pointptr ; 
int main(void){
    pointptr value = malloc(sizeof(Point)) ; 
    if(value == NULL) return -1 ; 
    value->x = 10 ; 
    value->y = 20 ; 
    printf("first : Addr is :%p of value :%d\n" , (void *)&value , value->x) ;
    printf("Second : Addr is :%p of value :%d\n" , (void *)&value , value->y) ;
    free(value) ;
    return 0 ;
}
//forloop + struct 
#include<stdio.h>
typedef struct {
    char name[20] ;
    int power_level  ; 
}Evil ;
int main(void){
    Evil mons[4] = {
        {"Evil" , 20} , 
        {"Demon" , 50} , 
        {"Devil" , 90} ,
        {"God" , 0} 
    } ;
    size_t size = sizeof(mons) / sizeof(mons[0]) ;
    for(int i = 0 ; i < size ; i++){
        printf("%s has the power level :%d\n" , mons[i].name  , mons[i].power_level) ; 
    }
    return 0 ;
}
//using pointer of struct 
#include<stdio.h>
#include<stdlib.h>
typedef struct Point{
    int num1 ;
    int num2 ;
}Point ;
typedef Point *point_ptr ;
int main(void){
    point_ptr data = malloc(sizeof(Point)) ;
    if(data == NULL) return -1 ;
    data->num1 = 10 ;
    data->num2 = 200 ;
    printf("Number 1 is :%d and number 2 is :%d\n" , data->num1 , data->num2) ;
    free(data) ;
    return 0 ;
}
//calculate 
#include<stdio.h>
int add(int a , int b){
    return a + b ;
}
int sub(int a , int b){
    return a - b ;
}
int mul(int a , int b){
    return a * b ;
}
int main(void){
    int (*op[3])(int , int) = {add , sub  , mul} ;
    printf("Addition :%d\n" , op[0](20 , 10)) ;
    printf("Sub : :%d\n" , op[1](10 , 20)) ;
    printf("Mul :%d\n" , op[2](10 , 30)) ;
}
