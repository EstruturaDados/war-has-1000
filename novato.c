#include <stdio.h>
#include <string.h>

#define MAX_TERRITORIOS 5
#define TAM_NOME 50
#define TAM_COR 20

// Definição da struct Territorio
typedef struct {
    char nome[TAM_NOME];
    char corExercito[TAM_COR];
    int numTropas;
} Territorio;

int main() {
    Territorio territorios[MAX_TERRITORIOS];

    printf("=== Cadastro de Territórios (WAR) ===\n");

    // Leitura dos dados
    for (int i = 0; i < MAX_TERRITORIOS; i++) {
        printf("\nTerritório %d:\n", i + 1);

        printf("Nome do território: ");
        fgets(territorios[i].nome, TAM_NOME, stdin);
        // Remove o '\n' do final, se existir
        territorios[i].nome[strcspn(territorios[i].nome, "\n")] = '\0';

        printf("Cor do exército: ");
        fgets(territorios[i].corExercito, TAM_COR, stdin);
        territorios[i].corExercito[strcspn(territorios[i].corExercito, "\n")] = '\0';

        printf("Número de tropas: ");
        scanf("%d", &territorios[i].numTropas);
        getchar(); // Limpa o \n do buffer após o scanf
    }

    // Impressão dos dados
    printf("\n=== Estado Atual do Mapa ===\n");
    for (int i = 0; i < MAX_TERRITORIOS; i++) {
        printf("\nTerritório %d:\n", i + 1);
        printf("Nome: %s\n", territorios[i].nome);
        printf("Cor do Exército: %s\n", territorios[i].corExercito);
        printf("Número de Tropas: %d\n", territorios[i].numTropas);
    }

    return 0;
}
