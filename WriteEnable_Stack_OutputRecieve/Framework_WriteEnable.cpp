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

	void Framework_WriteEnable::Write_End(unsigned char coreId)
	{
		ptr_WriteEnable->Write_End(
			ptr_WriteEnable->Get_WriteEnable_Control(),
			coreId,
			ptr_WriteEnable->Get_GlobalForWriteControl()
		);
	}

	void Framework_WriteEnable::Write_Start(unsigned char coreId)
	{
		ptr_WriteEnable->Write_Start(
			ptr_WriteEnable->Get_WriteEnable_Control(),
			coreId,
			ptr_WriteEnable->Get_GlobalForWriteControl()
		);
	}
}