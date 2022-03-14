#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <netdb.h>
#include <memory.h>
#include <errno.h>
#include <unistd.h>
#include <string.h>

#include "data.h"

#define SERVER_PORT 2000
#define MAX_SIZE_UDP_BUF 1000

int main()
{
    printf("-----------UDP SERVER-----------\n");
    struct sockaddr_in serveraddr, clientaddr;
    socklen_t sockaddr_len = (socklen_t)sizeof(struct sockaddr);
    fd_set readfdset;
    int bytes_sent = 0;
    int fd_comm = 0;
    StudentDetail studentDetail;
    char client_data[MAX_SIZE_UDP_BUF];
    struct hostent *clientinfo;

    int fd_socket_server = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    if (fd_socket_server == -1)
    {
        perror("Failed to create socket");
        return 1;
    }
    printf("Created Master server socket with fd: [%d]\n", fd_socket_server);

    serveraddr.sin_addr.s_addr = INADDR_ANY;
    serveraddr.sin_port = SERVER_PORT;
    serveraddr.sin_family = AF_INET;
    int bind_ret = bind(fd_socket_server, (struct sockaddr *)&serveraddr, sockaddr_len);
    if (bind_ret == -1)
    {
        perror("Failed to bind socket");
        close(fd_socket_server);
        return 1;
    }
    while (1)
    {

        int bytes_received = recvfrom(fd_socket_server, (char *)&client_data, sizeof(client_data), 0, (struct sockaddr *)&clientaddr, &sockaddr_len);
        if (bytes_received == 0)
        {
            printf("Not received any data, closing the connection with client\n");
            break;
        }
        clientinfo = gethostbyaddr((struct sockaddr *)&clientaddr.sin_addr.s_addr, sizeof(clientaddr.sin_addr.s_addr), AF_INET);
        if (clientinfo == NULL)
        {
            perror("Failed to get client info");
            break;
        }
        printf("Client ip: %s (%s)\n", clientinfo->h_name, inet_ntoa(clientaddr.sin_addr));
        printf("Client port: %d\n", clientaddr.sin_port);
        Student *s = (Student *)&client_data;

        if (s->age == -1)
        {
            printf("Name is %s and age is %d\n", s->name, s->age);
            printf("Closing the connection with client\n");
            bytes_sent = sendto(fd_socket_server, 0, 0, 0, (struct sockaddr *)&clientaddr, sockaddr_len);
            if (bytes_sent == -1)
            {
                perror("Failed to sent closing response to client");
                printf("Error: %d\n", errno);
                close(fd_socket_server);
                return 1;
            }
            break;
        }
        snprintf(studentDetail.desc, sizeof(StudentDetail), "Hi, My name is %s and I am %d years old!\n", s->name, s->age);
        bytes_sent = sendto(fd_socket_server, (char *)&studentDetail, sizeof(StudentDetail), 0, (struct sockaddr *)&clientaddr, sockaddr_len);
        if (bytes_sent == -1)
        {
            perror("Failed to sent response to client");
            printf("Error: %d\n", errno);
            close(fd_socket_server);
            return 1;
        }
        printf("Server sent %d bytes to client\n", bytes_sent);
    }
    close(fd_socket_server);
    return 0;
}