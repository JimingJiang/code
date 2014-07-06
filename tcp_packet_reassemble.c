#include<stdio.h>
#include<pcap.h>
#include<libnet.h>
#define BUFSIZE 100
#define IFDEV "lo"
#define SRCADDR "127.0.0.1"

void send_tcp_packet(u_long src_ip, u_short src_prt, u_long dst_ip, u_short dst_prt,
u_int32_t seq, u_int32_t ack, char *payload);
int main(int argc, char *argv[])
{
	char buffer[BUFSIZE];
	//set filter to capture
	pcap_t *caphandle;
	char *dev;
	char errbuf[PCAP_ERRBUF_SIZE];
	struct bpf_program bpf_filter;
	struct pcap_pkthdr pkthdr;
	bpf_u_int32 net_ip, net_mask;
	char filter_str[50];
	const u_char *packet;
	
	sprintf(filter_str,"tcp[13]==0x12 and src port %d", atoi(argv[2]));
	pcap_lookupnet(IFDEV, &net_ip, &net_mask, errbuf);
	caphandle = pcap_open_live(IFDEV, BUFSIZE, 1, 0, errbuf);
	pcap_compile(caphandle, &bpf_filter, filter_str, 0, net_ip);
	pcap_setfilter(caphandle, &bpf_filter);
	//ready to capture 
	
	//connect to server
	if(argc<3)
	{
		printf("Usage: %s <target ip> <target port>\n", argv[0]);
		exit(1);
	}
	struct sockaddr_in  servAddr;
	int sockfd;
	if((sockfd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0)
	{
        	printf("create socket failed\n");
        	exit(1);
        }

    	memset(&servAddr, 0, sizeof(servAddr));	
    	servAddr.sin_family      = AF_INET;	
    	servAddr.sin_addr.s_addr = inet_addr(argv[1]);	
    	servAddr.sin_port        = htons(atoi(argv[2]));	

	if(connect(sockfd, (struct sockaddr *) &servAddr, sizeof(servAddr)) < 0)
        {
        	printf("connect() failed\n");
		exit(1);
	}
	//connect done
	
	packet = pcap_next (caphandle, &pkthdr);
	//analysis packet
	struct tcphdr *tcpheader;
	u_int16_t src_port; //捕获数据包的目的端口，本地发送的源端口
	u_int32_t seq, ack;
	tcpheader = (struct tcphdr *) (packet + LIBNET_ETH_H + LIBNET_IPV4_H);
	
	src_port = (u_int16_t) ntohs(tcpheader->dest);
	ack = (u_int32_t)ntohl (tcpheader->ack_seq);
	seq = (u_int32_t)ntohl (tcpheader->seq);
	
	//got ack and seq from server
	printf("seq=%u, ack=%u\n",seq,ack);
	
	//construct tcp packet
	send_tcp_packet(inet_addr(SRCADDR), src_port, inet_addr(argv[1]), atoi(argv[2]), ack, seq+1, "01234");
	send_tcp_packet(inet_addr(SRCADDR), src_port, inet_addr(argv[1]), atoi(argv[2]), ack + 3, seq+1, "56789");
	
	close(sockfd);
	return 0;
}

/*
* construct and send tcp packet
*/
void send_tcp_packet(u_long src_ip, u_short src_prt, u_long dst_ip, u_short dst_prt,
			 u_int32_t seq, u_int32_t ack, char *payload)
{
	char lerrbuf[LIBNET_ERRBUF_SIZE];
   	u_short payload_s = strlen(payload);
	libnet_ptag_t t;   
	libnet_t *lhandle;
     	
	if((lhandle = libnet_init(LIBNET_RAW4, IFDEV, lerrbuf))== NULL)
	{
		printf("libnet_init() failed: %s\n", lerrbuf);
        	exit(1); 
    	}

    	t = libnet_build_tcp_options(
		"\003\003\012\001\002\004\001\011\010\012\077\077\077\077\000\000\000\000\000\000",
        	20,
        	lhandle,
        	0);
	if (t == -1)
    	{
        	printf("Can't build TCP options: %s\n", libnet_geterror(lhandle));
	        exit(1);
    	}

	t = libnet_build_tcp(
		src_prt,                                    /* source port */
        	dst_prt,                                    /* destination port */
		seq,                                        /* sequence number */
        	ack,                                        /* acknowledgement num */
        	TH_ACK,                                     /* control flags */
        	32767,                                      /* window size */
		0,                                          /* checksum */
		10,                                          /* urgent pointer */
		LIBNET_TCP_H + 20 + payload_s,              /* TCP packet size */
		payload,                                    /* payload */
		payload_s,                                  /* payload size */
		lhandle,                                          /* libnet handle */
		0);                                         /* libnet id */
	if (t == -1)
	{
        	printf("Can't build TCP header: %s\n", libnet_geterror(lhandle));
        	exit(1);
	}
	
	t = libnet_build_ipv4(
		LIBNET_IPV4_H + LIBNET_TCP_H + 20 + payload_s,/* length */
	      	0,                                          /* TOS */
		242,                                        /* IP ID */
		0,                                          /* IP Frag */
		64,                                         /* TTL */
		IPPROTO_TCP,                                /* protocol */
		0,                                          /* checksum */
		src_ip,                                     /* source IP */
		dst_ip,                                     /* destination IP */
		NULL,                                       /* payload */
		0,                                          /* payload size */
		lhandle,                                    /* libnet handle */
		0);                                         /* libnet id */
	if (t == -1)
	{
	        printf("Can't build IP header: %s\n", libnet_geterror(lhandle));
        	exit(1);
        }
	//发送构造好的数据包
	if (libnet_write(lhandle) == -1)
	{
        	printf("send error: %s\n", libnet_geterror(lhandle));
		exit(1);
	}
	libnet_destroy(lhandle);
}
