#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include <time.h>

<<<<<<< HEAD
int salvaArquivo();
char personagem();

int main(){
    char newFile[100], initFile[100], dimensao[30] ;
    int modo, x, y;
	printf("Digite o nome do arquivo do labirinto que deseja abrir(com o formato .txt): ");
	fgets(initFile, sizeof(initFile),stdin);
    initFile[strcspn(initFile, "\n")] = 0;
=======
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
>>>>>>> 59f491e19d19f88f51d83bddb56c9080b910e555
    
    //Lê a primeira linha do arquivo para determinar as dimensoes do labirinto
    FILE* teste = fopen(initFile, "r");
    fgets(dimensao, sizeof(dimensao), teste);
    sscanf(dimensao, "%d %d", &x,&y);
<<<<<<< HEAD
	char labirinto[x][y];
	
	//Atribui cada elemento do arquivo a um char [x][y] que pertence ao labirinto
	for (int i = 0; i < x; i++) {
        for (int j = 0; j < y; j++) {
			fscanf(teste, " %c", &labirinto[i][j]);
=======
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
>>>>>>> 59f491e19d19f88f51d83bddb56c9080b910e555
        }
    }
	fclose(teste);
	
	//Imprime o labirinto na tela
	for (int i = 0; i < x; i++) {
        for (int j = 0; j < y; j++) {
<<<<<<< HEAD
            printf("%c ", labirinto[i][j]);
=======
            printf("%c ", labirinto[i][j].objeto);
>>>>>>> 59f491e19d19f88f51d83bddb56c9080b910e555
        }
        printf("\n");
    }
	
<<<<<<< HEAD
    printf("Qual acao deseja realizar?\n[1] Tentar resolver uma vez.\n[2] Tentar resolver ate conseguir.\n[3] Salvar a resolucao.\n[4] Sair.\n\nDigite o numero que corresponde a sua escolha: ");
    scanf("%d", &modo); 
    switch (modo){
    case 1:
=======
    printf("Bem vindo ao labirinto do cirilo!\nQual acao deseja realizar?\n[1] Tentar resolver uma vez.\n[2] Tentar resolver ate conseguir.\n[3] Salvar a resolucao.\n[4] Sair.\n\nDigite o numero que corresponde a sua escolha: ");
    scanf("%d", &modo); 
    switch (modo){
    case 1:
        printf("Em breve\n");
>>>>>>> 59f491e19d19f88f51d83bddb56c9080b910e555
        
        break;

    case 2:
<<<<<<< HEAD

        break;
    
    case 3:
        system("clear"); //em linux é "clear" e em windows "cls"
=======
        printf("Em breve\n");
        break;
    
    case 3:
        system("cls"); //em Windows
        system("clear"); //em Linux
>>>>>>> 59f491e19d19f88f51d83bddb56c9080b910e555
        salvaArquivo(newFile, x, y, labirinto);
        
        break;

    case 4:
        
        break;
    }
    return 0;
}

<<<<<<< HEAD
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
//Retorna a posição do elemento da matriz colocado como parâmetro
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
	//switch posicao:
	
=======
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
>>>>>>> 59f491e19d19f88f51d83bddb56c9080b910e555
	 
	return 0;
	}

//Verifica se um determinado espaço é restrito, se sim retorna 1(true), caso contrário retorna 0(false)	
<<<<<<< HEAD
//EM DESENVOLVIMENTO
int blockedArea (char elemento, int x, int y, int i, int j){ // (x,y) são os limites do labirinto, (i,j) são a posição atual do objeto
	
	if(elemento == '#' || elemento == '*' || i > x-1 || i < 0 || j > y-1 || j < 0){
=======
int blockedArea (tElemento elemento){
	if(elemento.objeto == '#' || elemento.objeto == '*' || elemento.linha > 9 || elemento.linha < 0 || elemento.coluna > 9 || elemento.coluna < 0){
>>>>>>> 59f491e19d19f88f51d83bddb56c9080b910e555
		return 1;
	}
	else {
		return 0;
	}
<<<<<<< HEAD
	}
=======
	}
>>>>>>> 59f491e19d19f88f51d83bddb56c9080b910e555
