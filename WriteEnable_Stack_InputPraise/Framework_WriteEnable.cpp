#include "Framework_WriteEnable.h"
#include <cstddef>

namespace WaitEnableWrite
{
	class WaitEnableWrite::WriteEnable* Framework_WriteEnable::ptr_WriteEnable = NULL;

	Framework_WriteEnable::Framework_WriteEnable()
	{
		ptr_WriteEnable = NULL;
	}

	Framework_WriteEnable::~Framework_WriteEnable()
	{

	}

	void Framework_WriteEnable::Create_WriteEnable()
	{
		ptr_WriteEnable = new class WaitEnableWrite::WriteEnable();
		while (ptr_WriteEnable == NULL) { /* wait untill created */ }
	}

	void Framework_WriteEnable::Write_End(unsigned char coreId)
	{
		ptr_WriteEnable->Write_End(coreId);
	}

	void Framework_WriteEnable::Write_Start(unsigned char coreId)
	{
		ptr_WriteEnable->Write_Start(coreId);
	}

	WaitEnableWrite::WriteEnable* Framework_WriteEnable::Get_WriteEnable()
	{
		return ptr_WriteEnable;
	}
}