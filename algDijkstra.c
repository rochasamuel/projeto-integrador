//Sabemos que a busca em largura d� o menor caminho entre um v�rtice de partida para todos os demais no grafo
//O caminho � medido em n�mero de arestas, ou seja, ignora os pesos que estas tem.
//Embora �til para resolver v�rios problemas, o peso nas arestas � crucial quando queremos achar uma rota mais curta entre dois pontos.
//Nesse caso usamos o Algoritmo de Dijkstra, pois ele calcula o caminho mais curto em termos do peso total das arestas, entre o v�rtice inical e os demais.
//Esse peso total das arestas � a soma dos pesos de todas as arestas que comp�em o caminho.

//Funcionamento
//Para cada v�rtice do grafo, temos um atributo que � um limite superior para o peso do caminho mais curto do n� inicial at� o v�rtice,
//ou seja, uma estimativa do caminho mais curto, come�ando inicialmente em INFINITO
//Armazenamos o v�rtice predecessor nesse caminho mais curto, para sabermos n�o s� a dist�ncia, mas qual o caminho percorrido at� o objetivo.

//Funcionamento resumido
//Inicializar o grafo com a dist�ncia inicial = 0, a dist�ncia dos v�rtices = INF; para todo v�rtice diferente do inicial, e o predecessor do v�rtice = -1.
//Fa�a todos os v�rtices do grafo, inclusive o inicial serem abertos (onde n�o se sabe a dist�ncia precisa, ou seja, n�o foi visitado).
//Equanto tiver v�rtices em aberto, escolha um cuja estimativa seja a menor dentre os outros abertos (inicialmente sendo o v�rtice inicial),
//Feche o n�(Marcar como visitado, sendo ele o menor caminho, somente se j� conhecemos a dist�ncia deste n� at� o inicial)
//Relaxar as arestas para todo n� aberto adjacente a ele (definir a dist�ncia total at� este n�, ou seja, a somat�ria do v�rtice atual + dist�ncia do v�rtice adjacente)

#include <limits.h> // para utilizar o INT_MAX (maior inteiro poss�vel)
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
	for(v=0;v<G->vertices;v++){
		d[v] = INT_MAX/2; //Divide por dois pois, a soma do maior inteiro poss�vel + 1 fica um valor negativo.
		p[v] = -1;  //Predecessor
	}
	d[s] = 0; //Dist�ncia do incial
}

void distTotal(GRAFO *g, int *d, int *p, int u, int v){
	ADJACENCIA *ad = G->adj[u].cab;  //Cabe�alho da lista de adjac�ncia de u
	while (ad && ad->vertice != v) { //busca do v�rtice v
	ad = ad->prox;
	if(ad) {                        //relaxamento da aresta(u,v) e atualiza��o da estimativa e do predecessor
		if(d[v] > d[u] + ad->peso){
			d[v] = d[u] + ad->peso;
			p[v] = u;
		}
	}
	}
}
	
	int *dijkstra(GRAFO *g, int s){
		int *d = (int *)malloc(G->vertices*sizeof(int));  //Alocando mem�ria pro arranjo de dist�cias
		int p[G->vertices];                              //Aloco um arranjo para os predecessores
		bool aberto[G->vertices];
		inicializaGrafo(g,d,p,s);
		
		int i;
		for(i=0;i<G->vertices;i++)   {                   //Inicializo meu arranjo de abertos como true, pois todos est�o abertos
			aberto[i] = true;
			
			while(existeAberto(g,aberto)) {             //Enquanto existir n� aberto, verifico qual deles tem a menor dist�ncia estimada e fecho.
				int u = menorDist(g,aberto,d);
				aberto[u] = false;
				
				ADJACENCIA *ad = G->adj[u].cab;
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
		for(i=0;i<G->vertices;i++){
		if(aberto[i]) return (true);}
		return(false);
	}
	
	int menorDist(GRAFO *g, int *aberto, int *d){
		int i;
		for(i=0;i<G->vertices;i++){
			if(aberto[i]) {
			break;}
			if(i==G->vertices){
			 return(-1);}
			int menor = i;
			for(i=menor+1; i<G->vertices;i++){
			if(aberto[i] && (d[menor]>d[i])){
			menor = i;
			}}
			return(menor);
		}
}
