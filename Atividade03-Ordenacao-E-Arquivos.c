#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define ARQ_ENTRADA "dados.txt"
#define ARQ_SAIDA "ordenado.txt"
#define MAX_VAL 1000

/* ========== PROTÓTIPOS ========== */
// Arquivos (Plano 8)
int* carregarDados(const char *arquivo, int *qtd);
void salvarDados(const char *arquivo, int *v, int n);
int criarArquivoDados();
void exibirArquivo(const char *arquivo);
int alterarValorArquivo();

// Ordenação com ponteiros (Plano 9 e 11)
void bubbleSort(int *v, int n);
void insertionSort(int *v, int n);
void selectionSort(int *v, int n);
void mergeSort(int *v, int esq, int dir);
void merge(int *v, int esq, int meio, int dir);
void quickSort(int *v, int esq, int dir);
int particiona(int *v, int esq, int dir);
void trocar(int *a, int *b); // usa ponteiros - Plano 9

// Utilitários
void imprimirVetor(int *v, int n);
void copiarVetor(int *dest, int *orig, int n);

/* ========== MAIN COM SWITCH (Plano 12) ========== */
int main() {
    int opcao;
    int *dados = NULL;
    int qtd = 0;
    int *ordenado = NULL;
    int algoritmo = 0;
    srand(time(NULL));

    do {
        printf("\n========== ATIVIDADE 03 - ORDENACAO E ARQUIVOS ==========\n");
        printf("1 - Criar e gravar arquivo com dados desordenados (dados.txt)\n");
        printf("2 - Ler e exibir dados do arquivo dados.txt\n");
        printf("3 - Escolher algoritmo e ordenar -> salvar em ordenado.txt\n");
        printf("4 - Exibir arquivo ordenado.txt\n");
        printf("5 - Alterar um valor no arquivo e reordenar novamente\n");
        printf("0 - Sair\n");
        printf("Escolha: ");
        if(scanf("%d", &opcao) != 1) { // limpa buffer em caso de erro
            int c; while((c=getchar())!='\n' && c!=EOF);
            opcao = -1;
        }

        switch (opcao) {
            case 1:
                criarArquivoDados();
                break;

            case 2:
                exibirArquivo(ARQ_ENTRADA);
                break;

            case 3: {
                // 2) Ler dados do arquivo usando ponteiros
                if(dados != NULL) { free(dados); dados = NULL; }
                dados = carregarDados(ARQ_ENTRADA, &qtd);
                if(dados == NULL) {
                    printf("Erro: arquivo %s nao encontrado. Crie primeiro (opcao 1).\n", ARQ_ENTRADA);
                    break;
                }
                printf("\nDados carregados (%d valores): ", qtd);
                imprimirVetor(dados, qtd);

                // Aloca vetor ordenado
                if(ordenado != NULL) free(ordenado);
                ordenado = (int*) malloc(qtd * sizeof(int));
                if(ordenado == NULL) { printf("Erro de alocacao!\n"); free(dados); return 1; }
                copiarVetor(ordenado, dados, qtd);

                // 3) Escolher tipo de ordenação com SWITCH (Plano 12)
                printf("\n--- Escolha o algoritmo de ordenacao ---\n");
                printf("1 - Bubble Sort\n");
                printf("2 - Insertion Sort\n");
                printf("3 - Selection Sort\n");
                printf("4 - Merge Sort\n");
                printf("5 - Quick Sort\n");
                printf("Opcao: ");
                scanf("%d", &algoritmo);

                switch (algoritmo) {
                    case 1:
                        printf("\nOrdenando com Bubble Sort...\n");
                        bubbleSort(ordenado, qtd);
                        break;
                    case 2:
                        printf("\nOrdenando com Insertion Sort...\n");
                        insertionSort(ordenado, qtd);
                        break;
                    case 3:
                        printf("\nOrdenando com Selection Sort...\n");
                        selectionSort(ordenado, qtd);
                        break;
                    case 4:
                        printf("\nOrdenando com Merge Sort...\n");
                        mergeSort(ordenado, 0, qtd - 1);
                        break;
                    case 5:
                        printf("\nOrdenando com Quick Sort...\n");
                        quickSort(ordenado, 0, qtd - 1);
                        break;
                    default:
                        printf("Opcao invalida! Usando Bubble Sort como padrao.\n");
                        bubbleSort(ordenado, qtd);
                        break;
                }

                // 4) Salvar em novo arquivo
                salvarDados(ARQ_SAIDA, ordenado, qtd);
                printf("Vetor ordenado: ");
                imprimirVetor(ordenado, qtd);
                printf("Resultado salvo em %s\n", ARQ_SAIDA);

                free(dados); dados = NULL; // libera após uso, pode recarregar depois
                break;
            }

            case 4:
                exibirArquivo(ARQ_SAIDA);
                break;

            case 5: {
                if(alterarValorArquivo() == 0) {
                    printf("\nDeseja reordenar automaticamente agora? (1=Sim / 0=Nao): ");
                    int r; scanf("%d", &r);
                    if(r == 1) {
                        // recarrega e reordena com último algoritmo ou Bubble
                        if(dados != NULL) free(dados);
                        dados = carregarDados(ARQ_ENTRADA, &qtd);
                        if(ordenado != NULL) free(ordenado);
                        ordenado = (int*) malloc(qtd * sizeof(int));
                        copiarVetor(ordenado, dados, qtd);
                        
                        if(algoritmo == 0) algoritmo = 1;
                        printf("Reordenando com algoritmo %d...\n", algoritmo);
                        switch(algoritmo) {
                            case 1: bubbleSort(ordenado, qtd); break;
                            case 2: insertionSort(ordenado, qtd); break;
                            case 3: selectionSort(ordenado, qtd); break;
                            case 4: mergeSort(ordenado, 0, qtd-1); break;
                            case 5: quickSort(ordenado, 0, qtd-1); break;
                            default: bubbleSort(ordenado, qtd); break;
                        }
                        salvarDados(ARQ_SAIDA, ordenado, qtd);
                        printf("Reordenado e salvo em %s: ", ARQ_SAIDA);
                        imprimirVetor(ordenado, qtd);
                        free(dados); dados = NULL;
                    }
                }
                break;
            }

            case 0:
                printf("Saindo...\n");
                break;

            default:
                printf("Opcao invalida!\n");
                break;
        }
    } while (opcao != 0);

    if(dados) free(dados);
    if(ordenado) free(ordenado);
    return 0;
}

