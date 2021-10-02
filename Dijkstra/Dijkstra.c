#include "Dijkstra.h"

/*inicializações para o Grafo, passando seus respectivos valores para aresta, vértice e o seu vértice adjcente*/
Grafo constroiGrafo(int vertice){
	Grafo G = malloc(sizeof *G);
	G->aresta = vertice;
	G->vertice = 0;
	G->adjcente = Matriz(vertice,vertice,0);

	return G;
}

/*cria uma matriz de adjcência para o grafo*/
int **Matriz(int linha, int coluna, int valor){
	int **matriz = malloc(linha * sizeof (int*));

	for(int u = 0; u < linha; u++)
		matriz[u] = malloc(coluna * sizeof(int));
	for(int i = 0; i < linha; i++)
		for(int j = 0; j < coluna; j++)
			matriz[i][j] = valor;

	return matriz;
}

/*Inserção de um novo vértice no Grafo*/
void insereVertice(Grafo G, int v, int w, int peso){
    if(G == NULL)
        return;
	else if(G->adjcente[v][w] == 0){
		G->adjcente[v][w] = peso;
		G->adjcente[w][v] = peso; //matriz transposta
		G->vertice++;
	}
}

/*Remoção de um vértice no Grafo*/
void removeVertice(Grafo G, int v, int w){
    if(G == NULL)
        printf("Nao ha vertices a serem removidos");
	else if(G->adjcente[v][w] > 0){
		G->adjcente[v][w] = 0;
		G->adjcente[w][v] = 0; //matriz transposta
		G->vertice--;
	}
}

/*Imprime o Grafo, primeiramente o vértice e quais são suas adjcências*/
void imprimeGrafo(Grafo G){
	for(int i = 1; i < G->aresta; i++){
		printf("%2d -> ", i);
		for(int j = 0; j < G->aresta; j++)
			if(G->adjcente[i][j] > 0)
				printf("%2d", j);
		printf("\n");
	}
}

/*Inicializa os valores iniciais das arestas com -1, denomonandos de caminho, pois os mesmos serão os caminhos que ligam as arestas*/
void inicializaCaminho(int *caminho, int tamanho){
	for(int i = 0; i < tamanho; i++)
		caminho[i] = -1;
}

/*Imprime o caminho, caso exista*/
void mostraCaminho(int *caminho, int tamanho){
	for(int i = 0; i < tamanho-1; i++)
		if(caminho[i] == -1)
			return;
		else
			printf("%d ", caminho[i]);
}

/* Imprime o custo atribuído a cada caminho percorrido*/
int mostraCusto(Grafo G, int *caminho, int nivel){
	int custo = 0;

	if(nivel == 0)
		return 0;
    else
        for(int i = 0; i < nivel; i++)
            custo += G->adjcente[caminho[i++]][caminho[i++]];
    printf("  - Custo: %d", custo);

	return custo;
}

/*Imprime todas as rotas possíveis entre os vértices*/
void mostraRota(Grafo G, int *caminho, int nivel){
	printf("Opcao de rota numero %d: ", qtdRotas+1);
	for(int i = 0; i < nivel; i++)
		printf("%d ", caminho[i]);

	Rotas[qtdRotas].custo = mostraCusto(G, caminho, nivel);
	Rotas[qtdRotas].saltos = nivel-1;
	printf(" - Quantidade de vertices percorridos: %d\n", Rotas[qtdRotas].saltos);
	qtdRotas++;
}

