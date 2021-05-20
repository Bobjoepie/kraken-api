#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <curl/curl.h>
#include <chrono>
#include "rapidjson/document.h"
#include <rapidjson/writer.h>
#include <rapidjson/stringbuffer.h>
#include "rapidjson/prettywriter.h"

static size_t WriteCallback(void* contents, size_t size, size_t nmemb, void* userp)
{
    ((std::string*)userp)->append((char*)contents, size * nmemb);
    return size * nmemb;
}

int main2(int argc, char* argv[])
{
    CURL* curl;
    CURLcode res;
    std::string readBufferDOGEUSD, readBufferDOGEBTC, readBufferBTCUSD, readBufferTime;
    const char* jsonDOGEUSD;
    const char* jsonDOGEBTC;
    const char* jsonBTCUSD;
    const char* jsonTime;
    double initial = 100.0f;
    rapidjson::Document d1, d2, d3, dTime;
    curl_global_init(CURL_GLOBAL_ALL);
    curl = curl_easy_init();
    while (curl)
    {
        Sleep(1000);
        curl_easy_cleanup(curl);
        //curl_easy_reset(curl);
        //curl_global_cleanup();
        readBufferDOGEUSD.clear();
        readBufferDOGEBTC.clear();
        readBufferBTCUSD.clear();
        readBufferTime.clear();
        curl = nullptr;
        //curl_global_init(CURL_GLOBAL_ALL);
        curl = curl_easy_init();
        curl_easy_setopt(curl, CURLOPT_SSLCERTTYPE, "PEM");
        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 1L);
        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, 2L);
        curl_easy_setopt(curl, CURLOPT_USERAGENT, "Kraken C++ API Client");
        //curl_easy_setopt(curl, CURLOPT_POST, 1L);
        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYSTATUS, 1L);
        curl_easy_setopt(curl, CURLOPT_CAINFO, "C:\\curl\\curl-7.74.0_2-win64-mingw\\bin\\cacert.pem");
        curl_easy_setopt(curl, CURLOPT_CAPATH, "C:\\curl\\curl-7.74.0_2-win64-mingw\\bin\\cacert.pem");
        curl_easy_setopt(curl, CURLOPT_URL, "https://api.kraken.com/0/public/Ticker?pair=DOGEUSD");
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBufferDOGEUSD);
        
        res = curl_easy_perform(curl);

        if (res != CURLE_OK)
        {
            std::cout << "curl easy perform() returned " << curl_easy_strerror(res) << std::endl;
        }

        //curl_easy_cleanup(curl);
        
        curl_easy_setopt(curl, CURLOPT_URL, "https://api.kraken.com/0/public/Ticker?pair=DOGEBTC");
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBufferDOGEBTC);

        res = curl_easy_perform(curl);
        //curl_easy_cleanup(curl);

        curl_easy_setopt(curl, CURLOPT_URL, "https://api.kraken.com/0/public/Ticker?pair=BTCUSD");
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBufferBTCUSD);

        res = curl_easy_perform(curl);

        curl_easy_setopt(curl, CURLOPT_URL, "https://api.kraken.com/0/public/Time");
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBufferTime);

        res = curl_easy_perform(curl);
        
        jsonDOGEUSD = readBufferDOGEUSD.c_str();
        jsonDOGEBTC = readBufferDOGEBTC.c_str();
        jsonBTCUSD = readBufferBTCUSD.c_str();
        jsonTime = readBufferTime.c_str();
        
        d1.Parse(jsonDOGEUSD);
        d2.Parse(jsonDOGEBTC);
        d3.Parse(jsonBTCUSD);
        dTime.Parse(jsonTime);

        const rapidjson::Value& strAsk1 = d1["result"]["XDGUSD"]["a"];
        double floatAsk1 = std::stof(strAsk1[0].GetString());
        std::cout << "[DOGE -> USD] Buy: " << strAsk1[0].GetString() << " USD" << std::endl;
        const rapidjson::Value& strBid1 = d1["result"]["XDGUSD"]["b"];
        double floatBid1 = std::stof(strBid1[0].GetString());
        std::cout << "[DOGE -> USD] Sell: " << strBid1[0].GetString() << " USD" << std::endl;

        const rapidjson::Value& strAsk2 = d2["result"]["XXDGXXBT"]["a"];
        double floatAsk2 = std::stof(strAsk2[0].GetString());
        std::cout << "[BTC -> DOGE] Buy: " << strAsk2[0].GetString() << " DOGE" << std::endl;
        const rapidjson::Value& strBid2 = d2["result"]["XXDGXXBT"]["b"];
        double floatBid2 = std::stof(strBid2[0].GetString());
        std::cout << "[BTC -> DOGE] Sell: " << strBid2[0].GetString() << " DOGE" << std::endl;

        const rapidjson::Value& strAsk3 = d3["result"]["XXBTZUSD"]["a"];
        double floatAsk3 = std::stof(strAsk3[0].GetString());
        std::cout << "[BTC -> USD] Buy: " << strAsk3[0].GetString() << " USD" << std::endl;
        const rapidjson::Value& strBid3 = d3["result"]["XXBTZUSD"]["b"];
        double floatBid3 = std::stof(strBid3[0].GetString());
        std::cout << "[BTC -> USD] Sell: " << strBid3[0].GetString() << " USD" << std::endl;

        const rapidjson::Value& strTime = dTime["result"]["rfc1123"];
        std::cout << strTime.GetString() << std::endl;

        std::cout << initial << " USD start" << std::endl;
        double fee = 0.0000;
        double convert1 = (initial / floatAsk1) - (fee * (initial / floatAsk1));
        std::cout << convert1 << " DOGE" << std::endl;
        double convert2 = (floatBid2 * convert1) - (fee * (floatBid2 * convert1));
        std::cout << convert2 << " BTC" << std::endl;
        double convert3 = (floatBid3 * convert2) - (fee * (floatBid3 * convert2));
        double profit = convert3 / initial;
        //std::cout << convert1 << std::endl << convert2 << std::endl << convert3 << std::endl;
        if (profit > 1.00f)
        {
            initial = convert3;
            std::cout << "Increase to ";
            Sleep(1000);
        }
        std::cout << convert3 << " USD" << std::endl;
        std::cout << std::endl;
    }
    curl_global_cleanup();
    return 0;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
