//Գրել ծրագիր, որը կստեղծի 2 thread, 1-ին thread-ի կանչած ֆունկցիան դինամիկ 
// հիշողությունից կվերցնի զանգված և կլցնի զանգվածի մեջ մինչև N-ը եղած բոլոր 
// պարզ թվերը։ 2-րդ thread-ը ստանալու է 1-ին thread-ում ստեղծված զանգվածը և 
// կտպի էկրանին զանգվածի տարրերը, ինչպես նաև կազատի դինամիկ հիշողությունից 
// վերցրած տարածքը։

#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#define N_NUM 5

_Bool isPrime (int n)
{
    if (n < 2) return 0;
    
    for (int i = n - 1; i > 1; --i) {
        if (n % i == 0) {
            return 0;
        }
    }
    
    return 1;
}

void * worker1 (void * arg)
{
    int * arr = arg;
    
    for (int i = 0; i < N_NUM; ++i) {
        if (isPrime(i + 1)) {
            arr[i] = i + 1;
        }
    }
    
    return arr;
}

void * worker2 (void * arg)
{
    int * arr = arg;
    
    for (int i = 0; i < N_NUM; ++i) {
        if (!arr[i]) continue;
        printf("%i\n", arr[i]);
    }
    
    free(arr);
    arr = NULL;
    
    return NULL;
}

int main()
{
    int * arr = calloc(N_NUM, sizeof(int));
    
    if (arr == NULL) {
        printf("Error: calloc");
        return 1;
    }
    
    pthread_t t1;
    int thread1 = pthread_create(&t1, NULL, worker1, arr);
    if (thread1 != 0) {
        printf("Thread 1 Error");
        return 1;
    }
    
    if (pthread_join(t1, NULL) != 0) {
     printf("Join error t1");
     return 1;
    }
    
    pthread_t t2;
    int thread2 = pthread_create(&t2, NULL, worker2, arr);
    
    if (thread2 != 0) {
        printf("Thread 2 Error");
        return 1;
    }
    
    if (pthread_join(t2, NULL) != 0) {
        printf("Join error 2");
        return 1;
    }
    
    return 0;
}