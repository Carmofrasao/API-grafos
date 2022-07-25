#ifndef _GRAFO_H
#define _GRAFO_H

#include <graphviz/cgraph.h>

//-------------------------------------------------------------------------------
typedef Agraph_t *grafo;
typedef Agnode_t *vertice;
typedef Agedge_t *aresta;

#define vertex int

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
/*----------------------------------------------------------------------------*/

int color[1000];

// -----------------------------------------------------------------------------
// devolve o numero de arestas e vertices de uma componente de g
// caso g seja conexo, entao os valores serão iguais a n_vertices e n_arestas

void busca(grafo g, aresta e, vertice h, grafo_aresta *matriz, grafo_vertice * matriz_vertice);

// -----------------------------------------------------------------------------
// faz o produto de A por B e retorna em C

void multiplicar(int** A, int** B, int **C);

// -----------------------------------------------------------------------------
// retorna o calculo do rastro de uma matriz

int obterRastro(int** g);

// -----------------------------------------------------------------------------
// verifica se o grafo aceita duas cores em sua coloração

int biColor( Graph G, int v, int c);

// -----------------------------------------------------------------------------
// inicia uma lista que representa o grafo

Graph GrafoListInit( int Ve);

// -----------------------------------------------------------------------------
// adiciona um novo nodo a lista

link NovoNodo( vertex w, link next);

// -----------------------------------------------------------------------------
// adiciona uma nova aresta a lista

void IncerirAresta( Graph G, vertex v, vertex w);

// -----------------------------------------------------------------------------
// devolve o grafo lido da entrada padrão (formato dot)

grafo le_grafo(void);

// -----------------------------------------------------------------------------
// desaloca g

void destroi_grafo(grafo g);

// -----------------------------------------------------------------------------
// escreve g na saída padrão em formato dot
// devolve g

int escreve_grafo(grafo g);

// -----------------------------------------------------------------------------
// devolve o número de vértices de g

int n_vertices(grafo g);


// -----------------------------------------------------------------------------
// devolve o número de arestas do grafo

int n_arestas(grafo g);


// -----------------------------------------------------------------------------
// devolve o grau do vértice v em g

int grau(vertice v, grafo g);

// -----------------------------------------------------------------------------
// devolve o grau máximo de g

int grau_maximo(grafo g);

// -----------------------------------------------------------------------------
// devolve o grau mínimo de g

int grau_minimo(grafo g);

// -----------------------------------------------------------------------------
// devolve o grau médio de g

int grau_medio(grafo g);

//------------------------------------------------------------------------------
// devolve 1 se g é regular, ou 0 caso contrário

int regular(grafo g);

//------------------------------------------------------------------------------
// devolve 1 se g é completo, ou 0 caso contrário

int completo(grafo g);

//------------------------------------------------------------------------------
// devolve 1 se g é conexo, ou 0 caso contrário

int conexo(grafo g);

//------------------------------------------------------------------------------
// devolve 1 se g é bipartido, ou 0 caso contrário

int bipartido(grafo g);

//------------------------------------------------------------------------------
// devolve o número de triângulos (subgrafos completos de 3 vértices) em g

int n_triangulos(grafo g);

//------------------------------------------------------------------------------
// devolve uma matriz de adjacência de g onde as linhas/colunas
// estão ordenadas do mesmo modo que agfstnode() e agnxtnode()
// em libcgraph

int **matriz_adjacencia(grafo g);

//------------------------------------------------------------------------------
// devolve o grafo complementar a g

grafo complemento(grafo g);

#endif
