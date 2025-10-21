#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Estrutura de dados para representar um território
typedef struct {
    char nome[30];
    char cor[10];
    int tropas;
} Territorio;

// Função para cadastrar os territórios
void cadastrarTerritorios(Territorio* mapa, int total) {
    for (int i = 0; i < total; i++) {
        printf("\nCadastro do território %d:\n", i + 1);
        printf("Nome: ");
        scanf(" %[^\n]", mapa[i].nome);
        printf("Cor do exército: ");
        scanf(" %[^\n]", mapa[i].cor);
        printf("Número de tropas: ");
        scanf("%d", &mapa[i].tropas);
    }
}

// Função para exibir os territórios
void exibirTerritorios(Territorio* mapa, int total) {
    printf("\n--- Territórios ---\n");
    for (int i = 0; i < total; i++) {
        printf("%d - %s | Cor: %s | Tropas: %d\n", i, mapa[i].nome, mapa[i].cor, mapa[i].tropas);
    }
}

// Função que simula um ataque entre dois territórios
void atacar(Territorio* atacante, Territorio* defensor) {
    if (strcmp(atacante->cor, defensor->cor) == 0) {
        printf("\nErro: não é possível atacar um território da mesma cor!\n");
        return;
    }

    if (atacante->tropas <= 0) {
        printf("\nErro: o território atacante não possui tropas suficientes!\n");
        return;
    }

    int dadoAtacante = rand() % 6 + 1;
    int dadoDefensor = rand() % 6 + 1;

    printf("\nAtaque de %s contra %s\n", atacante->nome, defensor->nome);
    printf("Dado atacante: %d | Dado defensor: %d\n", dadoAtacante, dadoDefensor);

    if (dadoAtacante >= dadoDefensor) {
        printf("Atacante vence a rodada!\n");
        defensor->tropas--;
        if (defensor->tropas <= 0) {
            printf("Território conquistado!\n");
            strcpy(defensor->cor, atacante->cor);
            defensor->tropas = 1;
        }
    } else {
        printf("Defensor resiste ao ataque.\n");
        atacante->tropas--;
    }
}

// Função para liberar a memória alocada
void liberarMemoria(Territorio* mapa) {
    free(mapa);
}

int main() {
    srand(time(NULL)); // Inicializa aleatoriedade

    int total = 5;
    Territorio* mapa = (Territorio*)calloc(total, sizeof(Territorio));
    if (mapa == NULL) {
        printf("Erro ao alocar memória.\n");
        return 1;
    }

    cadastrarTerritorios(mapa, total);

    char continuar = 's';
    while (continuar == 's') {
        exibirTerritorios(mapa, total);

        int iAtacante, iDefensor;
        printf("\nEscolha o índice do território atacante (0 a 4): ");
        scanf("%d", &iAtacante);
        printf("Escolha o índice do território defensor (0 a 4): ");
        scanf("%d", &iDefensor);

        if (iAtacante >= 0 && iAtacante < total && iDefensor >= 0 && iDefensor < total) {
            atacar(&mapa[iAtacante], &mapa[iDefensor]);
        } else {
            printf("Índices inválidos.\n");
        }

        printf("\nDeseja realizar outro ataque? (s/n): ");
        scanf(" %c", &continuar);
    }

    liberarMemoria(mapa);
    printf("\nMemória liberada. Fim do jogo!\n");
    return 0;
}
