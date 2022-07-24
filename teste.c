#include <stdio.h>
#include <stdlib.h>
#include "grafo.h"

//------------------------------------------------------------------------------

int main(void) {

  grafo g = le_grafo();

  int v = n_vertices(g);
  int a = n_arestas(g);

  printf("v: %d, a: %d\n", v, a);

  for (vertice n = agfstnode(g); n; n = agnxtnode(g,n)){
    char *str = agnameof(n);
    int grau_v = grau(n, g);
    printf("nome: %s grau: %d, ", str, grau_v); 
  }
  printf("\n");

  int grau_max = grau_maximo(g);
  int grau_min = grau_minimo(g);
  int grau_med = grau_medio(g);

  printf("grau minimo: %d, grau medio: %d, grau maximo %d\n", grau_min, grau_med, grau_max);

  int comp = completo(g);
  printf("É completo? ");
  if (comp == 0){
    printf("NÃO\n");
  }
  else{
    printf("SIM\n");
  }
  
  int cone = conexo(g);
  printf("É conexo? ");
  if (cone == 0){
    printf("NÃO\n");
  }
  else{
    printf("SIM\n");
  }
  int bi = bipartido(g);
  printf("É bipartido? ");
  if (bi == 0){
    printf("NÃO\n");
  }
  else{
    printf("SIM\n");
  }

  escreve_grafo(g);

  int ** mat = matriz_adjacencia(g);
  for (int i = 0; i < n_vertices(g); i++){
    for(int l = 0; l < n_vertices(g); l++){
      printf("%d ", mat[i][l]);
    }
    printf("\n");
  }
  
  grafo aux = complemento(g);
  escreve_grafo(aux);

  printf("numero de triangulos: %d\n", n_triangulos(g));

  for(int l = 0; l < n_vertices(g); l++){
    free(mat[l]);
  }
  free(mat);

  destroi_grafo(g);
  destroi_grafo(aux);

  return 0;
}
