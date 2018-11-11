/**
 *  file    Main.c
 *  date    2009/01/02
 *  author  kkamagui 
 *          Copyright(c)2008 All rights reserved by kkamagui
 *  brief   C ���� �ۼ��� Ŀ���� ��Ʈ�� ����Ʈ ����
 */

#include "Types.h"
#include "Keyboard.h"
#include "Descriptor.h"
#include "PIC.h"
#include "Console.h"
#include "ConsoleShell.h"
#include "Task.h"
#include "PIT.h"
#include "DynamicMemory.h"
#include "HardDisk.h"
#include "FileSystem.h"
#include "SerialPort.h"
#include "MultiProcessor.h"
#include "VBE.h"

// Application Processor�� ���� Main �Լ�
void MainForApplicationProcessor( void );
// �׷��� ��带 �׽�Ʈ�ϴ� �Լ�
void kStartGraphicModeTest();

/**
 *  Bootstrap Processor�� C ��� Ŀ�� ��Ʈ�� ����Ʈ
 *      �Ʒ� �Լ��� C ��� Ŀ���� ���� �κ���
 */
void Main( void )
{
    int iCursorX, iCursorY;
    
    // ��Ʈ �δ��� �ִ� BSP �÷��׸� �о Application Processor�̸� 
    // �ش� �ھ�� �ʱ�ȭ �Լ��� �̵�
    if( *( ( BYTE* ) BOOTSTRAPPROCESSOR_FLAGADDRESS ) == 0 )
    {
        MainForApplicationProcessor();
    }
    
    // Bootstrap Processor�� ������ �Ϸ������Ƿ�, 0x7C09�� �ִ� Bootstrap Processor��
    // ��Ÿ���� �÷��׸� 0���� �����Ͽ� Application Processor������ �ڵ� ���� ��θ� ����
    *( ( BYTE* ) BOOTSTRAPPROCESSOR_FLAGADDRESS ) = 0;

    // �ܼ��� ���� �ʱ�ȭ�� ��, ���� �۾��� ����
    kInitializeConsole( 0, 10 );    
    kPrintf( "Switch To IA-32e Mode Success~!!\n" );
    kPrintf( "IA-32e C Language Kernel Start..............[Pass]\n" );
    kPrintf( "Initialize Console..........................[Pass]\n" );
    
    // ���� ��Ȳ�� ȭ�鿡 ���
    kGetCursor( &iCursorX, &iCursorY );
    kPrintf( "GDT Initialize And Switch For IA-32e Mode...[    ]" );
    kInitializeGDTTableAndTSS();
    kLoadGDTR( GDTR_STARTADDRESS );
    kSetCursor( 45, iCursorY++ );
    kPrintf( "Pass\n" );
    
    kPrintf( "TSS Segment Load............................[    ]" );
    kLoadTR( GDT_TSSSEGMENT );
    kSetCursor( 45, iCursorY++ );
    kPrintf( "Pass\n" );
    
    kPrintf( "IDT Initialize..............................[    ]" );
    kInitializeIDTTables();    
    kLoadIDTR( IDTR_STARTADDRESS );
    kSetCursor( 45, iCursorY++ );
    kPrintf( "Pass\n" );
    
    kPrintf( "Total RAM Size Check........................[    ]" );
    kCheckTotalRAMSize();
    kSetCursor( 45, iCursorY++ );
    kPrintf( "Pass], Size = %d MB\n", kGetTotalRAMSize() );
    
    kPrintf( "TCB Pool And Scheduler Initialize...........[Pass]\n" );
    iCursorY++;
    kInitializeScheduler();
    
    // ���� �޸� �ʱ�ȭ
    kPrintf( "Dynamic Memory Initialize...................[Pass]\n" );
    iCursorY++;
    kInitializeDynamicMemory();
    
    // 1ms�� �ѹ��� ���ͷ�Ʈ�� �߻��ϵ��� ����
    kInitializePIT( MSTOCOUNT( 1 ), 1 );
    
    kPrintf( "Keyboard Activate And Queue Initialize......[    ]" );
    // Ű���带 Ȱ��ȭ
    if( kInitializeKeyboard() == TRUE )
    {
        kSetCursor( 45, iCursorY++ );
        kPrintf( "Pass\n" );
        kChangeKeyboardLED( FALSE, FALSE, FALSE );
    }
    else
    {
        kSetCursor( 45, iCursorY++ );
        kPrintf( "Fail\n" );
        while( 1 ) ;
    }
    
    kPrintf( "PIC Controller And Interrupt Initialize.....[    ]" );
    // PIC ��Ʈ�ѷ� �ʱ�ȭ �� ��� ���ͷ�Ʈ Ȱ��ȭ
    kInitializePIC();
    kMaskPICInterrupt( 0 );
    kEnableInterrupt();
    kSetCursor( 45, iCursorY++ );
    kPrintf( "Pass\n" );
    
    // ���� �ý����� �ʱ�ȭ
    kPrintf( "File System Initialize......................[    ]" );
    if( kInitializeFileSystem() == TRUE )
    {
        kSetCursor( 45, iCursorY++ );
        kPrintf( "Pass\n" );
    }
    else
    {
        kSetCursor( 45, iCursorY++ );
        kPrintf( "Fail\n" );
    }

    // �ø��� ��Ʈ�� �ʱ�ȭ    
    kPrintf( "Serial Port Initialize......................[Pass]\n" );
    iCursorY++;
    kInitializeSerialPort();

    // ���� �½�ũ�� �ý��� ������� �����ϰ� ���� ����
    kCreateTask( TASK_FLAGS_LOWEST | TASK_FLAGS_THREAD | TASK_FLAGS_SYSTEM | TASK_FLAGS_IDLE, 0, 0, 
            ( QWORD ) kIdleTask, kGetAPICID() );

    // �׷��� ��尡 �ƴϸ� �ܼ� �� ����
    if( *( BYTE* ) VBE_STARTGRAPHICMODEFLAGADDRESS == 0 )
    {
        kStartConsoleShell();
    }
    // �׷��� ����̸� �׷��� ��� �׽�Ʈ �Լ� ����
    else
    {
        kStartGraphicModeTest();
    }
}

