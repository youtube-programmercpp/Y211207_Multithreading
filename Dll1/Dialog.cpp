#include "pch.h"
#include "Dialog.h"
#include <Windows.h>
#include <process.h>
#include "resource.h"
#include "Dialog.h"
namespace Win32Wrap {
	template<class T>INT_PTR DialogBoxParamW
	( _In_opt_ HINSTANCE hInstance     
	, _In_     LPCWSTR   lpTemplateName
	, _In_opt_ HWND      hWndParent    
	,          const T&  lpDialogFunc  
	)
	{
		return ::DialogBoxParamW
		( /*_In_opt_ HINSTANCE hInstance     */hInstance     
		, /*_In_     LPCWSTR   lpTemplateName*/lpTemplateName
		, /*_In_opt_ HWND      hWndParent    */hWndParent    
		, /*_In_opt_ DLGPROC   lpDialogFunc  */[](HWND hDlg, UINT uMsg, WPARAM wParam, LPARAM lParam)->INT_PTR
			{
				if (uMsg == WM_INITDIALOG)
					SetWindowLongPtr(hDlg, DWLP_USER, lParam);
				return (*reinterpret_cast<const T*>(GetWindowLongPtr(hDlg, DWLP_USER)))
				( /*HWND  */hDlg
				, /*UINT  */uMsg
				, /*WPARAM*/wParam
				, /*LPARAM*/lParam
				);
			}
		, /*_In_     LPARAM    dwInitParam   */LPARAM(&lpDialogFunc)
		);
	}
}
static void IncDlgItemInt
( _In_ HWND hDlg
, _In_ int  nIDDlgItem
, _In_ BOOL bSigned
)
{
	SetDlgItemInt(hDlg, nIDDlgItem, GetDlgItemInt(hDlg, nIDDlgItem, nullptr, bSigned) + 1, 0);
}
extern "C" void __stdcall Dll1_Dialog_Count_Alpha(HWND hDlg) { IncDlgItemInt(hDlg, IDC_STATIC_Thread_Alpha, false); }
extern "C" void __stdcall Dll1_Dialog_Count_Beta (HWND hDlg) { IncDlgItemInt(hDlg, IDC_STATIC_Thread_Beta , false); }
extern "C" void __stdcall Dll1_Dialog_Count_Gamma(HWND hDlg) { IncDlgItemInt(hDlg, IDC_STATIC_Thread_Gamma, false); }
extern "C" IMAGE_DOS_HEADER __ImageBase;
extern "C" INT_PTR Dll1_Dialog_Show
( HWND      hWndParent                           
, void    (*pfnStart  )(void* pClient, HWND hDlg)
, void    (*pfnStop   )(void* pClient           )
, void    (*pfnEnd    )(void* pClient           )
, void*     pClient                              
)
{
	return Win32Wrap::DialogBoxParamW
	( /*_In_opt_ HINSTANCE hInstance     */HINSTANCE(&__ImageBase)
	, /*_In_     LPCWSTR   lpTemplateName*/MAKEINTRESOURCEW(IDD_DIALOG1)
	, /*_In_opt_ HWND      hWndParent    */hWndParent
	, /*_In_opt_ DLGPROC   lpDialogFunc  */[pfnStart, pfnStop, pfnEnd, pClient](HWND hDlg, UINT uMsg, WPARAM wParam, LPARAM lParam)->INT_PTR
		{
			lParam;
			switch (uMsg) {
			case WM_COMMAND:
				switch (LOWORD(wParam)) {
				case IDCANCEL:
					(*pfnStop)(pClient);
					EndDialog(hDlg, IDCANCEL);
					return true;
				default:
					return false;
				}
			case WM_NCDESTROY:
				(*pfnEnd)(pClient);
				return false;
			case WM_INITDIALOG:
				(*pfnStart)(pClient, hDlg);
				return true;
			default:
				return false;
			}
		}
	);
}
