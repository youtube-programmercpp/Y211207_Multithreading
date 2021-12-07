#include <Windows.h>
#include <process.h>
#include <assert.h>
//�����p�X���b�h�֐��F�Ӗ��̂��铮���͖���
unsigned __stdcall ThreadProc(void* p)
{
	p;//�uwarning C4100: 'p': �����͊֐��̖{�̕��� 1 �x���Q�Ƃ���܂���B�v�΍�� C �����
	return 0;
}
int main()
{
	//�O�̃X���b�h���쐬
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
				//�O�̃X���b�h�S�Ă��I���܂ő҂�
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
				//��̃X���b�h�o�����I���܂ő҂�
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
				//��̃X���b�h�o�����I���܂ő҂�
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
				//��̃X���b�h���I���܂ő҂�
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
				//��̃X���b�h�o�����I���܂ő҂�
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
				//��̃X���b�h���I���܂ő҂�
				(void)WaitForSingleObject
				( /*_In_ HANDLE hHandle       */hThread2
				, /*_In_ DWORD  dwMilliseconds*/INFINITE
				);
				(void)CloseHandle(hThread2);
			}
		}
		else {
			if (hThread3) {
				//��̃X���b�h���I���܂ő҂�
				(void)WaitForSingleObject
				( /*_In_ HANDLE hHandle       */hThread3
				, /*_In_ DWORD  dwMilliseconds*/INFINITE
				);
				(void)CloseHandle(hThread3);
			}
			else {
				//�X���b�h�������s�͑S�Ď��s���Ă���
			}
		}
	}
}
