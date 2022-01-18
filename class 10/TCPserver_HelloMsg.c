/*	======================================================================
	FileName: TCPserver_HelloMsg.c
	Pair of: TCPclient_HelloMsg.c
	----------------------------------------------------------------------
	Purpose:
		To understand how TCP server-client model works.
	----------------------------------------------------------------------
	How to Run:
	A. In one terminal
		$	gcc TCPserver_HelloMsg.c -o TCPserver_HelloMsg
		$	./TCPserver_HelloMsg
	B.	In another terminal
		$	gcc TCPclient_HelloMsg.c -o TCPclient_HelloMsg
		$	./TCPclient_HelloMsg

	Output:		
		In two terminals, messages sent by each other will be displayed.
	----------------------------------------------------------------------
	Necessary System Calls:
	A.	socket()
		*	Task:	Create a socket.
		*	Synopsis: int socket(int domain, int type, int protocol);
		*	Return: file descriptor on suucess, -1 on error
		*	Header File: #include <sys/socket.h>

	B.	bind()
		*	Task:	Set local address{IP address:Port} for a socket.
		*	Synopsis: int bind(int sockfd, const struct sockaddr *addr, socklen_t addrlen);
		*	Return: 0 on suucess, -1 on error
		*	Header File: #include <sys/socket.h>

	C. listen()
		*	Task:	Invite incoming connections.		
		*	Synopsis: int listen(int sockfd, int backlog);
		*	Return: 0 on suucess, -1 on error
		*	Header File: #include <sys/socket.h>
	
	D. accept()
		*	Task:	wait for connection request and make a connection
					by spawing a new socket.
		*	Synopsis: int accept(int sockfd, struct sockaddr *addr, socklen_t *addrlen);
		*	Return: nonnegative integer (i.e., sockfd) on suucess, 
						-1 on error
		*	Header File: #include <sys/socket.h>

	E. send()
		*	Task:	Send Data
		*	Synopsis: ssize_t send(int sockfd, const void *buf, size_t len, int flags); 
		*	Return: the number of bytes on suucess, -1 on error
		*	Header File: #include <sys/socket.h>

	F. recv()
		*	Task:	Receive Data
		*	Synopsis: ssize_t recv(int sockfd, void *buf, size_t len, int flags);
		*	Return: the number of bytes received on suucess, -1 on error
		*	Header File: #include <sys/socket.h>

	G.	close()  
		* Task: Close a socket descriptor.
		* Synopsis: int close(int sockfd);
		* Return: 0 on suucess, -1 on error  
		* Header File: #include <unistd.h>  
	----------------------------------------------------------------------
	Necessary Library Functions:
	A.	memset() 
		* Task: fill the first n bytes of memory with a constant byte. 
		* Synopsis: void *memset(void *s, int c, size_t n);
		* Return: a pointer to the memory area, s  
		* Header File: #include <string.h> 

	B.	htons() 
		* Task: convert the unsigned short integer from HBO to NBO. 
		* Synopsis: uint16_t htons(uint16_t hostshort);
		* Return: an unsigned short integer  
		* Header File: #include <netinet/in.h> 

	C.	htonl() 
		* Task: convert the unsigned long integer from HBO to NBO. 
		* Synopsis:	uint32_t htonl(uint32_t hostlong);
		* Return: an unsigned long integer  
		* Header File: #include <netinet/in.h> 

	----------------------------------------------------------------------
	Notes:
	A.	Socket is an endpoint that is used to establish communication
		between two different processes running either in the same machine 
		or two different machines in a computer network or an internet.

	B. In Linux, a socket is considered as a file. Therefore, it can be
		represented by an integer known as a socket descriptor.

	C.	Sockets are mainly classified into two types: active and passive. 

		*	Active sockets are connected with the remote active sockets 
			through an open data connection. If this connection is closed, 
			the active sockets at each end point is destroyed. 

		*	Passive sockets are not connected; instead, they wait for an 
			incoming connection that will start a new active socket.

	D. Three parameters identify a socket:
			1. socket address family
			2.	socket type
			3.	socket protocol

		*	1st parameter determines the format of the address structure.

			2nd parameter determines the form of communication:
				(a) connection-oriented and (b) connectionless

			3rd parameter determines the supported protocols.For a pair
			{address family, type}, there is/are specific protocol(s).

		*	Example:
			int sockfd = socket(AF_INET, SOCK_STREAM, 0);
			AF_INET -- IPv4 Internet Protocol
			SOCK_STREAM -- supports sequenced, reliable, two-way, 
                       	connection-based byte  streams.
			0 -- only TCP is supported in the transport layer.
									[OR]
			int sockfd = socket(AF_INET, SOCK_DGRAM, 0);
			AF_INET -- IPv4 Internet Protocol
			SOCK_DGRAM -- 	supports connectionless, unreliable messages 
								of a fixed maximum length.
			0 -- only UDP is supported in the transport layer.

			Passing 0 for the parameter 'protocol' means the default
			protocol for a particular parameter pair {domain, type}.

			** see /etc/protocols or /usr/include/netinet/in.h

		*	Created socket exists in a name space (address family), but 
			has no address assigned to it.
		
	E.	A port number is a 16-bit unsigned integer, thus ranging 
		from 0 to 65535.
		*	well known ports: 0 - 1023
			registered ports: 1024 - 49151
			private ports:	49152 -65535
	
	F.	Byte Order (BO) decides how a number is stored and sent.
		*	There are two types of BO:
			1. Big Endian:	High-order byte of the number is stored in memory at the lowest address and sent at first.
			2. Little Endian: High-order byte of the number is stored in  memory at the lowest address and sent at first.

		*	NBO (Network Byte Order): 	decides how data will be exchanged between hosts.
			HBO (Host Byte Order):	decides how data will be stored inside a specific host.
			NBO is always Big Endian whereas HBO can be both depending on 
			the architecture of the machine.		

		*	To check BO in Ubuntu:
			$ lscpu | grep "Byte Order"

		*	We need to convert HBO of port address and IP address into 
			NBO using:
			htonl() -- translates an unsigned long integer into NBO.
			htons() -- translates an unsigned short integer into NBO. 
			htonl() is for IP address and htons() is for port number.

	G. When INADDR_ANY is used as the address while calling bind(), 
		the socket accepts connections to all the available IPs of 
		the machine.
	----------------------------------------------------------------------
	Sangeeta Biswas, Ph.D.
	Assistant Professor,
	Dept. of CSE, University of Rajshahi,
	Rajshahi-6205, Bangladesh.
	sangeeta.cse.ru@gmail.com / sangeeta.cse@ru.ac.bd
	----------------------------------------------------------------------
	26/04/2018
	======================================================================
*/

