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

	// 背景色
	Scene::SetBackground(Color(Palette::Green));

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

	POINT pt[1000];
	int i = 0;
	//const MultiPolygon polygons = image.alphaToPolygons();
	//image.bordered(10, Palette::Black);

	//auto tex = Texture(image);
	Font font(40);
	const Font emojiFont{ 20, Typeface::ColorEmoji };

	// `font` が絵文字用フォントも使えるようにする | Set emojiFont as a fallback
	font.addFallback(emojiFont);

	Image image{ 150, 150 };
	auto tree = emojiFont(U"🎄");
	tree.overwrite(image, Vec2{ -15, 0 });

	Texture tex(image);

	MultiPolygon multi_polygon = image.alphaToPolygons();

	int max_x = 0, max_y = 0;
	for (const auto& polygon : multi_polygon)
	{
		for (const auto& point : polygon.outer())
		{
			if (i > 1000) {
				break;
			}

			pt[i].x = point.x * 2;
			pt[i].y = point.y * 2;

			if (max_x < pt[i].x)
				max_x = pt[i].x;
			if (max_y < pt[i].y)
				max_y = pt[i].y;
			Console << U"{}, {}"_fmt(pt[i].x, pt[i].y);

			i++;
		}
	}

	Window::Resize(max_x, max_y);

	Console << Scene::Width();
	Console << Scene::Height();
	Console << max_x;
	Console << max_y;

	auto hRegion = CreatePolygonRgn(pt, i, ALTERNATE);			// 多角形リージョンより生成
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

		Print(U"Merry Xmas!");
		emojiFont(U"🎄").drawAt(Scene::Width() / 2, Scene::Height() / 2);
	}
}
