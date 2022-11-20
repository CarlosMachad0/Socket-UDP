/*Segundo exercicio
Para executar o programa digitar no terminal do ubuntu


$gcc ex2 -o 2
$./2 127.0.0.1 5000


Ao fim de 100 pacotes enviados, irão ser transmitidas as estatísticas



Objetivos todos atingidos.


*/



#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

void error(const char *);


int main(int argc, char *argv[])
{
    int sock, n;
    unsigned int length;
    struct sockaddr_in server, from;
    struct hostent *hp;
   
    if (argc != 3) { 
        printf("Usage: ./PingClient host port\n");
        exit(1);
    }
    printf("\n");
    
    
    //criação do datagram
    sock = socket(AF_INET, SOCK_DGRAM, 0);
    if (sock < 0) error("socket");
    struct timeval timeout = {1, 0};
    if (setsockopt(sock, SOL_SOCKET, SO_RCVTIMEO, (char*)&timeout, sizeof(struct timeval)) == -1) {
        error("setsockopt");
        exit(1);
    }

    // Conexão até ao host
    server.sin_family = AF_INET;
    hp = gethostbyname(argv[1]);
    if (hp==0) error("Unknown host");

    bcopy((char *)hp->h_addr, (char *)&server.sin_addr, hp->h_length);
    server.sin_port = htons(atoi(argv[2]));
    length=sizeof(struct sockaddr_in);

    int loss_count = 0;
    int time_recorded = 0;
    double min = 0.0;
    double mid = 0.0;
    double max = 0.0;
    double total = 0.0;
    
    
    //Ciclo for para mandar os 100 pacotes
    for(int i = 0; i < 100; i++) {
        char pingString[256];
        char nString[256];
        char timeString[256];
        char buffer[256];

        time_t rawtime;
        struct tm * timeinfo;
        time(&rawtime);
        timeinfo = localtime(&rawtime);
        struct timespec start, stop;
        double accum;
        if(clock_gettime(CLOCK_REALTIME, &start) == -1) {
            perror("clock gettime");
            exit(EXIT_FAILURE);
        }

        sprintf(pingString, "PING %d ", i);
        strftime(timeString, sizeof(timeString), "%H:%M:%S", timeinfo);
        strcpy(buffer, pingString);
        strcat(buffer, timeString);
        strcat(buffer, "\n");
        
        //Request
        n = sendto(sock, buffer, strlen(buffer), 0, (const struct sockaddr *)&server, length);
        if (n < 0) error("sendto");
        
        //A espera de resposta
        n = recvfrom(sock, buffer, 256, 0, (struct sockaddr *)&from, &length);
        if (n < 0) {
            loss_count++;
            printf("Request timeout.\n"); 
            continue;
        }
        if(clock_gettime(CLOCK_REALTIME, &stop) == -1) {
            perror("clock gettime");
            exit(EXIT_FAILURE);
        } 
        accum = ( stop.tv_sec - start.tv_sec ) * 1000.00 + ( stop.tv_nsec - start.tv_nsec ) /1000000.00;
        if(time_recorded == 0) {
            max = accum;
            min = accum;
        }
        time_recorded = 1;
        if(accum > max) max = accum;
        if(accum < min) min = accum;
        total += accum;
        sleep(1);

        printf("Ping Received From %s: ", argv[1]);
        printf("seq#=%i ", i);
        printf("time=%.*f ms\n", 3, accum);
        bzero(buffer, 256);
    }

    int received = 100 - loss_count;
   double percent = (loss_count / 100.0) * 100.0;
    printf("--- Estatisticas---\n");
    printf("Delta entre o primeiro e ultimo pacote enviado= %f ms\n", total);
    printf("100 pacotes enviados, %i pacotes recebidos, %.*f%% packet loss\n", received, 0,percent);
    if(time_recorded == 1) {
        double avg = total / received;
        printf("round-trip min/avg/max = %.*f/%.*f/%.*f ms\n", 3, min, 3, avg, 3, max);
    }
    printf("\n");

    close(sock);
    return 0;
}

void error(const char *msg)
{
    perror(msg);
    exit(0);
}
