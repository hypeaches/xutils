#include "curl_global_init.h"

#include <curl/curl.h>

namespace x {

CurlGlobalInit::CurlGlobalInit()
{
    curl_global_init(CURL_GLOBAL_ALL);
}

CurlGlobalInit::~CurlGlobalInit()
{
    curl_global_cleanup();
}

}
