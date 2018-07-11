#include <stdio.h>
#include <stdlib.h> 
#include<time.h>
#define MAX 41
#define FUNDO 0
#define PAREDE 1
#define PORTA 2
#define CAMINHO 3

void zerosMatriz(char M[][MAX])
{
	int i, j;
	
	for(i=0;i<MAX;i++)
		for(j=0;j<MAX;j++)
		   M[i][j] = FUNDO;
	
	for(i=0;i<MAX;i = i + (MAX - 1))    //bordas horizontais
		for(j=0;j<MAX;j++)
		   M[i][j] = PAREDE;
	for(i=1;i<MAX;i++)                  //bordas verticais
		for(j=0;j<MAX;j = j + (MAX - 1))
		   M[i][j] = PAREDE;
		   
	for(i=0;i<MAX;i = i + (MAX - 1))    //porta
	{
		j = rand()%(MAX);
		while((j%2 != 1))
		  j = rand()%(MAX);
		M[i][j] = PORTA;
	}
}


void salvaMatriz(char M[][MAX])
{
	int i, j;
	FILE *arq;
	
	if((arq = fopen("Labirinto.ppm", "w")) != NULL)
	{
		fprintf(arq,"P3\n%i %i\n255\n",MAX,MAX);
		
		for(i = 0; i < MAX; i++)
		{
			for(j = 0; j < MAX;j++)
			{
				switch(M[i][j])
				{
					case FUNDO:
						fprintf(arq,"255 255 255 "); //espaço em branco no final pra não emendar os elementos
						break;
					case PAREDE:
						fprintf(arq," 34 139  34 ");
						break;
					case PORTA:
						fprintf(arq,"  0   0   0 ");
						break;
					case CAMINHO:
						fprintf(arq,"255 255   0 ");
						break;
					
				}
			}
			fprintf(arq,"\n");
		}
	}
	else
	   printf("Erro ao salvar o arquivo\n");
}

void Solucao(char M[][MAX])
{
	int i = 0, j = 0;
	
	while(M[i][j] != PORTA)  //acha o começo
	 j++;
	i++;
	
	while(M[i][j + 1] == FUNDO)
	  {
	  	M[i][j] = CAMINHO;
	  	j++;
		}  
	
}
void Divide(char M[][MAX], int direcao, int imin, int imax, int jmin, int jmax, char cond)
{
	int i = 0, j = 0;
	
	if(cond != PAREDE)
	{
		if(direcao == 1) //horizontal
		{
	        while(((i%2) == 1) || (i == 0) || i == imax || i > imax)
				i = rand()%(imax) + imin;
	
			for(j = jmin ; j < jmax; j++)
	  			M[i][j] = PAREDE;
	  
			j = 0;
			while((j%2 != 1) || j == 0 || j == jmax || j > jmax)
				j = rand()%(jmax) + jmin;
				
	  			M[i][j] = FUNDO;
	  			
	 				cond = M[i - 2][j];
	 				if(cond != PAREDE)
	 				Divide(M, (direcao + 1), imin, i, jmin, jmax, cond); //pra cima
	 			
	 				cond = M[i + 2][j];
	 				if(cond != PAREDE)
	 				Divide(M, (direcao + 1), i, imax, jmin, jmax, cond); //pra baixo

	  			
		}
		if(direcao == 2) //vertical
		{
	
			while((j%2 == 1) || j <= jmin || j == jmax || j > jmax)
				j = rand()%(jmax) + jmin;
				
				for(i = imin; i <= imax; i++)
	 				M[i][j] = PAREDE;
	 				
				i = 0;
				while((i%2 != 1) || i == 0 || i == imax || i > imax)
					i = rand()%(imax) + imin;
					
	 			M[i][j] = FUNDO;
	 			
	 			
	 				cond = M[i][j - 2];
//	 				if(cond != PAREDE)
//	 				Divide(M, (direcao - 1), imin, imax, jmin, j, cond); //esquerda
//	 			
//	 				cond = M[i][j + 2];
//	 				if(cond != PAREDE)
//	 				Divide(M, (direcao - 1), imin, imax, j, jmax, cond); //direita
		}
		return;
	}
	else
	 return;
}
void CriaLab(char M[][MAX])
{
	int i, j, jmax;
	
	//J E I SÃO SEMPRE PAR então parede em todas as pares e porta aleatória
	
	//FALTA POR O WHILE DE PAR E IMPAR NESSA FUNÇÃO 
	//A PORTA DEVE SER SEMPRE PAR
	
	j = rand()%(MAX - 1) + 1;
	while((j%2 == 1) || j == 0 || j == MAX )
	 j = rand()%(MAX - 1) + 1;
	
	for(i = 1; i < MAX; i++)
	 M[i][j] = PAREDE;
	 
	 i=0;
	while((i%2) != 1) 
	i = rand()%(MAX - 3) + 1;
	
	M[i][j] = FUNDO;

	Divide(M, 1, 0, (MAX - 1), 0, j, (M[i][j] - 2)); //esquerda
	Divide(M, 1, 0, (MAX - 1), j, (MAX - 1), (M[i][j] + 2));  //direita
	
}


int main ()
{
	srand(time(0));
	char M[MAX][MAX];
	
	
	zerosMatriz(M);
	CriaLab(M);
	salvaMatriz(M);
	
	
	return 0;
}
