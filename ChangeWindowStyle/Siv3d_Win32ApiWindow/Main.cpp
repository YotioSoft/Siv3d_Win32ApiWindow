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
	auto hWnd = static_cast<HWND>(s3d::Platform::Windows::Window::GetHWND());

	// ウィンドウを角丸にする（要Win32API）
	// まず、ウィンドウの形を示すためのリージョンを作成（大きさ640x480, 角丸50x50）
	//auto hRegion = CreateRoundRectRgn(0, 0, 640, 480, 100, 100);
	// 次にウィンドウに適用
	//SetWindowRgn(hWnd, hRegion, 1);

	auto nIndex = GetWindowLongA(hWnd, GWL_STYLE);
	SetWindowLongA(hWnd, GWL_STYLE, nIndex & ~WS_CAPTION);

	SetLayeredWindowAttributes(hWnd, 0, 200, 2);

	// マウスクリックした地点の記録用
	Point mouse_clicked;
	while (System::Update()) {
		// ウィンドウの移動用処理
		/*
		if (MouseL.down()) {
			mouse_clicked = Cursor::Pos();
		}
		if (MouseL.pressed()) {
			Window::SetPos(Cursor::ScreenPos() - mouse_clicked);
		}
		*/
		Print << U"Hello!";
	}
}
