#include <Siv3D.hpp> // OpenSiv3D v0.6.6
#include <Siv3D/Windows/Windows.hpp>

#define DPI_STANDARD	96

// 現在の dpi 値を取得
// 96dpi に対して何倍の値か？
double getDpiDist(HWND hWnd) {
	return (double)GetDpiForWindow(hWnd) / DPI_STANDARD;
}

void Main()
{
	// 標準機能で枠なしウィンドウを作成
	Window::SetStyle(WindowStyle::Frameless);

	// 背景色は白に
	Scene::SetBackground(Color(Palette::White));

	// Windowハンドル取得
	auto hWnd = static_cast<HWND>(s3d::Platform::Windows::Window::GetHWND());

	// ウィンドウを角丸にする（要Win32API）
	// 現在の dpi を取得（←追加）
	double dpi_dist = getDpiDist(hWnd);
	// ウィンドウの形を示すためのリージョンを作成（大きさ:ウィンドウサイズ * dpiの倍数, 角丸100x100）
	auto hRegion = CreateRoundRectRgn(0, 0, Scene::Width() * dpi_dist, Scene::Height() * dpi_dist, 100, 100);
	// 次にウィンドウに適用
	SetWindowRgn(hWnd, hRegion, 1);

	// マウスクリックした地点の記録用
	Point mouse_clicked = Point{ 0, 0 };
	while (System::Update()) {
		// ウィンドウの移動用処理（←追加）
		if (MouseL.down()) {
			mouse_clicked = Cursor::Pos();
		}
		if (MouseL.pressed()) {
			Window::SetPos(Cursor::ScreenPos() - mouse_clicked);
		}
		Print << U"Hello!";
	}
}
