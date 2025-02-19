#include "WriteEnable_Stack_Server_OutputRecieve_Control.h"
#include <cstddef>

namespace WaitEnableWrite
{
    unsigned char WriteEnable_Stack_Server_OutputRecieve_Control::coreId_For_WritePraise_Index = NULL;
    int WriteEnable_Stack_Server_OutputRecieve_Control::ptr_count_CoreId_WriteActive[4] = { NULL, NULL, NULL, NULL };//NUMBER OF CORES
    int WriteEnable_Stack_Server_OutputRecieve_Control::ptr_count_CoreId_WriteIdle[4] = { NULL, NULL, NULL, NULL };//NUMBER OF CORES
    int WriteEnable_Stack_Server_OutputRecieve_Control::ptr_count_CoreId_WriteWait[4] = { NULL, NULL, NULL, NULL };//NUMBER OF CORES
    bool WriteEnable_Stack_Server_OutputRecieve_Control::flag_WriteState[4][2] = { {NULL, NULL}, {NULL, NULL}, {NULL, NULL}, {NULL, NULL} };//NUMBER OF CORES
    unsigned char WriteEnable_Stack_Server_OutputRecieve_Control::ptr_new_coreId_For_WritePraise_Index = NULL;
    bool WriteEnable_Stack_Server_OutputRecieve_Control::praisingWrite = NULL;
    unsigned char WriteEnable_Stack_Server_OutputRecieve_Control::ptr_que_CoreToWrite[4] = { NULL, NULL, NULL, NULL };//NUMBER OF CORES

    WriteEnable_Stack_Server_OutputRecieve_Control::WriteEnable_Stack_Server_OutputRecieve_Control(
        class WaitEnableWrite::WriteEnable_Stack_Server_OutputRecieve_Global* ptr_Global
    )
    {
        coreId_For_WritePraise_Index = unsigned char(0);
        int ptr_count_CoreId_WriteActive[4] = { int(0), int(0), int(0), int(0) };//NUMBER OF CORES
        int ptr_count_CoreId_WriteIdle[4] = { int(0), int(0), int(0), int(0) };//NUMBER OF CORES
        int ptr_count_CoreId_WriteWait[4] = { int(0), int(0), int(0), int(0) };//NUMBER OF CORES
        bool flag_WriteState[4][2] = { {bool(false), bool(false)}, {bool(false), bool(false)}, {bool(false), bool(false)}, {bool(false), bool(false)}};//NUMBER OF CORES
        flag_WriteState[0][0] = ptr_Global->GetConst_Write_IDLE(0);
        flag_WriteState[0][1] = ptr_Global->GetConst_Write_IDLE(1);
        flag_WriteState[1][0] = ptr_Global->GetConst_Write_IDLE(0);
        flag_WriteState[1][1] = ptr_Global->GetConst_Write_IDLE(1);
        flag_WriteState[2][0] = ptr_Global->GetConst_Write_IDLE(0);
        flag_WriteState[2][1] = ptr_Global->GetConst_Write_IDLE(1);
        flag_WriteState[3][0] = ptr_Global->GetConst_Write_IDLE(0);
        flag_WriteState[3][1] = ptr_Global->GetConst_Write_IDLE(1);
        unsigned char ptr_new_coreId_For_WritePraise_Index = unsigned char(1);
        bool praisingWrite = bool(false);
        unsigned char ptr_que_CoreToWrite[4] = { unsigned char(0), unsigned char(1), unsigned char(2), unsigned char(3) };//NUMBER OF CORES
        for (unsigned char index=0; index < ptr_Global->Get_NumCores(); index++)
        {
            ptr_que_CoreToWrite[index] = index;
        }
    }

    WriteEnable_Stack_Server_OutputRecieve_Control::~WriteEnable_Stack_Server_OutputRecieve_Control()
    {

    }

