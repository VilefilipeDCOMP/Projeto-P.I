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
    int PosI;
    int PosJ;
    int power;
    int endI;
    int endJ;
} atributos;

atributos player;


long int aleatorioizer;
int acc = 0;


void printlab();
int salvaArquivo();
void posicao(char objeto, int x, int y, char matriz[x][y]);
int blockedArea(char elemento, int x, int y, int i, int j);
int verificandoArea();
int aleatorio();
void rastroPlayer();
void batalha();
void mov_aleatoria();

int main(int argc, char **argv){
    char newFile[100], initFile[100], dimensao[30];
    int modo, x, y, win;
    char resp;
    player.power = 50;

    // Cria a semente para o número aleatório 
    aleatorioizer = time(NULL);
    srand(aleatorioizer);

	// Armazena o arquivo
    for (int i=0; i<argc; i++)
    	strcpy(initFile,argv[i]);
    
    //Lê a primeira linha do arquivo para determinar as dimensoes do labirinto
    FILE* teste = fopen(initFile, "r");
    fgets(dimensao, sizeof(dimensao), teste);
    sscanf(dimensao, "%d %d", &x,&y);

    //Declaração da variavel labirinto
	char labirinto[x][y];
	char labirintoORIGINAL[x][y];
	
	//Atribui cada elemento do arquivo a um char [x][y] que pertence ao labirinto
	for (int i = 0; i < x; i++) {
        for (int j = 0; j < y; j++) {
			fscanf(teste, " %c", &labirinto[i][j]);
            labirintoORIGINAL[i][j] = labirinto[i][j];
        }
    }
	fclose(teste);

  
	
    // int loopMenu = 0;
    for (int loopMenu = 0; loopMenu == 0;) {
        printlab(x,y,labirinto);
        printf("Qual acao deseja realizar?\n[1] Tentar resolver uma vez.\n[2] Tentar resolver ate conseguir.\n[3] Salvar a resolucao.\n[4] Sair.\n\nDigite o numero que corresponde a sua escolha: ");
        scanf("%d", &modo); 
        switch (modo){
        case 1:
            acc = 0;
            
            //Posição do objetivo e posição inicial do player
            posicao('$', x, y, labirinto);
            posicao('@', x, y, labirinto);

        	for (int i = 0; i < x; i++) {
                for (int j = 0; j < y; j++) {
                    labirinto[i][j] = labirintoORIGINAL[i][j];
                }
            }
            while(acc != -1){
                mov_aleatoria(x, y, labirinto);
                printlab(x,y,labirinto);
                // system("pause");
                // system("cls");
                system("clear");
                printf("posI: %i; posJ: %i\n", player.PosI, player.PosJ);
                printf("posI: %i; posJ: %i\n", player.endI, player.endJ);
                if (player.PosI == player.endI && player.PosJ == player.endJ){
                    labirinto[player.PosI][player.PosJ] = 'V';
                    printf("Escapou do labirinto!\n");
                    acc = -1;
                }
                // printf("\n");
            }
            
            break;

        case 2:
            for (int labLoop = 0; labLoop == 0;){   
                printf("%i",labLoop);
                acc = 0;
            
                //Posição do objetivo e posição inicial do player
                posicao('$', x, y, labirinto);
                posicao('@', x, y, labirinto);

                for (int i = 0; i < x; i++) {
                    for (int j = 0; j < y; j++) {
                        labirinto[i][j] = labirintoORIGINAL[i][j];
                    }
                }
                while(acc != -1){
                    mov_aleatoria(x, y, labirinto);
                    printlab(x,y,labirinto);
                    // system("pause");
                    // system("cls");
                    system("cls");
                    if (player.PosI == player.endI && player.PosJ == player.endJ){
                        labirinto[player.PosI][player.PosJ] = 'V';
                        printf("Escapou do labirinto!\n");
                        acc = -1;
                        labLoop = -1;
                    }
                    printf("\n");
                } 
                  
            }
            break;

        case 3:
            // system("cls"); //em linux é "clear" e em windows "cls"
            salvaArquivo(newFile, x, y, labirinto);
            loopMenu = 1;
            break;
        case 4:
            loopMenu = 1;
            break;
        }
        
    }  
    return 0; 
}

// Cuida da leitura e salvamento do labirinto ------------------------------------------

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
        if(i < y-1){
			fprintf(teste, "\n");
		}
	}    
    fclose(teste);
    return 0;
}

//------------------------------------------------------------------------------------
// Base para a movimentação ----------------------------------------------------------

void posicao(char objeto, int x, int y, char matriz[x][y]){
	int i;
    int j;
    if (objeto == '@'){
        for(i=0;i<x;i++){
		    for(j=0;j<y;j++){
			    if(matriz[i][j] == '@'){
				    player.PosI = i;
				    player.PosJ = j;
				    return;
			    }
		    }
	    }
    }
    else if (objeto == '$'){
            for(i=0;i<x;i++){
		        for(j=0;j<y;j++){
			        if(matriz[i][j] == '$'){
			            player.endI = i;
			            player.endJ = j;
				        return;
			        }
		        }
	        }
         }
         else printf("Função definida somente para os caracteres '@' e '$' ");
         return;
}

