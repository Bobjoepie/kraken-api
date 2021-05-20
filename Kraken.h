#pragma once
#include <curl/curl.h>
#include <string>


class Kraken
{
public:
	Kraken();
	Kraken(std::string key, std::string secret);
	Kraken(std::string key, std::string secret,
		std::string url, std::string version);
	~Kraken();
	void checkInput();
	std::string publicMethod(const std::string method, const std::string input) const;
private:
	void init();

	static size_t WriteCallback(void* contents, size_t size, 
		size_t nmemb, void* userp);

	CURL* m_curl;
	CURLcode m_res;

	std::string m_key;
	std::string m_secret;
	std::string m_url;
	std::string m_version;
};

