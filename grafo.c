#include <stdio.h>
#include <stdlib.h>
#include "grafo.h"

int contador;

void busca(grafo g, aresta e, vertice h, grafo_aux *matriz){
  for(int i = 0; i < n_arestas(g); i++){
    if(e == matriz[i].aux && matriz[i].marca == 1){
      return;
    }
  }

  for(int i = 0; i < n_arestas(g); i++){
    if(e == matriz[i].aux && matriz[i].marca == 0){
      matriz[i].marca = 1;
      contador++;
      break;
    }
  }

  for (aresta l = agfstout(g,h); l; l = agnxtout(g,l)){   
    // for(int i = 0; i < n_arestas(g); i++){
    //   if(l == matriz[i].aux && matriz[i].marca == 0){
    //     matriz[i].marca = 1;
    //     contador++;
    //     break;
    //   }
    // }
    
    printf("%s -> ", agnameof(h));
    vertice w = aghead(l);
    printf("%s\n", agnameof(w));
    busca(g, l, w, matriz);
  }
}

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
  contador = 0;
  vertice n = agfstnode(g);
  aresta e = agfstedge(g,n);

  grafo_aux * matriz = (grafo_aux*)calloc((long unsigned int)n_arestas(g), sizeof(grafo_aux));

  int i = 0;

  for (vertice m = agfstnode(g); m; m = agnxtnode(g,m)) {
    for (aresta f = agfstout(g,m); f; f = agnxtout(g,f)) {
      matriz[i].aux = f;
      matriz[i].marca = 0;
      i++;
    }
  }

  busca(g, e, n, matriz);

  printf("%d\n", contador);

  if(contador == n_arestas(g)){
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

