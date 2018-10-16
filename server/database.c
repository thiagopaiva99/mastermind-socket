#include <stdio.h>

typedef struct{
    char id[4];
    char nome[31];
    char apelido[31];
    char idade[4];
} JOGADOR;

typedef struct{
    char idJogador[4];
    int qtdVezes;
    int qtdTentUlt;
    int qtdMelhor;
    int qtdPior;
} SCORE;

void preencheJogador(JOGADOR *jog, char id[4], char nome[31], char apelido[31], char idade[4]){
    strcpy(jog->id, id);
    strcpy(jog->idade, idade);
    strcpy(jog->nome, nome);
    strcpy(jog->apelido, apelido);
}

void preencheScore(SCORE *scr, char id[4], int qtdVezes, int qtdTentUlt, int qtdMelhor, int qtdPior){
    scr->qtdVezes = qtdVezes;
    scr->qtdTentUlt = qtdTentUlt;
    scr->qtdMelhor = qtdMelhor;
    scr->qtdPior = qtdPior;
    strcpy(scr->idJogador, id);
}

int novaID(){
    FILE *arq;
    char linha[100], id[3], aux[3];
    char *result;
    int i;
    int ident = 0;

    arq = fopen("jogadores.mmd", "rt");

    if (arq == NULL){
        printf("Problemas na abertura do arquivo\n");
        return;
    }

    i = 0;

    while (!feof(arq)){
        result = fgets(linha, 100, arq);

        if (result)
        {
            id[0] = linha[0];
            id[1] = linha[1];
            id[2] = linha[2];
        }

        i++;
    }

    if (i > 0){
        ident = atoi(id);
        ident++;
    }
    else
        ident = 0;

    fclose(arq);

    return ident;
}

int insereJogador(char *Nome[30], char *Apelido[30], char *Idade[3]){
    FILE *arq;
    char linha[100];
    char insere[50];
    char id[3];
    char aux[3];
    char *result;
    int i;
    int ident = 0;

    ident = novaID();

    trataInteiro(ident, id);

    arq = fopen("jogadores.mmd", "a");

    if (arq == NULL){
        printf("Problemas na abertura do arquivo\n");
        return -1;
    }

    strtok(Nome, "\n");
    trataNome(Nome);
    escolheJogador(Nome, aux);

    if (strcmp(aux, "XXX") != 0)
        return 0;

    strtok(Apelido, "\n");
    trataNome(Apelido);
    strtok(Idade, "\n");

    for (i = strlen(Nome); i < 30; i++)
        strcat(Nome, " ");
    for (i = strlen(Apelido); i < 30; i++)
        strcat(Apelido, " ");
    for (i = strlen(Idade); i < 3; i++)
        strcat(Idade, " ");

    strcpy(insere, id);
    strcat(insere, "*");
    strcat(insere, Nome);
    strcat(insere, "*");
    strcat(insere, Apelido);
    strcat(insere, "*");
    strcat(insere, Idade);
    strcat(insere, "\n");

    result = fputs(insere, arq);

    if (result == EOF){
        printf("Erro na Gravacao\n");
        return -1;
    }

    fclose(arq);

    return 1;
}

int listaJogadores(JOGADOR lista[1000]){
    FILE *arq;
    char linha[100];
    char id[4];
    char nome[30];
    char apelido[30];
    char idade[3];
    char auxNome[30];
    char auxApelido[30];
    char *result;
    JOGADOR jogador;
    int i, j, flag, ident = 0;

    arq = fopen("jogadores.mmd", "rt");

    if (arq == NULL){
        printf("Problemas na abertura do arquivo\n");
        return;
    }

    i = 0;

    while (!feof(arq)){
        result = fgets(linha, 100, arq);

        if (result)
        {
            id[0] = linha[0];
            id[1] = linha[1];
            id[2] = linha[2];
            id[3] = '\0';

            for (j = 4; j < 34; j++)
                nome[j - 4] = linha[j];

            nome[30] = '\0';

            for (j = 35; j < 65; j++)
                apelido[j - 35] = linha[j];

            apelido[30] = '\0';

            for (j = 66; j < 69; j++)
                idade[j - 66] = linha[j];

            idade[3] = '\0';
        }

        preencheJogador(&lista[i], id, nome, apelido, idade);

        i++;
    }

    fclose(arq);

    if (i > 0)
        return i - 1;
    else
        printf("Não existem jogadores para serem exibidos!\n");
}

