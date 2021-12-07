#include <Windows.h>
#include <process.h>
#include <assert.h>
//実験用スレッド関数：意味のある動きは無し
unsigned __stdcall ThreadProc(void* p)
{
	p;//「warning C4100: 'p': 引数は関数の本体部で 1 度も参照されません。」対策の C 言語版
	return 0;
}
int main()
{
	//三つのスレッドを作成
	const HANDLE handles[] =
	{ (HANDLE)_beginthreadex
		( /*_In_opt_  void*                    _Security    */NULL
		, /*_In_      unsigned                 _StackSize   */0
		, /*_In_      _beginthreadex_proc_type _StartAddress*/ThreadProc
		, /*_In_opt_  void*                    _ArgList     */NULL
		, /*_In_      unsigned                 _InitFlag    */0
		, /*_Out_opt_ unsigned*                _ThrdAddr    */NULL
		)
	, (HANDLE)_beginthreadex
		( /*_In_opt_  void*                    _Security    */NULL
		, /*_In_      unsigned                 _StackSize   */0
		, /*_In_      _beginthreadex_proc_type _StartAddress*/ThreadProc
		, /*_In_opt_  void*                    _ArgList     */NULL
		, /*_In_      unsigned                 _InitFlag    */0
		, /*_Out_opt_ unsigned*                _ThrdAddr    */NULL
		)
	, (HANDLE)_beginthreadex
		( /*_In_opt_  void*                    _Security    */NULL
		, /*_In_      unsigned                 _StackSize   */0
		, /*_In_      _beginthreadex_proc_type _StartAddress*/ThreadProc
		, /*_In_opt_  void*                    _ArgList     */NULL
		, /*_In_      unsigned                 _InitFlag    */0
		, /*_Out_opt_ unsigned*                _ThrdAddr    */NULL
		)
	};
	assert(handles[0]);
	assert(handles[1]);
	assert(handles[2]);
	//三つのスレッド全てが終わるまで待つ
	const DWORD dwResult = WaitForMultipleObjects
	( /*_In_               DWORD          nCount        */_countof(handles)
	, /*_In_reads_(nCount) CONST HANDLE * lpHandles     */handles          
	, /*_In_               BOOL           bWaitAll      */TRUE            
	, /*_In_               DWORD          dwMilliseconds*/INFINITE         
	);
	assert(WAIT_OBJECT_0 <= dwResult && dwResult < WAIT_OBJECT_0 + _countof(handles));
	(void)CloseHandle(handles[2]);
	(void)CloseHandle(handles[1]);
	(void)CloseHandle(handles[0]);
}
