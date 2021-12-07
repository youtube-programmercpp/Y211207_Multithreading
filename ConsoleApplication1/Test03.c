#include <Windows.h>
#include <process.h>
//実験用スレッド関数：意味のある動きは無し
unsigned __stdcall ThreadProc(void* p)
{
	p;//「warning C4100: 'p': 引数は関数の本体部で 1 度も参照されません。」対策の C 言語版
	return 0;
}
int main()
{
	//三つのスレッドを作成
	HANDLE handles[3];
	HANDLE* pHandle = handles;
	if ((*pHandle = (HANDLE)_beginthreadex
		( /*_In_opt_  void*                    _Security    */NULL
		, /*_In_      unsigned                 _StackSize   */0
		, /*_In_      _beginthreadex_proc_type _StartAddress*/ThreadProc
		, /*_In_opt_  void*                    _ArgList     */NULL
		, /*_In_      unsigned                 _InitFlag    */0
		, /*_Out_opt_ unsigned*                _ThrdAddr    */NULL
		)) != NULL)
		++pHandle;
	if ((*pHandle = (HANDLE)_beginthreadex
		( /*_In_opt_  void*                    _Security    */NULL
		, /*_In_      unsigned                 _StackSize   */0
		, /*_In_      _beginthreadex_proc_type _StartAddress*/ThreadProc
		, /*_In_opt_  void*                    _ArgList     */NULL
		, /*_In_      unsigned                 _InitFlag    */0
		, /*_Out_opt_ unsigned*                _ThrdAddr    */NULL
		)) != NULL)
		++pHandle;
	if ((*pHandle = (HANDLE)_beginthreadex
		( /*_In_opt_  void*                    _Security    */NULL
		, /*_In_      unsigned                 _StackSize   */0
		, /*_In_      _beginthreadex_proc_type _StartAddress*/ThreadProc
		, /*_In_opt_  void*                    _ArgList     */NULL
		, /*_In_      unsigned                 _InitFlag    */0
		, /*_Out_opt_ unsigned*                _ThrdAddr    */NULL
		)) != NULL)
		++pHandle;
	const DWORD nCount = (DWORD)(pHandle - handles);
	if (nCount) {
		//nCount個のスレッド全てが終わるまで待つ
		(void)WaitForMultipleObjects
		( /*_In_               DWORD          nCount        */nCount           
		, /*_In_reads_(nCount) CONST HANDLE * lpHandles     */handles          
		, /*_In_               BOOL           bWaitAll      */TRUE            
		, /*_In_               DWORD          dwMilliseconds*/INFINITE         
		);
		do
			(void)CloseHandle(*--pHandle);
		while (pHandle > handles);
	}
}
