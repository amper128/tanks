#include <system/strings.h>

char tolower_uchar(char c)
{
	return std::tolower(c, std::locale());
}

char toupper_uchar (char c)
{
	return std::toupper(c, std::locale());
}

void ToLower(std::string& str)
{
	std::transform(str.begin(), str.end(), str.begin(), tolower_uchar);
}

void ToUpper(std::string& str)
{
	std::transform(str.begin(), str.end(), str.begin(), toupper_uchar);
}

std::vector<std::string> split(const std::string& source, char delim)
{
    std::vector<std::string> result;

    std::istringstream stream(source);
    std::string str;

    while (std::getline(stream, str, delim))
    {
	result.push_back(str);
    }

    return result;
}

std::string GetFileAsString(const std::string& strFileName)
{
	std::string content;
	std::ifstream in(strFileName.c_str(), std::ios::binary);
	std::istreambuf_iterator<char> begin(in), end;
	while(begin != end)
		content += *begin++;
	return content;
}


//это достаточно быстрый алгоритм перевода числа в строку, замена itoa (даже может быстрее работает)
char* inttostr(int val)
{
	static const int MAX = 32;
	static char buff[MAX]={0};
	char* res = buff + MAX - 2;
	do
	{
		*(res--) = '0' + val%10;
		val/=10;
	}
	while (val > 0);
	return res + 1;
}

char* ftostr(float val)
{
	char *string;
	string = new char[99];
	sprintf(string,"%f",val);
	return string;
}
