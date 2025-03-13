#include <iostream>
#include <curl/curl.h>
#include <vector>
#include <string>
#include <unordered_map>

int main(int argc, char** argv)
{
    std::unordered_map<std::string, std::string> params;

    auto process_func = [](std::string v) -> std::pair<std::string, std::string>{
        size_t pos = v.find("=");
        return {v.substr(0, pos), v.substr(pos + 1)};
    };

    for (int i = 1; i < argc; i++) {
        params.insert(process_func(argv[i]));
    }

    CURL *curl;
    struct curl_slist *host = NULL;
    host = curl_slist_append(NULL, params["host_resolve"].c_str());
    
    curl = curl_easy_init();
    if (curl) {
        curl_easy_setopt(curl, CURLOPT_RESOLVE, host);
        curl_easy_setopt(curl, CURLOPT_URL, "https://storage.googleapis.com");
        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0L);
        curl_easy_setopt(curl, CURLOPT_INTERFACE, params["local"].c_str());

        curl_easy_perform(curl);
        curl_easy_cleanup(curl);
    }

    curl_slist_free_all(host);

    return 0;
}