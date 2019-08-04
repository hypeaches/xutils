#include "http_header.h"

#include <cstring>
#include <string>

namespace x {

HttpHeader::HttpHeader()
{
    changed_ = false;
    slist_ = NULL;
}

HttpHeader::~HttpHeader()
{
    Clear();
}

void HttpHeader::Add(const char* kv)
{
    curl_slist* tmp = curl_slist_append(slist_, kv);
    if (tmp)
    {
        slist_ = tmp;
        changed_ = true;
    }
}

void HttpHeader::Add(const char* key, const char* val)
{
    std::string kv;
    kv.reserve(strlen(key) + strlen(val) + 2);
    kv.append(key).append(":").append(val);
    return Add(kv.c_str());
}

int HttpHeader::AppendToCurl(CURL* curl)
{
    int ec = 0;
    if (slist_ && changed_)
    {
        changed_ = false;
        ec = curl_easy_setopt(curl, CURLOPT_HTTPHEADER, slist_);
    }
    return ec;
}

void HttpHeader::Clear()
{
    if (slist_)
    {
        curl_slist_free_all(slist_);
        slist_ = NULL;
        changed_ = true;
    }
}

void HttpHeader::Clear(const char* key)
{
    return Add(key, "");
}

}
