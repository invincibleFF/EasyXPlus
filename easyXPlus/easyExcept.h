#ifndef EASY_EXCEPT_H
#define EASY_EXCEPT_H

#include <stdexcept>

namespace easyXPlus
{
	class EasyExcept : public std::logic_error
	{
	public:
		EasyExcept(std::string str) : logic_error(str)	{}
	};
}

#endif