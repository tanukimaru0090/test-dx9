#pragma once 
#include <string>
#include <format>

class Error final {
public:
	// �G���[���b�Z�[�W�ƃG���[�R�[�h��A�����ĕԂ��֐�
	static std::string fmtErrorCode(const std::string& errorMessage, const int errorCode);
};