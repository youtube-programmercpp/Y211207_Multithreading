#pragma once
#ifdef __cplusplus
extern "C" {
#endif
void __stdcall Dll1_Dialog_Count_Alpha(HWND hDlg);
void __stdcall Dll1_Dialog_Count_Beta (HWND hDlg);
void __stdcall Dll1_Dialog_Count_Gamma(HWND hDlg);
INT_PTR Dll1_Dialog_Show
( HWND      hWndParent                           
, void    (*pfnStart  )(void* pClient, HWND hDlg)
, void    (*pfnStop   )(void* pClient           )
, void    (*pfnEnd    )(void* pClient           )
, void*     pClient                              
);
#ifdef __cplusplus
}
#endif
