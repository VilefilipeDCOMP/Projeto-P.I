#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include <time.h>

#if defined(_WIN32) || defined(_WIN64) || defined(__WINDOWS__)
    #include <windows.h>
    void limpar(){

        system("cls");
    }
#else
    
    #include <unistd.h>
    
    void limpar(){
            system("clear");
        }
#endif


// Define um struct global para o player
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

// Utilizado para o movimento aleatorio com memoria
int pontosLab = 0;
int pontosLabAnt = 0;
int posicaoInicialdoLabI = 0;
int posicaoInicialdoLabJ = 0;
// int valorRelativo = 0;

void printlab();
int salvaArquivo();
void posicao(char objeto, int x, int y, char matriz[x][y]);
int blockedArea(char elemento, int x, int y, int i, int j);
int verificandoArea();
int aleatorio();
void rastroPlayer();
void batalha();
void mov_aleatoria();
void mov_aleatorio_inteligente();

int main(int argc, char **argv){
    char newFile[100], initFile[100], dimensao[30];
    int modo, x, y, win;
    char resp;
    player.power = 50;
    int accTest = 0;
    int limitador = 0;

    // Serve para resolver os problemas de acentuação em C
    setlocale(LC_ALL, "Portuguese_Brazil");

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
	char labirintoMEMORIA[x][y];
	
	//Atribui cada elemento do arquivo a um char [x][y] que pertence ao labirinto
	for (int i = 0; i < x; i++) {
        for (int j = 0; j < y; j++) {
			fscanf(teste, " %c", &labirinto[i][j]);
            labirintoORIGINAL[i][j] = labirinto[i][j];
        }
    }
	fclose(teste);

    for (int loopMenu = 0; loopMenu == 0;) {
        printf("\n");
        printlab(x,y,labirinto);
        printf("Qual ação deseja realizar?\n[1] Tentar resolver uma vez.\n[2] Tentar resolver ate conseguir.\n[3] Salvar a resolucao.\n[4] Sair.\n\nDigite o numero que corresponde a sua escolha: ");
        scanf("%d", &modo); 
        switch (modo){
        case 1:
            printf("[1] Aleatorio.\n[2] Aleatorio Inteligente.\n");
            scanf("%d", &modo); 
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
                if (modo == 1) {
                    mov_aleatoria(x, y, labirinto); 
                } 
                else {
                    mov_aleatorio_inteligente(x, y, labirinto);
                }
                printlab(x,y,labirinto);
                limpar();


                // printf("posI: %i; posJ: %i\n", player.PosI, player.PosJ);
                // printf("posI: %i; posJ: %i\n", player.endI, player.endJ);
                if (player.PosI == player.endI && player.PosJ == player.endJ){
                    labirinto[player.PosI][player.PosJ] = 'V';
                    printf("Escapou do labirinto!\n");
                    acc = -1;
                }
                // printf("\n");
            }
            
            break;

        case 2:
            accTest = 0;
            printf("[1] Aleatorio.\n[2] Aleatorio Inteligente.\n");
            scanf("%d", &modo); 
            for (int i = 0; i < x; i++) {
                for (int j = 0; j < y; j++) {
                    labirinto[i][j] = labirintoORIGINAL[i][j];
                }
            }

            // Como nesse caso, queremos que ele tente várias vezes (com um limitador de 100 vezes), utilizamos esse labloop.
            for (int labLoop = 0; labLoop == 0;){ 
                if (limitador <= 99) {
                    limitador++;
                    accTest++;  
                    acc = 0;
                    player.power = 50;
                    
                    for (int i = 0; i < x; i++) {
                        for (int j = 0; j < y; j++) {
                            labirinto[i][j] = labirintoORIGINAL[i][j];
                        }
                    }

                    //Posição do objetivo e posição inicial do player
                    posicao('$', x, y, labirinto);
                    posicao('@', x, y, labirinto);

                    while(acc != -1){
                        if (modo == 1){
                            mov_aleatoria(x, y, labirinto); 
                        } else {
                            mov_aleatorio_inteligente(x, y, labirinto);
                        }
                    
                        printf("Iteração %iº\n\n",accTest);
                        printlab(x,y,labirinto);
                        //limpar();
                        
                        

                        // Termina o loop de movimentações de um único labirinto (com o acc = -1) e termina o loop de repetir labs. até resolver (com o laploop = -1)
                        if (player.PosI == player.endI && player.PosJ == player.endJ){
                            labirinto[player.PosI][player.PosJ] = 'V';
                            printf("Escapou do labirinto!");
                            acc = -1;
                            labLoop = -1;
                        }                     
                        printf("\n");

                    }}
                    else
                        break;
            }
            break;

        case 3:
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
    printf("\n");
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

// Verifica se um determinado espaço é permitido, se sim retorna 1(true), caso contrário retorna 0(false)	
int blockedArea (char elemento, int x, int y, int i, int j){ 
    
    if(elemento == '#' || elemento == '*' || elemento == '!' || i > x-1 || elemento == '@' ||i < 0 || j > y-1 || j < 0){
        return 0;
    }
    else {
        return 1;
    }
}

// Serve somente para informar em que posições (Norte, Sul, Leste e Oeste) o personagem está livre para se locomover. 
int verificandoArea(int x, int y, char matriz[x][y]){
	char N = matriz[player.PosI-1][player.PosJ], S = matriz[player.PosI+1][player.PosJ], O = matriz[player.PosI][player.PosJ-1], L = matriz[player.PosI][player.PosJ+1];
    
    player.N = blockedArea(N, x, y, player.PosI-1, player.PosJ);
    player.S = blockedArea(S, x, y, player.PosI+1, player.PosJ);
    player.L = blockedArea(L, x, y, player.PosI, player.PosJ + 1);
    player.O = blockedArea(O, x, y, player.PosI, player.PosJ - 1);
}

int aleatorio(int x){
    return rand() % x;
}

// Serve para modificar a matriz do labirinto a cada movimentação
void rastroPlayer(int posI,int posJ,int x,int y,char matriz[x][y]){

    if (matriz[posI][posJ] != '@'){
        if (matriz[posI][posJ] == '.'){
            matriz[posI][posJ] = '*';
        }
        else if (matriz[posI][posJ] == '%'){
                 batalha(posI, posJ, x, y, matriz);
             }
    
    if(player.N == 0 && player.S == 0 && player.L == 0 && player.O == 0){

                matriz[posI][posJ] = '?';
       
           }
    // if (matriz[posI][posJ] == '$'){
    //     matriz[posI][posJ] = 'V';
    //     // acc = 10;
    // }
    }
}

void batalha(int i, int j, int x, int y,char matriz[x][y]){
    int f = aleatorio(100);
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

void mov_aleatoria(int x, int y, char matriz[x][y]){

    if (acc == 0){
        verificandoArea(x, y, matriz);
    }

    int r = aleatorio(4);
    int psI = player.PosI;
    int psJ = player.PosJ;
    
    // O personagem se move de acordo com o valor de r (seguindo o padrão: 0 = Norte, 1 = Sul, 2 = Oeste, 3 = Leste) e se a posição para tal direção esteja livre. Caso a posição não esteja livre, essa função será chamada novamente até encontrar um valor aceitável, porém caso todas as posições estejam ocupadas, será chamado o rastroPlayer (para colocar o simbolo ?).
    if (acc >= 0){
        acc ++;
        if (r == 0 && player.N == 1){
            rastroPlayer(psI,psJ,x,y,matriz);
            player.PosI --; // Atualizar a posição do personagem globalmente 
            // printf("\nI=%i  J=%i acc = %i\n",player.PosI+1, player.PosJ,acc);
            acc = 0;
            if(matriz[psI][psJ] == '+' || matriz[psI][psJ] == '?'){
                acc = -1;
                return;
            } 
        }
        else if (r == 1 && player.S == 1){
                 rastroPlayer(psI,psJ,x,y,matriz);
                 player.PosI ++;
                //  printf("\nI=%i  J=%i acc = %i\n",player.PosI-1, player.PosJ,acc);
                 acc = 0;
                 if(matriz[psI][psJ] == '+' || matriz[psI][psJ] == '?'){
                    acc = -1;
                    return;
                 }
             } 
             else if (r == 2 && player.O == 1){
                      rastroPlayer(psI,psJ,x,y,matriz);
                      player.PosJ --;
                    //   printf("\nI=%i  J=%i acc = %i\n",player.PosI, player.PosJ+1,acc);
                      acc = 0;
                      if(matriz[psI][psJ] == '+' || matriz[psI][psJ] == '?'){
                        acc = -1;
                        return;
                      }
                  }
                  else if (r == 3 && player.L == 1){
                           rastroPlayer(psI,psJ,x,y,matriz);
                           player.PosJ ++;
                        //    printf("\nI=%i  J=%i acc = %i\n",player.PosI, player.PosJ-1,acc);
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

void mov_aleatorio_inteligente (int x, int y, char matriz[x][y]) {
    if (acc == 0){
        verificandoArea(x, y, matriz);
    }
    int r = aleatorio(6);
    int psI = player.PosI;
    int psJ = player.PosJ;
    int posMaiorChanceX;
    int posMaiorChanceY;

    if (acc >= 0){
        acc ++;

        // A diferença entre essa movimentação e a outra é que o personagem terá mais chance de se mover em direção ao ponto final, provando ser útil em alguns casos.
        // No caso do eixo Y, ele verifica se o fim do labirinto é maior que a posição do personagem, caso verdade ele deve descer e se contrário subir
        if (psI < player.endI) {
            // Desce
            posMaiorChanceY = 1;
        } else {
            // Sobe
            posMaiorChanceY = 0;
        }

        if (psJ < player.endJ) {
            // Esquerda
            posMaiorChanceX = 2;
        } else {
            // Direita
            posMaiorChanceX = 3;
        }
        
        // printf("[DEBUG] psI: %i, psJ: %i\n", psI, psJ);
        // printf("[DEBUG] endI: %i, endJ: %i\n", player.endI, player.endJ);
        // printf("[DEBUG] MaiorChanceX: %i, MaiorChanceY: %i, r: %i\n", posMaiorChanceX, posMaiorChanceY, r);

        // Para ele ter mais chance de ir ao ponto desejado, será feito o aleatório de 6 valores. Os valores de 0 a 3 funcionaram da mesma forma que o último mecanismo de movimentação porém os valores de 4 a 5 serviram para que a posição de maior possibilidade tenha mais posibilidade de ser escolhido.
        if ((r == 0 || ((r == 4 || r == 5) && posMaiorChanceY == 0)) && player.N == 1){
            rastroPlayer(psI,psJ,x,y,matriz);
            player.PosI --;
            // printf("\nI=%i  J=%i acc = %i\n",player.PosI+1, player.PosJ,acc);
            acc = 0;
            if(matriz[psI][psJ] == '+' || matriz[psI][psJ] == '?'){
                acc = -1;
                return;
            } 
        }
        else if ((r == 1 || ((r== 4 || r == 5) && posMaiorChanceY == 1)) && player.S == 1){
                 rastroPlayer(psI,psJ,x,y,matriz);
                 player.PosI ++;
                 // printf("\nI=%i  J=%i acc = %i\n",player.PosI-1, player.PosJ,acc);
                 acc = 0;
                 if(matriz[psI][psJ] == '+' || matriz[psI][psJ] == '?'){
                    acc = -1;
                    return;
                 }
             } 
             else if ((r == 2 || ((r== 4 || r == 5) && posMaiorChanceX == 2)) && player.O == 1){
                      rastroPlayer(psI,psJ,x,y,matriz);
                      player.PosJ --;
                      //  printf("\nI=%i  J=%i acc = %i\n",player.PosI, player.PosJ+1,acc);
                      acc = 0;
                      if(matriz[psI][psJ] == '+' || matriz[psI][psJ] == '?'){
                        acc = -1;
                        return;
                      }
                  }
                  else if ((r == 3 || ((r== 4 || r == 5) && posMaiorChanceX == 3)) && player.L == 1){
                           rastroPlayer(psI,psJ,x,y,matriz);
                           player.PosJ ++;
                           // printf("\nI=%i  J=%i acc = %i\n",player.PosI, player.PosJ-1,acc);
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