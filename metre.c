#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Estrutura de território
typedef struct {
    char nome[30];
    char cor[10];
    int tropas;
} Territorio;

// Prototipação das funções
void inicializarMapa(Territorio* mapa, const int tamanho);
void exibirMapa(const Territorio* mapa, const int tamanho);
void atacar(Territorio* mapa, const int tamanho);
void atribuirMissao(char* destino, const char* missoes[], const int totalMissoes);
int verificarMissao(const char* missao, const Territorio* mapa, const int tamanho);
void exibirMissao(const char* missao);
void liberarMemoria(char* missao);

// Função principal
int main() {
    srand((unsigned)time(NULL));

    const int tamanhoMapa = 6;
    Territorio* mapa = (Territorio*)malloc(tamanhoMapa * sizeof(Territorio));
    inicializarMapa(mapa, tamanhoMapa);

    const char* missoes[] = {
        "Destruir o exército Verde",
        "Conquistar 3 territórios"
    };
    const int totalMissoes = 2;

    char* missaoJogador = (char*)malloc(100 * sizeof(char));
    atribuirMissao(missaoJogador, missoes, totalMissoes);
    exibirMissao(missaoJogador);

    int opcao;
    do {
        printf("\nMenu:\n1 - Atacar\n2 - Verificar Missão\n0 - Sair\nEscolha: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                atacar(mapa, tamanhoMapa);
                exibirMapa(mapa, tamanhoMapa);
                if (verificarMissao(missaoJogador, mapa, tamanhoMapa)) {
                    printf("\nMissão cumprida! Você venceu!\n");
                    opcao = 0;
                }
                break;
            case 2:
                if (verificarMissao(missaoJogador, mapa, tamanhoMapa)) {
                    printf("\nMissão cumprida!\n");
                } else {
                    printf("\nMissão ainda não cumprida.\n");
                }
                break;
            case 0:
                printf("\nSaindo do jogo...\n");
                break;
            default:
                printf("Opção inválida.\n");
        }
    } while (opcao != 0);

    liberarMemoria(missaoJogador);
    free(mapa);
    return 0;
}

// Inicializa o mapa com territórios fixos
void inicializarMapa(Territorio* mapa, const int tamanho) {
    const char* nomes[] = {"A", "B", "C", "D", "E", "F"};
    const char* cores[] = {"azul", "verde", "vermelha", "verde", "azul", "vermelha"};
    const int tropas[] = {5, 3, 4, 2, 6, 1};

    for (int i = 0; i < tamanho; i++) {
        strcpy(mapa[i].nome, nomes[i]);
        strcpy(mapa[i].cor, cores[i]);
        mapa[i].tropas = tropas[i];
    }
}

// Exibe o estado atual do mapa
void exibirMapa(const Territorio* mapa, const int tamanho) {
    printf("\nMapa Atual:\n");
    for (int i = 0; i < tamanho; i++) {
        printf("Território %s | Cor: %s | Tropas: %d\n", mapa[i].nome, mapa[i].cor, mapa[i].tropas);
    }
}

// Realiza um ataque entre dois territórios
void atacar(Territorio* mapa, const int tamanho) {
    int origem, destino;
    printf("Escolha o território atacante (0 a %d): ", tamanho - 1);
    scanf("%d", &origem);
    printf("Escolha o território defensor (0 a %d): ", tamanho - 1);
    scanf("%d", &destino);

    if (origem < 0 || origem >= tamanho || destino < 0 || destino >= tamanho) {
        printf("Índice inválido.\n");
        return;
    }

    if (strcmp(mapa[origem].cor, mapa[destino].cor) == 0) {
        printf("Não é possível atacar território da mesma cor.\n");
        return;
    }

    int dadoAtacante = rand() % 6 + 1;
    int dadoDefensor = rand() % 6 + 1;

    printf("Dados: Atacante %d vs Defensor %d\n", dadoAtacante, dadoDefensor);

    if (dadoAtacante > dadoDefensor) {
        strcpy(mapa[destino].cor, mapa[origem].cor);
        mapa[destino].tropas = mapa[origem].tropas / 2;
        printf("Território conquistado!\n");
    } else {
        mapa[origem].tropas--;
        printf("Ataque falhou. Tropas do atacante reduzidas.\n");
    }
}

// Atribui missão aleatória ao jogador
void atribuirMissao(char* destino, const char* missoes[], const int totalMissoes) {
    int indice = rand() % totalMissoes;
    strcpy(destino, missoes[indice]);
}

// Exibe a missão do jogador
void exibirMissao(const char* missao) {
    printf("\nSua missão: %s\n", missao);
}

// Verifica se a missão foi cumprida
int verificarMissao(const char* missao, const Territorio* mapa, const int tamanho) {
    if (strstr(missao, "Destruir o exército Verde")) {
        for (int i = 0; i < tamanho; i++) {
            if (strcmp(mapa[i].cor, "verde") == 0 && mapa[i].tropas > 0) {
                return 0;
            }
        }
        return 1;
    } else if (strstr(missao, "Conquistar 3 territórios")) {
        int contador = 0;
        for (int i = 0; i < tamanho; i++) {
            if (strcmp(mapa[i].cor, "azul") == 0) {
                contador++;
            }
        }
        return contador >= 3;
    }
    return 0;
}

// Libera memória alocada
void liberarMemoria(char* missao) {
    free(missao);
}
