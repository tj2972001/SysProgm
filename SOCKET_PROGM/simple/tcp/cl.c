#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <unistd.h>

#include "data.h"

#define SERVER_IP_ADDRESS "127.0.0.1"
#define SERVER_PORT 3000

int main()
{
    printf("-----------TCP CLIENT-----------\n");
    struct sockaddr_in serveraddr;
    socklen_t sockaddr_len = sizeof(struct sockaddr);
    Student student;             // Data to sent (req)
    StudentDetail studentDetail; // Response to receive (res)
    int bytes_send, bytes_received;
    struct hostent *dest = (struct hostent *)gethostbyname(SERVER_IP_ADDRESS);
    printf("Server addr is %s\n", dest->h_name);
    int fd_socket_client = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    printf("Created Master client socket with fd: [%d]\n", fd_socket_client);

    if (fd_socket_client == -1)
    {
        perror("Failed to create socket");
        return 1;
    }
    serveraddr.sin_family = AF_INET;
    serveraddr.sin_port = SERVER_PORT;
    serveraddr.sin_addr = *((struct in_addr *)dest->h_addr_list[0]);
    // printf("Addr is %u\n", serveraddr.sin_addr);
    int fd_comm_client = connect(fd_socket_client, (struct sockaddr *)&serveraddr, sockaddr_len);
    if (fd_comm_client == -1)
    {
        printf("%d\n", errno);
        perror("Failed to connect with server\n");
        close(fd_socket_client);
        return 1;
    }
    printf("Block on connect is released\n");

    do
    {
        printf("Enter age\n");
        fscanf(stdin, "%d", &student.age);
        printf("Enter name\n");
        scanf("%s", student.name);
        bytes_send = sendto(fd_socket_client, &student, sizeof(Student), 0, (struct sockaddr *)&serveraddr, sockaddr_len);
        printf("Sent [%d] bytes to server\n", bytes_send);
        bytes_received = recvfrom(fd_socket_client, (char *)&studentDetail, sizeof(StudentDetail), 0, (struct sockaddr *)&serveraddr, &sockaddr_len);
        printf("Received [%d] bytes from server\n", bytes_received);
        printf("Res from server is:%s\n", studentDetail.desc);
    } while (bytes_received != 0);

    printf("Closing the connection\n");
    close(fd_comm_client);
    return 0;
}
