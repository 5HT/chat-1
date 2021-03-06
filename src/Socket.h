/*
 * Copyright 2010-2014, Haiku, Inc. All rights reserved.
 * Distributed under the terms of the MIT license.
 *
 * Authors:
 *                Maxim Sokhatsky <maxim@synrc.com>
 *
 */

#ifndef ADAPTER_H_
#define ADAPTER_H_

#include <String.h>
#include <Message.h>

class Adapter
{

	public:
	
							enum SocketState {
								NONE,
								WAIT,
								CONNECTING,
								CONNECTED,
								ERROR
							};
		
		virtual 			~Adapter(){};
		virtual	int			Open(BString hostname, int port) = 0;
		virtual	int			SendData(BString xml) = 0;
		virtual int 		ReceiveData(BMessage* data) = 0;
		virtual	bool		IsConnected() = 0;
		virtual void		Close() = 0;
		
				BString		hostname;
				int			port;
				int			sock;

};

class Socket : public Adapter
{
	public:
		
		static	const int	BUF = 8192;
							
							Socket() { }
		virtual				~Socket();
		virtual void		Create(int domain, int sock_type, int protocol);
		virtual	int			Open(BString hostname, int port);
		virtual	int			SendData(BString xml);
		virtual int 		ReceiveData(BMessage* data);
		virtual	bool		IsConnected();
		virtual void		Close();
	
	protected:
	
				int			dom;
				int			type;
				int			proto;
				SocketState	state;
				char	  	data[Socket::BUF];
};

#endif
//.