#include <stdlib.h>		// exit()
#include <sys/socket.h>		//	socket(), bind()
#include <stdio.h>		// perror()
#include <netinet/in.h>		// htons(), htonl()
#include <unistd.h>		// close()
#include <string.h>		// strlen(), strcpy(), strcat(), memset()

#define LOCAL_PORT 49152
#define MSG_SZ 256

int get_sockfd(char bflag);
void turn_passive_socket(int sockfd, int backlog);
int get_active_sockfd(int sockfd);
void receive_msg(int sockfd);
void send_msg(int sockfd);
 
int main() {
	int sockfd, active_sockfd;

	/*	1. Create a socket and bind a unique name 
			(i.e. IP address:Port) to it, so that
			a client can access it via that name.
	*/
	sockfd  = get_sockfd('y');

	/*	2.	Turn a normal socket into a passive socket 
			which can be engaged in catching requests
			from remote sockets for communication.

		*	For multiple remote sockets, replace '1'
			by desired number of sockets.	
	 */
	turn_passive_socket(sockfd, 1);

	/*	3.	Spawn/Create an active socket communicating
			with a specific client socket.
	 */
	active_sockfd = get_active_sockfd(sockfd);

	/*	4.	Exchange message with a client.	*/
	send_msg(active_sockfd);
	receive_msg(active_sockfd);

	/*	5.	Close sockets by releasing any system
			resources acquired by sockets.	
	*/
	close(active_sockfd);
	close(sockfd);

	exit(EXIT_SUCCESS);
}

