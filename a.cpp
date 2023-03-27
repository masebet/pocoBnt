#include "Poco/Net/HTTPServer.h"
#include "Poco/Net/HTTPRequestHandler.h"
#include "Poco/Net/HTTPRequestHandlerFactory.h"
#include "Poco/Net/HTTPServerRequest.h"
#include "Poco/Net/HTTPServerResponse.h"
#include "Poco/Net/ServerSocket.h"
#include "Poco/Util/ServerApplication.h"
#include "Poco/File.h"
#include "Poco/Path.h"

#include <iostream>
#include <filesystem>
#include <fstream>
#include <string>
#include <regex>

using namespace Poco;
using namespace Poco::Net;
using namespace Poco::Util;
using namespace std;

class HelloRequestHandler: public HTTPRequestHandler
{
    void handleRequest(HTTPServerRequest& request, HTTPServerResponse& response){
        //Application& app = Application::instance();
        //app.logger().information("Request from %s", request.clientAddress().toString());
        //app.logger().information("server %s", request.serverAddress().toString());
        //app.logger().information("server %s", request.getURI());
        
        string a = "."+request.getURI();
        cout<<a<<endl;
        std::cout;

        fstream newFile;
        newFile.open(a, ios::in); 
        if (newFile.is_open()){
            std::string content{std::istreambuf_iterator<char>(newFile), std::istreambuf_iterator<char>()};
            response.setChunkedTransferEncoding(true);
            //response.setContentType("text/html");
            response.send() << content;
        }
        else {

            response.setChunkedTransferEncoding(true);
            response.setContentType("text/html");
            response.send() << "<html><head><title>Hello</title></head><body><h1>404</h1></body></html>";
        }
        //newFile.close(); 
    }

};

class HelloRequestHandlerFactory: public HTTPRequestHandlerFactory
{
    HTTPRequestHandler* createRequestHandler(const HTTPServerRequest&)
    {

        return new HelloRequestHandler;
    }
};

class WebServerApp: public ServerApplication
{
    void initialize(Application& self){
        loadConfiguration();
        ServerApplication::initialize(self);
    }

    int main(const std::vector<std::string>&){
        UInt16 port = static_cast<UInt16>(config().getUInt("port",80));
        HTTPServer srv(new HelloRequestHandlerFactory, port);
        srv.start();
        logger().information("HTTP Server started on port %hu.", port);
        waitForTerminationRequest();
        logger().information("Stopping HTTP Server...");
        srv.stop();
        return Application::EXIT_OK;
    }
};

POCO_SERVER_MAIN(WebServerApp)