#include <stdio.h>
#include <stdlib.h>
#include "grafo.h"

int contador_arestas, contador_vertices, V;

void busca(grafo g, aresta e, vertice h, grafo_aresta *matriz_aresta, grafo_vertice * matriz_vertice){
  for(int i = 0; i < n_arestas(g); i++){
    if(e == matriz_aresta[i].aux && matriz_aresta[i].marca == 1){
      // caso ja tenha passado na aresta atual, a recursão para
      return;
    }
    else if(e == matriz_aresta[i].aux && matriz_aresta[i].marca == 0){
      // marca a aresta atual para que ela não seja contabilizada novamente
      // e caso chegue nela novamente, a recursão pare
      matriz_aresta[i].marca = 1;
      contador_arestas++;
      break;
    }
  }

  for(int i = 0; i < n_vertices(g); i++){
    if(h == matriz_vertice[i].aux && matriz_vertice[i].marca == 0){
      // marca o vertice atual para que ele não seja contabilizado novamente
      matriz_vertice[i].marca = 1;
      contador_vertices++;
      break;
    }
  }

  // percorre todas as arestas do vertice h, 
  // passando o proximo vertice de cada aresta para a recursão
  for (aresta l = agfstout(g,h); l; l = agnxtout(g,l)){ 
    vertice w = aghead(l);
    busca(g, l, w, matriz_aresta, matriz_vertice);
  }
}

// Função para multiplicação de matrizes
void multiplicar(int** A, int** B, int **C){
  for (int i = 0; i < V; i++){
    for (int j = 0; j < V; j++){
      C[i][j] = 0;
      for (int k = 0; k < V; k++)
        C[i][j] += A[i][k]*B[k][j];
    }
  }
}
  
// Função para calcular rastro de uma matriz (soma dos elementos diagonais)
int obterRastro(int** graph){
  int rastro = 0;
  for (int i = 0; i < V; i++)
    rastro += graph[i][i];
  return rastro;
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
  int ** matriz = matriz_adjacencia(g);
  V = n_vertices(g);
  
  // matriz^2
  int ** aux2 = (int**)calloc((long unsigned int)n_vertices(g), sizeof(int*));
  if(!aux2){
    perror("erro de alocação");
    exit(1);
  }
  for (int i = 0; i < n_vertices(g); i++){
    aux2[i] = (int*)calloc((long unsigned int)n_vertices(g), sizeof(int));
    if(!matriz[i]){
      perror("erro de alocação");
      exit(1);
    }
  }
  
    // matriz^3
  int** aux3 = (int**)calloc((long unsigned int)n_vertices(g), sizeof(int*));
  if(!aux3){
    perror("erro de alocação");
    exit(1);
  }
  for (int i = 0; i < n_vertices(g); i++){
    aux3[i] = (int*)calloc((long unsigned int)n_vertices(g), sizeof(int));
    if(!matriz[i]){
      perror("erro de alocação");
      exit(1);
    }
  }
  
    // Inicializando matrizes auxiliares com 0
    for (int i = 0; i < V; ++i)
        for (int j = 0; j < V; ++j)
            aux2[i][j] = aux3[i][j] = 0;
  
    // aux2 é matriz^2 agora
    multiplicar(matriz, matriz, aux2);
  
    // após esta multiplicação aux3 é matriz^3
    multiplicar(matriz, aux2, aux3);
  
    int rastro = obterRastro(aux3);

    for (int i = 0; i < n_vertices(g); i++){
      free(matriz[i]);
      free(aux3[i]);
      free(aux2[i]);
    }
    free(matriz);
    free(aux2);
    free(aux3);

    return rastro / 6;
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
      aresta l = agedge(aux,agnode(aux, agnameof(n), FALSE), agnode(aux, agnameof(m), FALSE),NULL,FALSE);
      if (e == NULL && l == NULL && n != m){
        // verifica se não existe a aresta e no grafo original
        // caso seja verdade, cria ela no grafo aux
        agedge(aux,agnode(aux, agnameof(n), FALSE), agnode(aux, agnameof(m), FALSE),NULL,TRUE);
      }
    }
  }

  return aux;
}

