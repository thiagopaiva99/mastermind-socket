#include <stdio.h>
#include <string.h>
#include <time.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include "mastermind.h"
#include "database.h"
#define CORES "AZBVDP\0"
#define AJUDA "-o*\0"
#define PORTA 6666

void Inserir(char *request[2000], char *answer[2000], char nomearquivo[200])
{
    char jogador[30], apelido[30], idade[3], aux[2000];
    int inseriu = 0, i = 0, j = 0, inicio, fim;
    FILE *arq;
    char *result, insere[200];

    arq = fopen(nomearquivo, "a");

    if (arq == NULL)
    { 
        printf("Problemas na abertura do arquivo\n");
    }

    strcpy(aux, request);

    inicio = strchr(aux, '*') - aux; 
    aux[inicio] = '+';               
    inicio++;                        
    fim = strchr(aux, '*') - aux;    

    for (i = inicio; i < fim; i++)
    {
        jogador[i - inicio] = aux[i];
    }
    jogador[i - inicio] = '\0';

    inicio = strchr(aux, '*') - aux; 
    aux[inicio] = '+';               
    inicio++;                        
    fim = strchr(aux, '*') - aux;    

    for (i = inicio; i < fim; i++)
    {
        apelido[i - inicio] = aux[i];
    }
    apelido[i - inicio] = '\0';

    inicio = strchr(aux, '*') - aux; 
    aux[inicio] = '+';               
    inicio++;                        
    fim = strchr(aux, '*') - aux;    

    for (i = inicio; i < fim; i++)
    {
        idade[i - inicio] = aux[i]; 
    }
    idade[i - inicio] = '\0';

    strcpy(insere, "\n> INSERIR JOGADOR\n");
    strcat(insere, "> Nome: ");
    strcat(insere, jogador);
    strcat(insere, ".\n> Apelido: ");
    strcat(insere, apelido);
    strcat(insere, ".\n> Idade: ");
    strcat(insere, idade);
    strcat(insere, ".\n");

    inseriu = insereJogador(jogador, apelido, idade);

    if (inseriu > 0)
    {
        strcpy(answer, "Jogador Inserido com Sucesso: ");
        strcat(answer, jogador);
        strcat(insere, "> Jogador Inserido com Sucesso.\n");
    }
    else if (inseriu < 0)
    {
        strcpy(answer, "ERRO: Problemas na inserção do Jogador: ");
        strcat(answer, jogador);
        strcat(answer, "(database corrompida)");
        strcat(insere, "> ERRO: Problemas na inserção do Jogador.\n");
    }
    else
    {
        strcpy(answer, "ERRO: Já existe um jogador com esse nome na base: ");
        strcat(answer, jogador);
        strcat(insere, "> ERRO: Já existe um jogador com o nome na base.\n");
    }
    result = fputs(insere, arq);
    fclose(arq);
}

