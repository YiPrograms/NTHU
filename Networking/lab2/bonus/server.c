#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h> 
#include <sys/socket.h>
#include <netinet/in.h>
#include <time.h>
#include <arpa/inet.h> 
#include <sys/wait.h>
#include <pthread.h>
#include <math.h>
#define TIMEOUT 100
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
	unsigned char isLast;
}Header;

//==================
// Udp packet & data 
//==================
typedef struct udp_pkt{
	Header header;
	char data[1024];
}Udp_pkt;

//=============
// Declaration
//=============
int sockfd;
struct sockaddr_in info, client_info;
Udp_pkt snd_pkt,rcv_pkt;
socklen_t len;
pthread_t th1,th2;
int first_time_create_thread = 0;

char buffer[150000];
int window[15000];
int filesize;

const size_t datasize = sizeof(snd_pkt.data);

typedef enum _WND_STATE{
	NOT_SENT,
	SENT,
	ACKED
} WND_STATE;

//---------------------------------------
// Declare for critical section in bonus. 
//---------------------------------------
/*******************notice*******************************
 * 
 * If you dont need the bonus point, ignore this comment.
 * Use it like following block.
 * 
 * pthread_mutex_lock( &mutex );
 * ...
 * critical section
 * ...
 * pthread_mutex_unlock( &mutex );
 * 
 *********************************************************/
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;


//------------------------------
// Bonus part for timeout_thread
//------------------------------

// We use timeout thread to send & track timeouts for specific seq num
typedef struct _timeout_args {
	int n;
	int is_last;
} timeout_args;

void* timeout_thread(void *args)
{
	const unsigned int n = ((timeout_args *)args)->n;
	const unsigned int is_last = ((timeout_args *)args)->is_last;
	const unsigned int offset = datasize * n;
	const unsigned int datalen = (filesize - offset) < datasize? (filesize - offset): datasize;

	free(args);

	do {
		// Send the packet
		pthread_mutex_lock(&mutex);
			snd_pkt.header.seq_num = n;
			snd_pkt.header.isLast = is_last;
			memcpy(snd_pkt.data, buffer + offset, datalen);
			int numbytes;
			if ((numbytes = sendto(sockfd, &snd_pkt, sizeof(snd_pkt.header) + datalen, 0,(struct sockaddr *)&client_info, len)) == -1) 
			{
				printf("sendto error\n");
				return 0;
			}
		pthread_mutex_unlock(&mutex);


		printf("\tSend %d bytes (seq_num: %d)\n", numbytes, snd_pkt.header.seq_num);
			
		// Track timeout
		clock_t t;
		t = (clock()*1000)/CLOCKS_PER_SEC;

		// Wait for ACK received or timeout
		while (window[n] != ACKED && ((clock()*1000)/CLOCKS_PER_SEC - t) < TIMEOUT);

		// If ACK not received, resend packet
		if (window[n] != ACKED)
			printf("\tTimeout! Resend packet sequence %d!", n);

	} while (window[n] != ACKED);
	
	// ACK received for this seq num, exit thread
	pthread_exit(NULL);
}

//==================================
// You should complete this function
//==================================
int sendFile(FILE *fd)
{	
	// Read the file to buffer
	filesize=ftell(fd);
	rewind(fd);
	fread(buffer, 1, filesize, fd);

	memset(window, 0, sizeof(window));

	const int pkts_cnt = ceil(filesize * 1.0 / datasize);
	int cur_window = 0;

	do {

		// Check if there are packet in the window that haven't been sent
		// Create a timeout thread for such packets
		for (int i = cur_window; i < cur_window + WND_SIZE && i < pkts_cnt; i++) {
			if (window[i] == NOT_SENT) {
				timeout_args *args = (timeout_args *)malloc(sizeof(timeout_args));
				args->n = i;
				args->is_last = i == pkts_cnt - 1;
				pthread_create(&th2, NULL, timeout_thread, args);
				window[i] = SENT;
			}
		}

		// Since we track timeouts from the timeout thread,
		// we can use the main thread for receiving
		recvfrom(sockfd, &rcv_pkt, sizeof(rcv_pkt), 0, (struct sockaddr *)&client_info, (socklen_t *)&len);

		printf("\tReceived a packet ack_num = %d\n", rcv_pkt.header.ack_num);

		// Set the seq num state to ACKED
		window[rcv_pkt.header.ack_num] = ACKED;

		// Move the window if packets are ACKed
		while (window[cur_window] == ACKED)
			cur_window++;

	} while (cur_window < pkts_cnt);

	printf("send file successfully\n");
	fclose(fd);
	return 0;
}

