//Գրել ծրագիր, որի կատարման արդյունքում կստեղծվի thread և thread-ը կկանչի ֆունկցիա, 
// որը որպես արգումենտ ստանալու է զանգված և չափ։ Ֆունկցիան վերադարձնելու է 
// զանգվածի տարրերից երրորդ մեծագույնը։ 
// Ֆունկցիայի վերադարձված արժեքը տպել էկրանին։

#include <stdio.h>
#include <pthread.h>
#define ARR_SIZE 4

void * worker1 (void * arg)
{
    int * arr = arg;
    
    int first = 0;
    int second = 0;
    int third = 0;

    for (int i = 0; i < ARR_SIZE; ++i) {
        if (arr[i] > first) {
            third = second;
            second = first;
            first = arr[i];
        } else if (arr[i] > second) {
            third = second;
            second = arr[i];
        } else if (arr[i] > third) {
            third = arr[i];
        }
    }
    
    printf("Third max is: %i \n", third);
    
    return NULL;
}

int main ()
{
    int arr[ARR_SIZE] = {1, 5, 4, 3};
    
    pthread_t t1;
    
    if (pthread_create(&t1, NULL, worker1, arr) != 0) {
        printf("Error");
        return 1;
    }
    
    if (pthread_join(t1, NULL) != 0) {
        printf("Pthread join error");
    }
    
    return 0;
}