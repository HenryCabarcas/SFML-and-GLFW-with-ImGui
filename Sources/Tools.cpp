#include "Tools.h"

bool dirExists(char* path)
{
	struct stat info;

	if (stat(path, &info) != 0)
		return false;
	else if (info.st_mode & S_IFDIR)
		return true;
	else
		return false;
}

void Log(string message)
{
	string error_message = "Error: " + message;
	MessageBoxA(NULL, error_message.c_str(), "Something went wrong!", MB_ICONERROR);
}

void Log(HRESULT hr, string message)
{
	_com_error error(hr);
	string error_message = "Error: " + message + "\n" + error.ErrorMessage();
	wstring e_message = StringToWide(error_message);
	MessageBoxW(NULL, (LPCWSTR)e_message.c_str(), L"Something went wrong!", MB_ICONERROR);
}

wstring StringToWide(string str)
{
	wstring wide_string(str.begin(), str.end());
	return wide_string;
}

#ifdef ifstream

vector<string> readFile(string filename) {
	std::string STRING;
	vector<std::string> output;
	ifstream infile;
	infile.open(filename);
	while (infile.eof() == false) // To get you all the lines.
	{
		getline(infile, STRING); // Saves the line in STRING.
		output.push_back(STRING);
	}
	infile.close();
	return output;
}

#endif // ifstream

char* wchar_to_char(const wchar_t* pwchar)
{
	// get the number of characters in the string.
	int currentCharIndex = 0;
	char currentChar = pwchar[currentCharIndex];

	while (currentChar != '\0')
	{
		currentCharIndex++;
		currentChar = pwchar[currentCharIndex];
	}

	const int charCount = currentCharIndex + 1;

	// allocate a new block of memory size char (1 byte) instead of wide char (2 bytes)
	char* filePathC = (char*)malloc(sizeof(char) * charCount);

	for (int i = 0; i < charCount; i++)
	{
		// convert to char (1 byte)
		char character = pwchar[i];

		*filePathC = character;

		filePathC += sizeof(char);
	}
	filePathC += '\0';

	filePathC -= (sizeof(char) * charCount);

	return filePathC;
}

void  StringtoChar(string s, char& outStr)
{
	char cstr[sizeof(s) + 1];
	s.copy(cstr, s.size() + 1);
	cstr[s.size()] = '\0';
	strcpy(&outStr, cstr);
}

char* concatenchar(char array1[], char array2[]) {
	char* newArray = new char[std::strlen(array1) + std::strlen(array2) + 1];
	std::strcpy(newArray, array1);
	std::strcat(newArray, array2);
	return newArray;
	//delete[] newArray;
}

char* concatenchar(char array1[], const char array2[]) {
	char* newArray = new char[std::strlen(array1) + std::strlen(array2) + 1];
	std::strcpy(newArray, array1);
	std::strcat(newArray, array2);
	return newArray;
	//delete[] newArray;
}