void send_msg(int sockfd) {
	char msg[MSG_SZ];
	ssize_t sentStrSz;

	/*	Message intended to send to the client. */
	memset(msg, '\0', MSG_SZ);	//	Clear buffer before using.
	strcpy(msg,"Welcome to my colorful World!!!\n");

	/*	Send message to the remote host. 
		send(sockfd, buffer, buf_sz, 0);
			[[ EQUIVALENT OF ]]
		write(sockfd, buffer, buf_sz);
	*/	
	sentStrSz = send(sockfd, msg, strlen(msg) + 1, 0);// Extra byte for '\0'
	if(sentStrSz == -1){
		perror("Error during send()");
		close(sockfd);
		exit(EXIT_FAILURE);
	}
}

void receive_msg(int sockfd) {
	char msg[MSG_SZ], displayMsg[MSG_SZ];
	ssize_t recvStrSz;

	/*	1.	Receive the content sent by the remote host. 
			recv(sockfd, buffer, buf_sz, 0);
				[[ EQUIVALENT OF ]]
			read(sockfd, buffer, buf_sz);
	*/	
	memset(msg, '\0', MSG_SZ);	//	Clear buffer before using.
	recvStrSz = recv(sockfd, msg, MSG_SZ, 0);
	if(recvStrSz == -1){
		perror("Error during recv()");
		close(sockfd);
		exit(EXIT_FAILURE);
	}

	/*	2. Display the message. */
	memset(displayMsg, '\0', MSG_SZ);	//	Clear buffer before using.
	strcpy(displayMsg,"\n---Received Data from Client---\n");
	strcat(displayMsg, msg);
	strcat(displayMsg,"-------------------------------\n");
	write(1, displayMsg, strlen(displayMsg));	
}

int get_active_sockfd(int sockfd) {
	/*	accept() extracts the first connection request on the 
		queue of pending connections for the listening socket,
		sockfd, creates a new connected socket, and returns a 
		new file descriptor  referring  to that socket. 

		The newly created socket is not in the listening state. 
		The original socket  sockfd  is  unaffected  by  this 
		call.
	*/
	int active_sockfd = accept(sockfd, NULL, NULL);
	if(active_sockfd == -1){
		perror("Error during accept()");
		close(sockfd);
		exit(EXIT_FAILURE);
	}	

	return active_sockfd;
}

void turn_passive_socket(int sockfd, int backlog) {
	/*	listen() turns the socket referred to by 'sockfd' as a 
		passive socket, that is, as a socket that will be used 
		to accept incoming connection requests using accept(2).

		'backlog' argument defines the maximum length of queue
		holding sockfd. By this a server can be active for 
		multiple clients at a time.

		However, if syncookies is set 1(i.e., true), then there 
		is no logical maximum length and this setting is ignored. 
		Check the value of syncookies by typing:
		$  cat /proc/sys/net/ipv4/tcp_syncookies
	*/
	int status = listen(sockfd, backlog); 
	if(status == -1){
		perror("Error during listen()");
		close(sockfd);
		exit(EXIT_FAILURE);
	}
}

int get_sockfd(char bflag) {
	int sockfd, addrLen, status;
	struct sockaddr_in addr;
	struct sockaddr *sockAddrPtr;
	
	/*	Create a socket without a name (i.e., an address.)*/
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if(sockfd == -1){
		perror("Error during socket()");
		exit(EXIT_FAILURE);
	}

	/*	Explicitly bind a unique name (i.e., address) 
		to a socket. For a server it is mandatory to
		bind a TCP socket. But for a client it is optional.
		
		Operating System (OS) automatically selects and 
		binds a name to an unbound socket of a client 
		during establishing connection.
	*/
	if(bflag == 'y'){
		addr.sin_family = AF_INET;
		addr.sin_port = htons(LOCAL_PORT);
		//addr.sin_addr.s_addr = htonl(INADDR_ANY);	// Any IP of the host.
		addr.sin_addr.s_addr = INADDR_ANY;	// Any IP of the host.
	/* In order to use a specific IP, use: inet_aton("10.10.10.1", &addr.sin_addr.s_addr);
	*	It is not mandatory to use htonl() for INADDR_ANY.		
	*/
    	sockAddrPtr = (struct sockaddr *) &addr;
    	addrLen = sizeof(struct sockaddr_in);
		status = bind(sockfd, sockAddrPtr, addrLen);
		if(status == -1){
			perror("Error during bind()");
			close(sockfd);
			exit(EXIT_FAILURE);
		}
	}
	
	return sockfd;
}
