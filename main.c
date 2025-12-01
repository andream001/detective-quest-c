#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>

#define TAM_HASH 10
#define MAX_NOME 50

// STRUCTS PRINCIPAIS

// 1. ÁRVORE BINÁRIA - Mapa da Mansão
typedef struct NoMapa {
    char comodo[MAX_NOME];
    struct NoMapa *esquerda;
    struct NoMapa *direita;
} NoMapa;

// 2. BST - Pistas
typedef struct NoPista {
    int id;
    char descricao[MAX_NOME];
    char categoria[MAX_NOME];
    struct NoPista *esquerda;
    struct NoPista *direita;
} NoPista;

// 3. HASH TABLE - Suspeitos
typedef struct Suspeito {
    char nome[MAX_NOME];
    char pista[MAX_NOME];
    struct Suspeito *proximo;
} Suspeito;

typedef struct {
    Suspeito *tabela[TAM_HASH];
} TabelaHash;

// ESTRUTURA ANINHADA PRINCIPAL
typedef struct {
    NoMapa *mapa;
    NoPista *pistas;
    TabelaHash *suspeitos;
    char localAtual[MAX_NOME];
} Jogo;

// PROTÓTIPOS
// Mapa
NoMapa* criarNoMapa(char *comodo);
NoMapa* inserirMapa(NoMapa *raiz, char *comodo);
void exibirMapa(NoMapa *raiz, int nivel);

// Pistas
NoPista* criarNoPista(int id, char *desc, char *cat);
NoPista* inserirPista(NoPista *raiz, int id, char *desc, char *cat);
void exibirPistas(NoPista *raiz);
NoPista* buscarPista(NoPista *raiz, int id);

// Hash
int funcaoHash(char *chave);
void iniciarHash(TabelaHash *t);
void inserirSuspeito(TabelaHash *t, char *nome, char *pista);
void exibirSuspeitos(TabelaHash *t);

// Jogo
void iniciarJogo(Jogo *j);
void menuPrincipal(Jogo *j);

int main() {
    setlocale(LC_ALL, "Portuguese");
    Jogo jogo;
    iniciarJogo(&jogo);
    menuPrincipal(&jogo);
    return 0;
}

// IMPLEMENTAÇÕES - ÁRVORE BINÁRIA (MAPA)
NoMapa* criarNoMapa(char *comodo) {
    NoMapa *novo = (NoMapa*)malloc(sizeof(NoMapa));
    strcpy(novo->comodo, comodo);
    novo->esquerda = novo->direita = NULL;
    return novo;
}

NoMapa* inserirMapa(NoMapa *raiz, char *comodo) {
    if (raiz == NULL) return criarNoMapa(comodo);
    if (strcmp(comodo, raiz->comodo) < 0)
        raiz->esquerda = inserirMapa(raiz->esquerda, comodo);
    else
        raiz->direita = inserirMapa(raiz->direita, comodo);
    return raiz;
}

void exibirMapa(NoMapa *raiz, int nivel) {
    if (raiz != NULL) {
        exibirMapa(raiz->direita, nivel + 1);
        for (int i = 0; i < nivel; i++) printf("   ");
        printf("-> %s\n", raiz->comodo);
        exibirMapa(raiz->esquerda, nivel + 1);
    }
}

// BST - PISTAS
NoPista* criarNoPista(int id, char *desc, char *cat) {
    NoPista *novo = (NoPista*)malloc(sizeof(NoPista));
    novo->id = id;
    strcpy(novo->descricao, desc);
    strcpy(novo->categoria, cat);
    novo->esquerda = novo->direita = NULL;
    return novo;
}

NoPista* inserirPista(NoPista *raiz, int id, char *desc, char *cat) {
    if (raiz == NULL) return criarNoPista(id, desc, cat);
    if (id < raiz->id)
        raiz->esquerda = inserirPista(raiz->esquerda, id, desc, cat);
    else if (id > raiz->id)
        raiz->direita = inserirPista(raiz->direita, id, desc, cat);
    return raiz;
}

void exibirPistas(NoPista *raiz) {
    if (raiz != NULL) {
        exibirPistas(raiz->esquerda);
        printf("  [%d] %s (%s)\n", raiz->id, raiz->descricao, raiz->categoria);
        exibirPistas(raiz->direita);
    }
}

NoPista* buscarPista(NoPista *raiz, int id) {
    if (raiz == NULL || raiz->id == id) return raiz;
    if (id < raiz->id) return buscarPista(raiz->esquerda, id);
    return buscarPista(raiz->direita, id);
}

// HASH TABLE - SUSPEITOS
int funcaoHash(char *chave) {
    int hash = 0;
    for (int i = 0; chave[i] != '\0'; i++)
        hash += chave[i];
    return hash % TAM_HASH;
}