/* ========== FUNÇÕES DE ARQUIVO (Plano 8) ========== */

// Cria dados.txt - Requisito 1
int criarArquivoDados() {
    FILE *fp = fopen(ARQ_ENTRADA, "w");
    if(fp == NULL) {
        printf("Erro ao criar %s\n", ARQ_ENTRADA);
        return 1;
    }

    int n, modo;
    printf("\nQuantos numeros deseja gravar em %s? ", ARQ_ENTRADA);
    scanf("%d", &n);
    if(n <= 0 || n > MAX_VAL) {
        printf("Quantidade invalida! Usando 10.\n");
        n = 10;
    }

    printf("Como deseja preencher?\n1 - Digitar manualmente\n2 - Gerar aleatoriamente\nOpcao: ");
    scanf("%d", &modo);

    for(int i = 0; i < n; i++) {
        int valor;
        if(modo == 2) {
            valor = rand() % 100; // 0 a 99
        } else {
            printf("Valor %d: ", i+1);
            scanf("%d", &valor);
        }
        fprintf(fp, "%d\n", valor); // grava um por linha
    }

    fclose(fp);
    printf("Arquivo %s criado com %d valores!\n", ARQ_ENTRADA, n);
    return 0;
}

// Carrega dados usando ponteiros e alocação dinâmica (Plano 9)
int* carregarDados(const char *arquivo, int *qtd) {
    FILE *fp = fopen(arquivo, "r");
    if(fp == NULL) return NULL;

    // Conta quantos números existem
    int count = 0, temp;
    while(fscanf(fp, "%d", &temp) == 1) count++;
    if(count == 0) { fclose(fp); return NULL; }

    rewind(fp);

    // Alocação dinâmica com ponteiro (Plano 9)
    int *vetor = (int*) malloc(count * sizeof(int));
    if(vetor == NULL) { fclose(fp); return NULL; }

    int i = 0;
    // Leitura usando aritmética de ponteiros
    while(i < count && fscanf(fp, "%d", (vetor + i)) == 1) {
        i++;
    }

    fclose(fp);
    *qtd = count;
    return vetor;
}

void salvarDados(const char *arquivo, int *v, int n) {
    FILE *fp = fopen(arquivo, "w");
    if(fp == NULL) {
        printf("Erro ao abrir %s para escrita!\n", arquivo);
        return;
    }
    for(int i = 0; i < n; i++) {
        // uso de ponteiro: *(v+i)
        fprintf(fp, "%d\n", *(v + i));
    }
    fclose(fp);
}

