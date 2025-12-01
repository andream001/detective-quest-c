# 🕵️ Detective Quest - Jogo de Investigação em C

## 📝 Descrição

Jogo de detetive desenvolvido em linguagem C que implementa estruturas de dados avançadas para simular uma investigação criminal em uma mansão. O jogador assume o papel de um detetive que deve explorar cômodos, encontrar pistas e identificar o culpado.

Projeto acadêmico da disciplina de **Estruturas de Dados** da Estácio - **Tema 4: Algoritmos Avançados**.

## ✨ Estruturas de Dados Implementadas

### 1. 🏛️ Árvore Binária - Mapa da Mansão
- Representa a topologia dos cômodos da mansão
- Permite navegação hierárquica entre os ambientes
- **6 cômodos**: Sala de Estar, Biblioteca, Quarto Principal, Cozinha, Jardim, Escritório
- Visualização gráfica da estrutura em árvore

### 2. 🔍 BST (Binary Search Tree) - Sistema de Pistas
- Organiza pistas de forma ordenada por ID
- Busca eficiente em O(log n)
- **4 categorias**: Arma, Documento, Roupa, Substância
- Operações: inserção, busca e exibição em ordem

### 3. #️⃣ Tabela Hash - Suspeitos e Relações
- Vincula cada suspeito às pistas encontradas
- Função hash personalizada
- Tratamento de colisões por encadeamento
- **4 suspeitos**: Sr. Silva, Sra. Costa, Dr. Almeida, Mordomo

## 🎮 Funcionalidades

1. **Explorar Mapa** - Visualiza a árvore binária dos cômodos
2. **Ver Pistas** - Lista todas as pistas em ordem (percurso in-order da BST)
3. **Buscar Pista** - Busca pista específica por ID
4. **Ver Suspeitos** - Exibe tabela hash com suspeitos e suas pistas
5. **Adicionar Pista** - Inserção dinâmica de novas pistas
6. **Encerrar** - Finaliza a investigação

## 🚀 Como Compilar e Executar

### Pré-requisitos
```bash
# Compilador GCC instalado
gcc --version
```

### Compilação
```bash
gcc main.c -o detective
```

### Execução
**Linux/macOS:**
```bash
./detective
```

**Windows:**
```bash
detective.exe
```

## 💻 Estrutura do Código

```c
// Structs principais
typedef struct NoMapa { ... } NoMapa;        // Árvore Binária
typedef struct NoPista { ... } NoPista;      // BST
typedef struct Suspeito { ... } Suspeito;    // Hash Table
typedef struct TabelaHash { ... } TabelaHash;
typedef struct Jogo { ... } Jogo;            // Estrutura aninhada principal
```

### Operações Implementadas

**Árvore Binária:**
- `criarNoMapa()` - Cria novo nó
- `inserirMapa()` - Inserção de cômodo
- `exibirMapa()` - Exibição hierárquica

**BST:**
- `criarNoPista()` - Cria nova pista
- `inserirPista()` - Inserção ordenada
- `buscarPista()` - Busca por ID
- `exibirPistas()` - Percurso in-order

**Hash Table:**
- `funcaoHash()` - Função de hashing
- `inserirSuspeito()` - Adição com tratamento de colisão
- `exibirSuspeitos()` - Lista todos os suspeitos

## 📚 Conceitos Aplicados

- ✔️ **Variáveis** - Gerenciamento de estados e dados
- ✔️ **Structs** - 5 estruturas de dados personalizadas
- ✔️ **Operadores** - Comparações e manipulações
- ✔️ **Condicionais** - Validações de operações
- ✔️ **Estruturas Aninhadas** - `Jogo` contém `NoMapa*`, `NoPista*` e `TabelaHash*`
- ✔️ **Funções de Entrada/Saída** - Menu interativo com `printf()` e `scanf()`
- ✔️ **Alocação Dinâmica** - `malloc()` para nós das estruturas
- ✔️ **Recursão** - Percursos em árvores

## 📦 Estrutura do Projeto

```
detective-quest-c/
├── main.c          # Código fonte completo (261 linhas)
├── detective       # Executável compilado
├── README.md       # Documentação
└── LICENSE         # Licença MIT
```

## 👤 Autor

**andream001**  
Projeto Acadêmico Estácio 2025

## 📝 Licença

MIT License - Veja o arquivo LICENSE para detalhes

---

**Desenvolvido para a disciplina de Estruturas de Dados - Tema 4: Algoritmos Avançados**  
🎯 Implementação completa de Árvore Binária, BST e Hash Table em C
