#include <queue.h>
#include "skel.h"
#include <string.h>
#include "rtable.h"
#include <stdlib.h>
#include<sys/time.h>

struct arp_entry *arp_table;
int arp_table_len;

struct route_table_entry *rtable;
int rtable_size;

struct arp_entry *get_arp_entry(__u32 ip) {
	int i;
	for(i = 0; i < arp_table_len; i++) {
		if(arp_table[i].ip == ip) {
			return &arp_table[i];
		}
	}
  return NULL;
}

int read_rtable(char *file_name)

{
  int byte_value;
  FILE *in;
  uint entry_number;
  int i;
  char *p;
  char buffer [64];
  
  in = fopen(file_name,"r");
  if(!in)
  	return -1;
  entry_number = 0;
  while (fgets(buffer,63,in) != NULL) 
  {
  	rtable[entry_number].prefix = 0;
  	rtable[entry_number].next_hop = 0;
  	rtable[entry_number].mask = 0;
    
    p = strtok(buffer," .");
    i = 0;
    while (p != NULL) {
      
      byte_value = atoi(p);
      /*Prefix*/
      if (i < 4) 
      {
        if(i != 0)
         	rtable[entry_number].prefix = rtable[entry_number].prefix << 8;
         
         rtable[entry_number].prefix = rtable[entry_number].prefix | byte_value; 
      }
      if (i < 8 && i >= 4)
      {
      	/*Next hop*/
        
          byte_value = atoi(p);
          if(i != 4)
         	rtable[entry_number].next_hop = rtable[entry_number].next_hop << 8;
         
          rtable[entry_number].next_hop = rtable[entry_number].next_hop | byte_value;
        
      }
      /*Mask*/
      if ((7 < i) && (i < 12)) 
      {
        if(i != 7)
         	rtable[entry_number].mask = rtable[entry_number].mask << 8;
         
        rtable[entry_number].mask = rtable[entry_number].mask | byte_value;
      }
      /*Interface*/
      if (i == 12) 
      	rtable[entry_number].interface = byte_value;
      
      p = strtok(NULL," .");
      i++;
    }
    entry_number++;
  }
  
  fclose(in);
  return entry_number;
   
  
}

int compare (const void * a, const void * b)
{
	struct route_table_entry *x = (struct route_table_entry *)a;
	struct route_table_entry *y = (struct route_table_entry *)b;
	
	if(x->prefix > y->prefix)
		return 1;
	if(x->prefix < y->prefix)
		return -1;
	return 0;
}

int binary_search(int l,int r,__u32 dest_ip)
{

	while (l <= r)
	{
		int mid = l + (r - l) / 2;

		if(rtable[mid].prefix == (rtable[mid].mask & htonl(dest_ip)))
			return mid;

		if(rtable[mid].prefix < (rtable[mid].mask & htonl(dest_ip)))
			l = mid + 1;
		else
			r = mid - 1;
	}

	return -1;
}



struct route_table_entry *get_best_route(__u32 dest_ip) {
	
	int i, best_index = -1;
	for(i = 0; i < rtable_size; i++){
		if((rtable[i].mask & htonl(dest_ip)) == rtable[i].prefix){
			if( best_index == -1 || ntohl(rtable[i].mask) > ntohl(rtable[best_index].mask)) {
				best_index = i;
			}
		}
	}
	if(best_index >= 0){
		return &rtable[best_index];
	}
	return NULL;
}

void parse_arp_table() 
{
	FILE *f;
	fprintf(stderr, "Parsing ARP table\n");
	f = fopen("arp_table.txt", "r");
	DIE(f == NULL, "Failed to open arp_table.txt");
	char line[100];
	int i = 0;
	for(i = 0; fgets(line, sizeof(line), f); i++) {
		char ip_str[50], mac_str[50];
		sscanf(line, "%s %s", ip_str, mac_str);
		fprintf(stderr, "IP: %s MAC: %s\n", ip_str, mac_str);
		arp_table[i].ip = inet_addr(ip_str);
		int rc = hwaddr_aton(mac_str, arp_table[i].mac);
		DIE(rc < 0, "invalid MAC");
	}
	arp_table_len = i;
	fclose(f);
	fprintf(stderr, "Done parsing ARP table.\n");
}

