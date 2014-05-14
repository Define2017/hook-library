#include <stdio.h>
#include <windows.h>
#include "..\src\hook.h"

/**********************************************************************
 In this example, we'll hook the MessageBoxW function, declared as:
	int WINAPI MessageBoxW(
	  _In_opt_  HWND hWnd,
	  _In_opt_  LPCWSTR lpText,
	  _In_opt_  LPCWSTR lpCaption,
	  _In_      UINT uType
	);

**********************************************************************/

// Declare the hooks
HOOK_DECLARE(
	MyMessageBox, // The hook name (this can be anything you want)
	int,          // The return type of the hooked function
	WINAPI,       // The calling convention of the hooked function (WINAPI = stdcall)
	(HWND, LPCWSTR, LPCWSTR, UINT) // The hooked function parameters
);


BOOL WINAPI WinMain (HINSTANCE hInstance, HINSTANCE hPrevInst, char * szCmdLine, int iShow) {
	// Show the message box
	MessageBoxW(NULL, L"I have a dog named Foobar!", L"hook_example", MB_OK);

	// Install the hook
	HOOK_INSTALL(
		MyMessageBox, // Hook name
		"User32.dll", // Hooked library name
		"MessageBoxW" // Hooked function name
	);

	// Show the message box again (something different should happen now)
	MessageBoxW(NULL, L"I have a dog named Foobar!", L"hook_example", MB_OK);

	// Uninstall the hook
	HOOK_UNINSTALL(MyMessageBox);

	// Show the message box for the last time (it should be back to normal)
	MessageBoxW(NULL, L"I have a dog named Foobar!", L"hook_example", MB_OK);

	return FALSE;
}


// This is the stub function
HOOK_STUB_FUNCTION(
		MyMessageBox, // Hook name
		int,          // Return type (these must be the same as the hooked function)
		WINAPI,       // Calling convention
	  (HWND hWnd, LPCWSTR lpText, LPCWSTR lpCaption, UINT uType) // Parameters
) {
	char szText[1024];
	
	// Call the original function using a different title for the message box
	return HOOK_HOP(MyMessageBox)(hWnd, lpText, L"This call was hijacked!", uType);
}