    void WriteEnable_Stack_Server_OutputRecieve_Control::WriteEnable_Activate(
        unsigned char coreId,
        class WaitEnableWrite::WriteEnable_Stack_Server_OutputRecieve_Global* ptr_Global
    )
    {
        for (unsigned char index = 0; index < ptr_Global->Get_NumCores(); index++)
        {
            SetFlag_writeState(coreId, index, ptr_Global->GetConst_Write_WRITE(index));
        }
    }

    void WriteEnable_Stack_Server_OutputRecieve_Control::WriteEnable_SortQue(
        class WaitEnableWrite::WriteEnable_Stack_Server_OutputRecieve_Global* ptr_Global
    )
    {
        for (unsigned char index_A = 0; index_A < (ptr_Global->Get_NumCores() - 1); index_A++)
        {
            for (unsigned char index_B = (index_A + 1); index_B < ptr_Global->Get_NumCores(); index_B++)
            {
                if (GetFlag_writeState(Get_que_CoreToWrite(index_A), 0) == ptr_Global->GetConst_Write_WRITE(0)
                    && GetFlag_writeState(Get_que_CoreToWrite(index_A), 1) == ptr_Global->GetConst_Write_WRITE(1))
                {
                    if ((GetFlag_writeState(Get_que_CoreToWrite(index_B), 0) == ptr_Global->GetConst_Write_WAIT(0)
                        && GetFlag_writeState(Get_que_CoreToWrite(index_B), 1) == ptr_Global->GetConst_Write_WAIT(1))
                        || (GetFlag_writeState(Get_que_CoreToWrite(index_B), 0) == ptr_Global->GetConst_Write_IDLE(0)
                           && GetFlag_writeState(Get_que_CoreToWrite(index_B), 1) == ptr_Global->GetConst_Write_IDLE(1)))
                    {
                        WriteEnable_ShiftQueValues(index_A, index_B);
                    }
                    else if (GetFlag_writeState(Get_que_CoreToWrite(index_B), 0) == ptr_Global->GetConst_Write_WRITE(0)
                        && GetFlag_writeState(Get_que_CoreToWrite(index_B), 0) == ptr_Global->GetConst_Write_WRITE(1))
                    {
                        if (Get_count_WriteActive(index_A) > Get_count_WriteActive(index_B))
                        {
                            WriteEnable_ShiftQueValues(index_A, index_B);
                        }
                    }
                }
                else if (GetFlag_writeState(Get_que_CoreToWrite(index_A), 0) == ptr_Global->GetConst_Write_IDLE(0)
                    && GetFlag_writeState(Get_que_CoreToWrite(index_A), 1) == ptr_Global->GetConst_Write_IDLE(1))
                {
                    if (GetFlag_writeState(Get_que_CoreToWrite(index_B), 0) == ptr_Global->GetConst_Write_WAIT(0)
                        && GetFlag_writeState(Get_que_CoreToWrite(index_B), 1) == ptr_Global->GetConst_Write_WAIT(1))
                    {
                        WriteEnable_ShiftQueValues(index_A, index_B);
                    }
                    else if (GetFlag_writeState(Get_que_CoreToWrite(index_B), 0) == ptr_Global->GetConst_Write_IDLE(0)
                        && GetFlag_writeState(Get_que_CoreToWrite(index_B), 1) == ptr_Global->GetConst_Write_IDLE(1))
                    {
                        if (Get_count_WriteIdle(index_A) < Get_count_WriteIdle(index_B))
                        {
                            WriteEnable_ShiftQueValues(index_A, index_B);
                        }
                    }
                }
                else if (GetFlag_writeState(Get_que_CoreToWrite(index_A), 0) == ptr_Global->GetConst_Write_WAIT(0)
                    && GetFlag_writeState(Get_que_CoreToWrite(index_A), 1) == ptr_Global->GetConst_Write_WAIT(1))
                {
                    if (GetFlag_writeState(Get_que_CoreToWrite(index_B), 0) == ptr_Global->GetConst_Write_WAIT(0)
                        && GetFlag_writeState(Get_que_CoreToWrite(index_B), 1) == ptr_Global->GetConst_Write_WAIT(1))
                    {
                        if (Get_count_WriteWait(index_A) > Get_count_WriteWait(index_B))
                        {
                            WriteEnable_ShiftQueValues(index_A, index_B);
                        }
                    }
                }
            }
        }
    }

