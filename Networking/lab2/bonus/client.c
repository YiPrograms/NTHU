#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h> 
#include <sys/socket.h>
#include <netinet/in.h>
#include <time.h>
#include <arpa/inet.h> 

#include <errno.h>
#define WND_SIZE 4
/*****************notice**********************
 * 
 * You can follow the comment inside the code.
 * This kind of comment is for basic part.
 * =============== 
 * Some hints...
 * ===============
 * 
 * This kind of comment is for bonus part.
 * ---------------
 * Some hints...
 * ---------------
 * 
 * 
 * 
 *********************************************/

//==============
// Packet header 
//==============
typedef struct header{
	unsigned int seq_num;
	unsigned int ack_num;
	unsigned char is_last;
}Header;

//==================
// Udp packet & data 
//==================
typedef struct udp_pkt{
	Header header;
	char data[1024];
}Udp_pkt; 

//============
// Declaration
//============
int sockfd = 0;
Udp_pkt snd_pkt,rcv_pkt;
struct sockaddr_in info, client_info;
socklen_t len;
time_t t1, t2;

char buffer[150000];
int window[15000];

const size_t datasize = sizeof(snd_pkt.data);


//=====================
// Simulate packet loss
//=====================
int isLoss(double prob)
{
    double thres = prob * RAND_MAX;
    
    if(prob >= 1)
        return 1;//loss
    return (rand() <= thres);//not loss
}

//==================================
// You should complete this cunction
//==================================
int recvFile(FILE *fd)
{
	printf("FILE_EXISTS\n");

	char* str;
	char fileName[30];

	//==================================================================
	// Split the command into "download" & "filename", just get filename
	//==================================================================
	str = strtok(snd_pkt.data, " \n");	
	str = strtok(NULL, " \n");			
	
	sprintf(fileName, "download_");
	strcat(fileName, str);
	
	//FILE *fd;
	fd = fopen(fileName, "wb");


	struct timeval tv;
	tv.tv_sec = 3;
	tv.tv_usec = 0;
	setsockopt(sockfd, SOL_SOCKET, SO_RCVTIMEO, (const char*)&tv, sizeof tv);

	
	printf("Receiving...\n");
	memset(window, 0, sizeof(window));
	int cur_window = 0;
	int filesize = 0;
	int done=0;
	int last_packet = -100;
	memset(snd_pkt.data, '\0', sizeof(snd_pkt.data));
	while(!done) 
	{
		//=========================================================
		// You should receive packet at the beginning of while loop		
		//=========================================================
		// eg. while(recvfrom()....)
		int numbytes;
		while ((numbytes = recvfrom(sockfd, &rcv_pkt, sizeof(rcv_pkt), 0, (struct sockaddr *)&client_info, (socklen_t *)&len)) != -1) {

			//=======================
			// Simulation packet loss
			//=======================
			if(isLoss(0.5))
			{
				printf("\tOops! Packet loss!\n");
				break;
			}

			
			printf("\tReceived a packet seq_num = %d\n", rcv_pkt.header.seq_num);

			// Ignore packets that is over client's window size
			if (rcv_pkt.header.seq_num >= cur_window + WND_SIZE) {
				printf("\tOops! Over window size!\n");
				break;
			}
			
			//====================
			// Reply ack to server
			//====================
			int sendlen;
			snd_pkt.header.ack_num = rcv_pkt.header.seq_num;
			if ((sendlen = sendto(sockfd, &snd_pkt, sizeof(snd_pkt), 0,(struct sockaddr *)&client_info, len)) == -1) 
			{
				printf("sendto error\n");
				return 0;
			}


			// We've already received the packet before, so we just send ACK back to the server
			if (window[rcv_pkt.header.seq_num])
				break;
			
			//==============================================
			// Actually receive packet and write into buffer
			//==============================================

			// Track the last packet
			if (rcv_pkt.header.is_last)
				last_packet = rcv_pkt.header.seq_num;

			// Copy the data to our buffer, and track file size
			memcpy(buffer + rcv_pkt.header.seq_num * datasize, rcv_pkt.data, numbytes - sizeof(rcv_pkt.header));
			filesize += numbytes - sizeof(rcv_pkt.header);
			window[rcv_pkt.header.seq_num] = 1;

			// Move window forward if in-sequence packets are acked
			while (window[cur_window])
				cur_window++;

			// All packets are received
			if (cur_window == last_packet + 1){
				fwrite(buffer, 1, filesize, fd);
				printf("client received finished\n");
				done = 1;
				break;
			}
		}

		if (numbytes == -1) {
			int err = errno;
			if (err == EAGAIN)
				printf("Socket timeout! errno: %d\n", err);
			else
				printf("Socket error occurred! errno: %d\n", err);
		}
	}
	fclose(fd);
	return 0;
}

