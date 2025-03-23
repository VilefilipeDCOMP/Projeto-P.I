#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include <time.h>

int salvaArquivo();
void personagem();

int main(int argc, char **argv){
    char newFile[100], initFile[100], dimensao[30] ;
    int modo, x, y;
	
	// Armazena o arquivo
    for (int i=0; i<argc; i++)
    	strcpy(initFile,argv[i]);
    
    //Lê a primeira linha do arquivo para determinar as dimensoes do labirinto
    FILE* teste = fopen(initFile, "r");
    fgets(dimensao, sizeof(dimensao), teste);
    sscanf(dimensao, "%d %d", &x,&y);
	char labirinto[x][y];
	
	//Atribui cada elemento do arquivo a um char [x][y] que pertence ao labirinto
	for (int i = 0; i < x; i++) {
        for (int j = 0; j < y; j++) {
			fscanf(teste, " %c", &labirinto[i][j]);
        }
        }
	fclose(teste);
	
	//Imprime o labirinto na tela
	for (int i = 0; i < x; i++) {
        for (int j = 0; j < y; j++) {
            printf("%c ", labirinto[i][j]);
        }
        printf("\n");
    }
	
    printf("Qual acao deseja realizar?\n[1] Tentar resolver uma vez.\n[2] Tentar resolver ate conseguir.\n[3] Salvar a resolucao.\n[4] Sair.\n\nDigite o numero que corresponde a sua escolha: ");
    scanf("%d", &modo); 
    switch (modo){
    case 1:
        
        break;

    case 2:

        break;
    
    case 3:
        system("clear"); //em linux é "clear" e em windows "cls"
        salvaArquivo(newFile, x, y, labirinto);
        
        break;

    case 4:
        
        break;
    }
    return 0;
}

int salvaArquivo(char nome[100], int x, int y, char matriz[x][y]){
	int i,j;
	printf("Digite um nome para o arquivo: ");
    getchar();
    fgets(nome, 95,stdin);
    nome[strcspn(nome, "\n")] = 0;
        
    FILE* teste = fopen(strcat(nome, ".txt"), "w");
    fprintf(teste, "%d %d\n",x,y);
    for (i = 0; i < x; i++) {
		for (j = 0; j < y; j++) {
			fputc(matriz[i][j], teste);
            fprintf(teste, " ");
        }
        if(i < y-1){
			fprintf(teste, "\n");
		}
	}    
    fclose(teste);
    return 0;
	}

//int pos_x, pos_y;
//personagem(&pos_x, &pos_y, .....)
//Retorna a posição representado por '@'
//EM DESENVOLVIMENTO
/*
void personagem(int *a, int *b, int x, int y, char matriz[x][y]){
	int i,j;
	int cord[2]; 
	for(i=0;i<x;i++){
		for(j=0;j<y;j++){
			if(matriz[i][j] == ' @'){
				a* = i;
				b* = j;
				break;
			}
		}
	}
}
*/

//Feature que movimenta o personagem '@' pelo labirinto
//EM DESENVOLVIMENTO
int movimentando(char player, int x, int y, char matriz[x][y]){
	int posicao;
	char s1 = matriz[x-1][y], s2 = matriz[x+1][y], s3 = matriz[x][y-1], s4 = matriz[x][y+1]; 
	scanf("%d", &posicao); 
	return 0;
	}

//EM DESENVOLVIMENTO
//Verifica se um determinado espaço é restrito, se sim retorna 1(true), caso contrário retorna 0(false)	
int blockedArea (char elemento, int x, int y, int i, int j){ // (x,y) são os limites do labirinto, (i,j) são a posição atual do objeto
	
	if(elemento == '#' || elemento == '*' || i > x-1 || i < 0 || j > y-1 || j < 0){
		return 1;
	}
	else {
		return 0;
	}
	}