    void WriteEnable_Stack_Server_OutputRecieve_Control::WriteEnable_Request(
        unsigned char coreId,
        class WaitEnableWrite::WriteEnable_Stack_Server_OutputRecieve_Global* ptr_Global
    )
    {
        while (GetFlag_readWrite_Open() == true)
        {
            DynamicStagger(coreId);
        }
        SetFlag_readWrite_Open(true);
        Set_coreIdForWritePraiseIndex(Get_new_coreIdForWritePraiseIndex());
        if (Get_coreIdForWritePraiseIndex() == coreId)
        {
            for (unsigned char index = 0; index < 2; index++)
            {
                SetFlag_writeState(coreId, index, ptr_Global->GetConst_Write_WAIT(index));
            }
            // Function exit.
        }
        else
        {
            Set_new_coreIdForWritePraiseIndex(Get_coreIdForWritePraiseIndex() + 1);
            if (Get_new_coreIdForWritePraiseIndex() == ptr_Global->Get_NumCores())
            {
                Set_new_coreIdForWritePraiseIndex(0);
            }
            SetFlag_readWrite_Open(false);
            WriteEnable_Request(
                coreId,
                ptr_Global

            );
        }
    }

    void WriteEnable_Stack_Server_OutputRecieve_Control::WriteQue_Update(class WaitEnableWrite::WriteEnable_Stack_Server_OutputRecieve_Global* ptr_Global)
    {
        for (unsigned char index = 0; index < ptr_Global->Get_NumCores(); index++)
        {
            if (GetFlag_writeState(index, 0) == false)
            {
                if (GetFlag_writeState(index, 1) == false)
                {
                    Set_count_WriteActive(index, 0);
                    Set_count_WriteIdle(index, Get_count_WriteIdle(index) + 1);
                    Set_count_WriteWait(index, 0);
                }
                else if (GetFlag_writeState(index, 1) == true)
                {
                    Set_count_WriteActive(index, 0);
                    Set_count_WriteIdle(index, 0);
                    Set_count_WriteWait(index, Get_count_WriteWait(index) + 1);
                }
            }
            else if (GetFlag_writeState(index, 0) == true)
            {
                if (GetFlag_writeState(index, 1) == false)
                {
                    Set_count_WriteActive(index, Get_count_WriteActive(index) + 1);
                    Set_count_WriteIdle(index, 0);
                    Set_count_WriteWait(index, 0);
                }
            }
        }
    }

    unsigned char WriteEnable_Stack_Server_OutputRecieve_Control::Get_coreIdForWritePraiseIndex()
    {
        return coreId_For_WritePraise_Index;
    }
    int WriteEnable_Stack_Server_OutputRecieve_Control::Get_count_WriteActive(unsigned char coreId)
    {
        return ptr_count_CoreId_WriteActive[coreId];
    }
    int WriteEnable_Stack_Server_OutputRecieve_Control::Get_count_WriteIdle(unsigned char coreId)
    {
        return ptr_count_CoreId_WriteIdle[coreId];
    }
    int WriteEnable_Stack_Server_OutputRecieve_Control::Get_count_WriteWait(unsigned char coreId)
    {
        return ptr_count_CoreId_WriteWait[coreId];
    }
    unsigned char WriteEnable_Stack_Server_OutputRecieve_Control::GetFlag_CoreId_WriteEnable()
    {
        return ptr_que_CoreToWrite[0];
    }
    unsigned char WriteEnable_Stack_Server_OutputRecieve_Control::Get_new_coreIdForWritePraiseIndex()
    {
        return ptr_new_coreId_For_WritePraise_Index;
    }
    unsigned char WriteEnable_Stack_Server_OutputRecieve_Control::Get_que_CoreToWrite(unsigned char index)
    {
        return ptr_que_CoreToWrite[index];
    }

