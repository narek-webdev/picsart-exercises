//Գրեք C ծրագիր, որը զանգվածը բաժանում է հատվածների և յուրաքանչյուր հատվածը փոխանցում է առանձ
//ին thread-ի։ Յուրաքանչյուր thread պետք է գումարի իր հատվածի տարրերը և թարմացնի գլո
//բալ գումարի փոփոխականը։

#include <stdio.h>
#include <pthread.h>
#define ARR_SIZE 8
#define PART 2

int glob = 0;
    
typedef struct {
    int * arr;
    int start;
    int end;
} ThreadArray;

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

void * worker (void * arg)
{
    pthread_mutex_lock(&mutex);
        ThreadArray * struct_array = (ThreadArray *)arg;
        for (int i = struct_array->start; i < struct_array->end; ++i) {
            glob += struct_array->arr[i];
        }
    pthread_mutex_unlock(&mutex);
    return NULL;
}

int main ()
{
    if (ARR_SIZE < PART) {
        perror("Wrong params");
        return 1;
    }
    
    if (ARR_SIZE == 0 || PART == 0) {
        perror("Zero is not valid");
        return 1;
    }
    

    ThreadArray t_arr[PART];
    pthread_t threads[PART];
    
    int perBox = ARR_SIZE / PART;
    int rightIndex = 0;
    int leftIndex = 0;
        
    int arr[ARR_SIZE] = {1, 2, 3, 4, 5, 6, 7, 8};
    
    for (int i = 0; i < PART; ++i) {
        leftIndex = rightIndex;
        
        //If we reach the final move
        if (i == (PART - 1)) {
            rightIndex = ARR_SIZE; 
        } else {
            rightIndex = rightIndex + perBox;
        }

        t_arr[i].start = leftIndex;
        t_arr[i].end = rightIndex;
        t_arr[i].arr = arr;
    }

    for (int i = 0; i < PART; ++i) {
        if (pthread_create(&threads[i], NULL, worker, &t_arr[i])) {
            perror("pthread_create");
            return 1;
        }
    }
    
    for (int i = 0; i < PART; ++i) {
        if (pthread_join(threads[i], NULL)) {
            perror("pthread_join");
            return 1;
        }
    }
    
    printf("Global variable is: %i\n", glob);
    
    return 0;
}