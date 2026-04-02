#include <iostream>
#include <string>
#include <curl/curl.h>

// Callback function to store response data
size_t WriteCallback(void* contents, size_t size, size_t nmemb, std::string* output) {
    size_t totalSize = size * nmemb;
    output->append((char*)contents, totalSize);
    return totalSize;
}

int main() {
    CURL* curl;
    CURLcode res;
    std::string response;

    curl = curl_easy_init();
    if (curl) {
        // tests the json for is_even API
        curl_easy_setopt(curl, CURLOPT_URL, "https://api.isevenapi.xyz/api/iseven/240");
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);

        res = curl_easy_perform(curl);

        if (res != CURLE_OK) {
            std::cerr << "curl error: " << curl_easy_strerror(res) << std::endl;
        } else {
            // NOTE: JSON will need to be parsed by a separate program!
            std::cout << response << std::endl;
        }

        curl_easy_cleanup(curl);
    }

    return 0;
}