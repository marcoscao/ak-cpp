#ifndef _AK_SANDBOX_DRAFT_
#define _AK_SANDBOX_DRAFT_


// * App cliente-servidor: 
// 		- Incluir tests unitarios
// 		- cliente servidor con threadpool
//		- uso templates?
//		- Qt sockets
//


class tcp_connection {
	void connect( source, target ); 
};

class tcp_server {
public:
	void listen()
	{
		// connection received launch connection
	}

	
};



class tcp_client {
public:
	void connect_to( server_addr )
	{
		try {
			tcp_socket s;
			s.connect( ip );
		}
		catch {
		}

};
