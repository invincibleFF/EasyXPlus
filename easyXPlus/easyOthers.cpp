#ifndef EASY_OTHERS_H
#define EASY_OTHERS_H

#include <windows.h>
#include "easyOthers.h"
#include "easyExcept.h"

namespace easyXPlus
{
	///////////////////////////////////////////////////////////////////////////
	//									Others

	void Others::pauseAll(unsigned milliSecond)
	{
		if (milliSecond == 0)
			throw EasyExcept("Invalid parameter!");

		Sleep(milliSecond);
	}
}

#endif