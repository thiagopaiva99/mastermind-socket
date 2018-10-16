#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct
{
    int tentativa;
    char cores[4];
    char ajuda[4];   
}JOGADA;

char cor[7];
char ajuda[4];

void inicia (char cores[6], char auxilio[3]) {
    strcpy(cor, cores);
    strcpy(ajuda, auxilio); 
}

void iniciaJogada(JOGADA jog[9]) {
    int i = 0;
    for (i = 0; i < 9; i++) {
        preenche(&jog[i], 0, "0000", "----");
    }       
}

void sorteioEasy(char * senha[4]) { 
    char aux[4], cores[6];
    int i = 0, j = 0, isenha = 0, continua = 1;

    strcpy(cores, "123456");
    srand((unsigned)time(NULL) );

    for (i = 0; i < 4; i++) {
        continua = 1;
        do {
           isenha = (1 + (rand() % 6));
           sprintf(&aux[i], "%d", isenha);
           for (j = 0; j < 6; j++) {
               if (aux[i] == cores[j]) {
                   cores[j] = "X"; 
                   continua = 0;
                   j = 6; 
               }
           }        
        }while(continua);
    }   

    strcpy(senha, aux); 
    tabelaSorteio(senha);
}

void sorteioHard(char * senha[4])  { 
    char aux[4];
    int i = 0, isenha = 0;
    srand((unsigned)time(NULL) );
    for (i = 0; i < 4; i++) {
        isenha = (1 + (rand() % 6));
        sprintf(&aux[i], "%d", isenha);
    }   

    strcpy(senha, aux);
    tabelaSorteio(senha);
}

void tabelaSorteio(char * senha[4]) {
    char aux[4], c[2];
    int i = 0, num = 0;

    strcpy(aux, senha);

    for (i = 0; i < 4; i++) {
        c[0] = aux[i];
        c[1] = '\0';
        num = atoi(c); 
        aux[i] = cor[num-1];
    }
    aux[5] = '\0';

    strcpy(senha, aux);
}

void sinalizacao(char entrada[4], char senha[4], char* saida[4])
{
    int i, j, x;
    char aux[4], corretos[4];
    
    strcpy(aux, "----"); 
    strcpy(corretos, "----"); 
    for (i=0; i<4; i++) {
        x = senha[i];
        x = x + 32;
        if (entrada[i] == senha[i] || entrada[i] == x) { 
            aux[i] = '*'; 
            corretos[i] = senha[i];
        } 
    }

    for (i=0; i<4; i++) {
        x = senha[i];
        x = x + 32;
        if (entrada[i] != senha[i] || entrada[i] != x) {
            for (j=0; j<4; j++) {
                x = senha[j];
                x = x + 32;
                if ((entrada[i] == senha[j] || entrada[i] == x ) && senha[j] != corretos[i]) {
                    aux[i] = 'o';
                }
            }            
        } 
    }

    strcpy(saida, aux); 
}

int valEntrada(char entrada[4], char cores[6])
{
    int i = 0, j = 0, x, ehValido = 1;
    for (i = 0; i < 4; i++){
        ehValido = 1;
        for (j = 0; j < 6; j++){
            x = cores[j];
            x = x + 32;
            if (entrada[i] == cores[j] || entrada[i] == x) {                   
                ehValido = 0;
            } 
         }
         if (ehValido == 1) {
             return ehValido;
         }
    }
    return ehValido;
}

void preenche(JOGADA *jog, int tentativa, char cores[4], char ajuda[4])
{
    jog->tentativa = tentativa;
    strcpy(jog->cores, cores); 
    strcpy(jog->ajuda, ajuda); 
}

