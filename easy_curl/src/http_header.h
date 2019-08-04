#ifndef XUTILS_EASYCURL_HTTP_HEADER_H
#define XUTILS_EASYCURL_HTTP_HEADER_H

#include <curl/curl.h>

namespace x {

class EasyCurlImpl;

class HttpHeader
{
public:
    HttpHeader();
    ~HttpHeader();
    void Add(const char* kv);
    void Add(const char* key, const char* val);
    int AppendToCurl(CURL* curl);
    void Clear();
    void Clear(const char* key);
    bool IsHeaderChanged() const { return changed_; }

private:
    bool changed_;
    curl_slist* slist_;
};

}

#endif