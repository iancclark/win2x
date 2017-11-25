/*@@ Wedit generated application. Written Sat Mar 30 13:53:34 2002
 @@header: c:\lcc\projects\win2x\win2xres.h
 @@resources: c:\lcc\projects\win2x\win2x.rc
 Do not edit outside the indicated areas */
/*<---------------------------------------------------------------------->*/
/*<---------------------------------------------------------------------->*/
#include <windows.h>
#include <windowsx.h>
#include <commctrl.h>
#include <string.h>
#include <winsock2.h>

#include <X11/Xlib.h>
#include <X11/Xresource.h>
#include <X11/Xutil.h>
#include <X11/cursorfont.h>
#include <X11/Xatom.h>
#include <X11/extensions/XTest.h>

#include "win2xres.h"
/*<---------------------------------------------------------------------->*/
HINSTANCE hInst;		// Instance handle
HWND hwndMain;		//Main window handle

BOOL exploded;
Display *xdisp;
int x_xres,x_yres;
int win_xres,win_yres;



WSADATA *WsaData;
LRESULT CALLBACK MainWndProc(HWND hwnd,UINT msg,WPARAM wParam,LPARAM lParam);

/*<---------------------------------------------------------------------->*/
/*@@0->@@*/
static BOOL InitApplication(void)
{
	WNDCLASS wc;

	memset(&wc,0,sizeof(WNDCLASS));
	wc.style = CS_BYTEALIGNCLIENT ;
	wc.lpfnWndProc = (WNDPROC)MainWndProc;
	wc.hInstance = hInst;
	wc.hbrBackground = (HBRUSH)(COLOR_WINDOW+1);
	wc.lpszClassName = "win2xWndClass";
	wc.lpszMenuName = MAKEINTRESOURCE(IDMAINMENU);
	wc.hCursor = LoadCursor(NULL,IDC_ARROW);
	wc.hIcon = LoadIcon(NULL,IDI_APPLICATION);
	if (!RegisterClass(&wc))
		return 0;
/*@@0<-@@*/
	// ---TODO--- Call module specific initialization routines here

	return 1;
}

/*<---------------------------------------------------------------------->*/
/*@@1->@@*/
HWND Createwin2xWndClassWnd(void)
{
	return CreateWindowEx(WS_EX_TRANSPARENT,
		"win2xWndClass","win2x",
		WS_POPUP,
		CW_USEDEFAULT,0,CW_USEDEFAULT,0,
		NULL,
		NULL,
		hInst,
		NULL);
}
/*@@1<-@@*/
/*<---------------------------------------------------------------------->*/
/* --- The following code comes from c:\lcc\lib\wizard\defOnCmd.tpl. */
void MainWndProc_OnCommand(HWND hwnd, int id, HWND hwndCtl, UINT codeNotify)
{
	switch(id) {
		// ---TODO--- Add new menu commands here
		/*@@NEWCOMMANDS@@*/
		case IDM_EXIT:
		PostMessage(hwnd,WM_CLOSE,0,0);
		break;
	}
}

