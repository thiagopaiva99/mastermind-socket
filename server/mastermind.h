typedef struct
{
    int tentativa;
    char cores[4];
    char ajuda[4];   
}JOGADA;

// inicia variaveis globais
void inicia (char cores[6], char auxilio[3]);

// Inicia a "tabela" de jogadas toda zerada
void iniciaJogada(JOGADA jog[10]);

// Faz um sorteio de 4 números que não poderão se repetir
void sorteioEasy(char* senha[4]);

// Faz um sorteio de 4 números que podem se repetir
void sorteioHard(char* senha[4]);

// Função que devolve os indicadores se o jogador acertou ou não a senha
void sinalizacao(char entrada[4], char senha[4], char* saida[4]);

// Verifica se o Jogador colocou os caracteres permitidos
int valEntrada(char entrada[4], char cores[6]);

// Cria uma JOGADA usando o número da tentativa, as cores que o jogador escolheu e o que teve de saída (sinalização)
void preenche(JOGADA *jog, int tentativa, char cores[4], char ajuda[4]);

// Imprime as Jogadas conforme a Lista de jogadas
void exibe(JOGADA jog[10], char cores[6], char auxilio[3], char * impressao[2000]);

// Legenda das cores
void legenda (int leg, char cores[6], char auxilio[3], char * impressao[20000]);

// Imprime instruções sobre o jogo
void sobreMaster (char cores[6], char auxilio[3], char impressao[20000]);

// Imprime o cabeçalho inicial do jogo
void cabecMaster (char cores[6], char auxilio[3], char impressao[20000]);

// Transforma o Sorteio dos números nas "cores" escolhidas
void tabelaSorteio(char * senha[4]);