int main(int argc, char *argv[])
{
	//==============
	// Create socket
	//==============
	//int sockfd = 0;
	sockfd = socket(AF_INET , SOCK_DGRAM , 0);
	if (sockfd == -1)
	{
		printf("Fail to create a socket.");
	}

	//==================
	// Input server info
	//==================
	//struct sockaddr_in info;
	bzero(&info,sizeof(info));
	info.sin_family = AF_INET;

	char* server_ip=(char *)malloc(sizeof(char)*30);
	int server_port;

	printf("give me an IP to send: ");
	scanf("%s",server_ip);
	printf("server's's port? ");
	scanf("%d",&server_port);

	//==================================
	// Just test how to convert the type
	//==================================	
	info.sin_addr.s_addr = inet_addr(server_ip);
	info.sin_port = htons(server_port);

	server_port=htons(info.sin_port);
	server_ip=inet_ntoa(info.sin_addr);
	//printf("server %s : %d\n", server_ip, server_port);


	//====================================
	// Create send packet & receive packet
	//====================================
	memset(snd_pkt.data, '\0', sizeof(snd_pkt.data));
	len = sizeof(info);

	printf("Waiting for a commands...\n");
	getchar();
	while(fgets(snd_pkt.data, 30, stdin)) 
	{
        
		// ================================
		// command "exit": close the client
		// ================================
		if(strncmp(snd_pkt.data, "exit", 4) == 0) 
		{
			break;
		}
		// ==============================================================
		// command "download filename": download the file from the server
		// ==============================================================        
		else if(strncmp(snd_pkt.data, "download", 8) == 0) 
		{
			snd_pkt.header.seq_num = 0;
			snd_pkt.header.ack_num = 0;
			snd_pkt.header.is_last = 1;
			//We first set is_last to 1 so that server know its our first message.
			int numbytes;
			FILE* fd;
			//========================
			// Send filename to server
			//========================
			if ((numbytes = sendto(sockfd, &snd_pkt, sizeof(snd_pkt), 0,(struct sockaddr *)&info, len)) == -1) 
			{
				perror("error");
				return 0;
			}
			printf("client: sent %d bytes to %s\n", numbytes,inet_ntoa(info.sin_addr));
			//=========================================
			// Get server response if file exist or not
			//=========================================
			if ((numbytes = recvfrom(sockfd, &rcv_pkt, sizeof(rcv_pkt), 0, (struct sockaddr *)&info, (socklen_t *)&len)) == -1)
			{
				printf("recvfrom error\n");
				return 0;
			}	
			printf("client: receive %d bytes from %s\n", numbytes,inet_ntoa(info.sin_addr));
			//printf("%s", buf);
			
			//====================
			// File does not exist
			//====================
			if(strcmp(rcv_pkt.data,"FILE_NOT_EXISTS") == 0) 
			{
				printf("FILE_NOT_EXISTS\n");
			} 
			//==========================
			// File exists, receive file
			//==========================
			else if(strcmp(rcv_pkt.data,"FILE_EXISTS") == 0) 
			{
				t1=time(NULL);
				recvFile(fd);
				t2=time(NULL);
				printf("Total cost %ld secs\n",t2-t1);
			}	
			
		}
		else 
		{
			printf("Illegal command\n");	
		}
        
	printf("Waiting for a commands...\n");
    }

}


