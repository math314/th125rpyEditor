#include "util.h"

#include <stdarg.h>
#include <stdlib.h>
#include <stdio.h>

using namespace std;

//�t�H�[�}�b�g�����񂩂�string���쐬����
std::string from_format(const char* _format, ...){
	va_list arg;

    va_start(arg, _format);

	char buf[2048];
    vsprintf_s(buf, _format, arg);

    va_end(arg);

	return string(buf);
}