    void WriteEnable_Stack_Server_OutputRecieve_Control::Set_count_WriteActive(unsigned char coreId, int value)
    {
        ptr_count_CoreId_WriteActive[coreId] = value;
    }
    void WriteEnable_Stack_Server_OutputRecieve_Control::Set_count_WriteIdle(unsigned char coreId, int value)
    {
        ptr_count_CoreId_WriteIdle[coreId] = value;
    }
    void WriteEnable_Stack_Server_OutputRecieve_Control::Set_count_WriteWait(unsigned char coreId, int value)
    {
        ptr_count_CoreId_WriteWait[coreId] = value;
    }
    void WriteEnable_Stack_Server_OutputRecieve_Control::SetFlag_readWrite_Open(bool value)
    {
        praisingWrite = value;
    }
    void WriteEnable_Stack_Server_OutputRecieve_Control::SetFlag_writeState(unsigned char coreId, unsigned char index, bool value)
    {
        flag_WriteState[coreId][index] = value;
    }
    void WriteEnable_Stack_Server_OutputRecieve_Control::Set_new_coreIdForWritePraiseIndex(unsigned char value)
    {
        ptr_new_coreId_For_WritePraise_Index = value;
    }
    void WriteEnable_Stack_Server_OutputRecieve_Control::Set_que_CoreToWrite(unsigned char index, unsigned char value)
    {
        ptr_que_CoreToWrite[index] = value;
    }

    void WriteEnable_Stack_Server_OutputRecieve_Control::DynamicStagger(
        unsigned char coreId
    )
    {
        if (Get_coreIdForWritePraiseIndex() == coreId)
        {
            //exit early
        }
        else
        {
            int ptr_count = int(0);
            while (ptr_count < 20)//TODO record till flag change
            {
                ptr_count = ptr_count + 1;
            }
        }
    }

    void WriteEnable_Stack_Server_OutputRecieve_Control::WriteEnable_ShiftQueValues(
        unsigned char coreId_A,
        unsigned char coreId_B
    )
    {
        int temp_A = int(0);
        temp_A = Get_count_WriteActive(coreId_A);
        Set_count_WriteActive(coreId_A, Get_count_WriteActive(coreId_B));
        Set_count_WriteActive(coreId_B, temp_A);

        temp_A = Get_count_WriteIdle(coreId_A);
        Set_count_WriteIdle(coreId_A, Get_count_WriteIdle(coreId_B));
        Set_count_WriteIdle(coreId_B, temp_A);

        temp_A = Get_count_WriteWait(coreId_A);
        Set_count_WriteWait(coreId_A, Get_count_WriteWait(coreId_B));
        Set_count_WriteWait(coreId_B, temp_A);

        unsigned char temp_B = unsigned char(0);
        temp_B = Get_que_CoreToWrite(coreId_A);
        Set_que_CoreToWrite(coreId_A, Get_que_CoreToWrite(coreId_B));
        Set_que_CoreToWrite(coreId_B, temp_B);
    }

    bool WriteEnable_Stack_Server_OutputRecieve_Control::GetFlag_readWrite_Open()
    {
        return praisingWrite;
    }

    bool WriteEnable_Stack_Server_OutputRecieve_Control::GetFlag_writeState(unsigned char coreId, unsigned char index)
    {
        return flag_WriteState[coreId][index];
    }

    void WriteEnable_Stack_Server_OutputRecieve_Control::Set_coreIdForWritePraiseIndex(unsigned char value)
    {
        coreId_For_WritePraise_Index = value;
    }
}