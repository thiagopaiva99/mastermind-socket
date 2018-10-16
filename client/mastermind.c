#include<stdio.h> 
#include<string.h>    
#include <ctype.h>
#include <sys/socket.h> 
#include <sys/types.h>
#include <arpa/inet.h> 
#include <fcntl.h>

#define PORTA 6666
#define IP_HOST "10.0.2.15"

void Inserir (char * request[2000]) {
    char jogador[30];
    char apelido[30];
    char idade[3];

    int ok = 0;

    memset(request, 0x0, 2000);
    
    printf("*-------------------------------------*\n");
    printf("|                                     |\n");
    printf("|             Mastermind              |\n");
    printf("|     Adicionar um novo jogador       |\n");
    printf("|                                     |\n");
    printf("*-------------------------------------*\n");

    while ( ok == 0 ) {
        printf("\nNome do jogador \n");
        printf(">> ");

        fgets (jogador, 30, stdin); 
        __fpurge(stdin);

        if (strlen(jogador) > 1) {
            strtok(jogador, "\n");
            
            ok = 1;
        } else {            
            printf("É preciso digitar um nome para o jogador.\n\n");
            memset(jogador,0x0,30);
        }
    }

    ok = 0;

    while ( ok == 0 ) {
        printf("\n\nApelido do Jogador \n");
        printf(">> ");

        fgets (apelido, 30, stdin); 
        __fpurge(stdin);

        if (strlen(apelido) > 1) {
            strtok(apelido, "\n");
            
            ok = 1;            
        } else {
            printf("É preciso digitar um apelido para o jogador.\n\n");
            memset(apelido,0x0,30);
        }
    }

    ok = 0;

    while ( ok == 0 ) {
        printf("\n\nIdade do Jogador \n");
        printf(">> ");

        fgets (idade, 3, stdin);
        strtok(idade, "\n");

        __fpurge(stdin);
        if ( isdigit( idade[0] ) ) {
            if (strlen(idade) == 1) {
                ok = 1;
            } else {
                if (isdigit(idade[1])) {
                    ok = 1;
                }
            }
        } else {
            printf("Idade inválida (%s).\n\n", idade);
            memset(idade,0x0,3);
        }
    }

    system("clear");

    strcpy(request, "001");
    strcat(request, "*");  
    strcat(request, jogador);
    strcat(request, "*");    
    strcat(request, apelido);
    strcat(request, "*"); 
    strcat(request, idade);
    strcat(request, "*"); 
}

void Consultar (char * request[2000]) {
    char jogador[30];
    int ok = 0;

    memset(jogador,0x0,30);

    printf("*-------------------------------------*\n");
    printf("|                                     |\n");
    printf("|             Mastermind              |\n");
    printf("|      Buscar por algum jogador       |\n");
    printf("|                                     |\n");
    printf("*-------------------------------------*\n");

    while ( ok == 0 ) {
        printf("\nDigite o nome completo ou parcial do Jogador: \n");
        printf(">> ");

        fgets (jogador, 30, stdin); 
        __fpurge(stdin);

        if ( strlen(jogador) > 1 ) {
            strtok(jogador, "\n");
            
            ok = 1;
        } else {
            printf("É preciso digitar pelo menos um caractere para buscar o(s) jogador(es).\n\n");
            memset(jogador,0x0,30);
        }
    }

    strcpy(request, "002");
    strcat(request, "*");
    strcat(request, jogador);
    strcat(request, "*");
}

