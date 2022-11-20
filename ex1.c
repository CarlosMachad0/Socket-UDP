/*Primeiro exercicio
Para executar o programa digitar no terminal do ubuntu


$gcc ex1 -o 1
$./1

Para sair da execução do programa e imprimir as estatísticas, faça CTRL + C


Não consegui atingir todos os objetivos para este exercicio, estatisticas de jitter não apresentadas, número de pacotes recebidos em forma de ordenação de ping e apresentação do horario dos pings enviados de forma a vermos o delta.





*/




#include <stdio.h>
#include <strings.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include<netinet/in.h>
#include <stdbool.h>
#include<string.h>
#define PORT 5000
#define MAXLINE 1000


int main()
{
	char buffer[100];
	char *message = "Hello Client";
	int listenfd, len;
	struct sockaddr_in servaddr, cliaddr;
	bzero(&servaddr, sizeof(servaddr));

	// Criação do UDP Socket
	listenfd = socket(AF_INET, SOCK_DGRAM, 0);		
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	servaddr.sin_port = htons(PORT);
	servaddr.sin_family = AF_INET;

	// bind server address para o socket
	bind(listenfd, (struct sockaddr*)&servaddr, sizeof(servaddr));
	
	
	
        //Função while para correr sempre o programa	
        while(true){	
      
	//receber o datagram
	len = sizeof(cliaddr);
	int n = recvfrom(listenfd, buffer, sizeof(buffer), 0, (struct sockaddr*)&cliaddr,&len); //receber a mensagem 
	
	buffer[n] = '\0';
	
	puts(buffer);
	
	
		     	
	// enviar a resposta
	sendto(listenfd, message, MAXLINE, 0, (struct sockaddr*)&cliaddr, sizeof(cliaddr));
		
	  
	}	
	
}

