// CharacterEncodingConvert.h
#ifndef _CHARACTER_ENCODING_CONVERT_H_
#define _CHARACTER_ENCODING_CONVERT_H_

#include <string>

#ifdef WINDOWS
#include <windows.h>
#elif LINUX
#include <iconv.h>
#endif

class CharacterEncodingConvert
{
public:
	CharacterEncodingConvert();
	virtual ~CharacterEncodingConvert();

	static std::string GbkToUtf8(const char* srcStr);
	static std::string Utf8ToGbk(const char* srcStr);
};

#endif // !_CHARACTER_ENCODING_CONVERT_H_
