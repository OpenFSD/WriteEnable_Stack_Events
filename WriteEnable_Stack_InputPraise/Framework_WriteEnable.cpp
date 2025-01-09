#include "Framework_WriteEnable.h"
#include <cstddef>

namespace WaitEnableWrite
{
	//std::bitset<2> selectWhichWriteControl[2] = { false, false };
	class WaitEnableWrite::WriteEnable* Framework_WriteEnable::ptr_WriteEnable = NULL;

	Framework_WriteEnable::Framework_WriteEnable()
	{
		ptr_WriteEnable = NULL;
	}

	Framework_WriteEnable::~Framework_WriteEnable()
	{

	}

	void Framework_WriteEnable::Create_Request_Wait_Write()
	{
		ptr_WriteEnable = new class WaitEnableWrite::WriteEnable();
		while (ptr_WriteEnable == NULL) { /* wait untill created */ }
		ptr_WriteEnable->Initialise_Control(
			ptr_WriteEnable->Get_GlobalForWriteControl(),
			ptr_WriteEnable->Get_GlobalForWriteControl()->Get_NumCores()
		);
	}

	void Framework_WriteEnable::Write_End(unsigned char coreId)
	{
		ptr_WriteEnable->Write_End(
			ptr_WriteEnable->Get_WriteEnable_Control(),
			&coreId,
			ptr_WriteEnable->Get_GlobalForWriteControl()->Get_NumCores(),
			ptr_WriteEnable->Get_GlobalForWriteControl()
		);
	}

	void Framework_WriteEnable::Write_Start(unsigned char coreId)
	{
		ptr_WriteEnable->Write_Start(
			ptr_WriteEnable->Get_WriteEnable_Control(),
			&coreId,
			ptr_WriteEnable->Get_GlobalForWriteControl()->Get_NumCores(),
			ptr_WriteEnable->Get_GlobalForWriteControl()
		);
	}
}