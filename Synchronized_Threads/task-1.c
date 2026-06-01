//Ունենք գլոբալ 0-ով արժեքավորված փոփոխական, իրականացնել ծրագիր, որը յ
//ուրաքանչյուր thread֊ի միջոցով ավելացնում է փոփոխականի արժեքը 100֊ով։
//Օգտագործելով mutex` վստահ եղեք, որ արդյունքը կլինի 100֊ի բազմապատիկ։ 

#include <stdio.h>
#include <pthread.h>
#define T_NUM 3

int glob = 0;

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

void * worker (void * arg) {
    pthread_mutex_lock(&mutex);
    glob += 100;
    pthread_mutex_unlock(&mutex);
    
    return NULL;
}

int main ()
{
    pthread_t threads[T_NUM];

    for (int i = 0; i < T_NUM; ++i) {
        if (pthread_create(&threads[i], NULL, worker, NULL)) {
            perror("pthread_create");
            return 1;
        }
    }
    
    for (int i = 0; i < T_NUM; ++i) {
        if (pthread_join(threads[i], NULL)) {
            perror("pthread_join");
            return 1;
        }
    }
    
    printf("Global value: %i\n", glob);

    return 0;
}