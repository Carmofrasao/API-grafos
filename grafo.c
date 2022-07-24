#include <stdio.h>
#include <stdlib.h>
#include "grafo.h"

int contador_arestas, contador_vertices;

void busca(grafo g, aresta e, vertice h, grafo_aresta *matriz_aresta, grafo_vertice * matriz_vertice){
  for(int i = 0; i < n_arestas(g); i++){
    if(e == matriz_aresta[i].aux && matriz_aresta[i].marca == 1){
      return;
    }
    else if(e == matriz_aresta[i].aux && matriz_aresta[i].marca == 0){
      matriz_aresta[i].marca = 1;
      contador_arestas++;
      break;
    }
  }

  for(int i = 0; i < n_vertices(g); i++){
    if(h == matriz_vertice[i].aux && matriz_vertice[i].marca == 0){
      matriz_vertice[i].marca = 1;
      contador_vertices++;
      break;
    }
  }

  for (aresta l = agfstout(g,h); l; l = agnxtout(g,l)){ 
    vertice w = aghead(l);
    busca(g, l, w, matriz_aresta, matriz_vertice);
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
  contador_arestas = 0;
  
  vertice n = agfstnode(g);
  contador_vertices = 0;

  grafo_vertice * matriz_vertice = (grafo_vertice *)calloc((long unsigned int)n_vertices(g), sizeof(grafo_vertice));

  grafo_aresta * matriz_aresta = (grafo_aresta*)calloc((long unsigned int)n_arestas(g), sizeof(grafo_aresta));

  int i = 0;
  int l = 0;

  for (vertice m = agfstnode(g); m; m = agnxtnode(g,m)) {
    for (aresta f = agfstout(g,m); f; f = agnxtout(g,f)) {
      matriz_aresta[i].aux = f;
      matriz_aresta[i].marca = 0;
      i++;
    }
    matriz_vertice[l].aux = m;
    matriz_vertice[l].marca = 0;
    l++;
  }

  busca(g, NULL, n, matriz_aresta, matriz_vertice);

  free(matriz_vertice);
  free(matriz_aresta);

  if(contador_arestas == n_arestas(g) && contador_vertices == n_vertices(g)){
    return 1;
  }
  return 0;
}

// -----------------------------------------------------------------------------
int bipartido(grafo g) {
  for (vertice m = agfstnode(g); m; m = agnxtnode(g,m)) {
    for (vertice n = agfstnode(g); n; n = agnxtnode(g,n)){
      aresta e = agedge(g,m,n,NULL,FALSE);
      if (e != NULL)
        return 0;
    }
  }

  return 1;
}

// -----------------------------------------------------------------------------
int n_triangulos(grafo g) {
  int contador_triangulos = 0;
  for (vertice m = agfstnode(g); m; m = agnxtnode(g,m)) {
    for (vertice n = agfstnode(g); n; n = agnxtnode(g,n)){
      for (vertice h = agfstnode(g); h; h = agnxtnode(g,h)){
        aresta e = agedge(g,m,n,NULL,FALSE);
        aresta i = agedge(g,n,h,NULL,FALSE);
        aresta j = agedge(g,h,m,NULL,FALSE);
        if(e && i && j)
          contador_triangulos++;
      }
    }
  }
  return contador_triangulos;
}

// -----------------------------------------------------------------------------
int **matriz_adjacencia(grafo g) {
  int ** matriz = (int**)calloc((long unsigned int)n_vertices(g), sizeof(int*));
  if(!matriz){
    perror("erro de alocação");
    exit(1);
  }
  for (int i = 0; i < n_vertices(g); i++){
    matriz[i] = (int*)calloc((long unsigned int)n_vertices(g), sizeof(int));
    if(!matriz[i]){
      perror("erro de alocação");
      exit(1);
    }
  }

  grafo_vertice * matriz_vertice = (grafo_vertice *)calloc((long unsigned int)n_vertices(g), sizeof(grafo_vertice));
  int i = 0;
  for (vertice m = agfstnode(g); m; m = agnxtnode(g,m)){
    matriz_vertice[i].aux = m;
    i++;
  }

  for (vertice n = agfstnode(g); n; n = agnxtnode(g,n)){
    for (vertice m = agfstnode(g); m; m = agnxtnode(g,m)){
      aresta e = agedge(g,m,n,NULL,FALSE);
      if (e != NULL){
        int z, y;
        for (z = 0; z < n_vertices(g); z++){
          if(matriz_vertice[z].aux == n){
            break;
          }
        }
        for(y = 0; y < n_vertices(g); y++){
          if(matriz_vertice[y].aux == m){
            break;
          }
        }
        matriz[z][y] = 1;
        matriz[y][z] = 1;
      }
    }
  }
  free(matriz_vertice);
  return matriz;
}

// -----------------------------------------------------------------------------
grafo complemento(grafo g) {
  grafo aux;
  aux = agopen(FALSE, Agundirected, NULL);

  for (vertice m = agfstnode(g); m; m = agnxtnode(g,m)){
    agnode(aux,agnameof(m),TRUE);
  }
  
  for (vertice n = agfstnode(g); n; n = agnxtnode(g,n)){
    for (vertice m = agfstnode(g); m; m = agnxtnode(g,m)){
      aresta e = agedge(g,n,m,NULL,FALSE);
      if (e == NULL && n != m){
        agedge(aux,agnode(aux, agnameof(n), FALSE), agnode(aux, agnameof(m), FALSE),NULL,TRUE);
      }
    }
  }

  return aux;
}