void exibirArquivo(const char *arquivo) {
    FILE *fp = fopen(arquivo, "r");
    if(fp == NULL) {
        printf("Arquivo %s nao encontrado!\n", arquivo);
        return;
    }
    printf("\n--- Conteudo de %s ---\n", arquivo);
    char linha[100];
    while(fgets(linha, sizeof(linha), fp) != NULL) {
        printf("%s", linha);
    }
    printf("--- Fim ---\n");
    fclose(fp);
}

// Requisito 5: Alterar valor dentro do arquivo e reordenar
int alterarValorArquivo() {
    int qtd = 0;
    int *v = carregarDados(ARQ_ENTRADA, &qtd);
    if(v == NULL) {
        printf("Arquivo %s nao existe!\n", ARQ_ENTRADA);
        return 1;
    }

    printf("\nVetor atual (%d elementos):\n", qtd);
    for(int i = 0; i < qtd; i++) {
        printf("[%d]=%d ", i, *(v+i));
    }
    printf("\n");

    int pos, novo;
    printf("Digite a posicao que deseja alterar (0 a %d): ", qtd-1);
    scanf("%d", &pos);
    if(pos < 0 || pos >= qtd) {
        printf("Posicao invalida!\n");
        free(v);
        return 1;
    }
    printf("Digite o novo valor para a posicao %d: ", pos);
    scanf("%d", &novo);

    // Alteração via ponteiro
    *(v + pos) = novo;

    salvarDados(ARQ_ENTRADA, v, qtd);
    printf("Valor alterado! %s atualizado.\n", ARQ_ENTRADA);
    printf("Novo conteudo: ");
    imprimirVetor(v, qtd);

    free(v);
    return 0;
}

/* ========== ALGORITMOS DE ORDENAÇÃO COM PONTEIROS (Plano 11) ========== */

void trocar(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

void bubbleSort(int *v, int n) {
    for(int i = 0; i < n-1; i++) {
        for(int j = 0; j < n-i-1; j++) {
            // compara via ponteiro
            if(*(v+j) > *(v+j+1)) {
                trocar((v+j), (v+j+1));
            }
        }
    }
}

void insertionSort(int *v, int n) {
    for(int i = 1; i < n; i++) {
        int chave = *(v+i);
        int j = i-1;
        while(j >= 0 && *(v+j) > chave) {
            *(v+j+1) = *(v+j);
            j--;
        }
        *(v+j+1) = chave;
    }
}

void selectionSort(int *v, int n) {
    for(int i = 0; i < n-1; i++) {
        int min_idx = i;
        for(int j = i+1; j < n; j++) {
            if(*(v+j) < *(v+min_idx)) {
                min_idx = j;
            }
        }
        trocar((v+i), (v+min_idx));
    }
}

// Merge Sort
void merge(int *v, int esq, int meio, int dir) {
    int n1 = meio - esq + 1;
    int n2 = dir - meio;

    int *L = (int*) malloc(n1 * sizeof(int));
    int *R = (int*) malloc(n2 * sizeof(int));

    for(int i = 0; i < n1; i++) *(L+i) = *(v+esq+i);
    for(int j = 0; j < n2; j++) *(R+j) = *(v+meio+1+j);

    int i = 0, j = 0, k = esq;
    while(i < n1 && j < n2) {
        if(*(L+i) <= *(R+j)) {
            *(v+k) = *(L+i); i++;
        } else {
            *(v+k) = *(R+j); j++;
        }
        k++;
    }
    while(i < n1) { *(v+k) = *(L+i); i++; k++; }
    while(j < n2) { *(v+k) = *(R+j); j++; k++; }

    free(L); free(R);
}

void mergeSort(int *v, int esq, int dir) {
    if(esq < dir) {
        int meio = esq + (dir - esq)/2;
        mergeSort(v, esq, meio);
        mergeSort(v, meio+1, dir);
        merge(v, esq, meio, dir);
    }
}

// Quick Sort
int particiona(int *v, int esq, int dir) {
    int pivo = *(v+dir);
    int i = esq - 1;
    for(int j = esq; j < dir; j++) {
        if(*(v+j) <= pivo) {
            i++;
            trocar((v+i), (v+j));
        }
    }
    trocar((v+i+1), (v+dir));
    return i+1;
}

void quickSort(int *v, int esq, int dir) {
    if(esq < dir) {
        int p = particiona(v, esq, dir);
        quickSort(v, esq, p-1);
        quickSort(v, p+1, dir);
    }
}

/* ========== UTILITÁRIOS ========== */
void imprimirVetor(int *v, int n) {
    for(int i = 0; i < n; i++) {
        printf("%d ", *(v+i));
    }
    printf("\n");
}

void copiarVetor(int *dest, int *orig, int n) {
    for(int i = 0; i < n; i++) {
        *(dest+i) = *(orig+i);
    }
}
