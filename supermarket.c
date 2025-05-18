#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
#include <time.h>

int N, B, C, F, T, L;

int caixas_entregues = 0;
int caixas_na_area = 0;
int caminhao_num = 1;
int finalizou_caminhao = 0;

sem_t sem_area_carga; 
pthread_mutex_t mutex_area = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond_area_carga = PTHREAD_COND_INITIALIZER;

void *thread_caminhao(void *arg) {
    while (1) {
        int espera = rand() % (T * 1000000);
        usleep(espera);

        pthread_mutex_lock(&mutex_area);
        if (caixas_entregues >= N) {
            pthread_mutex_unlock(&mutex_area);
            break;
        }
        int caixas_pedido = 1 + rand() % C;
        if (caixas_entregues + caixas_pedido > N) 
            caixas_pedido = N - caixas_entregues;

        printf("Caminhão %d, vai entregar %d caixa(s) na área de carga\n", caminhao_num, caixas_pedido);

        int caixas_desc = 0;
        while (caixas_desc < caixas_pedido) {
            while (caixas_na_area >= B) 
                pthread_cond_wait(&cond_area_carga, &mutex_area);

            int pode_colocar = B - caixas_na_area;
            int restantes = caixas_pedido - caixas_desc;
            int descarregar = pode_colocar < restantes ? pode_colocar : restantes;

            caixas_na_area += descarregar;
            caixas_desc += descarregar;
            caixas_entregues += descarregar;

            printf("Caminhão %d, descarregou %d caixa(s) na área de carga\n", caminhao_num, descarregar);

            pthread_cond_broadcast(&cond_area_carga);
        }
        caminhao_num++;
        pthread_mutex_unlock(&mutex_area);
    }
    printf("Encerrou thread caminhão\n");
    finalizou_caminhao = 1;
    pthread_cond_broadcast(&cond_area_carga);
    return NULL;
}

char *funcionarios_nome[3] = {"Bilguêiti", "Torvalino", "Ólanmusgo"};

void *thread_funcionario(void *arg) {
    int id = *(int *)arg;
    free(arg);
    printf("Criada thread que simula o funcionário %s\n", funcionarios_nome[id]);

    while (1) {
        pthread_mutex_lock(&mutex_area);
        while (caixas_na_area == 0 && !finalizou_caminhao) 
            pthread_cond_wait(&cond_area_carga, &mutex_area);

        if (caixas_na_area == 0 && finalizou_caminhao) {
            pthread_mutex_unlock(&mutex_area);
            break;
        }

        caixas_na_area--;
        pthread_cond_broadcast(&cond_area_carga);
        pthread_mutex_unlock(&mutex_area);

        int tempo = 500000 + rand() % (L * 1000000);
        usleep(tempo);

        printf("Funcionário %s, levou uma caixa ao estoque\n", funcionarios_nome[id]);
    }
    printf("Trabalho do funcionário %s acabou\n", funcionarios_nome[id]);
    return NULL;
}

int main(int argc, char *argv[]) {
    if (argc != 7) {
        printf("Uso correto: %s N B C F T L\n", argv[0]);
        return 1;
    }

    N = atoi(argv[1]);
    B = atoi(argv[2]);
    C = atoi(argv[3]);
    F = atoi(argv[4]);
    T = atoi(argv[5]);
    L = atoi(argv[6]);

    if (N <= 1 || N >= 100) return 1;
    if (B <= 1 || B >= 10) return 1;
    if (C <= 1 || C >= 5) return 1;
    if (F <= 1 || F >= 4) return 1;
    if (T <= 1 || T >= 20) return 1;
    if (L <= 1 || L >= 15) return 1;

    srand(time(NULL));

    pthread_t thread_caminhoes;
    pthread_t funcionarios_threads[3];

    pthread_create(&thread_caminhoes, NULL, thread_caminhao, NULL);

    for (int i = 0; i < F; i++) {
        int *id = malloc(sizeof(int));
        *id = i;
        pthread_create(&funcionarios_threads[i], NULL, thread_funcionario, id);
    }

    pthread_join(thread_caminhoes, NULL);

    for (int i = 0; i < F; i++) {
        pthread_join(funcionarios_threads[i], NULL);
    }

    return 0;
}
