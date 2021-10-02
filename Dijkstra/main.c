#include "Dijkstra.h"

int main(){
    int caso, aresta = 7;
	Grafo g = constroiGrafo(aresta);

	do{
	    printf("--------------------------------------------------------------");
        printf("\n----ALGORITMO DE DIJKSTRA - PROBLEMA DO CAMINHO MAIS CURTO----");
        printf("\n-------CONSULTE O PDF 'MAPAS' PARA TER ACESSO AOS MAPAS-------");
        printf("\n--------------------------------------------------------------");
        printf("\n");
        printf("\nSELECIONE QUAL DOS MAPAS DESEJA SEGUIR\n");
        printf("\n1 - ZONA SUL\n");
        printf("\n2 - ZONA NORTE\n");
        printf("\n3 - MAPA DE ESTADOS\n");
        printf("\n0 - ENCERRAR PROGRAMA\n");
        scanf("%d", &caso);
        printf("\n");

        switch(caso){
        case 0:
            printf("SAINDO..\n");
            break;

        case 1:
            printf("GRAFO ZONA SUL\n");
            insereVertice(g, 1, 2, 2);
            insereVertice(g, 1, 4, 3);
            insereVertice(g, 2, 5, 2);
            insereVertice(g, 2, 3, 4);
            insereVertice(g, 3, 4, 1);
            insereVertice(g, 3, 6, 1);

            imprimeGrafo(g);
            inicializa(g);
            break;

        case 2:
            printf("GRAFO ZONA NORTE\n");
            insereVertice(g,4,6,3);
            insereVertice(g,4,3,1);
            insereVertice(g,6,3,1);
            insereVertice(g,6,2,2);
            insereVertice(g,3,2,5);
            insereVertice(g,3,1,4);
            insereVertice(g,1,5,1);
            insereVertice(g,4,1,2);
            insereVertice(g,2,1,2);

            imprimeGrafo(g);
            inicializa(g);
            break;

        case 3:
            printf("GRAFO DE ESTADOS\n");
            insereVertice(g,1,3,1);
            insereVertice(g,1,2,4);
            insereVertice(g,1,4,3);
            insereVertice(g,1,5,2);
            insereVertice(g,2,3,2);
            insereVertice(g,2,4,5);
            insereVertice(g,2,6,3);
            insereVertice(g,3,4,2);
            insereVertice(g,4,5,3);
            insereVertice(g,4,6,1);

            imprimeGrafo(g);
            inicializa(g);
            break;

        default:
            printf("OPCAO INDISPONIVEL, TENTE NOVAMENTE");
        }
	}while( caso != 0);

	return 0;
}
