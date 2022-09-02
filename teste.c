#include <stdio.h>
#include <stdlib.h>
#include "grafo.h"

//------------------------------------------------------------------------------

int main(void) {

  grafo g = le_grafo();

  decompoe(g);

  int v = n_vertices(g);
  int a = n_arestas(g);

  printf("v: %d, a: %d\n", v, a);

  int grau_max = grau_maximo(g);
  int grau_min = grau_minimo(g);
  int grau_med = grau_medio(g);

  printf("grau minimo: %d, grau medio: %d, grau maximo %d\n", grau_min, grau_med, grau_max);

  int reg = regular(g);
  printf("É regular? ");
  if (reg == 0){
    printf("NÃO\n");
  }
  else{
    printf("SIM\n");
  }

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

  printf("numero de triangulos: %d\n", n_triangulos(g));

  destroi_grafo(g);

  return 0;
}
