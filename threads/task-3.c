//Իրականացնել ծրագիր, որը ստեղծում է  N x N չափանի մատրից և արժեքավորում է այն։ 
// Պետք է ստեղծել միաժամանակ աշխատող 4 thread-ներ, 
// որոնցից յուրաքանչյուրը ունի առանձին ֆունկցիոնալություն.
//Գտնում և տպում է մատրիցի մեծագույն արժեքը։
//Գտնում և տպում է մատրիցի փոքրագույն արժեքը։
//Տպում է մատրիցի  գլխավոր և երկրորդական անկյունագծերը (խաչաձև)։
//Հաշվում և վերադարձնում է մատրիցի  արժեքների միջին թվաբանականը։

#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#define MATRIX_N 2

void * worker1 (void * arg)
{
    int (* matrix)[MATRIX_N] = arg;
    
    int max = matrix[0][0];
    
    for (int rows = 0; rows < MATRIX_N; ++rows) {
        for (int cols = 0; cols < MATRIX_N; ++cols) {
           if (matrix[rows][cols] > max) {
               max = matrix[rows][cols];
           }
        }
    } 
    
    printf("Maximum element is: %i\n", max);
    
    return NULL;
}

void * worker2 (void * arg)
{
    int (* matrix)[MATRIX_N] = arg;
    
    int min = matrix[0][0];
    
    for (int rows = 0; rows < MATRIX_N; ++rows) {
        for (int cols = 0; cols < MATRIX_N; ++cols) {
           if (matrix[rows][cols] < min) {
               min = matrix[rows][cols];
           }
        }
    } 
    
    printf("Minimum element is: %i\n", min);
    
    return NULL;
}

void * worker3 (void * arg)
{
    int (* matrix)[MATRIX_N] = arg;
    
    printf("Main ankyun: ");
    for (int rows = 0; rows < MATRIX_N; ++rows) {
        printf(" %d ", matrix[rows][rows]);
    }
    printf("\n");
    
    printf("Not main ankyun: ");
    for (int rows = 0; rows < MATRIX_N; ++rows) {
        printf(" %d ", matrix[rows][MATRIX_N - 1 - rows]);
    }
    printf("\n");
    
    return NULL;
}

void * worker4 (void * arg)
{
    int (*matrix)[MATRIX_N] = arg;
    int sum = 0;
    
    for (int rows = 0; rows < MATRIX_N; ++rows) {
        for (int cols = 0; cols < MATRIX_N; ++cols) {
            sum += matrix[rows][cols];
        }
    }
    
    int * mean = malloc(sizeof(int));
    if (mean == NULL) {
        return NULL;
    }
    
    *mean = sum / (MATRIX_N * MATRIX_N);
    
    return mean;
}

int main ()
{
    int matrix[MATRIX_N][MATRIX_N];
    
    for (int rows = 0; rows < MATRIX_N; ++rows) {
        for (int cols = 0; cols < MATRIX_N; ++cols) {
            printf("Write matrix [%d][%d]: ", rows, cols);
            scanf("%d", &matrix[rows][cols]);
        }
    }
    
    pthread_t t1;
    if (pthread_create(&t1, NULL, worker1, matrix) != 0) {
        printf("Error: thread 1");
        return 1;
    }
    
    pthread_t t2;
    if (pthread_create(&t2, NULL, worker2, matrix) != 0) {
        printf("Error: thread 2");
        return 1;
    }
    
    pthread_t t3;
    if (pthread_create(&t3, NULL, worker3, matrix) != 0) {
        printf("Error: thread 3");
        return 1;
    }
    
    pthread_t t4;
    if (pthread_create(&t4, NULL, worker4, matrix) != 0) {
        printf("Error: thread 4");
        return 1;
    }
    
    if (pthread_join(t1, NULL) != 0) {
        printf("Error: join 1");
    }
    
    if (pthread_join(t2, NULL) != 0) {
        printf("Error: join 2");
    }
    
    if (pthread_join(t3, NULL) != 0) {
        printf("Error: join 3");
    }
    
    void * res = NULL;
    
    if (pthread_join(t4, &res) != 0) {
        printf("Error: join 4");
    }
    
    if (res != NULL) {
        printf("Matrix arithmetic mean is: %d \n", *(int *)res);
        free(res);
    }
    
    return 0;
}