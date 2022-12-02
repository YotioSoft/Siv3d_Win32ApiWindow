#include <Siv3D.hpp> // OpenSiv3D v0.4.3
#include <Siv3D/Windows/Windows.hpp>

#define CLASSNAME "MyWindowClass"

void Main()
{
	// 標準機能で枠なしウィンドウを作成
	//Window::SetStyle(WindowStyle::Frameless);

	// 背景色は白に
	Scene::SetBackground(Color(Palette::White));

	// Windowハンドル取得
	HWND hWnd = static_cast<HWND>(s3d::Platform::Windows::Window::GetHWND());

	// ウィンドウを角丸にする（要Win32API）
	// まず、ウィンドウの形を示すためのリージョンを作成（大きさ640x480, 角丸50x50）
	//auto hRegion = CreateRoundRectRgn(0, 0, 640, 480, 100, 100);
	// 次にウィンドウに適用
	//SetWindowRgn(hWnd, hRegion, 1);

	HINSTANCE hInstance = ::GetModuleHandle(NULL);

	WNDCLASS wc;
	HWND hwnd;
	TCHAR szAppName[1024];
	/*
	// ウィンドウクラスの属性を設定
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc = DefWindowProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = hInstance;
	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wc.lpszMenuName = NULL;
	wc.lpszClassName = szAppName;

	// ウィンドウクラスを登録
	if (!RegisterClass(&wc)) return;
	*/

	GetClassName(hWnd, szAppName, 1024);

	Console << Unicode::Widen((char*)szAppName);

	auto hBtn = CreateWindowEx(0, L"BUTTON", L"Push!!",
			WS_CHILD | WS_VISIBLE | BS_FLAT,
			0, 0, 50, 30,
			hWnd, (HMENU)100, hInstance, NULL);

	// if (!hWndOwned) return FALSE;

	// 被所有ウィンドウ
	/*
	hWndOwned = CreateWindow(CLASSNAME, "Owned Window",
	 WS_POPUP | WS_CAPTION | WS_VISIBLE,
	 0, 0, 150, 100, hWnd, NULL, hInstance, NULL);
	if (!hWndOwned) return FALSE;
	*/

	// ウィンドウを表示する
	ShowWindow(hWnd, SW_NORMAL);
	UpdateWindow(hWnd);

	MSG msg;

	// マウスクリックした地点の記録用
	Point mouse_clicked;
	while (System::Update()) {
		// ウィンドウの移動用処理
		if (MouseL.down()) {
			mouse_clicked = Cursor::Pos();
		}
		if (MouseL.pressed()) {
			Window::SetPos(Cursor::ScreenPos() - mouse_clicked);
		}
		Print << U"Hello!";
	}
}
