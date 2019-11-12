//Sabemos que a busca em largura dá o menor caminho entre um vértice de partida para todos os demais no grafo
//O caminho é medido em número de arestas, ou seja, ignora os pesos que estas tem.
//Embora útil para resolver vários problemas, o peso nas arestas é crucial quando queremos achar uma rota mais curta entre dois pontos.
//Nesse caso usamos o Algoritmo de Dijkstra, pois ele calcula o caminho mais curto em termos do peso total das arestas, entre o vértice inical e os demais.
//Esse peso total das arestas é a soma dos pesos de todas as arestas que compõem o caminho.

//Funcionamento
//Para cada vértice do grafo, temos um atributo que é um limite superior para o peso do caminho mais curto do nó inicial até o vértice,
//ou seja, uma estimativa do caminho mais curto, começando inicialmente em INFINITO
//Armazenamos o vértice predecessor nesse caminho mais curto, para sabermos não só a distância, mas qual o caminho percorrido até o objetivo.

//Funcionamento resumido
//Inicializar o grafo com a distância inicial = 0, a distância dos vértices = INF; para todo vértice diferente do inicial, e o predecessor do vértice = -1.
//Faça todos os vértices do grafo, inclusive o inicial serem abertos (onde não se sabe a distância precisa, ou seja, não foi visitado).
//Equanto tiver vértices em aberto, escolha um cuja estimativa seja a menor dentre os outros abertos (inicialmente sendo o vértice inicial),
//Feche o nó(Marcar como visitado, sendo ele o menor caminho, somente se já conhecemos a distância deste nó até o inicial)
//Relaxar as arestas para todo nó aberto adjacente a ele (definir a distância total até este nó, ou seja, a somatória do vértice atual + distância do vértice adjacente)

#include <limits.h> // para utilizar o INT_MAX (maior inteiro possível)
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>  //para utilizar booleans

		int main(){
		/*  GRAFO *gr = criaGrafo(6);
			
			Aresta(gr, 0, 1, 10);
			Aresta(gr, 0, 2, 5);
			Aresta(gr, 2, 1, 3);
			Aresta(gr, 1, 3, 1);
			Aresta(gr, 2, 3, 8);
			Aresta(gr, 2, 4, 2);
			Aresta(gr, 4, 5, 6);
			Aresta(gr, 3, 5, 4);
			Aresta(gr, 3, 4, 4); */
			
			int *r = dijkstra(gr, 0);
			
			int i;
			for(i=0;i<gr->vertices;i++){
				printf("Distancia(v0 -> v%d = %d\n)",i,r[i]);
			}
			
			
		}

void inicialiaGrafo(GRAFO *g, int *d, int *p, int s){
	int v;
	for(v=0;v<g->vertices;v++){
		d[v] = INT_MAX/2; //Divide por dois pois, a soma do maior inteiro possível + 1 fica um valor negativo.
		p[v] = -1;  //Predecessor
	}
	d[s] = 0; //Distância do incial
}

void distTotal(GRAFO *g, int *d, int *p, int u, int v){
	ADJACENCIA *ad = g->adj[u].cab;  //Cabeçalho da lista de adjacência de u
	while (ad && ad->vertice != v) { //busca do vértice v
	ad = ad->prox;
	if(ad) {                        //relaxamento da aresta(u,v) e atualização da estimativa e do predecessor
		if(d[v] > d[u] + ad->peso){
			d[v] = d[u] + ad->peso;
			p[v] = u;
		}
	}
	}
}
	
	int *dijkstra(GRAFO *g, int s){
		int *d = (int *)malloc(g->vertices*sizeof(int));  //Alocando memória pro arranjo de distâcias
		int p[g->vertices];                              //Aloco um arranjo para os predecessores
		bool aberto[g->vertices];
		inicializaGrafo(g,d,p,s);
		
		int i;
		for(i=0;i<g->vertices;i++)   {                   //Inicializo meu arranjo de abertos como true, pois todos estão abertos
			aberto[i] = true;
			
			while(existeAberto(g,aberto)) {             //Enquanto existir nó aberto, verifico qual deles tem a menor distância estimada e fecho.
				int u = menorDist(g,aberto,d);
				aberto[u] = false;
				
				ADJACENCIA *ad = g->adj[u].cab;
				while(ad) {
					distTotal(g,d,p,u,ad->vertice);
					ad= ad->prox
				}
			}
		}
			return (d);
	}
	
	bool existeAberto(GRAFO *g, int *aberto){
		int i;
		for(i=0;i<g->vertices;i++){
		if(aberto[i]) return (true);}
		return(false);
	}
	
	int menorDist(GRAFO *g, int *aberto, int *d){
		int i;
		for(i=0;i<g->vertices;i++){
			if(aberto[i]) {
			break;}
			if(i==g->vertices){
			 return(-1);}
			int menor = i;
			for(i=menor+1; i<g->vertices;i++){
			if(aberto[i] && (d[menor]>d[i])){
			menor = i;
			}}
			return(menor);
		}
}
