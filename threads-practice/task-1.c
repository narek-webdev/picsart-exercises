//Ծրագիրը պետք է հարցնի օգտվողից մի ամբողջ թիվ n. 
// Ստեղծի թրեդ (thread), որը ստանում է այս թիվը որպես արգումենտ. 
// Թրեդը պետք է տպի բոլոր զույգ թվերը 0-ից մինչև n.

#include <stdio.h>
#include <pthread.h>

void * worker1 (void * arg)
{
    int n = *(int*)arg;
    
    printf("Print even numbers: \n");
    for (int i = 2; i <= n; i+=2)
    {
        printf("%d\n", i);
    }
    
    return NULL;
}

int main()
{
    int n = 0;
    
    printf("Write your number: ");
    scanf("%d", &n);

    if (n <= 0) {
        printf("Error: ");
        return 1;
    }
    
    pthread_t t1;
    
    if (pthread_create(&t1, NULL, worker1, &n) != 0) {
        printf("Thread create error: ");
        return 1;
    }
    
    if (pthread_join(t1, NULL) != 0) {
        printf("Thread join error: ");
        return 1;
    }
    
    return 0;
}