#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <stdbool.h>

#define NUM_PROCESSOS 5

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
int token = 0; // Inicialmente, o token está com o processo 0
int coordenador = NUM_PROCESSOS - 1; 

// Função da seção crítica
void secao_critica(int id) {
    printf("Processo %d está na seção crítica.\n", id);
    sleep(1); // Simula a operação na seção crítica
}

// Função que simula o comportamento dos processos
void* processo(void* arg) {
    int id = *((int*)arg);

    while (true) {
        pthread_mutex_lock(&mutex);
        // Exclusão Mútua - Algoritmo Token-Ring
        if (id == token) {
            secao_critica(id);
            token = (token + 1) % NUM_PROCESSOS;
        }

        // Verificação e eleição de coordenador - Algoritmo do Valentão
        if (id != coordenador && rand() % 10 == 0) { // Simula a falha do coordenador
            printf("Processo %d detectou a falha do coordenador %d e iniciou a eleição.\n", id, coordenador);
            for (int i = id + 1; i < NUM_PROCESSOS; i++) {
                printf("Processo %d envia mensagem de eleição para o processo %d.\n", id, i);
            }
            coordenador = id;
            for (int i = id + 1; i < NUM_PROCESSOS; i++) {
                printf("Processo %d informa ao processo %d que é o novo coordenador.\n", id, i);
            }
            printf("Processo %d se tornou o novo coordenador.\n", id);
        }
        pthread_mutex_unlock(&mutex);
        sleep(1); // Intervalo entre verificações
    }
}

int main() {
    pthread_t threads[NUM_PROCESSOS];
    int ids[NUM_PROCESSOS];

    // Cria as threads dos processos
    for (int i = 0; i < NUM_PROCESSOS; i++) {
        ids[i] = i;
        pthread_create(&threads[i], NULL, processo, (void*)&ids[i]);
    }

    // Aguarda a finalização das threads (nunca será alcançado)
    for (int i = 0; i < NUM_PROCESSOS; i++) {
        pthread_join(threads[i], NULL);
    }

    return 0;
}
