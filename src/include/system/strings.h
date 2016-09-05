#pragma once

#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <algorithm>

typedef std::string string;

char tolower_uchar(char c);
char toupper_uchar (char c);
void ToLower(string& str);
void ToUpper(string& str);
std::vector<string> split(const string& source, char delim = '\n' );
string GetFileAsString(const string& strFileName);

char* inttostr(int val);
char* ftostr(float val);
