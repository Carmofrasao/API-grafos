#include <stdio.h>
#include <stdlib.h>
#include "grafo.h"

#define vertex int

typedef Agedge_t *aresta;

/*---------------------------------------------------------------------*/
// estrutura para gerar vetores de arestas
typedef struct {
    aresta aux;
    int marca;
} grafo_aresta;

// estrutura para gerar vetores de vertices
typedef struct {
    vertice aux;
    int marca;
} grafo_vertice;
/*---------------------------------------------------------------------*/

/*Estrutura para auxiliar na criação de listas para representar o grafo*/
typedef struct node *link;

struct node { 
   vertex w; 
   link next; 
};

struct GrafoList {
   int V; 
   int A; 
   link *adj; 
};

typedef struct GrafoList *Graph;
/*---------------------------------------------------------------------*/

int V;
int color[1000];

/*----------------FUNÇÃO AUXILIAR PARA A FUNÇÃO conexo-----------------*/
// devolve o numero de arestas e vertices de uma componente de g
// caso g seja conexo, entao os valores serão iguais a n_vertices e n_arestas

static void busca(int i, int n, int *visitado, int **matriz){
  // marca o vertice como visitado
  visitado[i] = 1;

  // percorre todas as arestas do vertice h, 
  // passando o proximo vertice de cada aresta para a recursão
  for (int j = 0; j < n; j++){ 
    if(matriz[i][j] == 1 && !visitado[j])
      busca(j, n, visitado, matriz);
  }
}
/*------------------------------------------------------------------------*/

/*--------------FUNÇẼS AUXILIARES PARA A FUNÇÃO n_triangulos--------------*/
// faz o produto de A por B e retorna em C

static void multiplicar(int** A, int** B, int **C){
  for (int i = 0; i < V; i++){
    for (int j = 0; j < V; j++){
      C[i][j] = 0;
      for (int k = 0; k < V; k++)
        C[i][j] += A[i][k]*B[k][j];
    }
  }
}

// -----------------------------------------------------------------------------
// Função para calcular rastro de uma matriz (soma dos elementos diagonais)

static int obterRastro(int** g){
  int rastro = 0;
  for (int i = 0; i < V; i++)
    rastro += g[i][i];
  return rastro;
}
/*------------------------------------------------------------------------*/

/*--------------FUNÇẼS AUXILIARES PARA A FUNÇÃO bipartido-----------------*/

// inicializa uma lista que contem o grafo 
static Graph GrafoListInit( int Ve) { 
   Graph G = malloc( sizeof *G);
   G->V = Ve; 
   G->A = 0;
   G->adj = malloc( (long unsigned int)Ve * sizeof (link));
   for (vertex v = 0; v < Ve; ++v) 
      G->adj[v] = NULL;
   return G;
}

// adiciona um novo nodo a lista
static link NovoNodo( vertex w, link next) { 
   link a = malloc( sizeof (struct node));
   a->w = w; 
   a->next = next;     
   return a;                         
}

// adiciona uma nova aresta a lista
static void IncerirAresta( Graph G, vertex v, vertex w) { 
   for (link a = G->adj[v]; a != NULL; a = a->next) 
      if (a->w == w) return;
   G->adj[v] = NovoNodo( w, G->adj[v]);
   G->A++;
}

// verifica se o grafo aceita duas cores em sua coloração
static int biColor( Graph G, int v, int c){ 
  color[v] = c;
  for (link a = G->adj[v]; a != NULL; a = a->next) {
    int w = a->w; 
    if (color[w] == -1) {
      if (biColor( G, w, 1-c) == 0) 
        return 0; 
    }
    else { // v-w é de avanço ou de retorno
      if (color[w] == c) // base da recursão
        return 0;
    }
  }
  return 1;
}
/*-----------------------------------------------------------------------------*/

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

  // percorre todos os vertices buscando o maior grau
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

  // percorre todos os vertices buscando o menor grau
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

  // percorre todos os vertices somando os graus
  for (vertice n = agfstnode(g); n; n = agnxtnode(g,n)){
    grau_med += grau(n, g);
  }

  // tira a media da soma dos graus
  grau_med /= n_vertices(g);
  return grau_med;
}

