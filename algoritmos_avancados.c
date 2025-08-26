
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// --- Definições e Estruturas ---

/**
 * @struct Sala
 * @brief Representa um cômodo da mansão (um nó da árvore).
 *
 * Cada sala tem um nome e ponteiros para os cômodos à esquerda e à direita.
 */
typedef struct Sala {
    char *nome;
    struct Sala *esquerda;
    struct Sala *direita;
} Sala;

// --- Protótipos das Funções ---

Sala* criarSala(const char* nome);
void explorarSalas(Sala* salaInicial);
void liberarMapa(Sala* sala);

/**
 * @brief Função principal que monta o mapa da mansão e inicia a exploração.
 *
 * A estrutura da mansão (árvore) é definida aqui.
 */
int main() {
    // Criação do mapa da mansão (árvore binária)
    Sala* hall = criarSala("Hall de Entrada");
    hall->esquerda = criarSala("Sala de Jantar");
    hall->direita = criarSala("Biblioteca");

    hall->esquerda->esquerda = criarSala("Cozinha");
    hall->esquerda->direita = criarSala("Jardim de Inverno");

    hall->direita->esquerda = criarSala("Escritorio");
    hall->direita->direita = criarSala("Sala de Musica");

    // Adicionando alguns nós folha (becos sem saída)
    hall->esquerda->esquerda->esquerda = criarSala("Despensa");
    hall->direita->esquerda->direita = criarSala("Passagem Secreta");

    printf("Bem-vindo ao Detective Quest!\n");
    printf("Voce esta no Hall de Entrada. Explore a mansao para encontrar pistas.\n");

    // Inicia a exploração a partir do Hall de Entrada
    explorarSalas(hall);

    // Libera a memória alocada para o mapa ao final do jogo
    liberarMapa(hall);

    return 0;
}

/**
 * @brief Cria, de forma dinâmica, uma sala com nome.
 *
 * Aloca memória para uma nova sala (nó) e seu nome.
 * @param nome O nome da sala a ser criada.
 * @return Um ponteiro para a nova sala criada.
 */
Sala* criarSala(const char* nome) {
    Sala* novaSala = (Sala*)malloc(sizeof(Sala));
    if (novaSala == NULL) {
        perror("Erro ao alocar memoria para a sala");
        exit(EXIT_FAILURE);
    }

    novaSala->nome = (char*)malloc(strlen(nome) + 1);
    if (novaSala->nome == NULL) {
        perror("Erro ao alocar memoria para o nome da sala");
        free(novaSala);
        exit(EXIT_FAILURE);
    }
    strcpy(novaSala->nome, nome);

    novaSala->esquerda = NULL;
    novaSala->direita = NULL;

    return novaSala;
}

/**
 * @brief Permite a navegação do jogador pela árvore.
 *
 * Controla o loop de exploração, exibindo a sala atual e processando
 * a entrada do jogador para se mover.
 * @param salaInicial A sala de onde a exploração começa (a raiz).
 */
void explorarSalas(Sala* salaInicial) {
    Sala* salaAtual = salaInicial;
    char escolha;

    while (1) {
        printf("\n----------------------------------------\n");
        printf("Voce esta em: %s\n", salaAtual->nome);

        if (salaAtual->esquerda == NULL && salaAtual->direita == NULL) {
            printf("Este e um beco sem saida. Fim da exploracao neste caminho.\n");
            break;
        }

        printf("Para onde voce quer ir?\n");
        if (salaAtual->esquerda != NULL) printf(" (e) Esquerda -> %s\n", salaAtual->esquerda->nome);
        if (salaAtual->direita != NULL) printf(" (d) Direita  -> %s\n", salaAtual->direita->nome);
        printf(" (s) Sair do jogo\n");
        printf("Escolha: ");

        scanf(" %c", &escolha);
        while (getchar() != '\n'); // Limpa o buffer de entrada

        if (escolha == 'e' && salaAtual->esquerda) salaAtual = salaAtual->esquerda;
        else if (escolha == 'd' && salaAtual->direita) salaAtual = salaAtual->direita;
        else if (escolha == 's') {
            printf("\nVoce decidiu parar a exploracao. Ate a proxima, detetive!\n");
            break;
        } else {
            printf("\n>> Caminho ou opcao invalida. Tente novamente.\n");
        }
    }
}

/**
 * @brief Libera toda a memória alocada para o mapa (árvore) usando recursão.
 */
void liberarMapa(Sala* sala) {
    if (sala == NULL) return;
    liberarMapa(sala->esquerda);
    liberarMapa(sala->direita);
    free(sala->nome);
    free(sala);
}