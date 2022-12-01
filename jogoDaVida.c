#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#ifdef _WIN32
#include <Windows.h>
#else
//biblioteca para linux
#include <unistd.h>
#endif

#define N 30
#define M 30

int LeArquivo(char* nomeArquivo, int* matriz);
void EscreveMatriz(int *matriz);
void CalculaProximaGeracao(int *matriz);
int CalculaSituacaoCelula(int status, int nVizinhos);
void Delay(int tempo);
void Clear();

int main(int argc, char *argv[]){
    int numeroGeracoes = atoi(argv[2]);
    int matriz[N][M];

    if(argc != 3){
        printf("Erro! Utilize: %s nomeArquivo.txt qtdGeracoes\n", argv[0]);
        return 0;
    }else if(numeroGeracoes <= 0){
        printf("Numero de geracoes invalido. Digite um valor maior ou igual a 1.\n");
        return 0;
    }

    int erro = LeArquivo(argv[1], &matriz[0][0]);
     
    if(erro){
        return 0;
    }

    Clear();
    EscreveMatriz(&matriz[0][0]);
    for(int n = 1; n <= numeroGeracoes; n++){
        CalculaProximaGeracao(&matriz[0][0]);
        Delay(400);
        Clear();
        EscreveMatriz(&matriz[0][0]);
    }

    return 0;
}

//le e converte o arquivo pra inteiro
int LeArquivo(char* nomeArquivo, int* matriz){
    FILE *arquivo;

    arquivo = fopen(nomeArquivo, "r");
    if(arquivo == NULL){
        printf("Erro! Arquivo de texto nao encontrado.\n");
        return 1;
    }

    for(int i = 0; i < N; i++){
        //permite que haja espaços entre as celulas
        char linha[(2 * M) + 1];

        fscanf(arquivo, "%[^\n] \n", linha);

        //Remove os espaços da linha
        int posicao = 0;
        for(int i = 0; i < strlen(linha); i++){
            if(linha[i] == 32){
                continue;
            }else{
                linha[posicao] = linha[i];
                posicao++;
            }
        }
        linha[posicao] = '\0';
        
        if(strlen(linha) != M){
            printf("Erro na leitura da linha %d da matriz.\n", i + 1);

            if(strlen(linha) > M){
                printf("A linha possui %d celula(s) a mais.", strlen(linha) - M);
            }else{
                printf("A linha possui %d celula(s) a menos.", M - strlen(linha));
            }
            return 1;
        }

        for(int j = 0; j < M; j++){
            //transforma o caractere em inteiro
            *matriz++ = linha[j] - '0';
        }
    }
    fclose(arquivo);
    return 0;
}

void EscreveMatriz(int *matriz){
    int cVivo, cMorto;
    #ifdef WIN32
    //windows
    cVivo = 219;
    cMorto = 176;
    #else
    //linux
    cVivo = 64;
    cMorto = 46;
    #endif
    for(int i = 0; i < N; i++){
        for(int j = 0; j < M; j++){
            
            if(*matriz++ == 1){
                printf("%c%c", cVivo, cVivo);
            }else{
                printf("%c%c", cMorto, cMorto);
            }
        }
        printf("\n");
    }
}

void CalculaProximaGeracao(int *matriz){
    int matrizAnterior[N][M];
    int *enderecoInicial = matriz;

    //copia a matriz para matrizAnterior
    for(int i = 0; i < N; i++){
        for(int j = 0; j < M; j++){
            matrizAnterior[i][j] = *matriz++;
        }
    }
    //retorna o ponteiro para o inicio da matriz 
    matriz = enderecoInicial;

    //*************** análise da matriz *********************
    for(int i = 0; i < N; i++){ //linhas
        for(int j = 0; j < M; j++){ //colunas
            int vizinhosVivos = 0;
            
            //vizinho de cima
            if(i > 0 && matrizAnterior[i - 1][j] == 1){
                vizinhosVivos++;
            }

            //vizinho debaixo
            if(i < N - 1 && matrizAnterior[i + 1][j] == 1){
                vizinhosVivos++;
            }

            //vizinho da direita - acima
            if(i > 0 && j < M - 1 && matrizAnterior[i - 1][j + 1] == 1){
                vizinhosVivos++;
            }

            //vizinho da direita - exata
            if(j < M - 1 && matrizAnterior[i][j + 1] == 1){
                vizinhosVivos++;
            }

            //vizinho da direita - abaixo
            if(i < N - 1 && j < M - 1 && matrizAnterior[i + 1][j + 1] == 1){
                vizinhosVivos++;
            }

            //vizinho da esquerda - acima
            if(i > 0 && j > 0 && matrizAnterior[i - 1][j - 1] == 1){
                vizinhosVivos++;
            }

            //vizinho da esquerda - exata
            if(j > 0 && matrizAnterior[i][j - 1] == 1){
                vizinhosVivos++;
            }

            //vizinho da esquerda - abaixo
            if(i < N - 1 && j > 0 && matrizAnterior[i + 1][j - 1] == 1){
                vizinhosVivos++;
            }
            
            *matriz++ = CalculaSituacaoCelula(matrizAnterior[i][j], vizinhosVivos);
        }
    }
}

int CalculaSituacaoCelula(int status, int nVizinhos){
    if(status == 1){
        if(nVizinhos < 2 || nVizinhos > 3){
            return 0;
        }else{
            return 1;
        }
    }else if(status == 0 && nVizinhos == 3){
        return 1;
    }

    return 0;
}

//em milissegundos
void Delay(int tempo){
    #ifdef WIN32
    //windows
    Sleep(tempo);
    #else
    //linux
    usleep(1000 * tempo);
    #endif
}

void Clear(){
    #ifdef WIN32
    //windows
    system("cls");
    #else
    //linux
    system("clear");
    #endif
}