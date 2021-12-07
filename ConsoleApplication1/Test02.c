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
	const HANDLE hThread1 = (HANDLE)_beginthreadex
		( /*_In_opt_  void*                    _Security    */NULL
		, /*_In_      unsigned                 _StackSize   */0
		, /*_In_      _beginthreadex_proc_type _StartAddress*/ThreadProc
		, /*_In_opt_  void*                    _ArgList     */NULL
		, /*_In_      unsigned                 _InitFlag    */0
		, /*_Out_opt_ unsigned*                _ThrdAddr    */NULL
		);
	const HANDLE hThread2 = (HANDLE)_beginthreadex
		( /*_In_opt_  void*                    _Security    */NULL
		, /*_In_      unsigned                 _StackSize   */0
		, /*_In_      _beginthreadex_proc_type _StartAddress*/ThreadProc
		, /*_In_opt_  void*                    _ArgList     */NULL
		, /*_In_      unsigned                 _InitFlag    */0
		, /*_Out_opt_ unsigned*                _ThrdAddr    */NULL
		);
	const HANDLE hThread3 = (HANDLE)_beginthreadex
		( /*_In_opt_  void*                    _Security    */NULL
		, /*_In_      unsigned                 _StackSize   */0
		, /*_In_      _beginthreadex_proc_type _StartAddress*/ThreadProc
		, /*_In_opt_  void*                    _ArgList     */NULL
		, /*_In_      unsigned                 _InitFlag    */0
		, /*_Out_opt_ unsigned*                _ThrdAddr    */NULL
		);
	if (hThread1) {
		if (hThread2) {
			if (hThread3) {
				const HANDLE handles[] = { hThread1, hThread2, hThread3 };
				//三つのスレッド全てが終わるまで待つ
				(void)WaitForMultipleObjects
				( /*_In_               DWORD          nCount        */_countof(handles)
				, /*_In_reads_(nCount) CONST HANDLE * lpHandles     */handles          
				, /*_In_               BOOL           bWaitAll      */TRUE            
				, /*_In_               DWORD          dwMilliseconds*/INFINITE         
				);
				(void)CloseHandle(hThread3);
				(void)CloseHandle(hThread2);
				(void)CloseHandle(hThread1);
			}
			else {
				const HANDLE handles[] = { hThread1, hThread2 };
				//二つのスレッド双方が終わるまで待つ
				(void)WaitForMultipleObjects
				( /*_In_               DWORD          nCount        */_countof(handles)
				, /*_In_reads_(nCount) CONST HANDLE * lpHandles     */handles          
				, /*_In_               BOOL           bWaitAll      */TRUE            
				, /*_In_               DWORD          dwMilliseconds*/INFINITE         
				);
				(void)CloseHandle(hThread2);
				(void)CloseHandle(hThread1);
			}
		}
		else {
			if (hThread3) {
				const HANDLE handles[] = { hThread1, hThread3 };
				//二つのスレッド双方が終わるまで待つ
				(void)WaitForMultipleObjects
				( /*_In_               DWORD          nCount        */_countof(handles)
				, /*_In_reads_(nCount) CONST HANDLE * lpHandles     */handles          
				, /*_In_               BOOL           bWaitAll      */TRUE            
				, /*_In_               DWORD          dwMilliseconds*/INFINITE         
				);
				(void)CloseHandle(hThread3);
				(void)CloseHandle(hThread1);
			}
			else {
				//一つのスレッドが終わるまで待つ
				(void)WaitForSingleObject
				( /*_In_ HANDLE hHandle       */hThread1
				, /*_In_ DWORD  dwMilliseconds*/INFINITE
				);
				(void)CloseHandle(hThread1);
			}
		}
	}
	else {
		if (hThread2) {
			if (hThread3) {
				const HANDLE handles[] = { hThread2, hThread3 };
				//二つのスレッド双方が終わるまで待つ
				(void)WaitForMultipleObjects
				( /*_In_               DWORD          nCount        */_countof(handles)
				, /*_In_reads_(nCount) CONST HANDLE * lpHandles     */handles          
				, /*_In_               BOOL           bWaitAll      */TRUE            
				, /*_In_               DWORD          dwMilliseconds*/INFINITE         
				);
				(void)CloseHandle(hThread3);
				(void)CloseHandle(hThread2);
			}
			else {
				//一つのスレッドが終わるまで待つ
				(void)WaitForSingleObject
				( /*_In_ HANDLE hHandle       */hThread2
				, /*_In_ DWORD  dwMilliseconds*/INFINITE
				);
				(void)CloseHandle(hThread2);
			}
		}
		else {
			if (hThread3) {
				//一つのスレッドが終わるまで待つ
				(void)WaitForSingleObject
				( /*_In_ HANDLE hHandle       */hThread3
				, /*_In_ DWORD  dwMilliseconds*/INFINITE
				);
				(void)CloseHandle(hThread3);
			}
			else {
				//スレッド生成試行は全て失敗している
			}
		}
	}
}
