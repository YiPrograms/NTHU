#include <arpa/inet.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>
#include <netdb.h>

#define PORT 80

char url[1024];
char hostname[1024];
char buffer[10240000];

int main(int argc, char const *argv[]) {
	

	printf("Enter the hostname: ");
	scanf("%s", url);

	int hostname_sep = -1;
	int url_len = strlen(url);
	for (int i = 0; i < url_len; i++) {
		if (url[i] == '/') {
			hostname_sep = i;
			break;
		}
	}

	if (hostname_sep == -1) {
		printf("Could not resolve hostname from URL");
		return -1;
	}
	memcpy(hostname, url, hostname_sep);
	int hostname_len = strlen(hostname);


	int sock = 0;
	if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
		printf("\n Socket creation error \n");
		return -1;
	}

	struct sockaddr_in serv_addr;
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(PORT);

	struct hostent *he = gethostbyname(hostname);
	memcpy(&serv_addr.sin_addr, he->h_addr_list[0], he->h_length);

	// // Convert IPv4 and IPv6 addresses from text to binary form
	// if (inet_pton(AF_INET, hostname, &serv_addr.sin_addr) <= 0) {
	// 	printf("\nInvalid address/ Address not supported \n");
	// 	return -1;
	// }

	if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
		printf("\nConnection Failed \n");
		return -1;
	}


	char *buf_now = buffer;

	strcpy(buf_now, "GET ");
	buf_now += 4;

	strcpy(buf_now, url + hostname_sep);
	buf_now += url_len - hostname_sep;

	strcpy(buf_now, " HTTP/1.0\r\nHost: ");
	buf_now += 17;

	strcpy(buf_now, hostname);
	buf_now += hostname_len;

	strcpy(buf_now, "\r\n\r\n");
	buf_now += 4;

	printf("socket: Start sending HTTP request\n");
	if (send(sock, buffer, buf_now - buffer, 0) < 0) {
		printf("socket: Send failed\n");
		return -1;
	}

	printf("socket: Start read the response\n");
	buf_now = buffer;
	int read_len = 0;
	while ((read_len = read(sock, buf_now, sizeof(buffer) - (buf_now - buffer))) > 0) {
		buf_now += read_len;
	}
	printf("socket: Finish read to buffer\n");
	
	printf("======== Hyperlinks ========\n");
	int res_len = buf_now - buffer;
	for (int i = 7; i < res_len; i++) {
		if (buffer[i] == '=') {
			if (strncmp(buffer + (i - 7), "<a href=", 8) == 0) {
				for (int k = i + 2; k < res_len; k++) {
					if (buffer[k] == '\"') {
						buffer[k] = '\0';
						printf("%s\n", buffer + (i + 2));
						break;
					}
				}
			}
		}
	}

	return 0;
}