#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define POPULACAO_TAM 10
#define PESO_MAX 50
#define NUM_ITENS 5

typedef struct {
    int peso;
    int valor;
} Item;

Item itens[NUM_ITENS] = {
    {10, 60},
    {20, 100},
    {30, 120},
    {5, 30},
    {15, 50}
};

int gerarNumAleatorio(int min, int max) {
    return min + rand() % (max - min + 1);
}

int fitnessFunction(int *chromosome) {
    int peso_total = 0, valor_total = 0;
    for (int i = 0; i < NUM_ITENS; i++) {
        if (chromosome[i] == 1) {
            peso_total += itens[i].peso;
            valor_total += itens[i].valor;
        }
    }
    if (peso_total > PESO_MAX) {
        return 0;
    }
    return valor_total;
}

void crossover(int *parent1, int *parent2, int *child) {
    int crossover_point = gerarNumAleatorio(0, NUM_ITENS - 1);
    for (int i = 0; i < crossover_point; i++) {
        child[i] = parent1[i];
    }
    for (int i = crossover_point; i < NUM_ITENS; i++) {
        child[i] = parent2[i];
    }
}

void mutate(int *chromosome) {
    if(gerarNumAleatorio(0, 100) < 5){

        int mutation_point = gerarNumAleatorio(0, NUM_ITENS - 1);
        chromosome[mutation_point] = 1 - chromosome[mutation_point];
    }
}

void printSolution(int *chromosome) {
    printf("Itens Selecionados: \n");
    for (int i = 0; i < NUM_ITENS; i++) {
        if (chromosome[i] == 1) {
            printf("Item %d - Peso: %d, Valor: %d\n", i, itens[i].peso, itens[i].valor);
           
        }
    }
    printf("\n");
}

int main() {
    srand(time(NULL));

    int population[POPULACAO_TAM][NUM_ITENS];

    for (int i = 0; i < POPULACAO_TAM; i++) { //preenche cromossomo com valores binários
        for (int j = 0; j < NUM_ITENS; j++) {
            population[i][j] = rand() % 2; 
        }
    }
    int generations = 100;
    while (generations--) {
        int parent1 = rand() % POPULACAO_TAM; //seleciona aleatoriamente os pais
        int parent2 = rand() % POPULACAO_TAM;

        //crossover gera novo filho
        int child[NUM_ITENS];
        crossover(population[parent1], population[parent2], child);
        //mutação é aplicada com probabilidade
        if (gerarNumAleatorio(0, 100) < 10) {
            mutate(child);
        }
       
        int child_fitness = fitnessFunction(child);
        //Substituição do pior indivíduo (caso o filho seja melhor):
        if (child_fitness > fitnessFunction(population[POPULACAO_TAM - 1])) {
            for (int i = 0; i < NUM_ITENS; i++) {
                population[POPULACAO_TAM - 1][i] = child[i];
            }
        }
        //Ordenação da população por aptidão (fitness) 
        for (int i = 0; i < POPULACAO_TAM - 1; i++) {
            for (int j = i + 1; j < POPULACAO_TAM; j++) {
                if (fitnessFunction(population[i]) < fitnessFunction(population[j])) {
                    int temp[NUM_ITENS];
                    for (int k = 0; k < NUM_ITENS; k++) {
                        temp[k] = population[i][k];
                        population[i][k] = population[j][k];
                        population[j][k] = temp[k];
                    }
                }
            }
        }
    }

    printf("Melhor solucao:\n");
    printSolution(population[0]);
    
    return 0;
}