void Jogar (int sock) {
    char jogador[30];
    char id[4];
    char request[2000];
    char server_reply[2000];
    char entrada[4];
    
    int tentativa = 0;

    printf("*-------------------------------------*\n");
    printf("|                                     |\n");
    printf("|             Mastermind              |\n");
    printf("|               Jogar                 |\n");
    printf("|                                     |\n");
    printf("*-------------------------------------*\n");
    printf("\nDigite o nome do jogador");
    printf("\n\n>> ");

    fgets (jogador, 30, stdin);
    strtok(jogador, "\n");

    strcpy(request, "003");
    strcat(request, "*1*");
    strcat(request, jogador);
    strcat(request, "*");
    strcat(request, "\n");

    if ( send(sock , request , strlen(request) , 0) < 0 ) {
        puts("A funcao send falhou");
        return 1;
    }

    memset(server_reply,0x0,2000);  

    if ( recv(sock , server_reply , 2000 , 0) < 0 ) {
        puts("A funcao recv falhou");
    }
    
    if ( server_reply[0] == '*' ) {
        id[0] = server_reply[1];
        id[1] = server_reply[2];
        id[2] = server_reply[3];
        id[3] = '\0';
        
        memset(request,0x0,2000);
        strcpy(request, "003");
        strcat(request, "*2*");
        strcat(request, id);   
        strcat(request, "*");  
        strcat(request, "\n");
        
        system("clear");

        if ( send(sock , request , strlen(request) , 0) < 0 ) {
            puts("A funcao send falhou");
            return 1;
        }

        memset(server_reply,0x0,2000);  

        if ( recv(sock , server_reply , 2000 , 0) < 0 ) {
            puts("A funcao recv falhou");
        }

        puts(server_reply);

        for (tentativa = 0; tentativa < 10; tentativa++) {
            printf("Escolha 4 cores: \n");

            fgets (entrada, 5, stdin); 
            getchar(); 

            __fpurge(stdin);
            strcpy(request, entrada);
            
            if ( send(sock , request , strlen(request) , 0) < 0 ) {
                puts("A funcao send falhou");
                return 1;
            }

            memset(server_reply,0x0,2000);  

            if ( recv(sock , server_reply , 2000 , 0) < 0 ) {
                puts("A funcao recv falhou");
            }

            if ( server_reply[strlen(server_reply)-1] == '*' ) {
                server_reply[strlen(server_reply)-1] = ' '; 

                system("clear");     
            } else if ( server_reply[strlen(server_reply) - 1] == '#' ) {
                server_reply[strlen(server_reply) - 1] = ' ';
                tentativa = 10;
            } else {
                tentativa--;
            }

            system("clear");
            puts(server_reply);   
        }
    } else {
        system("clear");

        printf("*-------------------------------------*\n");
        printf("|                                     |\n");
        printf("|             Mastermind              |\n");
        printf("|       Jogador não encontrado        |\n");
        printf("|                                     |\n");
        printf("*-------------------------------------*\n");
    }
}


void Sortear(char * request[2000]) {
    int continuar = 1;

    do {
        printf("*-------------------------------------*\n");
        printf("|                                     |\n");
        printf("|             Mastermind              |\n");
        printf("|       Escolher tipo de jogo         |\n");
        printf("|                                     |\n");
        printf("*-------------------------------------*\n");
        printf("\n[ 1 ] EASY - Senha com cores que não se repetem.\n");
        printf("[ 2 ] HARD - Senha que repete as cores.\n\n");
        printf(">> ");
        
        scanf("%d", &continuar); 
        
        getchar();
        __fpurge(stdin);

        system("clear");

        switch( continuar ) {
            case 1:
                strcpy(request, "004");
                strcat(request, "*");
                strcat(request, "1");
                strcat(request, "*");

                continuar = 0;
            break;

            case 2:
                strcpy(request, "004");
                strcat(request, "*");
                strcat(request, "2");
                strcat(request, "*");

                continuar = 0;
            break;

            default:
                printf("Digite uma opcao valida\n");
        }
    } while( continuar );    
}

void Sobre () {
    char about[100];

    printf("Digite algo para voltar\n");

    fgets (about, 100, stdin); 
    __fpurge(stdin);

    system("clear");
}

