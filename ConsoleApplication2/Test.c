/*
* C言語で三つのスレッド：１：基礎技術の確認（３）
*/
#include <Windows.h>
#include <process.h>
#include "../Dll1/Dialog.h"
#pragma comment(lib, "Dll1.lib")
struct Sample {
	HWND   hDlg      ;
	HANDLE hStopEvent;
	DWORD  nCount    ;
	HANDLE handles[3];
};
BOOL Sample_Sleep
( struct Sample* pThis
, _In_ DWORD     dwMilliseconds
)
{
	return WaitForSingleObject
	( /*_In_ HANDLE hHandle       */pThis->hStopEvent
	, /*_In_ DWORD  dwMilliseconds*/dwMilliseconds
	) == WAIT_TIMEOUT;
}
unsigned __stdcall Sample_ThreadProc_Alpha(void* pvThis)
{
#define	pThis	((struct Sample*)pvThis)
	for (;;) {
		if (Sample_Sleep(pThis, 100))
			Dll1_Dialog_Count_Alpha(pThis->hDlg);
		else
			break;
	}
#undef	pThis
	return 0;
}
unsigned __stdcall Sample_ThreadProc_Beta(void* pvThis)
{
#define	pThis	((struct Sample*)pvThis)
	for (;;) {
		if (Sample_Sleep(pThis, 300))
			Dll1_Dialog_Count_Beta(pThis->hDlg);
		else
			break;
	}
#undef	pThis
	return 0;
}
unsigned __stdcall Sample_ThreadProc_Gamma(void* pvThis)
{
#define	pThis	((struct Sample*)pvThis)
	for (;;) {
		if (Sample_Sleep(pThis, 500))
			Dll1_Dialog_Count_Gamma(pThis->hDlg);
		else
			break;
	}
#undef	pThis
	return 0;
}
void Sample_AddThread
( struct Sample* pThis
, _In_ _beginthreadex_proc_type _StartAddress
)
{
	if ((pThis->handles[pThis->nCount] = (HANDLE)_beginthreadex
		( /*_In_opt_  void*                    _Security    */NULL
		, /*_In_      unsigned                 _StackSize   */0
		, /*_In_      _beginthreadex_proc_type _StartAddress*/_StartAddress
		, /*_In_opt_  void*                    _ArgList     */pThis
		, /*_In_      unsigned                 _InitFlag    */0
		, /*_Out_opt_ unsigned*                _ThrdAddr    */NULL
		)
	) != NULL)
		++pThis->nCount;
}
void Sample_Start(struct Sample* pThis, HWND hDlg)
{
	/*HWND  */pThis->hDlg       = hDlg                ;
	/*HANDLE*/pThis->hStopEvent = CreateEventW
	( /*_In_opt_ LPSECURITY_ATTRIBUTES lpEventAttributes*/NULL 
	, /*_In_     BOOL                  bManualReset     */TRUE 
	, /*_In_     BOOL                  bInitialState    */FALSE
	, /*_In_opt_ LPCWSTR               lpName           */NULL 
	);
	/*DWORD */pThis->nCount     = 0;

	//三つのスレッドを作成
	Sample_AddThread(pThis, Sample_ThreadProc_Alpha);
	Sample_AddThread(pThis, Sample_ThreadProc_Beta );
	Sample_AddThread(pThis, Sample_ThreadProc_Gamma);
}
void Sample_Stop(struct Sample* pThis)
{
	(void)SetEvent(pThis->hStopEvent);
}
void Sample_End(struct Sample* pThis)
{
	if (pThis->nCount) {
		//nCount個のスレッド全てが終わるまで待つ
		(void)WaitForMultipleObjects
		( /*_In_               DWORD          nCount        */pThis->nCount           
		, /*_In_reads_(nCount) CONST HANDLE * lpHandles     */pThis->handles          
		, /*_In_               BOOL           bWaitAll      */TRUE            
		, /*_In_               DWORD          dwMilliseconds*/INFINITE         
		);
		HANDLE* pHandle = pThis->handles + pThis->nCount;
		do
			(void)CloseHandle(*--pHandle);
		while (pHandle > pThis->handles);
	}
	(void)CloseHandle(pThis->hStopEvent);
}
int main()
{
	struct Sample d;
	Dll1_Dialog_Show
	( /*HWND      hWndParent                */NULL
	, /*void    (*pfnStart  )(void* pClient)*/Sample_Start
	, /*void    (*pfnStop   )(void* pClient)*/Sample_Stop
	, /*void    (*pfnEnd    )(void* pClient)*/Sample_End
	, /*void     *pClient                   */&d
	);
}