int listaScores(SCORE lista[1000]){
    FILE *arq;
    char *result;
    char linha[100];
    char idJog[3];
    char vezes[3];
    char ult[3];
    char melhor[3];
    char pior[3];
    int i;
    int iVezes;
    int iUlt;
    int iMelhor;
    int iPior;

    arq = fopen("score.mmd", "rt");

    if (arq == NULL){
        printf("Problemas na abertura do arquivo\n");
        return;
    }

    i = 0;

    while (!feof(arq)){
        result = fgets(linha, 100, arq);

        if (result)
        {
            idJog[0] = linha[0];
            idJog[1] = linha[1];
            idJog[2] = linha[2];
            idJog[3] = '\0';

            vezes[0] = linha[4];
            vezes[1] = linha[5];
            vezes[2] = linha[6];
            vezes[3] = '\0';
            iVezes = atoi(vezes);

            ult[0] = linha[8];
            ult[1] = linha[9];
            ult[2] = linha[10];
            ult[3] = '\0';
            iUlt = atoi(ult);

            melhor[0] = linha[12];
            melhor[1] = linha[13];
            melhor[2] = linha[14];
            melhor[3] = '\0';
            iMelhor = atoi(melhor);

            pior[0] = linha[16];
            pior[1] = linha[17];
            pior[2] = linha[18];
            pior[3] = '\0';
            iPior = atoi(pior);

            preencheScore(&lista[i], idJog, iVezes, iUlt, iMelhor, iPior);
        }

        i++;
    }

    i--;

    return i;
}

void findJogadorID(char idJog[3], char *nomeJog){
    FILE *arq;
    char linha[100], id[4], nome[30], apelido[30], idade[3];
    char *result;
    int j;
    JOGADOR escolhido;

    arq = fopen("jogadores.mmd", "rt");

    if (arq == NULL){
        printf("Problemas na abertura do arquivo\n");
        return;
    }

    while (!feof(arq)){
        result = fgets(linha, 100, arq);

        if (result)
        {
            id[0] = linha[0];
            id[1] = linha[1];
            id[2] = linha[2];
            id[3] = '\0';

            if (strcmp(idJog, id) == 0)
            {
                for (j = 4; j < 34; j++)
                    nome[j - 4] = linha[j];

                nome[30] = '\0';

                for (j = 35; j < 65; j++)
                    apelido[j - 35] = linha[j];

                apelido[30] = '\0';

                for (j = 66; j < 69; j++)
                    idade[j - 66] = linha[j];

                idade[3] = '\0';

                strcpy(nomeJog, nome);
            }
        }
    }

    fclose(arq);
}

void escolheJogador(char nomeJog[30], char *idJog[3]){
    FILE *arq;
    char linha[100], id[4], nome[30];
    char *result;
    int j;

    arq = fopen("jogadores.mmd", "rt");

    if (arq == NULL){
        printf("Problemas na abertura do arquivo\n");
        return;
    }

    while (!feof(arq)){
        result = fgets(linha, 100, arq);
        if (result)
        {
            id[0] = linha[0];
            id[1] = linha[1];
            id[2] = linha[2];
            id[3] = '\0';

            for (j = 4; j < 34; j++)
                nome[j - 4] = linha[j];

            nome[30] = '\0';

            trataString(30, nome);
            trataString(30, nomeJog);

            if (strcmp(nome, nomeJog) == 0)
            {
                strcpy(idJog, id);
                fclose(arq);
                return;
            }
        }
    }

    strcpy(idJog, "XXX");
    fclose(arq);
}