void exibe(JOGADA jog[10], char cores[6], char auxilio[3], char * impressao[2000])
{
    int i = 0;
    char legend[2000], tentativa[3], aux[3];
    legenda (3, cores, auxilio, legend);
    strcpy(impressao, legend);

    strcat(impressao, "         JOGADAS           RESPOSTAS   \n");
    strcat(impressao, "    *---------------*  *---------------*\n");
    for (i = 0; i <= 10; i++) {
        if (jog[i].tentativa > 0 && jog[i].tentativa < 10) {
            strcat(impressao, "T");
            sprintf(&tentativa, "%d", jog[i].tentativa); 
            strcat(impressao, tentativa);
            strcat(impressao, "  | ");
            aux[0] = jog[i].cores[0];
            aux[1] = '\0';
            strcat(impressao, aux);
            strcat(impressao, " | ");
            aux[0] = jog[i].cores[1];
            aux[1] = '\0';
            strcat(impressao, aux);
            strcat(impressao, " | ");
            aux[0] = jog[i].cores[2];
            aux[1] = '\0';
            strcat(impressao, aux);
            strcat(impressao, " | ");
            aux[0] = jog[i].cores[3];
            aux[1] = '\0';
            strcat(impressao, aux);
            strcat(impressao, " |  | ");
            aux[0] = jog[i].ajuda[0];
            aux[1] = '\0';
            strcat(impressao, aux);
            strcat(impressao, " | ");
            aux[0] = jog[i].ajuda[1];
            aux[1] = '\0';
            strcat(impressao, aux);
            strcat(impressao, " | ");
            aux[0] = jog[i].ajuda[2];
            aux[1] = '\0';
            strcat(impressao, aux);
            strcat(impressao, " | ");
            aux[0] = jog[i].ajuda[3];
            aux[1] = '\0';
            strcat(impressao, aux);
            strcat(impressao, " | \n");
        } else if (jog[i].tentativa == 10) {
            strcat(impressao, "t");
            sprintf(&tentativa, "%d", jog[i].tentativa); 
            strcat(impressao, tentativa);
            strcat(impressao, " | ");
            aux[0] = jog[i].cores[0];
            aux[1] = '\0';
            strcat(impressao, aux);
            strcat(impressao, " | ");
            aux[0] = jog[i].cores[1];
            aux[1] = '\0';
            strcat(impressao, aux);
            strcat(impressao, " | ");
            aux[0] = jog[i].cores[2];
            aux[1] = '\0';
            strcat(impressao, aux);
            strcat(impressao, " | ");
            aux[0] = jog[i].cores[3];
            aux[1] = '\0';
            strcat(impressao, aux);
            strcat(impressao, " |  | ");
            aux[0] = jog[i].ajuda[0];
            aux[1] = '\0';
            strcat(impressao, aux);
            strcat(impressao, " | ");
            aux[0] = jog[i].ajuda[1];
            aux[1] = '\0';
            strcat(impressao, aux);
            strcat(impressao, " | ");
            aux[0] = jog[i].ajuda[2];
            aux[1] = '\0';
            strcat(impressao, aux);
            strcat(impressao, " | ");
            aux[0] = jog[i].ajuda[3];
            aux[1] = '\0';
            strcat(impressao, aux);
            strcat(impressao, " | \n");
        }
    }
    strcat(impressao, "    *---------------*  *---------------*\n"); 
}

