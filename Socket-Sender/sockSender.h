#ifndef SOCKSENDER_H_INCLUDED
#define SOCKSENDER_H_INCLUDED
#define MAX_BUFFER_SIZE 2040
#include "main.h"
enum connInfo {
	INVALID_CONN = -1,
	VALID_CONN = 0
};

enum {
	INVALID_SOCK = -1
};

struct ip_header {
	unsigned int port;
	char* ip;
};
struct sock_header {
	int domain;
	int type;
	int protocol;
};
struct conn_data_t {
	char buffer[MAX_BUFFER_SIZE];
	char recbuff[MAX_BUFFER_SIZE];
	int flags;
};

class connection_t {
private:
	int sock;
public:
	ip_header* ip_head;
	sock_header* sock_head;
	conn_data_t* conn_data;
	connection_t(ip_header* arg1, sock_header* arg2);
	int sendData(conn_data_t* buffers, bool response = false);
	//int recive();
};


#endif