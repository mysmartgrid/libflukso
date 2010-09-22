#include "flukso.hpp"
#include <string>
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <iostream>
#include <sstream>


using namespace Flukso;


void Webservice::get_values() {
  CURLcode errcode = run_query();
  if (errcode) {
	std::cout << "Encountered CURL error " << errcode << 
	  ": " << curl_easy_strerror(errcode) << std::endl;
	//TODO: Propagate error to main. Think about error model.
	// How to handle reconnects?
  } 

  //TODO: Decode JSON.
}

// Write any errors in here
static char errorBuffer[CURL_ERROR_SIZE];

// Write all expected data in here
static std::string buffer;

// This is the writer call back function used by curl
static int writer(char *data, size_t size, size_t nmemb,
                  std::string *buffer)
{
  // What we will return
  int result = 0;

  // Is there anything in the buffer?
  if (buffer != NULL)
  {
    // Append the data to the buffer
    buffer->append(data, size * nmemb);

    // How much did we write?
    result = size * nmemb;
  }

  return result;
}

CURLcode Webservice::run_query() {
  CURL *curl;
  CURLcode result;
  struct curl_slist *slist = NULL;

  std::ostringstream oss;
  oss << _config->getBaseurl() << _config->getSensorId()
	<< "?interval=" << _config->getTimeInterval() 
	<< "&unit=" << _config->getUnit();
  std::string url(oss.str());
  if (_config->verbose()) 
	std::cout << "Query url: " << url << std::endl;

  curl = curl_easy_init();
  if (curl) {
	curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
	// Disable Peer Verification
	curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0L);
	curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, 0L);
	curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1);  
	// Adding Headers
	slist = curl_slist_append(slist, "Accept: application/json");
	slist = curl_slist_append(slist, "X-Version: 1.0");
	oss.flush();
	oss << "X-Token: " << _config->getTokenId();
	slist = curl_slist_append(slist, oss.str().c_str());
	curl_easy_setopt(curl, CURLOPT_HTTPHEADER, slist);

	// Forward received data to own function
	curl_easy_setopt(curl, CURLOPT_ERRORBUFFER, errorBuffer);
	curl_easy_setopt(curl, CURLOPT_WRITEDATA, &buffer);
	curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writer);

	// Performing request
	if (_config->debug())
	  std::cout << "Connecting to server and fetching data ...";
	result = curl_easy_perform(curl);
	if (_config->debug())
	  std::cout << "finished." << std::endl;

	long http_code = 0;
	curl_easy_getinfo (curl, CURLINFO_RESPONSE_CODE, &http_code);
	if (http_code == 200 && result != CURLE_ABORTED_BY_CALLBACK) {
	  if (_config->verbose()) {
		std::cout << "HTTP connection succeeded" << std::endl;
		std::cout << "Server data:" << std::endl;
		std::cout << buffer << std::endl;
	  }
	} else {
	  if (_config->verbose()) {
		std::cout << "HTTP Error: [CURL: " << result << ", " 
		  << curl_easy_strerror(result) << "] - " << errorBuffer;
		std::cout << "Server data:" << std::endl;
		std::cout << buffer << std::endl;
	  }
	}

  }
  // Cleaning up
  curl_easy_cleanup(curl);
  curl_slist_free_all(slist);
  return result;
}
