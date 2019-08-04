#include "http_request_impl.h"

namespace x {

namespace {

size_t writeCallback(void *ptr, size_t size, size_t nmemb, void *data)
{
    char* buf = static_cast<char*>(ptr);
    std::string* result = static_cast<std::string*>(data);
    result->clear();
    result->reserve(nmemb + 1);
    result->append(buf);
    return size * nmemb;
}

}

HttpRequestImpl::HttpRequestImpl()
{
    curl_ = curl_easy_init();
    error_code_ = 0;
    timeout_ = 0;
    conn_timeout_ = 0;
}

HttpRequestImpl::~HttpRequestImpl()
{
    if (curl_)
    {
        curl_easy_cleanup(curl_);
        curl_ = NULL;
    }
}

HttpRequest* HttpRequestImpl::AddHeader(const char* key, const char* val)
{
    header_.Add(key, val);
    return this;
}

HttpRequest* HttpRequestImpl::AddHeader(const char* kv)
{
    header_.Add(kv);
    return this;
}

HttpRequest* HttpRequestImpl::ClearHeader()
{
    header_.Clear();
    return this;
}

HttpRequest* HttpRequestImpl::ClearHeader(const char* key)
{
    header_.Clear(key);
    return this;
}

HttpRequest* HttpRequestImpl::SetConnectTimeout(long milliseconds)
{
    curl_easy_setopt(curl_, CURLOPT_CONNECTTIMEOUT_MS, milliseconds);
    return this;
}

HttpRequest* HttpRequestImpl::SetTimeout(long milliseconds)
{
    curl_easy_setopt(curl_, CURLOPT_TIMEOUT_MS, milliseconds);
    return this;
}

HttpRequest* HttpRequestImpl::SetUrl(const char* url)
{
    if (error_code_ == 0)
    {
        error_code_ = curl_easy_setopt(curl_, CURLOPT_URL, url);
    }
    return this;
}

int HttpRequestImpl::ErrorCode()
{
    return error_code_;
}

void HttpRequestImpl::SetErrorCode(int code)
{
    error_code_ = code;
}

int HttpRequestImpl::Get(std::string& result)
{
    error_code_ = header_.AppendToCurl(curl_);
    if (error_code_) return error_code_;
    curl_easy_setopt(curl_, CURLOPT_WRITEDATA, &result);
    error_code_ = curl_easy_setopt(curl_, CURLOPT_WRITEFUNCTION, &writeCallback);
    if (error_code_) return error_code_;
    error_code_ = curl_easy_perform(curl_);
    return error_code_;
}

int HttpRequestImpl::Get(const char* url, std::string& result)
{
    SetUrl(url);
    if (error_code_) return error_code_;
    return Get(result);
}

int HttpRequestImpl::Post(const std::string& body, std::string& result)
{
    error_code_ = header_.AppendToCurl(curl_);
    if (error_code_) return error_code_;

    error_code_ = curl_easy_setopt(curl_, CURLOPT_POST, 1L);
    if (error_code_) return error_code_;
    error_code_ = curl_easy_setopt(curl_, CURLOPT_POSTFIELDS, body.c_str());
    if (error_code_) return error_code_;
    error_code_ = curl_easy_setopt(curl_, CURLOPT_POSTFIELDSIZE, body.size());
    if (error_code_) return error_code_;

    curl_easy_setopt(curl_, CURLOPT_WRITEDATA, &result);
    error_code_ = curl_easy_setopt(curl_, CURLOPT_WRITEFUNCTION, &writeCallback);
    if (error_code_) return error_code_;
    error_code_ = curl_easy_perform(curl_);
    return error_code_;
}

int HttpRequestImpl::Post(const char* url, const std::string& body, std::string& result)
{
    SetUrl(url);
    if (error_code_) return error_code_;
    return Post(body, result);
}

}