/*<---------------------------------------------------------------------->*/
/*@@2->@@*/
LRESULT CALLBACK MainWndProc(HWND hwnd,UINT msg,WPARAM wParam,LPARAM lParam)
{
	char cow[128]; // TODO Remove this

	switch (msg) {
/*@@3->@@*/
	case WM_COMMAND:
		HANDLE_WM_COMMAND(hwnd,wParam,lParam,MainWndProc_OnCommand);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	case WM_DISPLAYCHANGE:
		/* Screen size may have changed
		 * wParam: BPP
		 * lParam: lowword:  x-res
		 *         highword: y-res */
		MessageBox(hwnd,"Don't handle resizing screens yet!", "Warning", MB_OK | MB_ICONWARNING);
		break;
	case WM_MOUSEMOVE:
		/* Mouse moving
		 * wParam: MK_CONTROL | MK_LBUTTON | MK_MBUTTON | MK_RBUTTON | MK_SHIFT
		 * lParam: lowword:  x
		 *         highword: y */
		XWarpPointer(xdisp,None,DefaultRootWindow(xdisp),0,0,0,0,LOWORD(lParam),HIWORD(lParam));
		XFlush(xdisp);
		if(exploded) {
			if(LOWORD(lParam) > (win_xres-4)) {
				// at right edge, unexplode
				SetWindowPos(hwndMain,HWND_TOPMOST,0,0,1,win_yres,0);
				SetCursorPos(5,HIWORD(lParam));
				exploded=FALSE;
			}
		} else {
			if(LOWORD(lParam) < 2) {
				// at left edge, explode
				SetFocus(hwndMain);
				SetWindowPos(hwndMain,HWND_TOPMOST,0,0,win_xres,win_yres,0);
				SetCursorPos(1020,HIWORD(lParam));
				exploded=TRUE;
			}
		}
		break;
	case WM_MOUSEWHEEL:
		/* Mousewheel
		 * wParam: lowword:  MK_CONTROL | MK_LBUTTON | MK_MBUTTON | MK_RBUTTON | MK_SHIFT
		 *         highword: delta z
		 * lParam: lowword:  x
		 * lParam: highword: y */
	case WM_MBUTTONUP:
		/* Middle Button UP
		 * wParam: lowword:  MK_CONTROL | MK_LBUTTON | MK_RBUTTON | MK_SHIFT
		 *         highword: delta z
		 * lParam: lowword:  x
		 * lParam: highword: y */
		XTestFakeButtonEvent(xdisp,2,False,0);
		XFlush(xdisp);
		break;
	case WM_MBUTTONDOWN:
		/* Middle Button DOWN
		 * wParam: lowword:  MK_CONTROL | MK_LBUTTON | MK_RBUTTON | MK_SHIFT
		 *         highword: delta z
		 * lParam: lowword:  x
		 * lParam: highword: y */
		XTestFakeButtonEvent(xdisp,2,True,0);
		XFlush(xdisp);
		break;
	case WM_LBUTTONUP:
		/* Left Button UP
		 * wParam: lowword:  MK_CONTROL | MK_MBUTTON | MK_RBUTTON | MK_SHIFT
		 *         highword: delta z
		 * lParam: lowword:  x
		 * lParam: highword: y */
		XTestFakeButtonEvent(xdisp,1,False,0);
		XFlush(xdisp);
		break;
	case WM_LBUTTONDOWN:
		/* Left Button DOWN
		 * wParam: lowword:  MK_CONTROL | MK_MBUTTON | MK_RBUTTON | MK_SHIFT
		 *         highword: delta z
		 * lParam: lowword:  x
		 * lParam: highword: y */
		XTestFakeButtonEvent(xdisp,1,True,0);
		XFlush(xdisp);
		break;
	case WM_RBUTTONUP:
		/* Right Button UP
		 * wParam: lowword:  MK_CONTROL | MK_LBUTTON | MK_MBUTTON | MK_SHIFT
		 *         highword: delta z
		 * lParam: lowword:  x
		 * lParam: highword: y */
		XTestFakeButtonEvent(xdisp,3,False,0);
		XFlush(xdisp);
		break;
	case WM_RBUTTONDOWN:
		/* Right Button DOWN
		 * wParam: lowword:  MK_CONTROL | MK_LBUTTON | MK_MBUTTON | MK_SHIFT
		 *         highword: delta z
		 * lParam: lowword:  x
		 * lParam: highword: y */
		XTestFakeButtonEvent(xdisp,3,True,0);
		XFlush(xdisp);
		break;
	case WM_KEYDOWN:
		/* Key down
		 * wParam: virtual keycode
		 * lParam: 0-15:  repeat count
		 *         16-23: scancode
		 *         24:    extended key?
		 *         25-28: reserved
		 *         30:    previous state
		 *         31:    transition state (0) */
		XTestFakeKeyEvent(xdisp,wParam,False,0);
		MapVirtualKeyEx
		XFlush(xdisp);
		break;
	case WM_KEYUP:
		/* Key up
		 * wParam: virtual keycode
		 * lParam: 0-15:  repeat count
		 *         16-23: scancode
		 *         24:    extended key?
		 *         25-28: reserved
		 *         30:    previous state (1)
		 *         31:    transition state (1) */
		XTestFakeKeyEvent(xdisp,wParam,True,0);
		XFlush(xdisp);
		break;
	case WM_SYSKEYDOWN:
		break;
	case WM_SYSKEYUP:
		break;
	default:
		return DefWindowProc(hwnd,msg,wParam,lParam);
	}
/*@@3<-@@*/
	return 0;
}
/*@@2<-@@*/
/*<---------------------------------------------------------------------->*/
/* --- The following code comes from c:\lcc\lib\wizard\tcpini.tpl. */
// WSADATA *InitWS2(void)
// Routine Description:
//
// Calls WSAStartup, makes sure we have a good version of WinSock2
//
//
// Return Value:
//  A pointer to a WSADATA structure - WinSock 2 DLL successfully started up
//  NULL - Error starting up WinSock 2 DLL.
//
WSADATA *InitWS2(void)
{
    int           Error;              // catches return value of WSAStartup
    WORD          VersionRequested;   // passed to WSAStartup
    static WSADATA       WsaData;            // receives data from WSAStartup
    BOOL          ReturnValue = TRUE; // return value flag


    // Start WinSock 2.  If it fails, we don't need to call
    // WSACleanup().
    VersionRequested = MAKEWORD(2, 0);
    Error = WSAStartup(VersionRequested, &WsaData);
    if (Error) {
        MessageBox(hwndMain,
                   "Could not find high enough version of WinSock",
                   "Error", MB_OK | MB_ICONSTOP | MB_SETFOREGROUND);
        ReturnValue = FALSE;
    } else {

        // Now confirm that the WinSock 2 DLL supports the exact version
        // we want. If not, make sure to call WSACleanup().
        if (LOBYTE(WsaData.wVersion) != 2) {
            MessageBox(hwndMain,
                       "Could not find the correct version of WinSock",
                       "Error",  MB_OK | MB_ICONSTOP | MB_SETFOREGROUND);
            WSACleanup();
            ReturnValue = FALSE;
        }
    }
    if (ReturnValue)
        return &WsaData;
    return(NULL);

} // InitWS2()

