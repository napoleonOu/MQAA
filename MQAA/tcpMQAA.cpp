#include <iostream>
#include <functional>
using namespace std;

#include "ec/loop.h"
#include "ec/tcpServer.h"
#include "ec/tcpClient.h"
#include "ec/timer.h"
#include "ec/singleton.h"

#include "index.h"
#include "ec/MQAA.pb.h"
#include <google/protobuf/message.h>
ec::LoginRequest logreq;
class MQAATcpServer : public ec::TcpServer
{
protected:
	virtual void onListenError()
	{
		cout << "MQAATcpServer::" << __FUNCTION__ << endl;
	}

	virtual void onSessionRead(ec::TcpSession *session)
	{
		uint32_t length = session->getInputBufferLength();
		char * buff = new char[length + 1];
		session->readInputBuffer((uint8_t *)buff, length);
		buff[length] = '\0';
		cout << "MQAATcpServer::" << __FUNCTION__
				<< " " << session->getId() << " data:" << buff << endl;
		//message.ParseFromString(buff);
		//cout<<"typename:"<<message.GetTypeName()<<endl;
		//cout<<"MSG type:"<<message.msg_type()<<endl;
		//cout<<"sequence:"<<message.sequence()<<endl;
		//cout<<"session_id:"<<message.session_id()<<endl;
		////cout<<""
		//ec::LoginRequest lgreq=message.request().login();
		//cout<<"username:"<<lgreq.username().c_str()<<endl;
		//cout<<"password:"<<lgreq.password().c_str()<<endl;
		
		logreq.ParseFromString(buff);
		cout<<"typename:"<<logreq.GetTypeName()<<endl;
		cout<<"logreq:"<<logreq.username()<<endl;
		cout<<"password:"<<logreq.password().c_str()<<endl;




		session->close();
	}

	virtual void onSessionDisconnected(ec::TcpSession *session)
	{
		cout << "MQAATcpServer::" << __FUNCTION__ << endl;
	}

	virtual void onNewSession(ec::TcpSession *session)
	{
		cout << "MQAATcpServer::" << __FUNCTION__ << session->getId() << endl;
	}
};

typedef ec::Singleton<MQAATcpServer> MQAATcpServerSingleton;

void tcpMQAA()
{
	MQAATcpServer &tcpServer = MQAATcpServerSingleton::instance();
	//if (!tcpServer.listen("127.0.0.1", 4567))
	if(!tcpServer.listen("127.0.0.1",4567))

	{
		cout << "listen failed" << endl;
		return;
	}
	tcpServer.wait();
}


