#include <Siv3D.hpp> // OpenSiv3D v0.4.3
#include <Siv3D/Windows/Windows.hpp>

#define GetHInstance( ) ((HINSTANCE)GetModuleHandle(0))

void Main()
{
	// 標準機能で枠なしウィンドウを作成
	//Window::SetStyle(WindowStyle::Frameless);

	// 背景色は白に
	Scene::SetBackground(Color(Palette::White));

	// Windowハンドル取得
	auto hWnd = static_cast<HWND>(s3d::Platform::Windows::Window::GetHWND());

	WNDCLASS wc;
		wc.style = CS_HREDRAW | CS_VREDRAW;
		wc.cbClsExtra = wc.cbWndExtra = 0;
		wc.hInstance = (HINSTANCE)GetWindowLongPtr(hWnd, GWLP_HINSTANCE);
		wc.hCursor = wc.hIcon = NULL;
		wc.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
		wc.lpszClassName = L"KITTY";
		wc.lpszMenuName = L"KITTY";

		if (!RegisterClass(&wc)) {
			Console << U"クラスの登録失敗";
		}



	// ウィンドウを角丸にする（要Win32API）
	// まず、ウィンドウの形を示すためのリージョンを作成（大きさ640x480, 角丸50x50）
	auto hRegion = CreateRoundRectRgn(0, 0, 640, 480, 100, 100);
	// 次にウィンドウに適用
	//SetWindowRgn(hWnd, hRegion, 1);

	//ボタンコントロール作成
	//HWND hwnd_button = CreateWindowA("button", "ボタン", WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON,
	//					50, 50, 100, 100, hWnd, (HMENU)100, (HINSTANCE)GetWindowLongPtr(hWnd, GWLP_HINSTANCE), NULL);
	//Console << GetWindowLongPtr(hWnd, GWLP_HINSTANCE);


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
	}
}
