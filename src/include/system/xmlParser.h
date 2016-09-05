#pragma once

#include "system.h"
#include "strings.h"
#include <map>


//PugiXML
#include "pugixml.hpp"

using namespace pugi;

class CXMLConfig
{
private:
	struct cfg
	{
		xml_document* doc;
		bool loaded;
	};

	std::map<std::string,cfg> configs;
	pugi::xml_node ReadNode(std::string file, std::string path);

public:
	static CXMLConfig& GetInstance();

	bool LoadXML(std::string file);
	void UnLoadXML(std::string file);

	bool ReadBool(std::string file, std::string path, std::string attr = "", bool def=false);
	uint ReadUInt(std::string file, std::string path, std::string attr = "", int def = 0);
	int ReadInt(std::string file, std::string path, std::string attr = "", int def = 0);
	float ReadFloat(std::string file, std::string path, std::string attr = "", float def = 0);
	double ReadDoouble(std::string file, std::string path, std::string attr = "", double def = 0);
	std::string ReadStr(std::string file, std::string path, std::string attr = "", std::string def = "");

	~CXMLConfig();
};
