#include <stdio.h>
#include <stdlib.h>
#include "grafo.h"

//------------------------------------------------------------------------------
grafo le_grafo(void) {
  return agread(stdin, NULL); 
}
//------------------------------------------------------------------------------
void destroi_grafo(grafo g) {
  agclose(g);
  return;
}
//------------------------------------------------------------------------------
int escreve_grafo(grafo g) {
  return agwrite(g, stdout);
}

// -----------------------------------------------------------------------------
int n_vertices(grafo g) {
  return agnnodes(g);
}

// -----------------------------------------------------------------------------
int n_arestas(grafo g) {
  return agnedges(g);
}

// -----------------------------------------------------------------------------
int grau(vertice v, grafo g) {
  return agdegree(g,v,TRUE,TRUE);
}

// -----------------------------------------------------------------------------
int grau_maximo(grafo g)  {
  vertice f = agfstnode(g);
  int grau_max = grau(f, g);

  for (vertice n = agnxtnode(g,f); n; n = agnxtnode(g,n)){
    int grau_v = grau(n, g);
    if(grau_v > grau_max){
      grau_max = grau_v;
    }
  }
  return grau_max;
}

// -----------------------------------------------------------------------------
int grau_minimo(grafo g)  {
  vertice f = agfstnode(g);
  int grau_min = grau(f, g);

  for (vertice n = agnxtnode(g,f); n; n = agnxtnode(g,n)){
    int grau_v = grau(n, g);
    if(grau_v < grau_min){
      grau_min = grau_v;
    }
  }
  return grau_min;
}

// -----------------------------------------------------------------------------
int grau_medio(grafo g) {
  int grau_med = 0;
  for (vertice n = agfstnode(g); n; n = agnxtnode(g,n)){
    grau_med += grau(n, g);
  }
  grau_med /= n_vertices(g);
  return grau_med;
}

// -----------------------------------------------------------------------------
int regular(grafo g) {
  vertice f = agfstnode(g);
  int grau_ant = grau(f, g);

  for (vertice n = agnxtnode(g,f); n; n = agnxtnode(g,n)){
    int grau_prox = grau(n, g);
    if(grau_prox != grau_ant){
      return 0;
    }
  }
  return 1;
}

// -----------------------------------------------------------------------------
int completo(grafo g) {
  for (vertice n = agfstnode(g); n; n = agnxtnode(g,n)){
    for (vertice m = agfstnode(g); m; m = agnxtnode(g,m)){
      if(m != n){
        aresta e = agedge(g,m,n,NULL,FALSE);
        if (e == NULL){
          return 0;
        }
      }
    }
  }
  return 1;
}

// -----------------------------------------------------------------------------
int conexo(grafo g) {  
  int index = 0;
  vertice n = agfstnode(g);
  aresta e = agfstout(g,n);

  // agtail e aghead obtêm o ponto final de uma aresta
  
  for (; n; n = n) {
    for (; e; e = agfstout(g,n)) {
      index++;
      printf("%s\n",agnameof(n));
    }
    n = aghead(e);
  }

  printf("%d\n", index);

  if(index == n_arestas(g)){
    return 1;
  }
  return 0;
}

// -----------------------------------------------------------------------------
int bipartido(grafo g) {
  
  return 0;
}

// -----------------------------------------------------------------------------
int n_triangulos(grafo g) {
  
  return 0;
}

// -----------------------------------------------------------------------------
int **matriz_adjacencia(grafo g) {
  
  return NULL;
}

// -----------------------------------------------------------------------------
grafo complemento(grafo g) {
  
  return NULL;
}