void Consultar(char *request[2000], char *impressao[20000], char nomearquivo[200])
{
    JOGADOR lista[1000], retorno[1000];
    char jogador[30], nome[30], *pos, aux[2000], respostas[1000][2000];
    int tam = 0, i = 0, k = 0, inicio, fim;
    FILE *arq;
    char *result, insere[200];

    tam = listaJogadores(lista);

    strcpy(aux, request);

    inicio = strchr(aux, '*') - aux; 
    aux[inicio] = '+';               
    inicio++;                        
    fim = strchr(aux, '*') - aux;    

    for (i = inicio; i < fim; i++)
    {
        jogador[i - inicio] = aux[i];
    }
    jogador[i - inicio] = '\0';

    arq = fopen(nomearquivo, "a");

    if (arq == NULL)
    { 
        printf("Problemas na abertura do arquivo\n");
    }
    strcpy(insere, "\n> BUSCAR JOGADOR\n");
    strcat(insere, "> Nome Parcial: ");
    strcat(insere, jogador);
    strcat(insere, "\n");

    trataNome(jogador);


    if (strlen(jogador) == 0)
    {
        strcat(insere, "> Nome INVALIDO \n");
        strcpy(impressao, "Nome Invalido (Com caracteres especiais ou Numeros)!");
        strcat(impressao, "\n");
    }
    else
    {
        jogador[0] = tolower(jogador[0]);

        k = 0;
        for (i = 0; i < tam; i++)
        {
            strcpy(nome, lista[i].nome);
            nome[0] = tolower(nome[0]);

            pos = strstr(nome, jogador);
            if (pos != NULL)
            {
                retorno[k] = lista[i]; 
                k++;
            }
        }

        memset(impressao, 0x0, 2000); 

        if (k > 0)
        {
            strcat(insere, "> Encontrou Jogador!\n");
            imprimeJogadores(retorno, k, respostas); 

            for (i = 0; i < k + 4; i++)
            {
                strcat(impressao, respostas[i]);
                strcat(insere, respostas[i]); 
            }
        }
        else
        {
            strcat(insere, "> NAO Encontrou Jogador!\n");
            strcpy(impressao, "Não encontrou nenhum jogador com a parcial: ");
            strcat(impressao, jogador);
            strcat(impressao, "\n");
        }
    }
    result = fputs(insere, arq);
    fclose(arq);
}

