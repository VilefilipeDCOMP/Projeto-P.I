#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include <time.h>

//Cada elemento do labirinto é representado dessa maneira
typedef struct{ 
    char objeto;
    int power;
    int linha;
    int coluna;
}tElemento;

int salvaArquivo();
tElemento personagem();
int movimentando();

int main(int argc, char **argv){
    char newFile[100], initFile[100], dimensao[30];
    int modo, x, y;
	// Armazena o arquivo
	for (int i=0; i<argc; i++)
	   strcpy(initFile,argv[i]);
    
    //Lê a primeira linha do arquivo para determinar as dimensoes do labirinto
    FILE* teste = fopen(initFile, "r");
    fgets(dimensao, sizeof(dimensao), teste);
    sscanf(dimensao, "%d %d", &x,&y);
	tElemento labirinto[x][y];
	
	//Atribui cada elemento do arquivo a um tElemento [x][y] que pertence ao labirinto
	for (int i = 0; i < x; i++) {
        for (int j = 0; j < y; j++) {
			fscanf(teste, " %c", &labirinto[i][j].objeto);
			labirinto[i][j].linha = i;
			labirinto[i][j].coluna = j;
			if(labirinto[i][j].objeto == '@'){
				labirinto[i][j].power = 50;
			}
			else
				labirinto[i][j].power = 0;
        }
    }
	fclose(teste);
	
	//Imprime o labirinto na tela
	for (int i = 0; i < x; i++) {
        for (int j = 0; j < y; j++) {
            printf("%c ", labirinto[i][j].objeto);
        }
        printf("\n");
    }
	
    printf("Bem vindo ao labirinto do cirilo!\nQual acao deseja realizar?\n[1] Tentar resolver uma vez.\n[2] Tentar resolver ate conseguir.\n[3] Salvar a resolucao.\n[4] Sair.\n\nDigite o numero que corresponde a sua escolha: ");
    scanf("%d", &modo); 
    switch (modo){
    case 1:
        
        break;

    case 2:

        break;
    
    case 3:
        system("cls"); //em linux é "clear"
        salvaArquivo(newFile, x, y, labirinto);
        
        break;

    case 4:
        
        break;
    }
    return 0;
}

int salvaArquivo(char nome[100], int x, int y, tElemento matriz[x][y]){
	printf("Digite um nome para o arquivo: ");
        getchar();
        fgets(nome, 95,stdin);
        nome[strcspn(nome, "\n")] = 0;
        
        FILE* teste = fopen(strcat(nome, ".txt"), "w");
        fprintf(teste, "%d %d\n",x,y);
        for (int i = 0; i < x; i++) {
            for (int j = 0; j < y; j++) {
                fputc(matriz[i][j].objeto, teste);
                fprintf(teste, " ");
            }
            fprintf(teste, "\n");
        }    
        fclose(teste);
        return 0;
	}

//Retorna o personagem representado por '@'
tElemento personagem(int x, int y, tElemento matriz[x][y]){
	int i,j;
	for(i=0;i<x;i++){
		for(j=0;j<y;j++){
			if(matriz[i][j].objeto == '@')
				return matriz [i][j];
		}
	}
	return matriz[i][j];
	}

//Feature que movimenta o personagem '@' pelo labirinto
int movimentando(tElemento player, int x, int y, tElemento matriz[x][y]){
	int i = player.linha, j = player.coluna;
	tElemento s1 = matriz[i-1][j], s2 = matriz[i+1][j], s3 = matriz[i][j-1], s4 = matriz[i][j+1]; 
	
	//NÃO TERMINEI ESSA AQUI
	 
	return 0;
	}

//Verifica se um determinado espaço é restrito, se sim retorna 1(true), caso contrário retorna 0(false)	
int blockedArea (tElemento elemento){
	if(elemento.objeto == '#' || elemento.objeto == '*' || elemento.linha > 9 || elemento.linha < 0 || elemento.coluna > 9 || elemento.coluna < 0){
		return 1;
	}
	else {
		return 0;
	}
	}
