project(easy_curl)

set(LIBRARY_OUTPUT_PATH ${PROJECT_ROOT_DIR}/build)

include_directories(
    ${PROJECT_ROOT_DIR}/easy_curl/include
)

set(SRC_LIST
    src/curl_global_init.cpp
    src/http_header.cpp
    src/http_request.cpp
    src/http_request_impl.cpp
)

add_library(${PROJECT_NAME} ${SRC_LIST})

target_link_libraries(${PROJECT_NAME}
    curl
)