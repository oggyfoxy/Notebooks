#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <netdb.h>


// struct addrinfo {
//   int ai_flags;
//   int ai_family;
//   int ai_socktype;
//   int ai_protocol;
//   size_t ai_addrlen;
//   struct sockaddr *ai_addr;
//   char *ai_canonname;
// 
//   struct addrinfo *ai_next;
// };
// 
// struct sockaddr {
//   unsigned short sa_family;
//   char sa_data[14];
// };
// 
// // IPv4: sockaddr_in and in_addr
// 
// struct sockaddr_in {
//   short int sin_family;
//   unsigned short int sin_port;
//   struct in_addr sin_addr; 
//   unsigned char sin_zero[8];
// };
// 
// // Internet address
// struct in_addr {
//   uint32_t s_addr;
// };
// 
// 
// // IPv6: sockaddr_in6 and in6_addr
// 
// struct sockaddr_in6 {
//   u_int16_t sin6_family;
//   u_int16_t sin6_port;
//   u_int32_t sin6_flowinfo;
//   struct in6_addr sin6_addr;
//   u_int32_t sin6_scope_id;
// };
// 
// struct in6_addr {
//   unsigned char s6_addr[16]; // ipv6 address
// };
// 
// struct sockaddr_storage { 
//   sa_family ss_family; 
// 
//   char __ss_pad1[_SS_PAD1SIZE];
//   int64_t __ss_align;
//   char __ss_pad2[_SS_PAD2SIZE];
// };

int getaddrinfo(const char *node, const char *service, const struct addrinfo *hints, struct addrinfo **res);
int main(void) {

  // IPV4

  char ip4[INET_ADDRSTRLEN];
  struct sockaddr_in sa;

  inet_ntop(AF_INET, &(sa.sin_addr), ip4, INET_ADDRSTRLEN);


  // IPv6

  char ip6[INET6_ADDRSTRLEN];
  struct sockaddr_in6 sa6;

  
  inet_ntop(AF_INET6, &(sa6.sin6_addr), ip6, INET6_ADDRSTRLEN);

  // int ipv4 = inet_pton(AF_INET, "10.12.110.57", &(sa.sin_addr));
  // inet_pton(AF_INET6, "2001:db8:63b3:1::3490", &(sa6.sin6_addr));

  printf("IPV4: %s\n", ip4);
  printf("IPV6: %s\n", ip6);
  
  /* SYSTEM CALLS */

  int status; 
  struct addrinfo hints;
  struct addrinfo *servinfo; // will point to the results

  memset(&hints, 0, sizeof hints); // zero's out the structs
  hints.ai_family = AF_UNSPEC;
  hints.ai_socktype = SOCK_STREAM; // TCP stream sockets
  hints.ai_flags = AI_PASSIVE;

  if ((status = getaddrinfo(NULL, "3490", &hints, &servinfo)) != 0) {
    fprintf(stderr, "gai error: %s\n", gai_strerror(status));
    exit(1);
  }

  freeaddrinfo(servinfo);

  return 0;

}