void legenda (int leg, char cores[6], char auxilio[3], char * impressao[20000]){
    char aux[3];
    int x = 0;
    if (leg == 1) {
        strcpy(impressao, "*----------------*\n");
        strcat(impressao, "|          |     |\n\n");  
        strcat(impressao, "| Amarelo  | ");
        aux[0] = cores[0];
        aux[1] = '\0';
        strcat(impressao, aux);
        strcat(impressao, "    |\n");
        strcat(impressao, "| Azul     | ");
        aux[0] = cores[1];
        aux[1] = '\0';
        strcat(impressao, aux);
        strcat(impressao, "    |\n");
        strcat(impressao, "| Branco   | ");
        aux[0] = cores[2];
        aux[1] = '\0';
        strcat(impressao, aux);
        strcat(impressao, "    |\n");
        strcat(impressao, "| Vermelho | ");
        aux[0] = cores[3];
        aux[1] = '\0';
        strcat(impressao, aux);
        strcat(impressao, "    |\n");
        strcat(impressao, "| Verde    | ");
        aux[0] = cores[4];
        aux[1] = '\0';
        strcat(impressao, aux);
        strcat(impressao, "    |\n");
        strcat(impressao, "| Preto    | ");
        aux[0] = cores[5];
        aux[1] = '\0';
        strcat(impressao, aux);
        strcat(impressao, "    |\n");
        strcat(impressao, "|          |     |\n\n");  
        strcpy(impressao, "*----------------*\n");
    } else if (leg == 2) {
        strcpy(impressao, " _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ \n");
        strcat(impressao, "|Cor ERRADA e Lugar ERRADO  | ");
        aux[0] = auxilio[0];
        aux[1] = '\0';
        strcat(impressao, aux);
        strcat(impressao, " |\n");
        strcat(impressao, "|Cor CERTA  e Lugar ERRADO  | ");
        aux[0] = auxilio[1];
        aux[1] = '\0';
        strcat(impressao, aux);
        strcat(impressao, " |\n");
        strcat(impressao, "|Cor CERTA  e Lugar CERTO   | ");
        aux[0] = auxilio[2];
        aux[1] = '\0';
        strcat(impressao, aux);
        strcat(impressao, " |\n");
        strcat(impressao, "|_ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _|\n\n");  
    } else if (leg == 3) {
        strcat(impressao, "*-------------------------------------*\n");
        strcat(impressao, "|                                     |\n");
        strcat(impressao, "|             Mastermind              |\n");
        strcat(impressao, "|     Tabela de cores e respostas     |\n");
        strcat(impressao, "|                                     |\n");
        strcat(impressao, "*-------------------------------------*\n\n");
        strcat(impressao, "*--------------*\n");
        strcat(impressao, "| Amarelo  | ");
        aux[0] = cores[0];
        aux[1] = '\0';
        strcat(impressao, aux);
        strcat(impressao, " |\n");
        strcat(impressao, "| Azul     | ");
        aux[0] = cores[1];
        aux[1] = '\0';
        strcat(impressao, aux);
        strcat(impressao, " |\n");
        strcat(impressao, "| Branco   | ");
        aux[0] = cores[2];
        aux[1] = '\0';
        strcat(impressao, aux);
        strcat(impressao, " |");
        strcat(impressao,"   *--------------------------------* \n");
        strcat(impressao, "| Vermelho | ");
        aux[0] = cores[3];
        aux[1] = '\0';
        strcat(impressao, aux);
        strcat(impressao, " |");
        strcat(impressao, "   | Cor ERRADA e Lugar ERRADO  | ");
        aux[0] = auxilio[0];
        aux[1] = '\0';
        strcat(impressao, aux);
        strcat(impressao, " |\n");
        strcat(impressao, "| Verde    | ");
        aux[0] = cores[4];
        aux[1] = '\0';
        strcat(impressao, aux);
        strcat(impressao, " |");
        strcat(impressao, "   | Cor CERTA  e Lugar ERRADO  | ");
        aux[0] = auxilio[1];
        aux[1] = '\0';
        strcat(impressao, aux);
        strcat(impressao, " |\n");
        strcat(impressao, "| Preto    | ");
        aux[0] = cores[5];
        aux[1] = '\0';
        strcat(impressao, aux);
        strcat(impressao, " |");
        strcat(impressao, "   | Cor CERTA  e Lugar CERTO   | ");
        aux[0] = auxilio[2];
        aux[1] = '\0';
        strcat(impressao, aux);
        strcat(impressao, " |\n");
        strcat(impressao, "*--------------*");   
        strcat(impressao,"   *--------------------------------*\n\n");  
    } 
}

void sobreMaster (char cores[6], char auxilio[3], char impressao[20000]){
    char legend[20000];
    strcat(impressao, "*-------------------------------------*\n");
    strcat(impressao, "|                                     |\n");
    strcat(impressao, "|             Mastermind              |\n");
    strcat(impressao, "|      Sobre o jogo Mastermind        |\n");
    strcat(impressao, "|                                     |\n");
    strcat(impressao, "*-------------------------------------*\n");
}

void cabecMaster (char cores[6], char auxilio[3], char impressao[20000]){
    legenda (3, cores, auxilio, impressao) ;   
}