void insereScore(char *id[4], int qtdVezes, int qtdTentUlt, int qtdMelhor, int qtdPior){
    FILE *arq;
    char linha[100], insere[50], idJog[3], vezes[3], ult[3], melhor[3], pior[3];
    char *result;
    SCORE lista[1000], atualizacao;
    int i, j, iVezes, iUlt, iMelhor, iPior;

    trataInteiro(qtdVezes, vezes);
    trataInteiro(qtdTentUlt, ult);
    trataInteiro(qtdMelhor, melhor);
    trataInteiro(qtdPior, pior);

    preencheScore(&atualizacao, id, qtdVezes, qtdTentUlt, qtdMelhor, qtdPior);

    if (qtdVezes > 1){
        arq = fopen("score.mmd", "r");

        if (arq == NULL)
        {
            printf("Problemas na abertura do arquivo\n");
            return;
        }

        i = 0;

        while (!feof(arq))
        {
            result = fgets(linha, 100, arq);
            if (result)
            {
                idJog[0] = linha[0];
                idJog[1] = linha[1];
                idJog[2] = linha[2];
                idJog[3] = '\0';

                if (strcmp(idJog, id) == 0)
                    lista[i] = atualizacao;
                else
                {
                    vezes[0] = linha[4];
                    vezes[1] = linha[5];
                    vezes[2] = linha[6];
                    vezes[3] = '\0';
                    iVezes = atoi(vezes);

                    ult[0] = linha[8];
                    ult[1] = linha[9];
                    ult[2] = linha[10];
                    ult[3] = '\0';
                    iUlt = atoi(ult);

                    melhor[0] = linha[12];
                    melhor[1] = linha[13];
                    melhor[2] = linha[14];
                    melhor[3] = '\0';
                    iMelhor = atoi(melhor);

                    pior[0] = linha[16];
                    pior[1] = linha[17];
                    pior[2] = linha[18];
                    pior[3] = '\0';
                    iPior = atoi(pior);

                    preencheScore(&lista[i], idJog, iVezes, iUlt, iMelhor, iPior);
                }

                i++;
            }
        }
        fclose(arq);
    }

    if (qtdVezes > 1){
        arq = fopen("score.mmd", "w");

        if (arq == NULL)
        {
            printf("Problemas na abertura do arquivo\n");
            return;
        }

        for (j = 0; j < i; j++)
        {
            trataInteiro(lista[j].qtdVezes, vezes);
            trataInteiro(lista[j].qtdTentUlt, ult);
            trataInteiro(lista[j].qtdMelhor, melhor);
            trataInteiro(lista[j].qtdPior, pior);

            strcpy(insere, lista[j].idJogador);
            strcat(insere, "*");
            strcat(insere, vezes);
            strcat(insere, "*");
            strcat(insere, ult);
            strcat(insere, "*");
            strcat(insere, melhor);
            strcat(insere, "*");
            strcat(insere, pior);
            strcat(insere, "\n");

            result = fputs(insere, arq);
        }
    }
    else{
        arq = fopen("score.mmd", "a");

        if (arq == NULL)
        {
            printf("Problemas na abertura do arquivo\n");
            return;
        }

        trataInteiro(atualizacao.qtdVezes, vezes);
        trataInteiro(atualizacao.qtdTentUlt, ult);
        trataInteiro(atualizacao.qtdMelhor, melhor);
        trataInteiro(atualizacao.qtdPior, pior);

        strcpy(insere, atualizacao.idJogador);
        strcat(insere, "*");
        strcat(insere, vezes);
        strcat(insere, "*");
        strcat(insere, ult);
        strcat(insere, "*");
        strcat(insere, melhor);
        strcat(insere, "*");
        strcat(insere, pior);
        strcat(insere, "\n");

        result = fputs(insere, arq);
    }

    if (result == EOF)
        printf("Erro na Gravacao\n");

    fclose(arq);
}

