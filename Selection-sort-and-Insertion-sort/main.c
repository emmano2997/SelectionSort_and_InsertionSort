#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int write_output_file();
int reload_array();

void SelectionSort(int A[], int n) {
    int i, j, min_idx, temp;

    for (i = 0; i < n-1; i++) {
        min_idx = i;
        for (j = i+1; j < n; j++) {
            if (A[j] < A[min_idx])
                min_idx = j;
        }
        if (min_idx != i) {
            temp = A[i];
            A[i] = A[min_idx];
            A[min_idx] = temp;
        }
    }
}

void InsertionSort(int A[], int n){
  int i,j,aux;
    for(i = 1; i < n; i++){
        j = i;

      while(j>0 && A[j-1] > A[j]){
        aux = A[j];
        A[j] = A[j-1];
        A[j-1] = aux;
        j--;
      }
    }
}

int main(void) {
    FILE *input;
    int n, i;
    clock_t start, end;
    double cpu_time_used_SS,cpu_time_used_IS;

  
  const char* arquivo = "num.1000.2.in";    // unica variavel que tem que ser alterada para a leitura de outros arquivos de entrada

  input = fopen(arquivo, "r"); // abre o arquivo de entrada
    if (input == NULL) {
        printf("Error ao abrir o arquivo caui aq\n");
        return 1; 
    }

    fscanf(input, "%d", &n); // Lê o tamanho do vetor e salva na variavel n
    int *A = (int *)malloc(n * sizeof(int));
    if (A == NULL) {
        printf("Error ao alocar memoria\n");
        fclose(input);
        return 1; 
    }

    for (i = 0; i < n; i++) { //ler o arquivo de entrada
        fscanf(input, "%d", &A[i]);
    }
    fclose(input);

    start = clock(); 
    SelectionSort(A, n);
    end = clock();
    cpu_time_used_SS = ((double) (end - start)) / CLOCKS_PER_SEC;    // calcula o tempo no algoritimo de Selection Sort

    if (write_output_file("SS_numeros-organizados.out", A, n) != 0) { //função que escreve o arquivo de saida
        free(A);
        return 1; 
    }

  if(reload_array(arquivo, A, n) != 0){
    free(A);
    return 1;
  }
    start = clock(); 
    InsertionSort(A, n);
    end = clock();
    cpu_time_used_IS = ((double) (end - start)) / CLOCKS_PER_SEC;    // calcula o tempo no algoritimo de Selection Sort

  if (write_output_file("IS_numeros-organizados.out", A, n) != 0) {
      free(A);
      return 1; 
  }
  
  free(A);

  printf("Tempo necessário para ordenarcom SelectionSort: %f s\n", cpu_time_used_SS);
  printf("Tempo necessário para ordenarcom InsertionSort: %f s\n", cpu_time_used_IS);

  printf("\t--- Comparação de tempo dos algoritimos de ordenação: %f s ---\n", cpu_time_used_SS - cpu_time_used_IS);
  
    return 0;
}

int write_output_file(const char* filename, int A[], int n) {
  FILE *output;
  int i;

    output = fopen(filename, "w"); //cria arquivo de saida
    if (output == NULL) {
        printf("Error ao criar arquivo de saida\n");
        free(A);
        return 1; 
    }

    fprintf(output, "%d\n", n);  //  escreve em um artquivo os valores organizados
    for (i = 0; i < n; i++) {
        fprintf(output, "%d\n", A[i]);
    }
    fclose(output);
  return  0;
}

int reload_array(const char* filename, int A[], int n) { // le novamente o arquivo de entrada
    FILE *input = fopen(filename, "r");
    if (input == NULL) {
        printf("Error ao abrir o arquivo \n");
        return 1; 
    }

    fscanf(input, "%d", &n);
    for (int i = 0; i < n; i++) {
        fscanf(input, "%d", &A[i]);
    }
    fclose(input);
    return 0;
}