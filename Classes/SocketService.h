#pragma once
#include "cocos2d.h"
#include <string.h>
#include "network/WebSocket.h"
#include "json/document.h"

USING_NS_CC;
using namespace std;
using namespace network;

class SocketService:public network::WebSocket::Delegate
{
public:

	static SocketService* socket;

	static SocketService* getInstance();
	
	static void delteInstance();
public:
	~SocketService();

	void initSocket();//≥ı ºªØsocket

	void sendMessage(string str);

	string getMessage();

	void setMessage(string s);

	void setPrivatePassword(string privateStr);

	string getPrivatePassword();

	void setPlayerType(string type);

	string  getPlayerType();

	void setAccount(string name);

	string  getAccount();


	virtual void onOpen(WebSocket* ws) ;

	virtual void onMessage(WebSocket* ws, const WebSocket::Data& data) ;
	
	virtual void onClose(WebSocket* ws) ;
	
	virtual void onError(WebSocket* ws, const WebSocket::ErrorCode& error) ;
private:
	WebSocket* client;

	string receiveMessage;

	bool ifReceviceMessage;

	string privatePassword;

	string playerType;

	string account;

};

