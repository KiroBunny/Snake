#pragma once

#define _CRT_SECURE_NO_WARNINGS
#define _USE_MATH_DEFINES
#ifdef UNICODE
# undef UNICODE
# define _MBCS
#endif

#ifndef __cplusplus
#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>
#else
#include <cstdlib>
#include <cstdio>
#include <cstdarg>
using namespace std;
#endif
#include <windows.h>

#ifdef __cplusplus
extern "C" {
#endif

#if defined(_MSC_VER) && (_MSC_VER < 1800)
	static int vsscanf(const char* s, const char* fmt, va_list ap); 
#endif

	void setcursor(int x, int y);
	int xyprintf(int x, int y, const char* format, ...);
	
#ifdef __cplusplus
}
#endif