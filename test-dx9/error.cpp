#include "error.hpp"
// �G���[���b�Z�[�W�ƃG���[�R�[�h��A�����ĕԂ��֐�
std::string Error::fmtErrorCode(const std::string& errorMessage, const int errorCode) {
	std::string fmtString =
		std::format("ERROR:{} ERROR-CODE:{}", errorMessage, errorCode);
	return fmtString;
}
