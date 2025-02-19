#include "WriteEnable_Stack_Client_OutputRecieve_Framework.h"
#include <cstddef>

namespace WaitEnableWrite
{
	class WaitEnableWrite::WriteEnable_Stack_Client_OutputRecieve* WriteEnable_Stack_Client_OutputRecieve_Framework::ptr_WriteEnable = NULL;

	WriteEnable_Stack_Client_OutputRecieve_Framework::WriteEnable_Stack_Client_OutputRecieve_Framework()
	{
		ptr_WriteEnable = NULL;
	}

	WriteEnable_Stack_Client_OutputRecieve_Framework::~WriteEnable_Stack_Client_OutputRecieve_Framework()
	{

	}

	void WriteEnable_Stack_Client_OutputRecieve_Framework::Create_WriteEnable()
	{
		ptr_WriteEnable = new class WaitEnableWrite::WriteEnable_Stack_Client_OutputRecieve();
		while (ptr_WriteEnable == NULL) { /* wait untill created */ }
	}

	void WriteEnable_Stack_Client_OutputRecieve_Framework::Write_End(unsigned char coreId)
	{
		ptr_WriteEnable->Write_End(coreId);
	}

	void WriteEnable_Stack_Client_OutputRecieve_Framework::Write_Start(unsigned char coreId)
	{
		ptr_WriteEnable->Write_Start(coreId);
	}

	WaitEnableWrite::WriteEnable_Stack_Client_OutputRecieve* WriteEnable_Stack_Client_OutputRecieve_Framework::Get_WriteEnable()
	{
		return ptr_WriteEnable;
	}
}