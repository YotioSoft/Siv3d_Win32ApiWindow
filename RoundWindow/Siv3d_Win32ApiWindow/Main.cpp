#include <Siv3D.hpp> // OpenSiv3D v0.4.3
#include <Siv3D/Windows/Windows.hpp>

#define CLASSNAME "MyWindowClass"

void Main()
{
	// 標準機能で枠なしウィンドウを作成
	Window::SetStyle(WindowStyle::Frameless);

	// 背景色は白に
	Scene::SetBackground(Color(Palette::White));

	// Windowハンドル取得
	auto hWnd = static_cast<HWND>(s3d::Platform::Windows::Window::GetHWND());

	// ウィンドウを角丸にする（要Win32API）
	// まず、ウィンドウの形を示すためのリージョンを作成（大きさ640x480, 角丸50x50）
	auto hRegion = CreateRoundRectRgn(0, 0, 640, 480, 100, 100);
	// 次にウィンドウに適用
	SetWindowRgn(hWnd, hRegion, 1);

	HINSTANCE hInstance = (HINSTANCE)GetWindowLongPtr(hWnd, GWLP_HINSTANCE);

	auto hWndChild = CreateWindow(L"MyWindowClass", L"Child Window",
	  WS_CHILD | WS_CAPTION | WS_VISIBLE,
	  0, 0, 150, 100, hWnd, NULL, hInstance, NULL);
	//if (!hWndChild) return FALSE;

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
	while (System::Update() && GetMessage(&msg, NULL, 0, 0)) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);

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