void Jogar(char *request[2000], char *senha[4], int socket, char nomearquivo[200])
{
    char jogador[30], id[3], aux[2000], impressao[20000], entrada[4], saida[4], pontuacao[3];
    int i, inicio, fim, tentativa, valida = 0, score = 0;
    JOGADA tabela[9];
    FILE *arq;
    char *result, insere[2000];

    arq = fopen(nomearquivo, "a");

    if (arq == NULL)
    { 
        printf("Problemas na abertura do arquivo\n");
    }
    strcpy(insere, "\n> JOGAR\n");

    strcpy(aux, request);

    inicio = strchr(aux, '*') - aux; 
    aux[inicio] = '+';               
    inicio++;                        

    if (aux[inicio] == '1')
    {
        inicio = strchr(aux, '*') - aux; 
        aux[inicio] = '+';               
        inicio++;                        
        fim = strchr(aux, '*') - aux;    

        for (i = inicio; i < fim; i++)
        {
            jogador[i - inicio] = aux[i]; 
        }
        jogador[i - inicio] = '\0';

        trataNome(jogador); 


        strcat(insere, "> BUSCAR JOGADOR PARA INICIAR JOGO\n");
        strcat(insere, "> Nome Completo: ");
        strcat(insere, jogador);
        strcat(insere, ".\n");

        escolheJogador(jogador, id);

        memset(impressao, 0x0, 2000);

        if (strcmp(id, "XXX") == 0)
        {
            strcat(insere, "> Jogador NAO ENCONTRADO\n");
            strcpy(impressao, "Jogador NAO ENCONTRADO\n");
        }
        else
        {
            strcat(insere, "> ID Jogador: ");
            strcat(insere, id);
            strcat(insere, "\n");
            strcpy(impressao, "*");
            strcat(impressao, id);
            strcat(impressao, "*\n");
        }

        write(socket, impressao, strlen(impressao));
    }
    else if (aux[inicio] == '2')
    {
        inicio = strchr(aux, '*') - aux; 
        aux[inicio] = '+';               
        inicio++;                        
        fim = strchr(aux, '*') - aux;    

        for (i = inicio; i < fim; i++)
        {
            id[i - inicio] = aux[i]; 
        }
        id[i - inicio] = '\0';

        strcat(insere, "> INICIA JOGO\n");
        cabecMaster(CORES, AJUDA, impressao);
        iniciaJogada(&tabela);               
        write(socket, impressao, strlen(impressao));

        if (strcmp(senha, "----") == 0)
        {
            sorteioEasy(senha); 
        }                       

        printf("Senha Gerada: %s\n", senha);

        for (tentativa = 0; tentativa < 10; tentativa++)
        {
            memset(request, 0x0, 2000);
            recv(socket, request, 2000, 0);

            strcpy(entrada, request);

            valida = 0;
            valida = valEntrada(entrada, CORES); 

            if (valida == 0)
            {
                sinalizacao(entrada, senha, &saida); 
                preenche(&tabela[tentativa], tentativa + 1, entrada, saida);
                
                strcat(insere, "> Entrada: ");
                strcat(insere, entrada);
                strcat(insere, " > Saida: ");
                strcat(insere, saida);
                strcat(insere, "\n");

                exibe(tabela, CORES, AJUDA, impressao); 

                if (strcmp(saida, "****") == 0)
                { 
                    score = 10 - tentativa; 
                    score = score * 10;

                    strcat(impressao, "\n\n=======================================\n\n");
                    strcat(impressao, "*-------------------------------------*\n");
                    strcat(impressao, "|                                     |\n");
                    strcat(impressao, "|             Mastermind              |\n");
                    strcat(impressao, "|       Você Ganhou! Score: ");
                    sprintf(&pontuacao, "%d", score);
                    strcat(impressao, pontuacao);
                    strcat(impressao, "        |\n");
                    strcat(impressao, "|                                     |\n");
                    strcat(impressao, "*-------------------------------------*\n\n");
                    strcat(impressao, "=======================================\n\n");
                    verificaScore(id, score); 
                    tentativa = 10;
                    impressao[strlen(impressao)] = '#'; 
                    impressao[strlen(impressao) + 1] = '\0';
                    strcat(insere, "> GANHADOR\n");
                    strcpy(senha, "----");
                }
                else if (strcmp(saida, "****") != 0 && tentativa == 9)
                {
                    strcat(impressao, "\n    -= INFELIZMENTE VOCE NAO DESCOBRIU A SENHA: ");
                    strcat(impressao, senha);
                    strcat(impressao, " =-\n");
                    score = 0;
                    strcat(impressao, "    -=           SCORE: ");
                    sprintf(&pontuacao, "%d", score);
                    strcat(impressao, pontuacao);
                    strcat(impressao, "            =-\n\n");
                    impressao[strlen(impressao)] = '#';
                    impressao[strlen(impressao) + 1] = '\0';
                }
                else
                {
                    impressao[strlen(impressao)] = '*'; 
                    impressao[strlen(impressao) + 1] = '\0';
                }
                write(socket, impressao, strlen(impressao));
            }
            else
            {
                strcat(insere, "> ERRO: entrada invalida > ");
                strcat(insere, entrada);
                strcat(insere, "\n");
                strcpy(impressao, "ERRO: entrada invalida! \nTENTE NOVAMENTE \n"); 
                write(socket, impressao, strlen(impressao));                       
                tentativa--;
            }
        }

        if (strcmp(saida, "****") != 0)
        {
            strcat(impressao, "\n    -= INFELIZMENTE VOCE NAO DESCOBRIU A SENHA: ");
            strcat(impressao, senha);
            strcat(impressao, " =-\n");
            score = 0;
            strcat(impressao, "    -=           SCORE: ");
            sprintf(&pontuacao, "%d", score);
            strcat(impressao, pontuacao);
            strcat(impressao, "            =-\n\n");
            impressao[strlen(impressao)] = '#';
            impressao[strlen(impressao) + 1] = '\0';

            verificaScore(id, score);

            strcat(insere, "> NAO GANHOU\n");
            write(socket, impressao, strlen(impressao)); 
            strcpy(senha, "----");                       
        }
    }
    result = fputs(insere, arq);
    fclose(arq);
}

