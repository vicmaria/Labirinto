#include <stdio.h>
#include <stdlib.h> 
#include<time.h>
#define MAX 41
#define TAM 100
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


void salvaMatriz(char M[][MAX], int n)
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
	
	
		if(direcao == 1) //horizontal
		{
			if(((imax - imin) >> 2) && ((jmax - jmin) >> 2))
			{
				if(cond != PAREDE)
	        {
	        
	        	while(((i%2) == 1) || (i == 0) || i <= imin || i >= imax)
	        		i = rand()%(imax - imin) + imin;
	
			for(j = jmin ; j < jmax; j++)
	  			M[i][j] = PAREDE;
	  
		
			while((j%2 == 0) || j == 0 || j <= jmin || j >= jmax)
				j = rand()%(jmax - jmin) + jmin;

	  			M[i][j] = FUNDO;
	  			

	 				if(cond != PAREDE)
	 				Divide(M, (direcao + 1), imin, i, jmin, jmax, cond); //pra cima

	 				if(cond != PAREDE)
	 				Divide(M, (direcao + 1), i, imax, jmin, jmax, cond); //pra baixo
			}
			else
			 return;
			}
			else
			 return;
	  			
		}
		if(direcao == 2) //vertical
		{
			if(((imax - imin) >> 2) && ((jmax - jmin) >> 2))
			{
				if(cond != PAREDE)
			{
				while((j%2 != 0) || j == 0 || j <= jmin || j >= jmax)
						j = rand()%(jmax - jmin) + jmin;
				
				for(i = imin; i <= imax; i++)
	 				M[i][j] = PAREDE;

				while((i%2 != 1) || i == 0 || i <= imin || i >= imax)
				{
					i = rand()%(imax - imin) + imin ;

				}
	
	 			M[i][j] = FUNDO;
	 			
	 			
	 			cond = M[i][j - 2];
	 				if(cond != PAREDE)
	 				Divide(M, (direcao - 1), imin, imax, jmin, j, cond); //esquerda
//	 			
						
				cond = M[i][j + 2];
	 				cond = M[i][j + 2];
	 				if(cond != PAREDE)
	 				Divide(M, (direcao - 1), imin, imax, j, jmax, cond); //direita
			}
			else
			return;
	
			}
			else
			 return;
		
		
		}
		return;
	

}
void CriaLab(char M[][MAX])
{
	int i, j, jmax;
	
	
	j = rand()%(MAX - 1) + 1;
	while((j%2 == 1) || j == 0 || j == MAX )
	 j = rand()%(MAX - 1) + 1;
	
	for(i = 1; i < MAX; i++)
	 M[i][j] = PAREDE;
	 
	i = 2;
	
	while((i%2 != 1) || i == 0 || i <= 3 || i >= MAX)
		i = rand()%(MAX - 3) + 3 ;

	
	M[i][j] = FUNDO;

	Divide(M, 1, 0, (MAX - 1), 0, j, (M[i][j - 2])); //esquerda
	Divide(M, 1, 0, (MAX - 1), j, (MAX - 1), (M[i][j + 2]));  //direita
	
}


int main ()
{
	srand(time(0));
	char M[MAX][MAX], op;
	int n = 0 ;
	

	do
	{
		system("cls");
		printf("[1] - Gerar labirinto\n");
		printf("[2] - Gerar solucao do labirinto atual\n");
		printf("[3] - Apagar todos os labirintos\n");
		printf("[4] - Sair do programa\n");
		printf("--------------------------------------------\nLabirintos gerados: %d\n", n);
		printf("--------------------------------------------\nOpcao: ");
		fflush(stdin);  //limpar buffer do teclado
		op = getchar();                                 //getche( ); //é o getch que mostra na tela o que colocou e pega só um caracter
		
		switch(op)
		{
			case '1':
				zerosMatriz(M);
				CriaLab(M);
				n++;
				salvaMatriz(M, n);
				break;
			case'2':
				
				break;
			case '3':
			
				break;
			
		}
		
	}while(op != '4');
	

	
	
	return 0;
}
