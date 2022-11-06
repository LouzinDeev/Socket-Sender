#include "main.h"
#include "sockSender.h"

connection_t::connection_t(ip_header* arg1, sock_header* arg2) {
	conn_data = (conn_data_t*)malloc(sizeof(conn_data_t));
	ip_head = (ip_header*)malloc(sizeof(ip_header));
	sock_head = (sock_header*)malloc(sizeof(sock_header));
	sock = 0;
	ip_head = arg1;
	sock_head = arg2;
	sock = socket(sock_head->domain, sock_head->type, sock_head->protocol);
	struct sockaddr_in address;
	address.sin_addr.s_addr = inet_addr(ip_head->ip);
	address.sin_port = htons(ip_head->port);
	address.sin_family = AF_INET;
	if (connect(sock, (sockaddr*)&address, sizeof(address)) < 0) {
		std::cout << "Connect Error" << std::endl;
	}
}

int connection_t::sendData(conn_data_t* buffers, bool response) {
	int res = 0;
	res = send(sock, buffers->buffer, sizeof(buffers->buffer), buffers->flags);
	if (res < 0) {
		std::cout << "Can't send data" << std::endl;
		return 0;
	}
	if (response) {
		res = recv(sock, buffers->recbuff, sizeof(buffers->recbuff), buffers->flags);
		if (res == 0) {
			std::cout << "Can't recive data, or no data for recive" << std::endl;
		}
		else if (res < 0) {
			std::cout << "Recive error" << std::endl;
		}
	}
	return 1;
}