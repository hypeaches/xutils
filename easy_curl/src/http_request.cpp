#include "easy_curl/http_request.h"
#include "curl_global_init.h"
#include "http_request_impl.h"

namespace x {

static CurlGlobalInit global_init;


HttpRequest::~HttpRequest()
{
}

HttpRequest* HttpRequest::Create()
{
    return new HttpRequestImpl;
}

}
