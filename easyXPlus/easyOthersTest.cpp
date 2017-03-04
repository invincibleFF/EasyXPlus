#include "easyOthers.h"
#include "easyExcept.h"

#include "SU.h"

using namespace easyXPlus;

///////////////////////////////////////////////////////////////////////////////
//										Tests

void PauseAll_PassZero_ThrowExcept()
{
	SU_ASSERT_THROW( Others::pauseAll(0), EasyExcept);
}