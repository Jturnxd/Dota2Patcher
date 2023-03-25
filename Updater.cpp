#include <windows.h>
#include <shellapi.h>
#include <curl/curl.h>
#include <thread>
#include "Dota2Patcher.h"

size_t WriteRemoteString(void* ptr, size_t size, size_t nmemb, void* stream) {
	std::string data((const char*)ptr, (size_t)size * nmemb);
	*((std::stringstream*)stream) << data;
	return size * nmemb;
}

void Patcher::CheckUpdate() {
	std::stringstream out;
	CURL* curl = curl_easy_init();
	curl_easy_setopt(curl, CURLOPT_URL, "https://raw.githubusercontent.com/Wolf49406/Dota2Patcher/master/version.txt");
	curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteRemoteString);
	curl_easy_setopt(curl, CURLOPT_WRITEDATA, &out);
	curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0);
	CURLcode CURLresult = curl_easy_perform(curl);

	if (CURLresult != CURLE_OK) {
		std::cout << "Update check error! Code => " << CURLresult << std::endl;
		return;
	}

	std::string remote_version = out.str();
	
	if (strcmp(remote_version.c_str(), Globals::local_version.c_str())) {
		std::cout << "Update required!" << std::endl;
		std::cout << "Local version: " << Globals::local_version << "\nRemote version: " << remote_version << std::endl;
		std::cout << "Download latest release here: \nhttps://github.com/Wolf49406/Dota2Patcher/releases/latest" << std::endl;
		system("pause");
	}
}
