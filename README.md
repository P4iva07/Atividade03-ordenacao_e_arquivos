Atividade Avaliativa 03 - Ordenação e Arquivos em C
Projeto desenvolvido para a disciplina de Estrutura de Dados em C, integrando manipulação de arquivos e algoritmos de ordenação.

Descrição
O programa implementa um sistema completo de gerenciamento de dados numéricos com as seguintes funcionalidades:

Criação e gravação de arquivo com valores desordenados (dados.txt)
Leitura dos dados utilizando ponteiros e alocação dinâmica
Ordenação com 5 algoritmos diferentes à escolha do usuário
Gravação do resultado ordenado em novo arquivo (ordenado.txt)
Alteração de valores no arquivo original e reordenação
Algoritmos Implementados
Bubble Sort
Insertion Sort
Selection Sort
Merge Sort
Quick Sort
Conceitos Aplicados
Manipulação de arquivos: fopen, fprintf, fscanf, fgets, fclose
Ponteiros: aritmética de ponteiros, passagem por referência, alocação dinâmica com malloc/free
Estrutura switch/case: menus interativos
Ordenação: implementação dos 5 algoritmos clássicos
Como Compilar e Executar
Linux / macOS
gcc atividade03_ordenacao_e_arquivos.c -o atividade03
./atividade03
Windows (MinGW)
gcc atividade03_ordenacao_e_arquivos.c -o atividade03.exe
atividade03.exe
Como Usar
Execute o programa e escolha a opção 1 para criar o arquivo dados.txt
Informe a quantidade de números e se deseja digitar manualmente ou gerar aleatoriamente
Use a opção 3 para escolher o algoritmo de ordenação
O resultado será salvo em ordenado.txt
Use a opção 5 para alterar um valor e reordenar
Estrutura de Arquivos
atividade03_ordenacao_e_arquivos.c - Código fonte principal
dados.txt - Arquivo com dados de entrada (gerado pelo programa)
ordenado.txt - Arquivo com dados ordenados (gerado pelo programa)
Exemplo de Arquivos
dados.txt

42
15
8
23
4
ordenado.txt

4
8
15
23
42
