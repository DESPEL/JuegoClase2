#pragma once

#include <Windows.h>
#include <fstream>
#include <map>
#include <string>
//#include "cocos2d.h"

class TranslationEngine
{
private: 
	TranslationEngine();

	static TranslationEngine* globalEngine;
	inline static std::string defaultLanguage = "ES_MX";
	std::string language;

	std::map<std::string, std::string> langStrings;
public:
	enum Language {
		ES_MX = 0, EN_US = 1
	};


	static TranslationEngine* getInstance();

	void setLanguage(std::string lang);

	std::string getLanguage() {
		return language;
	}

	std::string get(std::string strname) {
		return langStrings[strname];
	}

	std::string operator[](std::string strname) {
		return langStrings[strname];
	}

};