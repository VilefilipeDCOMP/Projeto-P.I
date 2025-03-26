#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include <time.h>

typedef struct{
	
	int N;
	int S;
	int L;
	int O;
	int power;
    int PosI;
    int PosJ;
	
} atributos;

atributos player;

long int randomizer;
int acc = 0;

//EM DESENVOLVIMENTO
//Verifica se um determinado espaço é permitido, se sim retorna 1(true), caso contrário retorna 0(false)	
int blockedArea (char elemento, int x, int y, int i, int j){ 
    
    if(elemento == '#' || elemento == '*' || i > x-1 || i < 0 || j > y-1 || j < 0){
        return 0;
    }
    else {
        return 1;
    }
}
int random();
int salvaArquivo();
void posInicial();
int verificandoArea();
void printlab();
void mov_aleatoria();


	

int main(int argc, char **argv){
    char newFile[100], initFile[100], dimensao[30];
    int modo, x, y;
    randomizer = time(NULL);
	
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

	printlab(x,y,labirinto);
    printf("Qual acao deseja realizar?\n[1] Tentar resolver uma vez.\n[2] Tentar resolver ate conseguir.\n[3] Salvar a resolucao.\n[4] Sair.\n\nDigite o numero que corresponde a sua escolha: ");
    scanf("%d", &modo); 
    switch (modo){
    case 1:
        // printf("Em breve\n");
        posInicial(x,y,labirinto);
        printf("I=%i  J=%i\n",player.PosI, player.PosJ);
        mov_aleatoria(x, y, labirinto);
        mov_aleatoria(x, y, labirinto);
        mov_aleatoria(x, y, labirinto);
        mov_aleatoria(x, y, labirinto);
        mov_aleatoria(x, y, labirinto);
        mov_aleatoria(x, y, labirinto);
        printf("\n");
        printlab(x,y,labirinto);
        //printf("Baixo: %c", baixo);
        break;

    case 2:
        printf("Em breve\n");
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
	printf("Digite um nome para o arquivo (Sem o '.txt'): ");
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
        //char s1 = matriz[posI-1][posJ], s2 = matriz[posI+1][pos
        if(i < y-1){
			fprintf(teste, "\n");
		}
	}    
    fclose(teste);
    return 0;
	}

//int pos_x, pos_y;
//posInicial(&pos_x, &pos_y, .....)
//Retorna a posição representado por '@'
//EM DESENVOLVIMENTO

void posInicial(int x, int y, char matriz[x][y]){
	int i;
    int j;
    for(i=0;i<x;i++){
		for(j=0;j<y;j++){
			if(matriz[i][j] == '@'){
				player.PosI = i;
				player.PosJ = j;
				break;
			}
		}
	}
}


int verificandoArea(int x, int y, char matriz[x][y]){
	char N = matriz[player.PosI-1][player.PosJ], S = matriz[player.PosI+1][player.PosJ], O = matriz[player.PosI][player.PosJ-1], L = matriz[player.PosI][player.PosJ+1];
    
    player.N = blockedArea(N, x, y, player.PosI-1, player.PosJ);
    player.S = blockedArea(S, x, y, player.PosI+1, player.PosJ);
    player.L = blockedArea(L, x, y, player.PosI, player.PosJ + 1);
    player.O = blockedArea(O, x, y, player.PosI, player.PosJ - 1);


    printf("N %d S %d L %d O %d\n", player.N,player.S,player.L,player.O);
}

//Feature que movimenta o posInicial '@' pelo labirinto
//EM DESENVOLVIMENTO


void mov_aleatoria(int x, int y, char matriz[x][y]){ // retorna a próx posição
    acc ++;
	char N = matriz[player.PosI-1][player.PosJ], S = matriz[player.PosI+1][player.PosJ], O = matriz[player.PosI][player.PosJ-1], L = matriz[player.PosI][player.PosJ+1];
    
    verificandoArea(x, y, matriz);
    
    int r = random(4);

    int psI = player.PosI;
    int psJ = player.PosJ;

    if (matriz[psI][psJ] != '@')
        matriz[psI][psJ] = '*';

    if (r == 0 && player.N == 1){
        printf("%c", N);
        printf("\n%d",r);
        player.PosI --;
        printf("\nI=%i  J=%i\n %i",player.PosI, player.PosJ,acc);
    }
    else if (r == 1 && player.S == 1){
        printf("%c", S);
        printf("\n%d",r);
        player.PosI ++;
        printf("\nI=%i  J=%i\n %i",player.PosI, player.PosJ,acc);
    }
    else if (r == 2 && player.O == 1){
        printf("%c", O);
        printf("\n%d",r);
        player.PosJ --;
        printf("\nI=%i  J=%i\n %i",player.PosI, player.PosJ,acc);
    }
    else if (r == 3 && player.L == 1){
        printf("%c", L);
        printf("\n%d",r);
        player.PosJ ++;
        printf("\nI=%i  J=%i\n%i",player.PosI, player.PosJ,acc);
    }
    else if(player.N == 0 && player.S == 0 && player.L == 0 && player.O == 0){
        printf("Preso no Labirinto");
    }
    else {mov_aleatoria(x, y, matriz); }

    


    
}

int random(int x){
    randomizer ++;
    srand(randomizer);

    int r = rand() % x;
    return r;
}


// int mov(int x, int y, char matriz[x][y]) {
    //     printf("%c")
    //     return 0;
    // }


void printlab(int x, int y, char labirinto[x][y]){
    for (int i = 0; i < x; i++) {
        for (int j = 0; j < y; j++) {
            printf("%c ", labirinto[i][j]);
        }
        if (i < y){
        printf("\n");
    }
    } 
}
