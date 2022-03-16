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

void process_and_print_packet(char *, int);

int main()
{
    int sockfd;
    char buffer[MAX_SNIFFER_BUF_SIZE];
    struct sockaddr_ll serveraddr; // For eth details
    struct sockaddr_in packet_info;
    int sockaddr_ll_len = sizeof(struct sockaddr_ll);
    int sockaddr_len = sizeof(struct sockaddr);
    socklen_t packet_info_size = sizeof(packet_info);
    int packets_to_sniff;
    int bytes_received = 0;
    const char *inf = "wlp2s0";
    struct sockaddr saddr;
    int saddr_len = sizeof saddr;

    memset(buffer, 0, MAX_SNIFFER_BUF_SIZE);

    printf("----------SNIFFER_IF!-------------\n");
    printf("Enter number of packets to sniff\n");
    scanf("%d", &packets_to_sniff);

    /****CREATE RAW SOCKET****/
    sockfd = socket(AF_PACKET, SOCK_RAW, htons(ETH_P_IP));
    if (sockfd == -1)
    {
        perror("Failed to create Raw socket");
        return 1;
    }
    /****BIND RAW SOCKET TO INTERFACE***/
    // Copy the interface name into the structure
    struct ifreq inr;
    bzero(&serveraddr, sizeof(serveraddr));
    bzero(&inr, sizeof(inr));
    strncpy((char *)inr.ifr_name, inf, IFNAMSIZ);
    //  Get id of interface using ioctl
    printf("inf is %s\n", inf);

    if (ioctl(sockfd, SIOCGIFINDEX, &inr) == -1)
    {
        perror("Failed to get interface id");
        close(sockfd);
        return 1;
    }
    // Store server details in structure to pass to bind
    printf("Interface index is %d\n", inr.ifr_ifindex);
    serveraddr.sll_ifindex = inr.ifr_ifindex;
    serveraddr.sll_protocol = htons(ETH_P_IP);
    serveraddr.sll_family = AF_PACKET;
    if (bind(sockfd, (struct sockaddr *)&serveraddr, sizeof(serveraddr)) == -1)
    {
        perror("Failed to bind Raw socket to interface");
        close(sockfd);
        return 1;
    }
    printf("Binded successfully\n");
    while (packets_to_sniff--)
    {
        printf("Blocking on recvfrom\n");
        bytes_received = recvfrom(sockfd, buffer, MAX_SNIFFER_BUF_SIZE, 0, (struct sockaddr *)&packet_info, &packet_info_size);
        if (bytes_received == -1)
        {
            perror("Failed to receive packets");
            close(sockfd);
            return 1;
        }
        printf("Bytes received: %d\ti: %d\n", bytes_received, packets_to_sniff);
        // process_and_print_packet(buffer, bytes_received);
    }
    close(sockfd);
    printf("DONE!! SNIFFED %d PACKETS SUCCESSFULLY\n", packets_to_sniff);
    return 0;
}
void process_and_print_packet(char *buffer, int len)
{
    // TODO: Packet processing and printing in Hex format
    buffer[len - 1] = '\0';
    printf("------------PACKET----------\n");
    printf("%s", buffer);
}