int main(int argc, char *argv[])
{
	//===========================
	// argv[1] is for server port
	//===========================
	sockfd = socket(AF_INET , SOCK_DGRAM , 0);

	if (sockfd == -1)
	{
		printf("Fail to create a socket.");
	}
	//=======================
	// input server info
	// IP address = 127.0.0.1
	//=======================
	bzero(&info,sizeof(info));
	info.sin_family = AF_INET;
	int port=atoi(argv[1]);
	info.sin_addr.s_addr = INADDR_ANY ;
	info.sin_port = htons(port);
	//printf("server %s : %d\n", inet_ntoa(info.sin_addr), htons(info.sin_port));

	//================
	// Bind the socket
	//================	
	if(bind(sockfd, (struct sockaddr *)&info, sizeof(info)) == -1)
	{
		perror("server_sockfd bind failed: ");
		return 0;
	}

	//====================================
	// Create send packet & receive packet
	//====================================
	memset(rcv_pkt.data, '\0', sizeof(rcv_pkt.data));

	//====================
	// Use for client info
	//====================
	bzero(&client_info,sizeof(client_info));
	client_info.sin_family = AF_INET;
	len = sizeof(client_info);

	printf("====Parameter====\n");
	printf("Server's IP is 127.0.0.1\n");
	printf("Server is listening on port %d\n",port);
	printf("==============\n");

	while(1)
	{
		//=========================
		// Initialization parameter
		//=========================
		snd_pkt.header.seq_num = 0;
		snd_pkt.header.ack_num = 0;
		snd_pkt.header.isLast = 0;
		FILE *fd;
		
		printf("server waiting.... \n");
		char *str;
		while ((recvfrom(sockfd, &rcv_pkt, sizeof(rcv_pkt), 0, (struct sockaddr *)&client_info, (socklen_t *)&len)) != -1)
		{
			//In client, we set is_last 1 to confirm server get client's first message.
			if(rcv_pkt.header.isLast == 1)
				break;
		}  
		printf("process command.... \n");
		str = strtok(rcv_pkt.data, " ");
		
		//===============================================================
		// command "download filename": download the file from the server
		// and then check if filename is exist
		//===============================================================
		if(strcmp(str, "download") == 0) 
		{
			str = strtok(NULL, " \n");
			printf("filename is %s\n",str);
			//===================
			// if file not exists 
			//===================
			if((fd = fopen(str, "rb")) == NULL) 
			{    
				//=======================================
				// Send FILE_NOT_EXISTS msg to the client
				//=======================================
				printf("FILE_NOT_EXISTS\n");
                		strcpy(snd_pkt.data, "FILE_NOT_EXISTS");
				int numbytes;
				if ((numbytes = sendto(sockfd, &snd_pkt, sizeof(snd_pkt), 0,(struct sockaddr *)&client_info, len)) == -1) 
				{
					printf("sendto error\n");
					return 0;
				}
				printf("server: sent %d bytes to %s\n", numbytes,inet_ntoa(client_info.sin_addr));
			} 
			//==================
			// else, file exists 
			//==================
			else 
			{
				fseek(fd,0,SEEK_END);
                		printf("FILE_EXISTS\n");
				strcpy(snd_pkt.data, "FILE_EXISTS");
				
				
				//==================================
				// Send FILE_EXIST msg to the client
				//==================================
				int numbytes;
				if ((numbytes = sendto(sockfd, &snd_pkt, sizeof(snd_pkt), 0,(struct sockaddr *)&client_info, len)) == -1) 
				{
					printf("sendto error\n");
					return 0;
				}
				printf("server: sent %d bytes to %s\n", numbytes,inet_ntoa(client_info.sin_addr));

				//==========================================================================
				// Sleep 1 seconds before transmitting data to make sure the client is ready
				//==========================================================================
				sleep(1);
				printf("trasmitting...\n");

				//=====================================
				// Start to send the file to the client
				//=====================================

				sendFile(fd);
				
			}
		}
		else 
		{
			printf("Illegal request!\n");   
		}
	}
}
