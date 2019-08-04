#ifndef XUTILS_EASYCURL_HTTP_REQUEST_IMPL_H
#define XUTILS_EASYCURL_HTTP_REQUEST_IMPL_H

#include <curl/curl.h>
#include "easy_curl/http_request.h"

#include "http_header.h"

namespace x {

class HttpRequestImpl : public x::HttpRequest
{
public:
    HttpRequestImpl();

public:
    virtual ~HttpRequestImpl();
    virtual HttpRequest* AddHeader(const char* key, const char* val) override;
    virtual HttpRequest* AddHeader(const char* kv) override;
    virtual HttpRequest* ClearHeader() override;
    virtual HttpRequest* ClearHeader(const char* key) override;
    virtual HttpRequest* SetConnectTimeout(long milliseconds) override;
    virtual HttpRequest* SetTimeout(long milliseconds) override;
    virtual HttpRequest* SetUrl(const char* url) override;

    virtual int Get(std::string& result) override;
    virtual int Get(const char* url, std::string& result) override;
    virtual int Post(const std::string& body, std::string& result) override;
    virtual int Post(const char* url, const std::string& body, std::string& result) override;

    virtual int ErrorCode();

public:
    void SetErrorCode(int code);

private:
    CURL* curl_;
    int error_code_;
    int timeout_;
    int conn_timeout_;
    HttpHeader header_;
};

}

#endif