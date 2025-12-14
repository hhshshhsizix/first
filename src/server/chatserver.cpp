#include "chatserver.hpp"
#include "json.hpp"
#include <functional>
#include <string>
#include "chatservice.hpp"
using namespace std;
using namespace placeholders;
using json = nlohmann::json;


// 聊天服务器
ChatServer::ChatServer(EventLoop* loop,
                        const InetAddress& listenAddr,
                        const string& nameArg)
    : _server(loop, listenAddr, nameArg)
    {
        // 连接消息回调
        _server.setConnectionCallback(std::bind(&ChatServer::onConnection, this, _1));

        // 注册消息回调
        _server.setMessageCallback(std::bind(&ChatServer::onMessage, this, _1, _2, _3));

        // 设置线程数量
        _server.setThreadNum(4);

    }

// 启动服务
void ChatServer::start()
{
    _server.start();
}

// 上报连接相关信息的回调函数
void ChatServer::onConnection(const TcpConnectionPtr& conn)
{
    if(!conn->connected())
    {
        ChatService::instance()->clientCloseException(conn);
        //conn->shutdown();
    }
    
}
        
// 上报读写事件的回调函数
void ChatServer::onMessage(const TcpConnectionPtr& conn,
                            Buffer* buf,
                            Timestamp time)
{
    string bu = buf->retrieveAllAsString();
    json js = json::parse(bu);

    auto msghandler = ChatService::instance()->gethandler(js["msgid"].get<int>());
    // 回调消息绑定好的事件处理器,来执行相应的业务处理
    msghandler(conn, js, time);
}