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

	Window::Resize(300, 300);

	// Windowハンドル取得
	auto hWnd = static_cast<HWND>(s3d::Platform::Windows::Window::GetHWND());

	// ウィンドウを角丸にする（要Win32API）
	// 現在の dpi を取得（←追加）
	double dpi_dist = getDpiDist(hWnd);
	// ウィンドウの形を示すためのリージョンを作成（大きさ:ウィンドウサイズ * dpiの倍数, 角丸100x100）
	//auto hRegion = CreateRoundRectRgn(0, 0, Scene::Width() * dpi_dist, Scene::Height() * dpi_dist, 100, 100);
	// 楕円形リージョンの生成
	// 左上x=0, 左上y=0, 右下x=Scene::Width(), 右下y=Scene::Height()
	//auto hRegion = CreateEllipticRgn(0, 0, Scene::Width(), Scene::Height());
	// 三角形リージョンの生成
	/*
	POINT pt[5];
	pt[0].x = 0;				pt[0].y = 0;					// 頂点1: (0, 0)
	pt[1].x = Scene::Width();	pt[1].y = 0;					// 頂点2: (Scene::Width(), 0)
	pt[2].x = 30;				pt[2].y = Scene::Height();		// 頂点3: (30, Scene::Height())
	auto hRegion = CreatePolygonRgn(pt, 3, ALTERNATE);			// 多角形リージョンより生成
	*/
	// 星型リージョンの生成
	Console << U"{}, {}"_fmt(Scene::Width() / 2 * Math::Sin(90_deg), Scene::Height() / 2 * Math::Cos(90_deg));
	POINT pt[5];
	int r = Scene::Width() / 2;
	pt[0].x = Scene::Width() / 2 + r * Math::Cos(-90_deg);	pt[0].y = Scene::Height() / 2 + r * Math::Sin(-90_deg);
	pt[1].x = Scene::Width() / 2 + r * Math::Cos(-90_deg + 72_deg);	pt[1].y = Scene::Height() / 2 + r * Math::Sin(-90_deg + 72_deg);
	pt[2].x = Scene::Width() / 2 + r * Math::Cos(-90_deg + 72_deg * 2);	pt[2].y = Scene::Height() / 2 + r * Math::Sin(-90_deg + 72_deg * 2);
	pt[3].x = Scene::Width() / 2 + r * Math::Cos(-90_deg + 72_deg * 3);	pt[3].y = Scene::Height() / 2 + r * Math::Sin(-90_deg + 72_deg * 3);
	pt[4].x = Scene::Width() / 2 + r * Math::Cos(-90_deg + 72_deg * 4);	pt[4].y = Scene::Height() / 2 + r * Math::Sin(-90_deg + 72_deg * 4);
	auto hRegion = CreatePolygonRgn(pt, 5, ALTERNATE);			// 多角形リージョンより生成
	// ウィンドウに適用
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
