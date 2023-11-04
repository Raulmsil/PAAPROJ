#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>

struct Aluno {
  int ano;
  char nome[100];
  char disciplina[30];
  float nota;
};

void trocar(struct Aluno *a, struct Aluno *b) {
  struct Aluno temp = *a;
  *a = *b;
  *b = temp;
}

int ordenarPorNotaBubble(struct Aluno alunos[], int tamanho) {
  int i, j, passos = 0;
  for (i = 0; i < tamanho - 1; i++) {
    for (j = 0; j < tamanho - i - 1; j++) {
      passos++;
      if (alunos[j].nota > alunos[j + 1].nota) {
        trocar(&alunos[j], &alunos[j + 1]);
      }
    }
  }
  return passos;
}

void merge(struct Aluno v1[], int n1, struct Aluno v2[], int n2, struct Aluno v[]) {
  int i1 = 0, i2 = 0, i = 0;

  while (i1 < n1 && i2 < n2) {
    if (v1[i1].nota < v2[i2].nota) v[i] = v1[i1++];
    else v[i++] = v2[i2++];
  }
  
  while (i1 < n1) v[i++] = v1[i1++];
  while (i2 < n2) v[i++] = v2[i2++];
}

int ordenarPorNotaMergeSort(struct Aluno v[], int n) {
  if (n < 2)
    return 0;
  int meio = n / 2,
      n1 = meio,
      n2 = n - meio,
      passos;
  
  struct Aluno v1[n1], v2[n2];

  for (int i = 0; i < n1; i++) {
    v1[i] = v[i];
  }
  for (int i = 0; i < n2; i++) {
    v2[i] = v[meio + i];
  }

  passos += ordenarPorNotaMergeSort(v1, n1);
  passos += ordenarPorNotaMergeSort(v2, n2);

  merge(v1, n1, v2, n2, v);
  return passos;
}

int main(void) {
  printf("Escolha uma das opções abaixo:\n"
         "1. Ordenar por nota (Bubble Sort).\n"
         "2. Ordenar por nota (Merge Sort).\n");
  int opcao;
  float aleatorio[200000]; // Correção: Deve ser float para as notas.
  FILE *arq;
  arq = fopen("entrada.csv", "r");

  if (arq == NULL) {
    perror("Erro ao abrir o arquivo de entrada");
    return 1;
  }

  int numAlunos = 0;
  struct Aluno alunos[200000];

  while (fscanf(arq, "%d,%99[^,],%29[^,],%f\n", 
          &alunos[numAlunos].ano, 
          alunos[numAlunos].nome,
          alunos[numAlunos].disciplina,
          &alunos[numAlunos].nota) != EOF) {    numAlunos++;  }

  fclose(arq);

  srand(time(NULL));
  for (int i = 0; i < numAlunos; i++) {
    float a =(float)rand() / (float)RAND_MAX * 10.0; // Geração de notas aleatórias entre 0 e 10.
    aleatorio[i] = (float) a;
  }

  arq = fopen("entrada.csv", "w");

  if (arq == NULL) {
    perror("Erro ao abrir o arquivo de entrada");
    return 1;
  }

  for (int i = 0; i < numAlunos; i++) {
    fprintf(arq, "%d,%s,%s,%.2f\n", 
            alunos[i].ano, 
            alunos[i].nome, 
            alunos[i].disciplina, 
            aleatorio[i]);
  }

  fclose(arq);

  scanf("%d", &opcao);
  int passos = 0;
  switch (opcao) {
    case 1:
      passos = ordenarPorNotaBubble(alunos, numAlunos);           
      break;
    case 2:
      passos = ordenarPorNotaMergeSort(alunos, numAlunos);
      break;
    default:
      printf("Opção Inválida !!!");
  }

  FILE *saida = fopen("saida.csv", "w");
  if (saida == NULL) {
    perror("Erro ao abrir o arquivo de saída");
    return 1;
  }

  fprintf(saida, "Ano,Nome,Disciplina,Nota\n");

  for (int i = 0; i < numAlunos; i++) {
    fprintf(saida, "%d,%s,%s,%.2f\n", 
            alunos[i].ano, 
            alunos[i].nome, 
            alunos[i].disciplina, 
            alunos[i].nota);
  }

  fclose(saida);

  printf("\nDados ordenados com sucesso. O resultado foi salvo em saida.csv.\n");
  printf("Passos: %d\n", passos);

  return 0;
}
