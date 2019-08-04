#ifndef XUTILS_EASYCURL_HTTP_REQUEST_H
#define XUTILS_EASYCURL_HTTP_REQUEST_H

#include <string>

namespace x {

class HttpRequest
{
public:
    static HttpRequest* Create();

public:
    virtual ~HttpRequest();
    virtual HttpRequest* AddHeader(const char* key, const char* val) = 0;
    virtual HttpRequest* AddHeader(const char* kv) = 0;
    virtual HttpRequest* ClearHeader() = 0;
    virtual HttpRequest* ClearHeader(const char* key) = 0;
    virtual HttpRequest* SetConnectTimeout(long milliseconds) = 0;
    virtual HttpRequest* SetTimeout(long milliseconds) = 0;
    virtual HttpRequest* SetUrl(const char* url) = 0;
    virtual int Get(std::string& result) = 0;
    virtual int Get(const char* url, std::string& result) = 0;
    virtual int Post(const std::string& body, std::string& result) = 0;
    virtual int Post(const char* url, const std::string& body, std::string& result) = 0;
    virtual int ErrorCode() = 0;

};

}

#endif