int main(int argc, char *argv[])
{
	packet m;
	packet c_m;
	int rc;
	struct icmphdr *icmp;

	arp_table_len = 0;

	queue arp_q = queue_create();
	if(!arp_q)
	{
		printf("Failed to create queue\n");
		return 0;
	}

	init(argc - 2, argv + 2);

	rtable = malloc(sizeof(struct route_table_entry) * 64300);
	arp_table = malloc(sizeof(struct  arp_entry) * 100);

	rtable_size = read_rtable(argv[1]);

	uint8_t mac_broadcast[6];
	if(hwaddr_aton("ff:ff:ff:ff:ff:ff",mac_broadcast) == -1)
		printf("failed to create mac broadcast\n");

	uint8_t mac_router[6];
	uint8_t wanted_mac[6];

	int check = -1;

	qsort(rtable,rtable_size,sizeof(struct route_table_entry),compare);

	while (1) {
		//1.Get packet
		printf("Asteapta pachet\n");
		rc = get_packet(&m);
		DIE(rc < 0, "get_message");
		/* Students will write code here */
		struct ether_header *eth_hdr = (struct ether_header *)m.payload;
		struct iphdr *ip_hdr = (struct iphdr *)(m.payload + sizeof(struct ether_header));
		
		
		//2.Check if it's for the router,if it is,answer if it is ICMP ECHO request
		for(int i = 0; i < 3; i++)
		{
			struct in_addr inp;
			inet_aton(get_interface_ip(i),&inp);
			
			if(inp.s_addr == ip_hdr->daddr)
			{
				check = 1;
				
				icmp = parse_icmp(m.payload);
				
				if(!icmp)
					break;
			
				if(icmp->type == 8 && ip_checksum(icmp,sizeof(struct icmphdr)) != 0)
				{
					send_icmp(ip_hdr->saddr,ip_hdr->daddr,eth_hdr->ether_dhost,
						eth_hdr->ether_shost,0,0,
						m.interface,icmp->un.echo.id,icmp->un.echo.sequence);
				
					break;
				}
				else
					break;
			}
		}
		
		if(check == 1)
		{
			check = -1;
			continue;
		}

		//3.Check if it's ARP Request,answer
		//4.Check if it's ARP Reply, update ARP table
		struct arp_header *arp_hdr = parse_arp(m.payload);
		if(arp_hdr)
		{
			struct ether_header eth_arp;			
			if(arp_hdr->op == htons(ARPOP_REQUEST))
			{
				for(int i = 0; i < 3; i++)
				{
					struct in_addr inp;
					inet_aton(get_interface_ip(i),&inp);
					if(inp.s_addr == arp_hdr->tpa)
					{
						get_interface_mac(i,wanted_mac);
						build_ethhdr(&eth_arp,wanted_mac,arp_hdr->sha,htons(0x0806));
						send_arp(arp_hdr->spa,arp_hdr->tpa,&eth_arp,m.interface,htons(ARPOP_REPLY));
						
						break;
					}
				}
				continue;
			}
			//update ARP and check if the head of the queue can be sent
			if(arp_hdr->op == htons(ARPOP_REPLY))
			{	
				
				arp_table[arp_table_len].ip = htonl(arp_hdr->spa);
				memcpy(arp_table[arp_table_len].mac,arp_hdr->sha,6);
				arp_table_len++;

				
				if(queue_empty(arp_q) == 1)
					continue;
				
				packet *p = (packet *)top(arp_q);
				struct ether_header *eth_hdr_arp = (struct ether_header *)p->payload;
				struct iphdr *ip_hdr_arp = (struct iphdr *)(p->payload + sizeof(struct ether_header));
				
				int best_route_arp = binary_search(0,rtable_size - 1,ip_hdr_arp->daddr);
				if(best_route_arp == -1)
				{
					send_icmp_error(ip_hdr_arp->saddr,ip_hdr_arp->daddr,eth_hdr_arp->
		 			ether_dhost,eth_hdr_arp->ether_shost,3,0,p->interface);
					continue;
				}

				if(rtable[best_route_arp].next_hop != htonl(arp_hdr->spa))
					continue;

				get_interface_mac(rtable[best_route_arp].interface,eth_hdr_arp->ether_shost);
				memcpy(eth_hdr_arp->ether_dhost,arp_hdr->sha,6);
				send_packet(rtable[best_route_arp].interface,p);
				p = (packet *)queue_deq(arp_q);
			}
			continue;
		}

		//5.Check ttl
		if(ip_hdr->ttl <= 1)
		{
			printf("ttl expired\n");
			send_icmp_error(ip_hdr->saddr,ip_hdr->daddr,eth_hdr->
				ether_dhost,eth_hdr->ether_shost,11,0,m.interface);
			continue;
		}
			
		//6.Check checksum
		if(ip_checksum(ip_hdr,sizeof(struct iphdr)) != 0)
		{
			printf("Wrong checksum\n");
			continue;
		}

		//7.Decrement ttl and update checksum
		ip_hdr->ttl--;
		ip_hdr->check = 0;
		ip_hdr->check = ip_checksum(ip_hdr,sizeof(struct iphdr));

		//8.Search for route
		int best_route = binary_search(0,rtable_size - 1,ip_hdr->daddr);

		//send icmp with host_unreachable
		if(best_route == -1)
		{
			send_icmp_error(ip_hdr->saddr,ip_hdr->daddr,eth_hdr->
		 		ether_dhost,eth_hdr->ether_shost,3,0,m.interface);
			continue;
		}

		//9.Update macs
		struct arp_entry *arp = get_arp_entry(rtable[best_route].next_hop);
		
		if(!arp)
		{
			//send arp request
			struct ether_header eth_arp;
			get_interface_mac(rtable[best_route].interface,mac_router);

			build_ethhdr(&eth_arp,mac_router,mac_broadcast,htons(0x0806));
			
			//creeaza header ether cu type potrivit si macsursa mac curent
			send_arp(htonl(rtable[best_route].next_hop),
				inet_addr(get_interface_ip(rtable[best_route].interface)),
				&eth_arp,
				rtable[best_route].interface,
				htons(ARPOP_REQUEST));

			memcpy(&c_m,&m,sizeof(m));
			queue_enq(arp_q,&c_m);
			
			continue;
		}
		else
		{
			get_interface_mac(rtable[best_route].interface,eth_hdr->ether_shost);
			memcpy(eth_hdr->ether_dhost,arp->mac,6);
		}

		
		//10.Send packet
		send_packet(rtable[best_route].interface,&m);
	}


}
