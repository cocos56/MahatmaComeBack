#include "SocketService.h"

SocketService* SocketService::socket = NULL;

SocketService::~SocketService()
{
	client->close();
}

SocketService* SocketService::getInstance()
{
	if (socket == NULL)
	{
		socket = new SocketService();
	}
	return socket;
}
void SocketService::initSocket()
{
	auto s = FileUtils::getInstance()->getStringFromFile("Data.json");
	rapidjson::Document doc;
	doc.Parse<0>(s.c_str());
	auto ip = doc["ip"].GetString();
	auto port = doc["port"].GetInt();
	string str = String::createWithFormat("ws://%s:%d", ip, port)->getCString();
	client = new WebSocket();
	client->init(*this, str);

	receiveMessage = "";
	ifReceviceMessage = false;
	privatePassword = "";
}



void SocketService::onOpen(WebSocket* ws)
{
	log("connect successful");
}
void SocketService::onMessage(WebSocket* ws, const WebSocket::Data& data)
{
	//接收到服务器发来的消息
	log("%s", data.bytes);

	receiveMessage = data.bytes;

	ifReceviceMessage = true;
}

void SocketService::onClose(WebSocket* ws)
{
	log("connect stop");
}

void SocketService::onError(WebSocket* ws, const WebSocket::ErrorCode& error)
{

}

void SocketService::delteInstance()
{
	if (socket)
	{
		delete socket;
		socket = NULL;
	}
}

void SocketService::sendMessage(string str)
{
	log("%s", str.c_str());
	client->send(str);
}

std::string SocketService::getMessage()
{
	return receiveMessage;
}

void SocketService::setPrivatePassword(string privateStr)
{
	privatePassword = privateStr;
}

std::string SocketService::getPrivatePassword()
{
	return privatePassword;
}

void SocketService::setMessage(string s)
{
	receiveMessage = s;
}

void SocketService::setPlayerType(string type)
{
	this->playerType = type;
}

string SocketService::getPlayerType()
{
	return playerType;
}

void SocketService::setAccount(string name)
{
	this->account = name;
}

std::string SocketService::getAccount()
{
	return this->account;
}