/**
 *  Application Processor�� C ��� Ŀ�� ��Ʈ�� ����Ʈ
 *      ��κ��� �ڷᱸ���� Bootstrap Processor�� ������ �������Ƿ� �ھ �����ϴ�
 *      �۾��� ��
 */
void MainForApplicationProcessor( void )
{
    QWORD qwTickCount;

    // GDT ���̺��� ����
    kLoadGDTR( GDTR_STARTADDRESS );

    // TSS ��ũ���͸� ����. TSS ���׸�Ʈ�� ��ũ���͸� Application Processor�� 
    // ����ŭ ���������Ƿ�, APIC ID�� �̿��Ͽ� TSS ��ũ���͸� �Ҵ�
    kLoadTR( GDT_TSSSEGMENT + ( kGetAPICID() * sizeof( GDTENTRY16 ) ) );

    // IDT ���̺��� ����
    kLoadIDTR( IDTR_STARTADDRESS );
    
    // �����ٷ� �ʱ�ȭ
    kInitializeScheduler();
    
    // ���� �ھ��� ���� APIC�� Ȱ��ȭ
    kEnableSoftwareLocalAPIC();

    // ��� ���ͷ�Ʈ�� ������ �� �ֵ��� �½�ũ �켱 ���� �������͸� 0���� ����
    kSetTaskPriority( 0 );

    // ���� APIC�� ���� ���� ���̺��� �ʱ�ȭ
    kInitializeLocalVectorTable();

    // ���ͷ�Ʈ�� Ȱ��ȭ
    kEnableInterrupt();    

    // ��Ī I/O ��� �׽�Ʈ�� ���� Application Processor�� ������ �� �ѹ��� ���
    kPrintf( "Application Processor[APIC ID: %d] Is Activated\n",
            kGetAPICID() );

    // ���� �½�ũ ����
    kIdleTask();
}

/**
 *  �׷��� ��带 �׽�Ʈ�ϴ� �Լ�
 */
void kStartGraphicModeTest()
{
    VBEMODEINFOBLOCK* pstVBEMode;
    WORD* pwFrameBufferAddress;
    WORD wColor = 0;
    int iBandHeight;
    int i;
    int j;

    // Ű �Է��� ���
    kGetCh();
    
    // VBE ��� ���� ������ ��ȯ�ϰ� ���� ������ ������ ���� ��巹���� ����
    pstVBEMode = kGetVBEModeInfoBlock();
    pwFrameBufferAddress = ( WORD* ) ( ( QWORD ) pstVBEMode->dwPhysicalBasePointer );
   
    // ȭ���� ���η� 32 ����Ͽ� ���� ĥ��
    iBandHeight = pstVBEMode->wYResolution / 32;
    while( 1 )
    {
        for( j = 0 ; j < pstVBEMode->wYResolution ; j++ )
        {
            // X ���� ũ�⸸ŭ ������ ���ۿ� ���� ����
            for( i = 0 ; i < pstVBEMode->wXResolution ; i++ )
            {
                // ���� �޸� �������� ����ϴ� �κ�
                // Y ���� ���� ��ġ(j)�� X ���� ũ�⸦ ���ϸ� Y ���� ���� ��巹����
                // ����� �� �ְ�, ���⿡ X ���� ������(i)�� ���ϸ� ���� �ȼ��� �����
                // ��巹���� ���� �� ����
                pwFrameBufferAddress[ ( j * pstVBEMode->wXResolution ) + i ] = 
                    wColor;
            }

            // Y ��ġ�� 32 ����� ������ ������ �������� ���� �ٲ�
            if( ( j % iBandHeight ) == 0 )
            {
                wColor = kRandom() & 0xFFFF;
            }
        }
        // Ű �Է��� ���
        kGetCh();
    }
}