#pragma once 
#include <string>
#include <format>

class Error final {
public:
	// エラーメッセージとエラーコードを連結して返す関数
	static std::string fmtErrorCode(const std::string& errorMessage, const int errorCode);
};