//EM DESENVOLVIMENTO
//Verifica se um determinado espaço é permitido, se sim retorna 1(true), caso contrário retorna 0(false)	
int blockedArea (char elemento, int x, int y, int i, int j){ 
    
    if(elemento == '#' || elemento == '*' || elemento == '!' || i > x-1 || elemento == '@' ||i < 0 || j > y-1 || j < 0){
        return 0;
    }
    else {
        return 1;
    }
}

int verificandoArea(int x, int y, char matriz[x][y]){
	char N = matriz[player.PosI-1][player.PosJ], S = matriz[player.PosI+1][player.PosJ], O = matriz[player.PosI][player.PosJ-1], L = matriz[player.PosI][player.PosJ+1];
    
    player.N = blockedArea(N, x, y, player.PosI-1, player.PosJ);
    player.S = blockedArea(S, x, y, player.PosI+1, player.PosJ);
    player.L = blockedArea(L, x, y, player.PosI, player.PosJ + 1);
    player.O = blockedArea(O, x, y, player.PosI, player.PosJ - 1);


    // printf("N %d S %d L %d O %d\n", player.N,player.S,player.L,player.O);
}

int aleatorio(int x){
    return rand() % x;
}


// int mov(int x, int y, char matriz[x][y]) {
    //     printf("%c")
    //     return 0;
    // }



void rastroPlayer(int posI,int posJ,int x,int y,char matriz[x][y]){

    if (matriz[posI][posJ] != '@'){
        if (matriz[posI][posJ] == '.'){
            matriz[posI][posJ] = '*';
        }
        else if (matriz[posI][posJ] == '%'){
                 batalha(posI, posJ, x, y, matriz);
             }
    // if (matriz[posI][posJ] == '$'){
    //     matriz[posI][posJ] = 'V';
    //     // acc = 10;
    // }
    }
}

void batalha(int i, int j, int x, int y,char matriz[x][y]){
    int f = aleatorio(100);
    printf("P = %d", player.power);
    switch (player.power){
        case 50:
            if (f < 50){
                player.power += 10;
                matriz[i][j] = '!';
            }
            else 
                matriz[i][j] = '+';
            break;
        
        case 60:
            if (f < 60){
                player.power += 10;
                matriz[i][j] = '!';
            }
            else 
                matriz[i][j] = '+';
            break;

        case 70:
            if (f < 70){
                player.power += 10;
                matriz[i][j] = '!';
            }
            else 
                matriz[i][j] = '+';
            break;

        case 80:
            if (f < 80){
                player.power += 10;
                matriz[i][j] = '!';
            }
            else 
                matriz[i][j] = '+';
            break;

        case 90:
            if (f < 90){
                player.power += 10;
                matriz[i][j] = '!';
            }
            else 
                matriz[i][j] = '+';
            break;

        case 100:
                matriz[i][j] = '!';
            break;
    }
}

//------------------------------------------------------------------------------------
// Algoritmo de modificação ----------------------------------------------------------

void mov_aleatoria(int x, int y, char matriz[x][y]){ // retorna a próx posição
    
    if (acc == 0){
        verificandoArea(x, y, matriz);
    }
    int r = aleatorio(4);
    int psI = player.PosI;
    int psJ = player.PosJ;
    
    
    if (acc >= 0){
        acc ++;
        
        if (r == 0 && player.N == 1){
            rastroPlayer(psI,psJ,x,y,matriz);
            player.PosI --;
            printf("\nI=%i  J=%i acc = %i\n",player.PosI+1, player.PosJ,acc);
            acc = 0;
            if(matriz[psI][psJ] == '+' || matriz[psI][psJ] == '?'){
                acc = -1;
                return;
            } 
        }
        else if (r == 1 && player.S == 1){
                 rastroPlayer(psI,psJ,x,y,matriz);
                 player.PosI ++;
                 printf("\nI=%i  J=%i acc = %i\n",player.PosI-1, player.PosJ,acc);
                 acc = 0;
                 if(matriz[psI][psJ] == '+' || matriz[psI][psJ] == '?'){
                    acc = -1;
                    return;
                 }
             } 
             else if (r == 2 && player.O == 1){
                      rastroPlayer(psI,psJ,x,y,matriz);
                      player.PosJ --;
                      printf("\nI=%i  J=%i acc = %i\n",player.PosI, player.PosJ+1,acc);
                      acc = 0;
                      if(matriz[psI][psJ] == '+' || matriz[psI][psJ] == '?'){
                        acc = -1;
                        return;
                      }
                  }
                  else if (r == 3 && player.L == 1){
                           rastroPlayer(psI,psJ,x,y,matriz);
                           player.PosJ ++;
                           printf("\nI=%i  J=%i acc = %i\n",player.PosI, player.PosJ-1,acc);
                           acc = 0;
                           if(matriz[psI][psJ] == '+' || matriz[psI][psJ] == '?'){
                            acc = -1;
                            return;
                           }
                       }
                        else if(player.N == 0 && player.S == 0 && player.L == 0 && player.O == 0){
                                rastroPlayer(psI,psJ,x,y,matriz);
                                acc = -1;
                             }
                             else mov_aleatoria(x, y, matriz); 
    }
}
