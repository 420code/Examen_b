examen_b.c
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <semaphore.h>
    typedef struct cubitoenmaicra
{
    int hash;
} bloque;

bloque operacion[10];
int contGlobal = 0;

void *facto1(void *ola)
{
    int numero = (int)operacion[contGlobal].hash;
    int a;
    a = numero * numero;
    printf("a=%d\n", a);
    pthread_exit((void *)a);
}
void *facto2(void *k)
{
    int numero2 = (int)operacion[contGlobal].hash + 1;
    int b;
    b = numero2 * numero2;
    printf("b=%d\n", b);
    pthread_exit((void *)b);
}
void *facto3(void *ase)
{
    int numero3 = (int)operacion[contGlobal].hash + 2;
    int c;
    c = numero3 * numero3;
    printf("c=%d\n", c);
    pthread_exit((void *)c);
}

int nose()
{
    printf("hola");
    int a, b, c;
    pthread_t t1, t2, t3;
    pthread_create(t1, NULL, &facto1, (void *)operacion[contGlobal].hash);
    pthread_create(t1, NULL, &facto2, (void *)operacion[contGlobal].hash);
    pthread_create(t1, NULL, &facto3, (void *)operacion[contGlobal].hash);
    pthread_join(&facto1, (void **)&a);
    pthread_join(&facto2, (void **)&b);
    pthread_join(&facto3, (void **)&c);
    int nuevoHash = a + b + c;
    return nuevoHash;
}

int main()
{
    pid_t pid;
    srand(getpid());
    int cantProcesos, i, menu, hashNuevo;
    for (i = 0; i < 10; i++)
    {
        operacion[i].hash = 0;
    }
    operacion[contGlobal].hash = rand() % 9 + 1;
    printf("Cuantos procesos desea crear?\n");
    scanf("%d", &cantProcesos);
    for (i = 0; i < cantProcesos; i++)
    {
        pid = fork();
        if (pid == 0)
        {
            nose();
        }
    }
    hashNuevo = WEXITSTATUS((int)nose);
    operacion[contGlobal + 1].hash = hashNuevo;
    printf("Se ha creado la transacción. Hash anterior: %d. Hash actual: %d\n", operacion[contGlobal].hash, operacion[contGlobal + 1].hash);
    contGlobal++;
}
