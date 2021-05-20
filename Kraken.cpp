#include "Kraken.h"
#include <stdexcept>
#include <vector>
#include <sstream>

Kraken::Kraken()
	:m_key(""), m_secret(""), m_url("https://api.kraken.com"), m_version("0")
{
	init();
}

Kraken::Kraken(std::string key, std::string secret)
	:m_key(key), m_secret(secret), m_url("https://api.kraken.com"), m_version("0")
{
	init();
}

Kraken::Kraken(std::string key, std::string secret, std::string url, std::string version)
	: m_key(key), m_secret(secret), m_url(url), m_version(version)
{
	init();
}

Kraken::~Kraken()
{
	curl_easy_cleanup(m_curl);
}

void Kraken::init()
{
	m_curl = curl_easy_init();
	curl_global_init(CURL_GLOBAL_ALL);
	if (m_curl)
	{
		curl_easy_setopt(m_curl, CURLOPT_VERBOSE, 0L);
		curl_easy_setopt(m_curl, CURLOPT_SSL_VERIFYPEER, 1L);
		curl_easy_setopt(m_curl, CURLOPT_SSL_VERIFYHOST, 2L);
		curl_easy_setopt(m_curl, CURLOPT_USERAGENT, "Kraken C++ API Client");
		//curl_easy_setopt(m_curl, CURLOPT_POST, 1L);
		curl_easy_setopt(m_curl, CURLOPT_SSL_VERIFYSTATUS, 1L);
		curl_easy_setopt(m_curl, CURLOPT_CAINFO, "C:\\curl\\curl-7.74.0_2-win64-mingw\\bin\\cacert.pem");
		curl_easy_setopt(m_curl, CURLOPT_CAPATH, "C:\\curl\\curl-7.74.0_2-win64-mingw\\bin\\cacert.pem");
		// set callback function 
		curl_easy_setopt(m_curl, CURLOPT_WRITEFUNCTION, Kraken::WriteCallback);
	}
	else 
	{
		throw std::runtime_error("can't create curl handle");
	}

}

void Kraken::checkInput()
{

}

std::string Kraken::publicMethod(const std::string method, const std::string input) const
{
	// build method URL
	std::string path = "/" + m_version + "/public/" + method;
	std::string method_url = m_url + path;
	curl_easy_setopt(m_curl, CURLOPT_URL, method_url.c_str());

	// build postdata 
	//std::string postdata = build_query(input);
	//curl_easy_setopt(curl_, CURLOPT_POSTFIELDS, postdata.c_str());

	// reset the http header
	//curl_easy_setopt(curl_, CURLOPT_HTTPHEADER, NULL);

	// where CURL write callback function stores the response
	std::string response;
	curl_easy_setopt(m_curl, CURLOPT_WRITEDATA, static_cast<void*>(&response));

	// perform CURL request
	CURLcode result = curl_easy_perform(m_curl);
	if (result != CURLE_OK) {
		std::ostringstream oss;
		oss << "curl_easy_perform() failed: " << curl_easy_strerror(result);
		throw std::runtime_error(oss.str());
	}

	return response;
}

size_t Kraken::WriteCallback(void* contents, size_t size, size_t nmemb, void* userp)
{
	((std::string*)userp)->append((char*)contents, size * nmemb);
	return size * nmemb;
}