int main(int argc , char *argv[])
{
    int     sock;
    struct  sockaddr_in server;
    char    message[2000];
    char    server_reply[2000];
    char    ip_host[17];
    int     continuar = 1;
    char    id[3];

    system("clear");

    sock = socket( AF_INET , SOCK_STREAM , 0 );

    if ( sock == -1 ) {
        printf("*-------------------------------------*\n");
        printf("|                                     |\n");
        printf("|  Não foi possivel criar o socket.   |\n");
        printf("|                                     |\n");
        printf("*-------------------------------------*\n");
    }

    printf("*-------------------------------------*\n");
    printf("|                                     |\n");
    printf("|     Digite o IP do servidor.        |\n");
    printf("|                                     |\n");
    printf("*-------------------------------------*\n");
    printf("\n>> ");

    fgets (ip_host, 17, stdin);
    
    server.sin_addr.s_addr  = inet_addr(ip_host);
    server.sin_family       = AF_INET;
    server.sin_port         = htons(PORTA);

    int     status;
    long    arg;
    struct  timeval  timeout;

    timeout.tv_sec = 10;
    timeout.tv_usec = 0;

    fd_set set;

    FD_ZERO( &set );
    FD_SET( sock, &set );

    fcntl(sock, F_SETFL, O_NONBLOCK);

    connect(sock, (struct sockaddr *)&server , sizeof(server));

    if ( select( sock + 1, NULL, &set, NULL, &timeout ) == 1 ) {
        int so_error;
        socklen_t len = sizeof so_error;

        getsockopt(sock, SOL_SOCKET, SO_ERROR, &so_error, &len);

        if ( so_error != 0 ) {
            system("clear");
            printf("*-----------------------------------------*\n");
            printf("|                                         |\n");
            printf("|  Não foi possível conectar ao servidor. |\n");
            printf("|                                         |\n");
            printf("*-----------------------------------------*\n");

            return 1;
        } else {
            fcntl(sock, F_GETFL, NULL);
            arg &= (~O_NONBLOCK); 

            fcntl(sock, F_SETFL, arg);
            printf("\nConectado!\n");
        }
    } else {
        perror("ERRO: A conexao falhou.");
        return 1;
    }     
    
    system("clear");

    do {
        printf("*---------------------*\n");
        printf("|                     |\n");
        printf("|      MasterMind     |\n");
        printf("|                     |\n");
        printf("*---------------------*\n");
        printf("\nSelecione a opção desejada:\n\n");
        printf("[ 1 ] Novo jogador\n");
        printf("[ 2 ] Buscar Jogador\n");
        printf("[ 3 ] Jogar\n");
        printf("[ 4 ] Modo de Jogo\n");
        printf("[ 5 ] Ranking\n");
        printf("[ 6 ] Sobre\n");
        printf("[ 0 ] Sair\n\n");
        printf("\n>> ");

        scanf("%d", &continuar); 
        
        getchar();
        __fpurge(stdin);

        system("clear");

        switch( continuar ) {
            case 1:
	            Inserir(message);

                if ( strcmp(message, "999") != 0 ) {
                    if( send(sock , message , strlen(message) , 0) < 0) {
                        perror("A funcao send falhou");
                        return 1;
                    }

                    memset(server_reply,0x0,2000);

                    if( recv(sock , server_reply , 2000 , 0) < 0) {
                        perror("A funcao recv falhou");
                        break;
                    }   

                    puts(server_reply);
                }
            break;

            case 2:
                Consultar(message);
                if( send(sock , message , strlen(message) , 0) < 0) {
                    perror("A funcao send falhou");
                    return 1;
                }
                
                memset(server_reply, 0x0, 2000);
                if( recv(sock , server_reply , 2000 , 0) < 0 ) {
                    perror("A funcao recv falhou");
                    break;
                }

                puts(server_reply);
            break;

            case 3:
                Jogar(sock);
            break;

            case 4:
                Sortear(message);
                
                if( send(sock , message , strlen(message) , 0) < 0) {
                    puts("A funcao send falhou");
                    return 1;
                }

                memset(server_reply, 0x0, 2000);

                if( recv(sock , server_reply , 2000 , 0) < 0 ) {
                    puts("A funcao recv falhou");
                    break;
                }

                puts(server_reply); 
            break;

            case 5:
                strcpy(message, "005");

                if( send(sock , message , strlen(message) , 0) < 0) {
                    puts("A funcao send falhou");
                    return 1;
                }

                memset(server_reply,0x0,2000);

                if( recv(sock , server_reply , 2000 , 0) < 0 ) {
                    puts("A funcao recv falhou");
                    break;
                }

                puts(server_reply);
            break;

            case 6:
                strcpy(message, "006"); 

                if( send(sock , message , strlen(message) , 0) < 0 ) {
                    puts("A funcao send falhou");
                    return 1;
                }

                memset(server_reply, 0x0, 2000);

                if( recv(sock , server_reply , 2000 , 0) < 0 ) {
                    puts("A funcao recv falhou");
                    break;
                }

                puts(server_reply);
                
                Sobre();
            break;

            case 0:
            break;

            default:
                printf("Digite uma opcao valida\n");
        }
    } while(continuar);
 
    close(sock);

    return 0;
}
