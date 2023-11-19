#include "error.hpp"
// エラーメッセージとエラーコードを連結して返す関数
std::string Error::fmtErrorCode(const std::string& errorMessage, const int errorCode) {
	std::string fmtString =
		std::format("ERROR:{} ERROR-CODE:{}", errorMessage, errorCode);
	return fmtString;
}