void Sortear(char *request[2000], char *answer[2000], char *senha[4], char nomearquivo[200])
{
    char aux[2000];
    int inicio, fim;
    FILE *arq;
    char *result, insere[2000];

    arq = fopen(nomearquivo, "a");

    if (arq == NULL)
    {
        printf("Problemas na abertura do arquivo\n");
    }

    strcpy(aux, request);

    strcpy(insere, "\n> SORTEIA SENHA\n");

    inicio = strchr(aux, '*') - aux;
    inicio++;
    
    if (aux[inicio] == '2')
    {
        sorteioHard(senha);
        strcat(insere, "> Senha HARD: ");
        strcat(insere, senha);
        strcat(insere, "\n");
        strcpy(answer, "Uma senha que pode repetir as cores será gerada!\nBoa Sorte!\n");
    }
    else
    {
        sorteioEasy(senha);
        printf("> Senha EASY: %s\n", senha);
        strcat(insere, "> Senha EASY: ");
        strcat(insere, senha);
        strcat(insere, "\n");
        strcpy(answer, "");
    }

    result = fputs(insere, arq);
    fclose(arq);
}

void Estatistica(char *impressao[20000], char nomearquivo[200])
{
    SCORE lista[1000], ranking[1000];
    char idPrimeiro[3], nomeExibe[30], vezes[3], ult[3], melhor[3], pior[3], aux[3];
    int score = 0;
    int tam = 0, i = 0, j = 0, k = 0;
    FILE *arq;
    char *result, insere[2000];

    tam = listaScores(lista);

    arq = fopen(nomearquivo, "a");

    if (arq == NULL)
    {
        printf("Problemas na abertura do arquivo\n");
    }
    strcpy(insere, "\n> ESTATISTICAS\n");

    for (i = 0; i < tam; i++)
    {
        score = 0;
        for (j = 0; j < tam; j++)
        {
            if (lista[j].qtdMelhor > score && i == 0)
            {
                score = lista[j].qtdMelhor;
                ranking[i] = lista[j];
            }
            else
            {
                if (lista[j].qtdMelhor <= ranking[i - 1].qtdMelhor && lista[j].qtdMelhor > score)
                { 
                  
                    if (lista[j].qtdMelhor == ranking[i - 1].qtdMelhor && lista[j].qtdPior > ranking[i - 1].qtdPior)
                    {
                        score = lista[j].qtdMelhor;
                        ranking[i] = ranking[i - 1];
                        ranking[i - 1] = lista[j];
                    }
                    else
                    {
                        score = lista[j].qtdMelhor; 
                        ranking[i] = lista[j];      
                    }
                }
            }
        }
        for (j = 0; j < tam; j++)
        {
            for (k = 0; k < tam; k++)
            {
                if (strcmp(lista[j].idJogador, ranking[k].idJogador) == 0)
                {
                    lista[j].qtdMelhor = -1;
                }
            }
        }
    }

    strcat(impressao, "Id Nome                           Melhor   Pior   Última  Vezes \n");
    for (i = 0; i < tam; i++)
    {
        strcpy(idPrimeiro, ranking[i].idJogador);
        findJogadorID(idPrimeiro, nomeExibe);       
        trataInteiro(ranking[i].qtdVezes, vezes);   
        trataInteiro(ranking[i].qtdTentUlt, ult);   
        trataInteiro(ranking[i].qtdMelhor, melhor); 
        trataInteiro(ranking[i].qtdPior, pior);     
        strcat(impressao, ranking[i].idJogador);
        strcat(impressao, nomeExibe);
        strcat(impressao, "  ");
        strcat(impressao, melhor);
        strcat(impressao, "     ");
        strcat(impressao, pior);
        strcat(impressao, "     ");
        strcat(impressao, ult);
        strcat(impressao, "     ");
        strcat(impressao, vezes);
        strcat(impressao, "  \n");

        strcat(insere, "> ");
        sprintf(aux, "%d", i + 1);
        strcat(insere, aux);
        strcat(insere, "o Jogador: ");
        strcat(insere, nomeExibe);
        strcat(insere, "\n");
    }

    strcat(insere, impressao);
    result = fputs(insere, arq);
    fclose(arq);
}

