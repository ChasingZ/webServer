#include "chatserver.hpp"
#include <nlohmann/json.hpp>
#include "chatservice.hpp"

#include <functional>
using namespace std;
using namespace placeholders;
using json = nlohmann::json;

ChatServer::ChatServer(EventLoop *loop,
                const InetAddress &listenAddr,
                const string &nameArg)
    :_server(loop,listenAddr,nameArg),_loop(loop)
{
    // 注册链接回调
    _server.setConnectionCallback(std::bind(&ChatServer::onConnection, this,_1));

    //注册消息回调
    _server.setMessageCallback(std::bind(&ChatServer::onMessage,this,_1,_2,_3));

    //设置线程数量
    _server.setThreadNum(4);   //一个I/O线程、三个work线程
}

//启动服务
void ChatServer::start()
{
    _server.start();
}
//上报链接相关信息的回调函数
void ChatServer::onConnection(const TcpConnectionPtr& conn)
{
    // 用户断开链接
    if(!conn->connected())
    {
        ChatService::instance()->clientCloseException(conn);
        conn->shutdown();
    }
}
//上报读写事件相关信息的回调函数
void ChatServer::onMessage(const TcpConnectionPtr & conn,
                Buffer * buffer,
                Timestamp time)
{
    string buf = buffer->retrieveAllAsString();
    // 数据的反序列化
    json js = json::parse(buf);

    //达到的目的：完全解耦网络模块的代码和业务模块的代码
    //通过js["msgid"] 获取 -》 业务handler -》conn js time
    //获得handler以后，在进行调用
    auto msgHandler = ChatService::instance()->getHandler(js["msgid"].get<int>());//强转
    //回调消息绑定好的事件处理，来执行相应的业务处理
    msgHandler(conn, js, time);
}

