#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <memory.h>
#include <errno.h>
#include <unistd.h>
#include <string.h>
#include <arpa/inet.h>

#include "data.h"

#define SERVER_PORT 2000
#define LIMIT_CONN 10
#define MAX_SIZE_TCP_BUF 1000
#define MAX_CONCURRENT_CLIENT 10

int monitoredfdset[MAX_CONCURRENT_CLIENT];

void print_clientDetails(struct sockaddr_in *clientaddr)
{

    uint32_t clientaddr_ip = clientaddr->sin_addr.s_addr;
    uint16_t clientaddr_port = clientaddr->sin_port;
    printf("ip addr: [%u]\t port: [%u]\n", clientaddr_ip, clientaddr_port);
}

void print_monitoredfdset()
{
    printf("[");
    for (int i = 0; i < MAX_CONCURRENT_CLIENT; i++)
        printf("%d ", monitoredfdset[i]);
    printf("]\n");
}

void initialize_monitoredfdset()
{
    for (int i = 0; i < MAX_CONCURRENT_CLIENT; i++)
    {
        monitoredfdset[i] = -1;
    }
}

void add_monitoredfdset(int fd_commn)
{
    int i = 0;
    for (; i < MAX_CONCURRENT_CLIENT; i++)
    {
        if (monitoredfdset[i] == -1)
        {
            break;
        }
    }
    if (i != MAX_CONCURRENT_CLIENT)
        monitoredfdset[i] = fd_commn;
}

void remove_monitoredset(int fd_commn)
{
    int i = 0;
    for (; i < MAX_CONCURRENT_CLIENT; i++)
    {
        if (monitoredfdset[i] == fd_commn)
        {
            break;
        }
    }
    if (i != MAX_CONCURRENT_CLIENT)
        monitoredfdset[i] = -1;
}

void reinit_monitoredfdset(fd_set *readfdset_)
{
    FD_ZERO(readfdset_);
    int i = 0;
    for (; i < MAX_CONCURRENT_CLIENT; i++)
    {
        if (monitoredfdset[i] != -1)
        {
            FD_SET(monitoredfdset[i], readfdset_);
        }
    }
}

int getMax_monitoredset()
{
    int i = 0;
    int max = -1;
    for (; i < MAX_CONCURRENT_CLIENT; i++)
    {
        if (monitoredfdset[i] > max)
        {
            max = monitoredfdset[i];
        }
    }
    return max;
}

int main()
{
    printf("-----------TCP SERVER CAN HANDLE CONCURRENT CLIENTS-----------\n");
    struct sockaddr_in serveraddr, clientaddr;
    socklen_t sockaddr_len = (socklen_t)sizeof(struct sockaddr);
    int fd_comm = -1;
    StudentDetail studentDetail;
    char client_data[MAX_SIZE_TCP_BUF];
    struct hostent *clientinfo;
    fd_set readfdset;

    initialize_monitoredfdset();

    int fd_socket_server = socket(AF_INET, SOCK_STREAM, 0);
    printf("fd_socket_server : [%d]\n", fd_socket_server);
    if (fd_socket_server == -1)
    {
        perror("Failed to create socket");
        return 1;
    }
    printf("Created Master server socket with fd: [%d]\n", fd_socket_server);

    serveraddr.sin_addr.s_addr = INADDR_ANY;
    serveraddr.sin_port = (in_port_t)SERVER_PORT;
    serveraddr.sin_family = AF_INET;

    int bind_ret = bind(fd_socket_server, (struct sockaddr *)&serveraddr, sockaddr_len);
    if (bind_ret == -1)
    {
        perror("Failed to bind socket");
        close(fd_socket_server);
        return 1;
    }

    int listen_ret = listen(fd_socket_server, LIMIT_CONN);
    if (listen_ret == -1)
    {
        perror("Failed to listen on port");
        close(fd_socket_server);
        return 1;
    }

    add_monitoredfdset(fd_socket_server);

    while (1)
    {
        printf("Waiting for client\n");
        reinit_monitoredfdset(&readfdset);
        select(getMax_monitoredset() + 1, &readfdset, 0, 0, 0);
        if (FD_ISSET(fd_socket_server, &readfdset))
        {
            printf("Blocked on access call\n");
            fd_comm = accept(fd_socket_server, (struct sockaddr *)&clientaddr, &sockaddr_len);
            if (fd_comm == -1)
            {
                perror("Failed to accept request");
                sleep(1);
                continue;
            }
            printf("Released from accept()\n");
            print_clientDetails(&clientaddr);
            add_monitoredfdset(fd_comm);
            printf("Now monitoredset has become after add_monitoredfdset\n");
            print_monitoredfdset();
        }
        else
        {
            int i = 0;
            fd_comm = -1;
            memset(client_data, 0, sizeof(client_data));
            for (; i < MAX_CONCURRENT_CLIENT; i++)
            {
                if (FD_ISSET(monitoredfdset[i], &readfdset))
                {
                    fd_comm = monitoredfdset[i];
                    int bytes_received = recvfrom(fd_comm, (char *)&client_data, sizeof(client_data), 0, (struct sockaddr *)&clientaddr, &sockaddr_len);
                    if (bytes_received == 0)
                    {
                        printf("Not received any data, closing the connection with client\n");
                        close(fd_comm);
                        break;
                    }
                    Student *s = (Student *)&client_data;

                    if (s->age == -1)
                    {
                        printf("Name is %s and age is %d\n", s->name, s->age);
                        printf("Closing the connection with client\n");
                        close(fd_comm);
                        remove_monitoredset(fd_comm);
                        printf("Now monitoredset has become after remove_monitoredset\n");
                        print_monitoredfdset();
                        break;
                    }
                    snprintf(studentDetail.desc, sizeof(StudentDetail), "Hi, My name is %s and I am %d years old!\n", s->name, s->age);
                    int bytes_sent = sendto(fd_comm, (char *)&studentDetail, sizeof(StudentDetail), 0, (struct sockaddr *)&clientaddr, sockaddr_len);
                    if (bytes_sent == -1)
                    {
                        perror("Failed to sent response to client");
                        printf("Error: %d\n", errno);
                        close(fd_comm);
                        remove_monitoredset(fd_comm);
                        printf("Now monitoredset has become after remove_monitoredset\n");
                        print_monitoredfdset();
                        return 1;
                    }
                    printf("Server sent %d bytes to client\n", bytes_sent);
                }
            }
        }
    }
    close(fd_socket_server);
    return 0;
}

/*
C1:
    1 c1a
    2 c1b
    3 c1c
C2
    11 c2a
    12 c2b
    13 c2c
*/