void verificaScore(char *idJogador[4], int scoreTentativa){
    FILE *arq;
    char linha[100], id[4], qtdVezes[4], qtdUlt[4], qtdMelhor[4], qtdPior[4];
    char *result;
    SCORE score;
    int i, j, vezes = 0, ult, melhor, pior;

    arq = fopen("score.mmd", "rt");

    if (arq == NULL){
        printf("Problemas na abertura do arquivo\n");
        return;
    }

    i = 0;

    while (!feof(arq)){
        result = fgets(linha, 100, arq);

        if (result)
        {
            id[0] = linha[0];
            id[1] = linha[1];
            id[2] = linha[2];
            id[3] = '\0';

            if (strcmp(idJogador, id) == 0)
            {
                qtdVezes[0] = linha[4];
                qtdVezes[1] = linha[5];
                qtdVezes[2] = linha[6];
                qtdVezes[3] = '\0';
                vezes = atoi(qtdVezes);
                vezes++;

                qtdMelhor[0] = linha[12];
                qtdMelhor[1] = linha[13];
                qtdMelhor[2] = linha[14];
                qtdMelhor[3] = '\0';
                melhor = atoi(qtdMelhor);

                if (scoreTentativa > melhor)
                {
                    melhor = scoreTentativa;
                }

                qtdPior[0] = linha[16];
                qtdPior[1] = linha[17];
                qtdPior[2] = linha[18];
                qtdPior[3] = '\0';
                pior = atoi(qtdPior);

                if (scoreTentativa < pior)
                {
                    pior = scoreTentativa;
                }

                insereScore(idJogador, vezes, scoreTentativa, melhor, pior);
            }
        }
    }

    if (vezes <= 1){
        insereScore(idJogador, 1, scoreTentativa, scoreTentativa, scoreTentativa);
    }

    fclose(arq);
}

void imprimeJogadores(JOGADOR lista[1000], int tamLista, char impressao[1000][2000]){
    SCORE listaScore[1000];
    char melhor[3];
    int i = 0, j = 0, tam = 0, score = 0, jogou = 0;
    tam = listaScores(listaScore);

    strcpy(impressao[0], "*-------------------------------------------------------------------------------------*\n");
    strcpy(impressao[1], "| ID  | NOME                          | APELIDO                       | IDADE | SCORE |\n");
    strcpy(impressao[2], "|-----|-------------------------------|-------------------------------|-------|-------|\n");
    for (i = 0; i < tamLista; i++){
        strcpy(impressao[i + 3], "| ");
        strcat(impressao[i + 3], lista[i].id);
        strcat(impressao[i + 3], " | ");
        strcat(impressao[i + 3], lista[i].nome);
        strcat(impressao[i + 3], "| ");
        strcat(impressao[i + 3], lista[i].apelido);
        strcat(impressao[i + 3], "|  ");
        strcat(impressao[i + 3], " ");
        strcat(impressao[i + 3], lista[i].idade);
        strcat(impressao[i + 3], " | ");
        score = 0;
        jogou = 0;

        for (j = 0; j < tam; j++)
        {
            if (strcmp(lista[i].id, listaScore[j].idJogador) == 0)
            {
                score = listaScore[j].qtdMelhor;
                jogou = 1;
            }
        }

        if (jogou == 1)
            trataInteiro(score, melhor);
        else
            strcpy(melhor, "-----");

        strcat(impressao[i + 3], melhor);
        strcat(impressao[i + 3], " |\n");
    }

    strcpy(impressao[i + 3], "*-------------------------------------------------------------------------------------*\n");
}

void trataString(int tam, char *string){
    int flag, i, j;
    char aux[tam];
    flag = 0;
    i = 0;

    for (j = tam - 1; j >= 0; j--){
        if (string[j] != ' ')
            flag = 1;

        if (flag > 0)
        {
            aux[j] = string[j];
            i++;
        }
    }

    aux[i] = '\0';

    strcpy(string, aux);
}

void trataInteiro(int val, char *string){
    char aux[3];

    sprintf(aux, "%d", val);

    if (val < 10){
        string[0] = '0';
        string[1] = '0';
        string[2] = aux[0];
    }
    else if (val < 100){
        string[0] = '0';
        string[1] = aux[0];
        string[2] = aux[1];
    }
    else{
        strcpy(string, aux);
    }

    string[3] = '\0';
}

void trataNome(char *string){
    int tam = 0, i = 0, j = 0;
    char aux[3];
    tam = strlen(string);

    for (i = 0; i <= tam; i++){
        if ((string[i] >= '!' && string[i] <= '@') || (string[i] >= '[' && string[i] <= '`') || (string[i] >= '{' && string[i] <= '~'))
        {
            for (j = i; j <= tam; j++)
                string[j] = string[j + 1];
            tam--;
            i--;
        }
    }

    string[tam] = '\0';

    for (i = 0; i <= tam; i++)
        string[i] = tolower(string[i]);

    string[0] = toupper(string[0]);
}