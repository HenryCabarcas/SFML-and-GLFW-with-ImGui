#pragma once
#include "Dependances.h"

void Log(string message);
void Log(HRESULT hr, string message);
wstring StringToWide(string str);
bool dirExists(char* path);
#ifdef ifstream

vector<string> readFile(string filename);

#endif // ifstream
char* wchar_to_char(const wchar_t* pwchar);
void  StringtoChar(std::string s, char& outStr);
char* concatenchar(char array1[], const char array2[]);
char* concatenchar(char array1[], char array2[]);
