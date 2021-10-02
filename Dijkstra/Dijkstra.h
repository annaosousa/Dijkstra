#ifndef DIJKSTRA_H_INCLUDED
#define DIJKSTRA_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

typedef struct grafo{
	int aresta;
	int vertice;
	int **adjcente;
} *Grafo;


struct caminho{
	int custo;
	int saltos;
} *Rotas;


typedef struct estado{
	int antecessor;
	int tamanho;
	enum{permanente, tentativa} rotulo;
} *Estado;

int qtdRotas;

Grafo constroiGrafo(int vertice);

int **Matriz(int linha, int coluna, int valor);

int mostraCusto(Grafo G, int *caminho, int nivel);

int verificaPercorrido(int *caminho, int vertice, int nivel);

void inicializa(G);

void imprimeGrafo(Grafo G);

void removeVertice(Grafo G, int v, int w);

void mostraCaminho(int *caminho, int tamanho);

void caminhos(Grafo G, int origem, int destino);

void menorCusto(Grafo G, int origem, int destino);

void inicializaCaminho(int *caminho, int tamanho);

void mostraRota(Grafo G, int *caminho, int nivel);

void insereVertice(Grafo G, int v, int w, int peso);

void mostraRotas(Grafo G, int v, int w, int *a, int nivel);

void menorCaminho(Grafo G, int origem , int destino , int *caminho);

#endif // DIJKSTRA_H_INCLUDED
