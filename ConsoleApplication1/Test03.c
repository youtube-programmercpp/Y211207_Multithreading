#include <Windows.h>
#include <process.h>
//�����p�X���b�h�֐��F�Ӗ��̂��铮���͖���
unsigned __stdcall ThreadProc(void* p)
{
	p;//�uwarning C4100: 'p': �����͊֐��̖{�̕��� 1 �x���Q�Ƃ���܂���B�v�΍�� C �����
	return 0;
}
int main()
{
	//�O�̃X���b�h���쐬
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
		//nCount�̃X���b�h�S�Ă��I���܂ő҂�
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