/*Base do Algoritmo Dijkstra, verifica qual e o menor caminho*/
void menorCaminho(Grafo G, int origem , int destino , int *caminho){
    int aux = 0, min = INT_MAX;
	Estado *estado = malloc(G->aresta * sizeof(Estado*));

	for (int i = 0; i < G->aresta; i++){
		estado[i]->antecessor =-1;
		estado[i]->tamanho = INT_MAX;
		estado[i]->rotulo = tentativa;
	}
	estado[destino]->tamanho = 0;
	estado[destino]->rotulo = permanente;
	do{
		for (int i = 0; i < G->aresta; i++){
			if((G->adjcente[destino][i] != 0) && (estado[i]->rotulo == tentativa))
				if((estado[destino]->tamanho + G->adjcente[destino][i]) < estado[i]->tamanho){
					estado[i]->antecessor = destino;
					estado[i]->tamanho = estado[destino]->tamanho + G->adjcente[destino][i];
 				}
            destino = 0;
 			if(estado[i]->rotulo == tentativa && estado[i]->tamanho < min){
 				min = estado[i]->tamanho;
 				destino = i;
 			}
        }
 		estado[destino]->rotulo = permanente;
 	}while(destino != origem);

 	do{
 	 	caminho[aux++] = origem;
 		origem = estado[origem]->antecessor;
 	 }while(origem >= 0);

 }

 /*Verifica quais vertices já foram percorridos*/
int verificaPercorrido(int *caminho, int vertice, int nivel){
	for(int i = 0; i < nivel; i++){
		if(caminho[i] == vertice)
			return 1;
	}

	return 0;
}

/*Verifica se todas as rotas apresentadas ja foram percorridas*/
void mostraRotas(Grafo G, int v, int w, int *caminho, int nivel){
	if(v == w){
		mostraRota(G, caminho, nivel);
		return;
	}
	else{
        if(nivel == 0){
			caminho[0] = v;
			nivel++;
		}
		for(int i = 0; i < G->aresta; i++)
			if((G->adjcente[v][i] > 0) && (verificaPercorrido(caminho, i, nivel) != 1)){
				caminho[nivel] = i;
				mostraRotas(G, i, w, caminho, nivel + 1);
			}
	}
}

/*Encontra a rota com o menor custo(peso), imprime qual tem o menor custo e o menor número de vértices percorridos*/
void menorCusto(Grafo G, int origem, int destino){
	int opcao, menorCusto = Rotas[0].custo, menorSalto = Rotas[0].saltos, melhorRotaCusto = 0, melhorRotaSalto = 0;
    int *a = malloc(G->aresta * sizeof(int));

	inicializaCaminho(a, G->aresta);

        for(int i = 1; i < qtdRotas; i++){
            if(Rotas[i].custo < menorCusto){
                menorCusto = Rotas[i].custo;
                melhorRotaCusto = i;
            }
            if(Rotas[i].saltos < menorSalto){
                menorSalto = Rotas[i].saltos;
                melhorRotaSalto = i;
            }
        }
    printf("\n--------Menores custos e rotas ---------");
	printf("\nRota com menor custo eh a rota %d sendo seu custo igual a %d", melhorRotaCusto+1, menorCusto);
	printf("\nRota com o menor numero de vertice eh a rota %d dispondo de %d vertices\n", melhorRotaSalto+1, menorSalto);
	printf("\n--------Informe a opcao desejada--------- \n1 - Menor custo\n2 - Menor numero de vertices ");
	scanf("%d", &opcao);

	printf("\n--------Melhor Rota - Dijkstra--------\n");
	if(opcao == 1)
        printf("->Siga pela rota %d para obter o menor custo ate o seu destino\n\n", melhorRotaCusto+1);
    else if(opcao == 2)
        printf("->Siga a rota %d para obter o menor numero de vertices ate o seu destino\n\n", melhorRotaSalto+1);
    else
        printf("Opcao invalida!\n\n");
    //menorCaminho(g, origem, destino, a);
	mostraCaminho(a, G->aresta);
}

/*Funcao chamada na main para imprimir as rotas*/
void caminhos(Grafo G, int origem, int destino){
	int *a = malloc(G->aresta * sizeof(int));
	Rotas = malloc(G->vertice * G->vertice * sizeof(struct caminho));
	qtdRotas = 0;

	inicializaCaminho(a, G->aresta);
	printf("\n-------------Todas as rotas-------------\n");
	mostraRotas(G, origem, destino, a, 0);
}

/*Recebe a aresta de origem e destino, e chama as demais funções com o intuito de encontrar os caminhos e custos*/
void inicializa(Grafo G){
    int origem, destino, aux;
    printf("\nInsira o ponto de partida e o destino final: ");
    scanf("%d%d", &origem, &destino);

    caminhos(G, origem, destino);
    menorCusto(G, origem, destino);
}
