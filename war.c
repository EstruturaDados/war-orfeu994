// WAR.c
// Programa para gerenciar informações de territórios em um jogo de WAR
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h> // Para gerar numeros aleatorios

#ifdef _WIN32
#define CLEAR "cls"
#else
#define CLEAR "clear"
#endif

#define NUM_TERRITORIOS 5

// Estrutura para armazenar informações de um território
typedef struct {
    char nome[30];
    char cor[10];
    int tropas;
} Territorio;

// Funcoes
void limparBuffer();
void realizarAtaque(Territorio* territorios);
void listarMissoes(char* missoes[], int totalMissoes);
void atribuirMissao(char* destino, char* missoes[], int totalMissoes);
int verificarMissao(char* missao, Territorio* mapa, int tamanho);

int main() {
    int i;
    int opcao;
    char continuar = 's';

    srand(time(NULL)); // Inicializa o gerador de numeros aleatorios

    // Inicializa os territorios com os dados especificados
    Territorio territorios[NUM_TERRITORIOS] = {
        {"Africa", "Verde", 5},
        {"Europa", "Azul", 5},
        {"America", "Vermelho", 5},
        {"Oceania", "Branco", 5},
        {"Asia", "Amarelo", 5}
    };

    // Inicializa as missoes
    char* missoes[] = {
        "Perder o territorio Africa",
        "Perder o territorio Europa",
        "Perder o territorio America",
        "Perder o territorio Oceania",
        "Perder o territorio Asia"
    };
    int totalMissoes = sizeof(missoes) / sizeof(missoes[0]);

    // Missao do jogador (armazenada dinamicamente)
    char* missaoJogador = (char*)malloc(50 * sizeof(char));
    if (missaoJogador == NULL) {
        printf("Erro ao alocar memoria para a missao do jogador.\n");
        return 1;
    }

    // Atribui uma missao ao jogador
    atribuirMissao(missaoJogador, missoes, totalMissoes);

    do {
        system(CLEAR);

        printf("\n--------------------------------\n");
        printf("\n--- Detalhes dos Territorios ---\n");
        for (i = 0; i < NUM_TERRITORIOS; i++) {
            printf("\nTerritorio %d:\n", i + 1);
            printf("Nome: %s\n", territorios[i].nome);
            printf("Cor: %s\n", territorios[i].cor);
            printf("Numero de Tropas: %d\n", territorios[i].tropas);
            printf("--------------------------------");
        }

        printf("\n\nSua missao: %s\n", missaoJogador);

        printf("\nEscolha uma opcao:\n");
        printf("1 - Listar Missoes\n");
        printf("2 - Realizar Ataque\n");
        printf("3 - Sair\n");
        printf("Opcao: ");
        scanf("%d", &opcao);
        limparBuffer();

        switch (opcao) {
        case 1:
            listarMissoes(missoes, totalMissoes);
            break;
        case 2:
            realizarAtaque(territorios);
            break;
        case 3:
            printf("Saindo do jogo...\n");
            continuar = 'n';
            break;
        default:
            printf("Opcao invalida! Tente novamente.\n");
            break;
        }

        // Verifica se a missao foi cumprida
        if (verificarMissao(missaoJogador, territorios, NUM_TERRITORIOS)) {
            printf("\nParabens! Voce cumpriu sua missao: %s\n", missaoJogador);
            printf("Voce venceu esta missao!\n");

            
            printf("\nPressione Enter para continuar...");
            limparBuffer();

            // Atribui uma nova missao ao jogador
            printf("\nAtribuindo uma nova missao...\n");
            atribuirMissao(missaoJogador, missoes, totalMissoes);
        }

    } while (continuar == 's' || continuar == 'S');

    free(missaoJogador); // Libera a memoria alocada para a missao do jogador
    return 0;
}

// Funcao para limpar o buffer de entrada
void limparBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

// Funcao para listar as missoes
void listarMissoes(char* missoes[], int totalMissoes) {
    printf("\n--- Missoes Disponiveis ---\n");
    for (int i = 0; i < totalMissoes; i++) {
        printf("Missao %d: %s\n", i + 1, missoes[i]);
    }
    printf("\nPressione Enter para continuar...");
    limparBuffer();
}

// Funcao para atribuir uma missao ao jogador
void atribuirMissao(char* destino, char* missoes[], int totalMissoes) {
    int indice = rand() % totalMissoes; // Sorteia uma missao
    strcpy(destino, missoes[indice]);  // Copia a missao para o destino
    printf("\nMissao atribuida: %s\n", destino);
}

