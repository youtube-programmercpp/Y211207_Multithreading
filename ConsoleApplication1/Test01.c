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
	//�O�̃X���b�h�S�Ă��I���܂ő҂�
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
