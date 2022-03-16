#include <stdio.h>
#include <features.h>
#include <sys/socket.h>
#include <linux/if_packet.h>
#include <linux/if_ether.h>
#include <errno.h>
#include <sys/ioctl.h>
#include <net/if.h>
#include <arpa/inet.h>
#include <string.h>
#include <unistd.h>

#define MAX_SNIFFER_BUF_SIZE 65536

int main()
{
    int sockfs;
    struct sockaddr_in packet_info;
    socklen_t packet_info_len = sizeof packet_info;
    int bytes_received = 0;
    char buffer[MAX_SNIFFER_BUF_SIZE];
    memset(buffer, 0, sizeof(buffer));
    sockfs = socket(AF_PACKET, SOCK_RAW, htons(ETH_P_ALL));
    if (sockfs == -1)
    {
        perror("Failed to create socket");
        return 1;
    }

    while (1)
    {
        bytes_received = recvfrom(sockfs, buffer, sizeof(buffer), 0, (struct sockaddr *)&packet_info, &packet_info_len);
        if (bytes_received == -1)
        {
            perror("Failed to receive response");
            close(sockfs);
            return 1;
        }
        printf("Received %d bytes from %s\n", bytes_received, inet_ntoa(packet_info.sin_addr));
    }
}