
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define VM 1
#define VD 2
#define AM 3
#define AZ 4
#define RX 5


//Definicao do tipo struct  -------------------------------------------------------------
struct sNo {
	int estacao;
	int tmp_acumulado;
	char via;
};
typedef struct sNo sNo;

struct sLinha {
	int tempo;
	char linha;
};
typedef struct sLinha sLinha;


//Funcoes -------------------------------------------------------------------------------
void SelectionSort(sNo *A[], int qtd_no);


int main(){
	int i,j,k;

	//Coleta dos dados de localizacao do usuario ----------------------------------------
	int origem, destino;
	printf("Estacao de origem:\n");
	scanf("%d", &origem);
	printf("Estacao de destino:\n");
	scanf("%d", &destino);
	if (origem > 20 || destino > 20){
		printf("Localizacao invalida\n");
		return 0;
	}


	//Criacao da matriz ---------------------------------------------------
								//	1			2			3			4			5			6			7			8			9			10			11			12			13			14			15			16			17			18			19			20
	sLinha matriz_adj [20][20] = {	0	,0		,16	,VM		,0	,0		,0	,0		,0	,0		,0	,0		,0	,0		,0	,0		,0	,0		,0	,0		,0	,0		,0	,0		,0	,0		,0	,0		,0	,0		,0	,0		,0	,0		,0	,0		,0	,0		,0	,0	,
									16	,VM		,0	,0		,14	,VM		,0	,0		,0	,0		,0	,0		,0	,0		,8	,AM		,0	,0		,0	,0		,0	,0		,0	,0		,0	,0		,0	,0		,7	,AM		,0	,0		,0	,0		,0	,0		,0	,0		,0	,0	,
									0	,0		,14	,VM		,0	,0		,12	,VM		,0	,0		,0	,0		,0	,0		,0	,0		,0	,0		,0	,0		,0	,0		,0	,0		,13	,AM		,0	,0		,0	,0		,11	,RX		,0	,0		,0	,0		,0	,0		,0	,0	,
									0	,0		,0	,0		,12	,VM		,0	,0		,12	,VM		,0	,0		,0	,0		,0	,0		,0	,0		,0	,0		,0	,0		,0	,0		,0	,0		,0	,0		,0	,0		,0	,0		,0	,0		,0	,0		,0	,0		,0	,0	,
									0	,0		,0	,0		,0	,0		,12	,VM		,0	,0		,14	,VM		,0	,0		,0	,0		,0	,0		,0	,0		,0	,0		,0	,0		,0	,0		,9	,AZ		,0	,0		,0	,0		,10	,AZ		,0	,0		,0	,0		,0	,0	,
									0	,0		,0	,0		,0	,0		,0	,0		,14	,VM		,0	,0		,0	,0		,0	,0		,0	,0		,0	,0		,15	,VD		,0	,0		,0	,0		,0	,0		,0	,0		,0	,0		,0	,0		,0	,0		,0	,0		,0	,0	,
									0	,0		,0	,0		,0	,0		,0	,0		,0	,0		,0	,0		,0	,0		,15	,VD		,0	,0		,0	,0		,0	,0		,0	,0		,0	,0		,0	,0		,0	,0		,0	,0		,0	,0		,0	,0		,0	,0		,0	,0	,
									0	,0		,8 	,AM		,0	,0		,0	,0		,0	,0		,0	,0		,15	,VD		,0	,0		,11	,VD		,0	,0		,0	,0		,11	,AM		,0	,0		,0	,0		,0	,0		,0	,0		,0	,0		,0	,0		,0	,0		,0	,0	,
									0	,0		,0	,0		,0	,0		,0	,0		,0	,0		,0	,0		,0	,0		,11	,VD		,0	,0		,13	,VD		,0	,0		,17	,AZ		,7	,AZ		,0	,0		,0	,0		,0	,0		,0	,0		,0	,0		,0	,0		,0	,0	,
									0	,0		,0	,0		,0	,0		,0	,0		,0	,0		,0	,0		,0	,0		,0	,0		,13	,VD		,0	,0		,16	,VD		,0	,0		,11	,RX		,0	,0		,0	,0		,0	,0		,0	,0		,0	,0		,0	,0		,0	,0	,
									0	,0		,0	,0		,0	,0		,0	,0		,0	,0		,15	,VD		,0	,0		,0	,0		,0	,0		,16	,VD		,0	,0		,0	,0		,0	,0		,0	,0		,0	,0		,0	,0		,0	,0		,0	,0		,0	,0		,0	,0	,
									0	,0		,0	,0		,0	,0		,0	,0		,0	,0		,0	,0		,0	,0		,11	,AM		,17	,AZ		,0	,0		,0	,0		,0	,0		,0	,0		,0	,0		,0	,0		,0	,0		,0	,0		,0	,0		,0	,0		,0	,0	,
									0	,0		,0	,0		,13	,RX		,0	,0		,0	,0		,0	,0		,0	,0		,0	,0		,7	,AZ		,11	,RX		,0	,0		,0	,0		,0	,0		,9	,AZ		,0	,0		,0	,0		,0	,0		,0	,0		,0	,0		,0	,0	,
									0	,0		,0	,0		,0	,0		,0	,0		,9	,AZ		,0	,0		,0	,0		,0	,0		,0	,0		,0	,0		,0	,0		,0	,0		,9	,AZ		,0	,0		,0	,0		,0	,0		,0	,0		,0	,0		,0	,0		,0	,0	,
									0	,0		,7	,AM		,0	,0		,0	,0		,0	,0		,0	,0		,0	,0		,0	,0		,0	,0		,0	,0		,0	,0		,0	,0		,0	,0		,0	,0		,0	,0		,7	,AM		,0	,0		,0	,0		,0	,0		,0	,0	,
									0	,0		,0	,0		,11	,RX		,0	,0		,0	,0		,0	,0		,0	,0		,0	,0		,0	,0		,0	,0		,0	,0		,0	,0		,0	,0		,0	,0		,7	,AM		,0	,0		,12	,AM		,0	,0		,13	,RX		,0	,0	,
									0	,0		,0	,0		,0	,0		,0	,0		,10	,AZ		,0	,0		,0	,0		,0	,0		,0	,0		,0	,0		,0	,0		,0	,0		,0	,0		,0	,0		,0	,0		,12	,AM		,0	,0		,9	,AM		,0	,0		,0	,0	,
									0	,0		,0	,0		,0	,0		,0	,0		,0	,0		,0	,0		,0	,0		,0	,0		,0	,0		,0	,0		,0	,0		,0	,0		,0	,0		,0	,0		,0	,0		,0	,0		,9	,AM		,0	,0		,0	,0		,0	,0	,
									0	,0		,0	,0		,0	,0		,0	,0		,0	,0		,0	,0		,0	,0		,0	,0		,0	,0		,0	,0		,0	,0		,0	,0		,0	,0		,0	,0		,0	,0		,13	,RX		,0	,0		,0	,0		,0	,0		,12	,RX	,
									0	,0		,0	,0		,0	,0		,0	,0		,0	,0		,0	,0		,0	,0		,0	,0		,0	,0		,0	,0		,0	,0		,0	,0		,0	,0		,0	,0		,0	,0		,0	,0		,0	,0		,0	,0		,12	,RX		,0	,0	};

	//Criacao do vetor de nos -----------------------------------------------------------
	sNo No[20] = {	1	,99999	,0	,
					2	,99999	,0	,
					3	,99999	,0	,
					4	,99999	,0	,
					5	,99999	,0	,
					6	,99999	,0	,
					7	,99999	,0	,
					8	,99999	,0	,
					9	,99999	,0	,
					10	,99999	,0	,
					11	,99999	,0	,
					12	,99999	,0	,
					13	,99999	,0	,
					14	,99999	,0	,
					15	,99999	,0	,
					16	,99999	,0	,
					17	,99999	,0	,
					18	,99999	,0	,
					19	,99999	,0	,
					20	,99999	,0	};

	//Criacao de vetor de ponteiros para No ---------------------------------------------
	int qtd_pno = 20;

	sNo **pNo;
	pNo = calloc(qtd_pno, sizeof(sNo*));
	if(pNo == NULL){
		printf("Erro de memoria\n");
		exit(1);
	}

	for (i = 0; i < qtd_pno; i++){
		pNo[i] = &No[i];	
	}

	//Criacao da origem -----------------------------------------------------------------
	No[origem-1].tmp_acumulado = 0;
	
	//Loop com algoritmo de Dijkstra para encontrar melhor caminho ----------------------
	int est_atual = 0;

	SelectionSort(pNo, qtd_pno);
	est_atual = pNo[0]->estacao;

	while(est_atual != destino){

		for(i = 0; i < 20; i++){

			if (matriz_adj[est_atual-1][i].tempo){

				if (matriz_adj[est_atual-1][(No[est_atual-1].via) - 1].linha != matriz_adj[i][(est_atual) - 1].linha && est_atual != origem) j = (No[est_atual-1].tmp_acumulado) + (matriz_adj[est_atual-1][i].tempo) + 6;
				else j = (No[est_atual-1].tmp_acumulado) + (matriz_adj[est_atual-1][i].tempo);

				if(No[i].tmp_acumulado > j){

					No[i].tmp_acumulado = j;
					No[i].via = No[est_atual-1].estacao;
				}

			}

		}

		if(qtd_pno >= 1){
			for(i = 0; i <= qtd_pno-1; i++){
				pNo[i] = pNo[i+1];
			}
		}
				
		qtd_pno--;
		pNo = realloc(pNo,(sizeof(sNo*) * qtd_pno));

		if(qtd_pno > 1){
			SelectionSort(pNo, qtd_pno);
		}

		est_atual = pNo[0]->estacao;
	}

	//Imprimindo caminho para usuario ---------------------------------------------------
	int qtd_pts = 1;	
	int *caminho = calloc(qtd_pts, sizeof(int));
	caminho[0] = destino;

	est_atual = destino;
	while (est_atual != origem){
		qtd_pts++;
		est_atual = No[est_atual-1].via;
		caminho = realloc(caminho,(sizeof(int) * qtd_pts));
		caminho[qtd_pts-1] = est_atual;
	}

	switch(matriz_adj[caminho[qtd_pts-1]-1][caminho[(qtd_pts-1)-1]-1].linha){
		case 1:
			printf("Pegue a linha vermelha, ");
		break;
		case 2:
			printf("Pegue a linha verde, ");
		break;
		case 3:
			printf("Pegue a linha amarela, ");
		break;
		case 4:
			printf("Pegue a linha azul, ");
		break;
		case 5:
			printf("Pegue a linha roxa, ");
		break;
	}

	for (i = (qtd_pts-1), j = matriz_adj[caminho[i]-1][caminho[i-1]-1].linha; i > 0 ; i--){

		if (matriz_adj[caminho[i]-1][caminho[i-1]-1].linha != j){

			switch(matriz_adj[caminho[i]-1][caminho[i-1]-1].linha){
				case 1:
					printf("va ate a estacao %d, em seguida pegue a linha vermelha ", caminho[i]);
				break;
				case 2:
					printf("va ate a estacao %d, em seguida pegue a linha verde ", caminho[i]);
				break;
				case 3:
					printf("va ate a estacao %d, em seguida pegue a linha amarela ", caminho[i]);
				break;
				case 4:
					printf("va ate a estacao %d, em seguida pegue a linha azul ", caminho[i]);
				break;
				case 5:
					printf("va ate a estacao %d, em seguida pegue a linha roxa ", caminho[i]);
				break;
			}

			j = matriz_adj[caminho[i]-1][caminho[i-1]-1].linha;

		}else{
			j = matriz_adj[caminho[i]-1][caminho[i-1]-1].linha;
		}
	}

	printf("ate a estacao %d, entao chegara ao seu destino\n", caminho[0]);



return 0;
}

//Funcao de organizacao por tmp_acumulado -----------------------------------------------
void SelectionSort(sNo *A[], int qtd_pno){

	sNo *temp;
	int i, j, Imin;

	for(i = 0; i < qtd_pno - 1; i++){
		Imin = i;
		for(j = i + 1; j < qtd_pno; j++){

			if((A[j]->tmp_acumulado) < (A[Imin]->tmp_acumulado)){
				Imin = j;
			}
		}

		temp = A[Imin];
		A[Imin] = A[i];
		A[i] = temp;
	}
}
