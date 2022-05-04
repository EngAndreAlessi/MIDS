#pragma once
#include <string>
#include <iostream>
#include "CppLib/Utilities/header/Macros.h"

/*
	adicione "#define DEBUG_MODE" no código ou 
	a flag "-DDEBUG_MODE" durante a compilação 
	para exibir informações extras durante a
	execução
*/

#ifdef DEBUG_MODE
	#define log_message(label, msg)				\
		do										\
		{										\
			std::cout << label << ": ";			\
			std::cout << msg << std::endl;		\
		}										\
		while(false)
	#define log_message2(label, msg1, msg2)		\
		do										\
		{										\
			std::cout << label << ": ";			\
			std::cout << msg1 << ", ";			\
			std::cout << msg2 << std::endl;		\
		}										\
		while(false)
	#define log_function(callback)		callback()
#endif

#ifndef DEBUG_MODE
	#define log_message(label, msg)				;
	#define log_message2(label, msg1, msg2)		;
	#define log_function(callback)				;
#endif