// Funcao para verificar se a missao foi cumprida
int verificarMissao(char* missao, Territorio* mapa, int tamanho) {
    for (int i = 0; i < tamanho; i++) {
        char missaoEsperada[50];
        sprintf(missaoEsperada, "Perder o territorio %s", mapa[i].nome);
        
        // Se a missão era perder e o território não está mais com a cor original
        if (strcmp(missao, missaoEsperada) == 0 && mapa[i].tropas > 0) {
            // Verifica se a cor NÃO é mais a original (ex.: Verde para África)
            if ((strcmp(mapa[i].nome, "Africa") == 0 && strcmp(mapa[i].cor, "Verde") != 0) ||
                (strcmp(mapa[i].nome, "Europa") == 0 && strcmp(mapa[i].cor, "Azul") != 0) ||
                (strcmp(mapa[i].nome, "America") == 0 && strcmp(mapa[i].cor, "Vermelho") != 0) ||
                (strcmp(mapa[i].nome, "Oceania") == 0 && strcmp(mapa[i].cor, "Branco") != 0) ||
                (strcmp(mapa[i].nome, "Asia") == 0 && strcmp(mapa[i].cor, "Amarelo") != 0)) {
                    return 1; // missão concluída
            }
        }
    }
    return 0;
}


// Funcao para realizar um ataque baseado na escolha do usuario
void realizarAtaque(Territorio* territorios) {
    int atacante, defensor;
    int dadoAtacante, dadoDefensor;

    printf("\n--- Realizar Ataque ---\n");

    // Pergunta ao usuario qual territorio sera o atacante
    printf("Escolha o territorio atacante (1 a %d): ", NUM_TERRITORIOS);
    scanf("%d", &atacante);
    limparBuffer();

    // Verifica se o atacante e valido
    if (atacante < 1 || atacante > NUM_TERRITORIOS) {
        printf("Territorio atacante invalido! Tente novamente.\n");
        return;
    }

    // Pergunta ao usuario qual territorio sera o defensor
    printf("Escolha o territorio defensor (1 a %d): ", NUM_TERRITORIOS);
    scanf("%d", &defensor);
    limparBuffer();

    // Verifica se o defensor e valido
    if (defensor < 1 || defensor > NUM_TERRITORIOS || defensor == atacante) {
        printf("Territorio defensor invalido! Tente novamente.\n");
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

    printf("\nTerritorio Atacante: %s (Tropas: %d)\n", territorios[atacante].nome, territorios[atacante].tropas);
    printf("Territorio Defensor: %s (Tropas: %d)\n", territorios[defensor].nome, territorios[defensor].tropas);

    // Gera os dados aleatorios para o ataque
    dadoAtacante = (rand() % 6) + 1; // Dado de 1 a 6
    dadoDefensor = (rand() % 6) + 1; // Dado de 1 a 6

    printf("\n--- Numeros Sorteados ---\n");
    printf("Atacante (%s): %d\n", territorios[atacante].nome, dadoAtacante);
    printf("Defensor (%s): %d\n", territorios[defensor].nome, dadoDefensor);

    // Compara os dados e atualiza as tropas
    if (dadoAtacante > dadoDefensor) {
        territorios[defensor].tropas--;
        printf("\nResultado: O atacante venceu! O defensor perdeu uma tropa.\n");
    } else if (dadoAtacante < dadoDefensor) {
        territorios[atacante].tropas--;
        printf("\nResultado: O defensor venceu! O atacante perdeu uma tropa.\n");
    } else {
        printf("\nResultado: Empate! Ninguem perdeu tropas.\n");
    }

    // Verifica se o defensor perdeu todas as tropas
    if (territorios[defensor].tropas <= 0) {
        printf("\nO territorio %s foi conquistado pelo atacante!\n", territorios[defensor].nome);
        territorios[defensor].tropas = 1; // O atacante deixa uma tropa no territorio conquistado
        territorios[atacante].tropas--; // O atacante perde uma tropa ao conquistar
        strcpy(territorios[defensor].cor, territorios[atacante].cor); // Atualiza a cor do defensor
    }

    printf("\n--- Atualizacao ---\n");
    printf("Territorio Atacante: %s (Tropas: %d)\n", territorios[atacante].nome, territorios[atacante].tropas);
    printf("Territorio Defensor: %s (Tropas: %d)\n", territorios[defensor].nome, territorios[defensor].tropas);

    // Pausa para o jogador ver os resultados
    printf("\nPressione Enter para continuar...");
    limparBuffer();
}