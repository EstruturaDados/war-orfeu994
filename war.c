// ============================================================================
//         PROJETO WAR ESTRUTURADO - DESAFIO DE CÓDIGO


//feito por matheus dirceu neri orfeu994
// ============================================================================
// WAR.c
// Programa para gerenciar informações de territórios em um jogo de WAR
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h> // Para gerar numeros aleatorios

// Define o comando para limpar a tela dependendo do sistema operacional
#ifdef _WIN32
#define CLEAR "cls"
#else
#define CLEAR "clear"
#endif

// Removido o #define NUM_TERRITORIOS
// Variável global para o número de territórios
int NUM_TERRITORIOS;

// Estrutura para armazenar informações de um território
typedef struct {
    char nome[30];
    char cor[10];
    int tropas;
} Territorio;


// limpeza de buffer
void limparBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

// Funcao para realizar um ataque baseado na sorte
void realizarAtaque(Territorio* territorios) {
    int atacante, defensor;

    printf("\n--- Realizar Ataque ---\n");
    printf("Escolha o territorio atacante (1 a %d): ", NUM_TERRITORIOS);
    scanf("%d", &atacante);
    limparBuffer();

    printf("Escolha o territorio defensor (1 a %d): ", NUM_TERRITORIOS);
    scanf("%d", &defensor);
    limparBuffer();

    // Verifica se os territorios escolhidos sao validos
    if (atacante < 1 || atacante > NUM_TERRITORIOS || defensor < 1 || defensor > NUM_TERRITORIOS) {
        printf("Territorios invalidos! Tente novamente.\n");
        return;
    }

    // Ajusta os indices para o array (0-based)
    atacante--;
    defensor--;

    // Verifica se o atacante tem tropas suficientes
    if (territorios[atacante].tropas <= 1) {
        printf("O territorio atacante nao tem tropas suficientes para atacar!\n");
        return;
    }

    // Verifica se o defensor tem tropas suficientes
    if (territorios[defensor].tropas <= 0) {
        printf("O territorio defensor nao tem tropas suficientes para se defender!\n");
        return;
    }

    printf("\n--- Iniciando o ataque entre '%s' e '%s' ---\n", territorios[atacante].nome, territorios[defensor].nome);

    // Simula o ataque baseado na sorte
    int dadoAtacante = rand() % 6 + 1; // Numero aleatorio entre 1 e 6
    int dadoDefensor = rand() % 6 + 1; // Numero aleatorio entre 1 e 6

    printf("Atacante (%s) tirou: %d\n", territorios[atacante].nome, dadoAtacante);
    printf("Defensor (%s) tirou: %d\n", territorios[defensor].nome, dadoDefensor);

    if (dadoAtacante > dadoDefensor) {
        printf("O atacante venceu esta rodada! O defensor perdeu 1 tropa.\n");
        territorios[defensor].tropas--;
    } else {
        printf("O defensor venceu esta rodada! O atacante perdeu 1 tropa.\n");
        territorios[atacante].tropas--;
    }

    // Verifica se o defensor foi derrotado
    if (territorios[defensor].tropas <= 0) {
        printf("O territorio '%s' foi conquistado pelo atacante!\n", territorios[defensor].nome);
        strcpy(territorios[defensor].cor, territorios[atacante].cor); // Atualiza a cor do defensor
        territorios[defensor].tropas = 1; // Garante que o territorio conquistado tenha pelo menos 1 tropa
    }

    printf("\n--- Tropas Atualizadas ---\n");
    printf("Territorio '%s': %d tropas\n", territorios[atacante].nome, territorios[atacante].tropas);
    printf("Territorio '%s': %d tropas\n", territorios[defensor].nome, territorios[defensor].tropas);
}

// Funcao principal
// Permite ao usuário inserir dados para vários territórios e exibi-los
//
int main() {
    int i;
    char continuar;

    srand(time(NULL)); // Inicializa o gerador de números aleatórios

    printf("Digite o numero de territorios (maximo 20): ");
    scanf("%d", &NUM_TERRITORIOS);
    limparBuffer();

    if (NUM_TERRITORIOS < 1 || NUM_TERRITORIOS > 20) {
        printf("Numero de territorios invalido! Usando o valor padrao de 5.\n");
        NUM_TERRITORIOS = 5;
    }

    // Aloca memoria para os territorios
    Territorio* territorios = (Territorio*)malloc(NUM_TERRITORIOS * sizeof(Territorio));
    if (territorios == NULL) {
        fprintf(stderr, "Erro ao alocar memoria.\n");
        return 1;
    }

    // Preenche os dados dos territorios
    for (i = 0; i < NUM_TERRITORIOS; i++) {

        system(CLEAR); // Limpa a tela antes de cada entrada

        printf("Digite o nome do territorio %d: ", i + 1);
        fgets(territorios[i].nome, sizeof(territorios[i].nome), stdin);
        territorios[i].nome[strcspn(territorios[i].nome, "\n")] = 0;

        printf("Digite a cor do territorio (EX: Azul e Verde) %d: ", i + 1);
        fgets(territorios[i].cor, sizeof(territorios[i].cor), stdin);
        territorios[i].cor[strcspn(territorios[i].cor, "\n")] = 0;

        printf("Digite o numero de tropas no territorio %d: ", i + 1);
        scanf("%d", &territorios[i].tropas);
        limparBuffer();
    }

    do {
        system(CLEAR);

        printf("\n--------------------------------\n");
        printf("\n--- Detalhes dos Territorios ---\n");
        for (i = 0; i < NUM_TERRITORIOS; i++) {
            printf("Territorio %d:\n", i + 1);
            printf("Nome: %s\n", territorios[i].nome);
            printf("Cor: %s\n", territorios[i].cor);
            printf("Numero de Tropas: %d\n\n", territorios[i].tropas);
            printf("--------------------------------\n");
        }

        realizarAtaque(territorios);

        printf("\nDeseja realizar outro ataque? (s/n): ");
        scanf(" %c", &continuar);
        limparBuffer();
    } while (continuar == 's' || continuar == 'S');

    free(territorios);
    return 0;
}
