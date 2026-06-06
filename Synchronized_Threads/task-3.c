//Գրել ծրագիր, որը ստեղծում է 2 thread, որոնք 
//միաժամանակ աշխատելով տպում են զանգվածի անդամները ճիշտ հաջորդականությամբ։ 
//Առաջինը տպում է միայն զույգ  ինդեքսներով էլեմենտները, երկրորդը՝  միայն կենտերը։

#include <stdio.h>
#include <pthread.h>
#define ARR_SIZE 5

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond = PTHREAD_COND_INITIALIZER;

int ready = 0;

void * odd_thread(void * arg) 
{
    int * arr = (int *)arg;
    
    for (int i = 1; i < ARR_SIZE; i+=2) 
    {
        pthread_mutex_lock(&mutex);

        while (ready != 1)
        {
            pthread_cond_wait(&cond, &mutex);
        }

        printf("%d\n", arr[i]);
        
        ready = 0;
        pthread_cond_signal(&cond);

        pthread_mutex_unlock(&mutex);
    }
    
    return NULL;
}

void * even_thread (void * arg) 
{
    int * arr = (int *)arg;
      
    for (int i = 0; i < ARR_SIZE; i += 2) 
    {
        pthread_mutex_lock(&mutex);

        while (ready != 0)
        {
            pthread_cond_wait(&cond, &mutex);
        }

        printf("%d\n", arr[i]);
        
        ready = 1;
        pthread_cond_signal(&cond);

        pthread_mutex_unlock(&mutex);
    }

    return NULL;
}

int main()
{
    int arr[ARR_SIZE] = {1, 2, 3, 4, 5};
    
    pthread_t t_even, t_odd;
    
    pthread_create(&t_even, NULL, even_thread, (void *)arr);
    pthread_create(&t_odd, NULL, odd_thread, (void *)arr);
        
    pthread_join(t_even, NULL);
    pthread_join(t_odd, NULL);

    return 0;
}