// CharacterEncodingConvert.cpp
#include "CharacterEncodingConvert.h"

#ifdef WINDOWS
std::string CharacterEncodingConvert::GbkToUtf8(const char* srcStr)
{
	int len = MultiByteToWideChar(CP_ACP, 0, srcStr, -1, NULL, 0);
	wchar_t* wstr = new wchar_t[len + 1];
	memset(wstr, 0, len + 1);
	MultiByteToWideChar(CP_ACP, 0, srcStr, -1, wstr, len);
	len = WideCharToMultiByte(CP_UTF8, 0, wstr, -1, NULL, 0, NULL, NULL);
	char* str = new char[len + 1];
	memset(str, 0, len + 1);
	WideCharToMultiByte(CP_UTF8, 0, wstr, -1, str, len, NULL, NULL);
	std::string strTemp = str;
	if (wstr) delete[] wstr;
	if (str) delete[] str;
	return strTemp;
}

std::string CharacterEncodingConvert::Utf8ToGbk(const char* srcStr)
{
	int len = MultiByteToWideChar(CP_UTF8, 0, srcStr, -1, NULL, 0);
	wchar_t* wszGBK = new wchar_t[len + 1];
	memset(wszGBK, 0, len * 2 + 2);
	MultiByteToWideChar(CP_UTF8, 0, srcStr, -1, wszGBK, len);
	len = WideCharToMultiByte(CP_ACP, 0, wszGBK, -1, NULL, 0, NULL, NULL);
	char* szGBK = new char[len + 1];
	memset(szGBK, 0, len + 1);
	WideCharToMultiByte(CP_ACP, 0, wszGBK, -1, szGBK, len, NULL, NULL);
	std::string strTemp(szGBK);
	if (wszGBK) delete[] wszGBK;
	if (szGBK) delete[] szGBK;
	return strTemp;
}
#elif LINUX
std::string CharacterEncodingConvert::GbkToUtf8(const char * srcStr)
{
	std::string resultStr="";
	char* destStr=NULL;
	iconv_t cd;
	char **pin = &srcStr;
	char **pout = &destStr;

	int srcLen = strlen(srcStr);
	int destLen = srcLen * 3; // 保持足够空间进行编码转换

	cd = iconv_open("utf8", "gbk");
	if (cd == 0)
		return resultStr;
	memset(destStr, 0, destLen);
	if (iconv(cd, pin, &srcLen, pout, &destLen) == -1)
		return resultStr;
	iconv_close(cd);
	*pout = '\0';
	resultStr = destStr;
	return resultStr;
}

std::string CharacterEncodingConvert::Utf8ToGbk(const char * srcStr)
{
	std::string resultStr = "";
	char* destStr = NULL;
	iconv_t cd;
	char **pin = &srcStr;
	char **pout = &destStr;

	int srcLen = strlen(srcStr);
	int destLen = srcLen * 3; // 保持足够空间进行编码转换

	cd = iconv_open("gbk", "utf8");
	if (cd == 0)
		return resultStr;
	memset(destStr, 0, destLen);
	if (iconv(cd, pin, &srcLen, pout, &destLen) == -1)
		return resultStr;
	iconv_close(cd);
	*pout = '\0';
	resultStr = destStr;
	return resultStr;
}
#endif