void iniciarHash(TabelaHash *t) {
    for (int i = 0; i < TAM_HASH; i++)
        t->tabela[i] = NULL;
}

void inserirSuspeito(TabelaHash *t, char *nome, char *pista) {
    int indice = funcaoHash(nome);
    Suspeito *novo = (Suspeito*)malloc(sizeof(Suspeito));
    strcpy(novo->nome, nome);
    strcpy(novo->pista, pista);
    novo->proximo = t->tabela[indice];
    t->tabela[indice] = novo;
}

void exibirSuspeitos(TabelaHash *t) {
    printf("\n=== SUSPEITOS E PISTAS ===\n");
    for (int i = 0; i < TAM_HASH; i++) {
        Suspeito *atual = t->tabela[i];
        while (atual != NULL) {
            printf("  %s -> Pista: %s\n", atual->nome, atual->pista);
            atual = atual->proximo;
        }
    }
}

// FUNÇÕES DO JOGO
void iniciarJogo(Jogo *j) {
    j->mapa = NULL;
    j->pistas = NULL;
    j->suspeitos = (TabelaHash*)malloc(sizeof(TabelaHash));
    iniciarHash(j->suspeitos);
    strcpy(j->localAtual, "Entrada");
    
    // Pré-carregar mapa
    j->mapa = inserirMapa(j->mapa, "Sala de Estar");
    j->mapa = inserirMapa(j->mapa, "Biblioteca");
    j->mapa = inserirMapa(j->mapa, "Quarto Principal");
    j->mapa = inserirMapa(j->mapa, "Cozinha");
    j->mapa = inserirMapa(j->mapa, "Jardim");
    j->mapa = inserirMapa(j->mapa, "Escritório");
    
    // Pré-carregar pistas
    j->pistas = inserirPista(j->pistas, 1, "Faca ensanguentada", "Arma");
    j->pistas = inserirPista(j->pistas, 2, "Carta ameaçadora", "Documento");
    j->pistas = inserirPista(j->pistas, 3, "Luvas sujas", "Roupa");
    j->pistas = inserirPista(j->pistas, 4, "Veneno", "Substância");
    
    // Pré-carregar suspeitos
    inserirSuspeito(j->suspeitos, "Sr. Silva", "Faca ensanguentada");
    inserirSuspeito(j->suspeitos, "Sra. Costa", "Carta ameaçadora");
    inserirSuspeito(j->suspeitos, "Dr. Almeida", "Veneno");
    inserirSuspeito(j->suspeitos, "Mordomo", "Luvas sujas");
}

void menuPrincipal(Jogo *j) {
    int opcao, idPista;
    
    printf("\n\n╔═════════════════════════════╗\n");
    printf("║   DETECTIVE QUEST    ║\n");
    printf("╚═════════════════════════════╝\n\n");
    
    do {
        printf("\n┌───────────────────┐\n");
        printf("│ Local: %s \n", j->localAtual);
        printf("└───────────────────┘\n");
        printf("\n1. Explorar Mapa da Mansão\n");
        printf("2. Ver Pistas Encontradas\n");
        printf("3. Buscar Pista Específica\n");
        printf("4. Ver Suspeitos e Relações\n");
        printf("5. Adicionar Nova Pista\n");
        printf("0. Encerrar Investigação\n");
        printf("\nEscolha: ");
        scanf("%d", &opcao);
        
        switch(opcao) {
            case 1:
                printf("\n=== MAPA DA MANSÃO ===\n");
                exibirMapa(j->mapa, 0);
                break;
            case 2:
                printf("\n=== PISTAS ENCONTRADAS ===\n");
                exibirPistas(j->pistas);
                break;
            case 3:
                printf("Digite o ID da pista: ");
                scanf("%d", &idPista);
                NoPista *resultado = buscarPista(j->pistas, idPista);
                if (resultado != NULL)
                    printf("\nPista: %s (%s)\n", resultado->descricao, resultado->categoria);
                else
                    printf("\nPista não encontrada!\n");
                break;
            case 4:
                exibirSuspeitos(j->suspeitos);
                break;
            case 5: {
                int novoId;
                char desc[MAX_NOME], cat[MAX_NOME];
                printf("ID da nova pista: ");
                scanf("%d", &novoId);
                getchar();
                printf("Descrição: ");
                fgets(desc, MAX_NOME, stdin);
                desc[strcspn(desc, "\n")] = 0;
                printf("Categoria: ");
                fgets(cat, MAX_NOME, stdin);
                cat[strcspn(cat, "\n")] = 0;
                j->pistas = inserirPista(j->pistas, novoId, desc, cat);
                printf("\nPista adicionada com sucesso!\n");
                break;
            }
            case 0:
                printf("\nInvestigação encerrada. Até a próxima, detetive!\n");
                break;
            default:
                printf("\nOpção inválida!\n");
        }
    } while (opcao != 0);
}