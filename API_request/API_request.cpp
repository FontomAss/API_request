
#include <iostream>
#include <curl/curl.h>

static size_t write_data(char* data, size_t size, size_t nmemb, void* userp) {
    std::string* response = (std::string*)userp;
    response->append(data, size * nmemb);
    return size * nmemb;
}

int main() {
    CURL* curl;
    CURLcode res;

    std::string response;

    curl_global_init(CURL_GLOBAL_DEFAULT);

    curl = curl_easy_init();
    if (curl) {
        curl_easy_setopt(curl, CURLOPT_URL, "https://catfact.ninja/fact");
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_data);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);

        res = curl_easy_perform(curl);

        if (res != CURLE_OK) {
            std::cerr << "Error: " << curl_easy_strerror(res) << std::endl;
            return 1;
        }

        std::cout << response << std::endl;

        curl_easy_cleanup(curl);
    }

    curl_global_cleanup();

    return 0;
}
