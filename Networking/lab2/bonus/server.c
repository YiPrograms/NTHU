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
Udp_pkt snd_pkt,rcv_pkt,rcv_pkt_buffer;
socklen_t len;
pthread_t th1,th2;
int first_time_create_thread = 0;

int got_rcv = 0;

char buffer[150000];
int window[15000];
int filesize;

const size_t datasize = sizeof(snd_pkt.data);

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
pthread_mutex_t recv_mutex = PTHREAD_MUTEX_INITIALIZER;


//==============================
// Basic part for receive_thread
//==============================
/*******************notice***************************
 * 
 * In bonus part, you should use following threads to
 * checking timeout and receive client ack.
 * 
 ***************************************************/
void* receive_thread()
{
	//===================
	// Receive client ack
	//===================
	// A thread keep receiving client ack
	while (recvfrom(sockfd, &rcv_pkt_buffer, sizeof(rcv_pkt), 0, (struct sockaddr *)&client_info, (socklen_t *)&len) != -1)
	{
		pthread_mutex_lock(&recv_mutex);
			got_rcv = 1;
			memcpy(&rcv_pkt, &rcv_pkt_buffer, sizeof(rcv_pkt));
		pthread_mutex_unlock(&recv_mutex);
	}	
	//==========================================
	// Keep the thread alive not to umcomment it
	//==========================================
	//pthread_exit(NULL);
}

//------------------------------
// Bonus part for timeout_thread
//------------------------------

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
			
		clock_t t;
		t = (clock()*1000)/CLOCKS_PER_SEC;

		while (window[n] != 2 && ((clock()*1000)/CLOCKS_PER_SEC - t) < TIMEOUT);

		if (window[n] != 2) {
			printf("\tTimeout! Resend packet sequence %d! window = %d\n", n, window[n]);
		}

	} while (window[n] != 2);
	
	pthread_exit(NULL);
}

//==================================
// You should complete this function
//==================================
// Send file function, it call receive_thread function at the first time.
int sendFile(FILE *fd)
{	
	filesize=ftell(fd);
	rewind(fd);
	fread(buffer, 1, filesize, fd);

	//----------------------------------------------------------------
	// Bonus part for declare timeout threads if you need bonus point,
	// umcomment it and manage the thread by youself
	//----------------------------------------------------------------
	// At the first time, we need to create thread.
	if(!first_time_create_thread)
	{
		first_time_create_thread=1;
		pthread_create(&th1, NULL, receive_thread, NULL);
		//pthread_create(&th2, NULL, timeout_process, NULL);
	}
	/*******************notice************************
	 * 
	 * In basic part, you should finish this function.
	 * You can try test_clock.c for clock() usage.
	 * checking timeout and receive client ack.
	 * 
	 ************************************************/

	got_rcv = 0;
	memset(window, 0, sizeof(window));

	const int pkts_cnt = ceil(filesize * 1.0 / datasize);
	int cur_window = 0;

	printf("\tPackets count: %d\n", pkts_cnt);


	do {
		for (int i = cur_window; i < cur_window + WND_SIZE && i < pkts_cnt; i++) {
			if (window[i] == 0) {
				timeout_args *args = (timeout_args *)malloc(sizeof(timeout_args));
				args->n = i;
				args->is_last = i == pkts_cnt - 1;
				pthread_create(&th2, NULL, timeout_thread, args);
				window[i] = 1;
			}
		}

		got_rcv = 0;

		while (!got_rcv);

		pthread_mutex_lock(&recv_mutex);
			printf("\tReceived a packet ack_num = %d\n", rcv_pkt.header.ack_num);
			window[rcv_pkt.header.ack_num] = 2;
			printf("\tSet window %d: %d\n", rcv_pkt.header.ack_num, window[rcv_pkt.header.ack_num]);
		pthread_mutex_unlock(&recv_mutex);


		while (window[cur_window] == 2)
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