int main(int argc, char *argv[])
{
    int socket_desc, client_sock, c, read_size, escolha, i, tamResposta;
    struct sockaddr_in server, client;
    char client_message[2000], game_answer[2000], id_func[4], game_answers[20000], nomarq[200];
    FILE *arq;
    char *result, insere[50];

    system("clear");

    socket_desc = socket(AF_INET, SOCK_STREAM, 0);
    if (socket_desc == -1)
    {
        printf("Nao foi possivel criar o socket.\nVerifique se a porta não estah sendo usada.");
    }
    puts("Socket criado.");

    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons(PORTA);

    if (bind(socket_desc, (struct sockaddr *)&server, sizeof(server)) < 0)
    {
        perror("Comando bind falhou.");
        return 1;
    }
    puts("Comando bind funcionou.");

    listen(socket_desc, 1);

    puts("Aguardando Conexoes...");
    c = sizeof(struct sockaddr_in);

    client_sock = accept(socket_desc, (struct sockaddr *)&client, (socklen_t *)&c);
    if (client_sock < 0)
    {
        perror("Comando accept falhou!");
        return 1;
    }
    printf("Conexao aceita. \nCliente Conectado: %s\n", inet_ntoa(client.sin_addr));

    strcpy(nomarq, "Logs/");
    strcat(nomarq, inet_ntoa(client.sin_addr));
    strcat(nomarq, "-");
    strcat(nomarq, __DATE__);

    arq = fopen(nomarq, "a");
    if (arq == NULL)
    {
        printf("Problemas na abertura do arquivo\n");
        return;
    }

    strcpy(insere, "> Cliente Conectado: ");
    strcat(insere, inet_ntoa(client.sin_addr));
    strcat(insere, "\n");
    result = fputs(insere, arq);

    fclose(arq);
    char senha[4];
    strcpy(senha, "----");
    inicia(CORES, AJUDA);

    while ((read_size = recv(client_sock, client_message, 2000, 0)) > 0)
    {
        memset(game_answer, 0x0, 2000);   
        memset(game_answers, 0x0, 20000); 

        id_func[0] = client_message[0];
        id_func[1] = client_message[1];
        id_func[2] = client_message[2];
        id_func[3] = '\0';

        escolha = atoi(id_func);
        switch (escolha)
        {
        case 1:
            Inserir(client_message, game_answer, nomarq);
            write(client_sock, game_answer, strlen(game_answer));
            break;
        case 2:
            Consultar(client_message, game_answers, nomarq);
            write(client_sock, game_answers, strlen(game_answers));
            break;
        case 3:
            Jogar(client_message, senha, client_sock, nomarq);
            break;
        case 4:
            Sortear(client_message, game_answer, senha, nomarq);
            write(client_sock, game_answer, strlen(game_answer));
            break;
        case 5:
            Estatistica(game_answers, nomarq);
            write(client_sock, game_answers, strlen(game_answers));
            break;
        case 6:
            arq = fopen(nomarq, "a");
            result = fputs(insere, arq);
            fclose(arq);
            sobreMaster(CORES, AJUDA, game_answers);
            write(client_sock, game_answers, strlen(game_answers));
            break;
        default:
            printf("\n\nErro.\n");
        }
    }

    printf("\n");

    if (read_size == 0)
    {
        puts("> O Cliente Desconectou.");
        arq = fopen(nomarq, "a");
        strcpy(insere, "\nO Cliente desconectou\n DIA: ");
        strcat(insere, __DATE__);
        strcat(insere, "\nHORA: ");
        strcat(insere, __TIME__);
        strcat(insere, "\n\n\n");
        result = fputs(insere, arq);
        fclose(arq);
    }
    else if (read_size == -1)
    {
        perror("Comando recv falhou!");
    }

    return 0;
}
