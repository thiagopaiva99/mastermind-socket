#include <stdio.h>

typedef struct{
    char id[4]; 
    char nome[31];
    char apelido[31];
    char idade[4];
}JOGADOR;

typedef struct
{
    char idJogador[4]; 
    int qtdVezes;      
    int qtdTentUlt;    
    int qtdMelhor;     
    int qtdPior;       
}SCORE;

// Função para colocar os dados do jogador na struct de Jogador
void preencheJogador(JOGADOR *jog, char id[4], char nome[31], char apelido[31], char idade[4]);

// Função para colocar os dados do score do jogador na struct de SCORE
void preencheScore(SCORE *scr, char id[4], int qtdVezes, int qtdTentUlt, int qtdMelhor, int qtdPior);

// Insere os Jogadores no arquivo de Jogador
int insereJogador (char* Nome[30], char* Apelido[30], char* Idade[3]);

// Lê o arquivo de Jogadores e devolve uma lista de JOGADOR
int listaJogadores (JOGADOR lista[1000]);

// Lê o arquivo de SCORES e devolve uma lista de SCORES
int listaScores (SCORE lista[1000]);

// Encontra o nome do Jogador pela ID dele
void findJogadorID (char idJog[3], char * nomeJog);

// Recebe o nome do Jogador de devolve a ID dele para ser impresso no SCORE
void escolheJogador (char nomeJog[30], char * idJog[3]);

// Insere Score no arquivo de Scores
void insereScore (char* id[4], int qtdVezes, int qtdTentUlt, int qtdMelhor, int qtdPior);

// Faz o tratamento do SCORE do jogador, recebe a id do jogador e o score da partida
void verificaScore (char* idJogador[4], int scoreTentativa);

// Imprime uma lista de Jogadores
void imprimeJogadores (JOGADOR lista[1000], int tamLista, char impressao[1000][2000]);

// Insere espaços em uma string até o tamanho recebido (usada para impressão em tela e gravação de dados)
void trataString (int tam, char * string);

// Recebe um inteiro e devolve uma string com zeros a esquerda
void trataInteiro (int val, char * string);

// Retira números da String, e deixa apenas a primeira leira em maiuscula
void trataNome (char * string);
