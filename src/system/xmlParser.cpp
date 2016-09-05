#include <system/xmlParser.h>

CXMLConfig& CXMLConfig::GetInstance()
{
	static CXMLConfig _instance;
	return _instance;
}

bool CXMLConfig::LoadXML(std::string file)
{
	if (configs.find(file) != configs.end()) {
		if (configs[file].loaded) return true;
	}

	pugi::xml_document* doc = new xml_document;
	pugi::xml_parse_result result = doc->load_file(("gamedata/scripts/config/"+file+".xml").c_str());
	if (!result)
		return false; // Ошибка парсинга данных
	configs[file].doc = doc;
	configs[file].loaded = true;
	return true;
}

void CXMLConfig::UnLoadXML(std::string file)
{
	if (configs.find(file) != configs.end()) {
		if (configs[file].loaded) {
			delete configs[file].doc;
			configs[file].loaded = false;
		}
		configs.erase(file);
	}
}

pugi::xml_node CXMLConfig::ReadNode(std::string file, std::string path)
{
	std::vector<std::string> p;
	p = split(path,'/');

	pugi::xml_node node;
	node = configs[file].doc->child(p[0].c_str());

	for (char i = 1; i < p.size(); i++) {
		node = node.child(p[i].c_str());
	}
	return node;
}

std::string CXMLConfig::ReadStr(std::string file, std::string path, std::string attr, std::string def)
{
	std::string ret;
	if (configs.find(file) != configs.end()) {
		if (configs[file].loaded) {
			pugi::xml_node node = ReadNode(file, path);

			if (node) {
				if (attr == "")
					ret = node.child_value();
				else
					ret = node.attribute(attr.c_str()).value();
			}
		}
	}
	if (ret == "") ret = def;
	return ret;
}

float CXMLConfig::ReadFloat(std::string file, std::string path, std::string attr, float def)
{
	return atof(ReadStr(file,path,attr,"0").c_str());
}

int CXMLConfig::ReadInt(std::string file, std::string path, std::string attr, int def)
{
	return atoi(ReadStr(file,path,attr,inttostr(def)).c_str());
}

bool CXMLConfig::ReadBool(std::string file, std::string path, std::string attr, bool def)
{
	bool ret = def;
	std::string tmp = ReadStr(file,path,attr,"");
	ToLower(tmp);
	if (tmp == "true") ret = true;
	else if (tmp == "false") ret = false;
	else ret = def;
	return ret;
}


CXMLConfig::~CXMLConfig()
{
	std::map<std::string,cfg>::iterator it;
	for (it=configs.begin(); it != configs.end(); it++) {
		//if ((*it).doc) delete((*it).doc);
	}
}