// -----------------------------------------------------------------------------
int regular(grafo g) {
  vertice f = agfstnode(g);
  int grau_ant = grau(f, g);

  // percorre todos os vertices verificando se tem o mesmo grau que o primeiro vertice
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

  // percorre todos os vertices verificando se ha aresta entre n e m
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
  int ** matriz = matriz_adjacencia(g);
  int *visitado = (int*)calloc((long unsigned int)n_vertices(g), sizeof(int));

  int n_componentes = 0;

  // inicializa todo vertice como nao visitado 
  for(int i = 0; i < n_vertices(g); i++) 
    visitado[i] = 0; 
  
  // recursivamente visita vertices adjacentes 
  for(int i = 0; i < n_vertices(g); i++){ 
    if(visitado[i] == 0){ 
      busca(i, n_vertices(g), visitado, matriz); 
      n_componentes++; 
    } 
  }
  
  free(matriz);

  return n_componentes;
}

// -----------------------------------------------------------------------------
int bipartido(grafo g) {
  // G é uma lista para auxiliar a verificação
  Graph G = GrafoListInit(n_vertices(g));

  // vetor auxiliar para comparação futura
  grafo_vertice * matriz_vertice = (grafo_vertice *)calloc((long unsigned int)n_vertices(g), sizeof(grafo_vertice));

  int l = 0;

  for (vertice m = agfstnode(g); m; m = agnxtnode(g,m)) {
    matriz_vertice[l].aux = m;
    matriz_vertice[l].marca = 0;
    l++;
  }

  for (vertice n = agfstnode(g); n; n = agnxtnode(g,n)){
    for (vertice m = agfstnode(g); m; m = agnxtnode(g,m)){
      // preenchendo a lista G com os vertices do grafo g
      aresta e = agedge(g,n,m,NULL,FALSE);
      if (e != NULL && n != m){
        int i;
        for(i = 0; i < n_vertices(g); i++){
          if(m == matriz_vertice[i].aux){
            break;
          }
        }
        for(l = 0; l < n_vertices(g); l++){
          if(n == matriz_vertice[l].aux){
            break;
          }
        }
        IncerirAresta(G, l, i);
      }
    }
  }
  
  // verificação para saber se G aceita duas cores
  for (int v = 0; v < G->V; ++v) 
    color[v] = -1; // incolor
  for (int v = 0; v < G->V; ++v)
    if (color[v] == -1) // começa nova etapa
        if (biColor( G, v, 0) == 0) {
          free(matriz_vertice);
          return 0;
        }
  free(matriz_vertice);
  return 1;
}

// -----------------------------------------------------------------------------
int n_triangulos(grafo g) {
  int ** matriz = matriz_adjacencia(g);
  V = n_vertices(g);
  
  /*matrizes auxiliares para auxiliar a verificação*/
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

    // calculo feito por manipulação Aritmética
    return rastro / 6;
}

// -----------------------------------------------------------------------------
int **matriz_adjacencia(grafo g) {

  // matriz de retorno
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

  // vetor auxiliar para comparação futura
  grafo_vertice * matriz_vertice = (grafo_vertice *)calloc((long unsigned int)n_vertices(g), sizeof(grafo_vertice));
  int i = 0;
  for (vertice m = agfstnode(g); m; m = agnxtnode(g,m)){
    matriz_vertice[i].aux = m;
    i++;
  }

  // percorre todo o grafo para prencher a matriz
  for (vertice n = agfstnode(g); n; n = agnxtnode(g,n)){
    for (vertice m = agfstnode(g); m; m = agnxtnode(g,m)){
      aresta e = agedge(g,m,n,NULL,FALSE);
      if (e != NULL){
        int z, y;

        // encontra os indices para cada vertice
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

  // copia os vertices de g em aux
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

// -----------------------------------------------------------------------------
grafo decompoe(grafo g){
  if(agisundirected(g) == 1)
    return g;
  
  for (grafo subg = agfstsubg(g); subg; subg = agnxtsubg(subg)){
    agsubg(subg, NULL, 1);
    escreve_grafo(subg);
  }

  return g;
}