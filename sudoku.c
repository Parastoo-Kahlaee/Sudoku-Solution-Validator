#include<pthread.h>
#include<stdio.h>
#include<stdlib.h>
#include <unistd.h>

int table[9][9];
int repeat[9][11];
void set_0(int num)
{
    for (int i = 0; i < 9; i++)
        repeat[i][num] = 0;  
}

void* sudoku(void* arg) {
    int thread_num = *(int*)arg;
    if (thread_num == 10)
    {
        for (int i = 0; i < 9; i++)
        {
            set_0(10);
            for (int j = 0; j < 9; j++)
            {
                repeat[table[i][j]-1][thread_num]++;
            }
            for (int j = 0; j < 9; j++)
            {
                if (repeat[j][thread_num] > 1 || repeat[j][thread_num] < 1)
                {
                    printf("not valid : rows\n");
                    pthread_exit(NULL);
                }
            }
        }
    }
    else if (thread_num == 9)
    {
        for (int i = 0; i < 9; i++)
        {
            set_0(9);
            for (int j = 0; j < 9; j++)
            {
                repeat[table[j][i]-1][thread_num]++;
            }
            for (int j = 0; j < 9; j++)
            {
                if (repeat[j][thread_num] > 1 || repeat[j][thread_num] < 1)
                {
                    printf("not valid : columns\n");
                    pthread_exit(NULL);
                }
            }
        }
    }
    else 
    {
        //set_0();
        for (int i = (thread_num % 3) * 3 ; i < (thread_num % 3) * 3 + 3; i++) //khat amood
        {
            for (int j = (thread_num / 3) * 3; j < (thread_num / 3) * 3 + 3; j++ )
            {
                repeat[table[j][i]-1][thread_num]++;
                //printf("%d ",table[i][j]);
            }
            //printf("\n");  
        }
        for (int j = 0; j < 9; j++)
        {
            if (repeat[j][thread_num] > 1 || repeat[j][thread_num] < 1)
            {
                printf("not valid %d \n",thread_num + 1);
                pthread_exit(NULL);
            }
        }
    }
    pthread_exit(NULL);
}
int main() 
{
    const int NUM_THREADS = 11;
    pthread_t threads[NUM_THREADS];
    int thread_ids[NUM_THREADS];

    for (int i = 0; i < 9; i++)
    {
        for (int j = 0; j < 9; j++)
        {
            scanf("%d", &table[i][j]);
        }
    }
    for (int i = 0; i < NUM_THREADS; i++) {
        thread_ids[i] = i;
        int result = pthread_create(&threads[i], NULL, sudoku, &thread_ids[i]);
        if (result) {
            fprintf(stderr, "Error %d\n", i + 1);
            exit(1);
        }
    }
    for (int i = 0; i < NUM_THREADS; i++) {
        pthread_join(threads[i], NULL);
    }

    printf("Threads finished\n");
    return 0;
}