/*<---------------------------------------------------------------------->*/
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, INT nCmdShow)
{
	MSG msg;
	HANDLE hAccelTable;
	int xevent,err,maj,min;

	hInst = hInstance;
	if (!InitApplication())
		return 0;
	hAccelTable = LoadAccelerators(hInst,MAKEINTRESOURCE(IDACCEL));
	if ((hwndMain = Createwin2xWndClassWnd()) == (HWND)0)
		return 0;
	// Find windows resolution: GetDeviceCaps
	win_xres=GetDeviceCaps(GetDC(hwndMain),HORZRES);
	win_yres=GetDeviceCaps(GetDC(hwndMain),VERTRES);

	/* tall thin window */
	SetWindowPos(hwndMain,HWND_TOPMOST,0,0,1,win_yres,0);
	exploded = FALSE;
	ShowWindow(hwndMain,SW_SHOW);
	WsaData = InitWS2();
	if (WsaData == NULL)
		return 0;

	if(!strlen(lpCmdLine)) {
		MessageBox(hwndMain,"Usage: win2x <server:display>","Usage", MB_OK | MB_ICONINFORMATION );
		return 0;
	}
	//MessageBox(hwndMain,lpCmdLine,"temp",MB_OK);
	xdisp = XOpenDisplay(lpCmdLine);
	if(xdisp == NULL) {
		MessageBox(hwndMain,"Could not connect to X Server", "Fatal Error", MB_OK | MB_ICONSTOP | MB_SETFOREGROUND);
		return 0;
	}
	if(XTestQueryExtension(xdisp, &xevent, &err, &maj, &min)) {
		// worked
	} else {
		MessageBox(hwndMain,"X Server does not support XTst","Fatal Error", MB_OK | MB_ICONSTOP | MB_SETFOREGROUND);
		return 0;
	}
	// Get X resolution
	// WidthOfScreen, HeightOfScreen
	x_xres=DisplayWidth(xdisp,xdisp->default_screen);
	x_yres=DisplayHeight(xdisp,xdisp->default_screen);
	while (GetMessage(&msg,NULL,0,0)) {
		if (!TranslateAccelerator(msg.hwnd,hAccelTable,&msg)) {
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}
	WSACleanup();
	return msg.wParam;
}

