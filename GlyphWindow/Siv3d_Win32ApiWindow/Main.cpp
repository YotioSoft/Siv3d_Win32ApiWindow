#include <Siv3D.hpp> // OpenSiv3D v0.6.6
#include <Siv3D/Windows/Windows.hpp>
void Main()
{
	// 標準機能で枠なしウィンドウを作成
	Window::SetStyle(WindowStyle::Frameless);

	// 背景色
	Scene::SetBackground(Color(Palette::Green));

	// Windowハンドル取得
	auto hWnd = static_cast<HWND>(s3d::Platform::Windows::Window::GetHWND());

	// クリスマスツリー型リージョンの生成
	POINT pt[1000];
	const Font emojiFont{ 20, Typeface::ColorEmoji };

	// Imageに🎄をoverwrite
	// ImageからMultiPolygonを取得
	Image image{ 150, 150 };
	auto tree = emojiFont(U"🎄");
	tree.overwrite(image, Vec2{ -15, 0 });	// フォントの余白分を左に寄せてoverwriteする
	MultiPolygon multi_polygon = image.alphaToPolygons();

	// ポリゴンをもとにリージョンを作成
	int max_x = 0, max_y = 0;
	int i = 0;
	for (const auto& polygon : multi_polygon)
	{
		for (const auto& point : polygon.outer())
		{
			if (i > 1000) {
				break;			// 最大1000角形とする
			}
			pt[i].x = point.x * 2;
			pt[i].y = point.y * 2;

			if (max_x < pt[i].x)
				max_x = pt[i].x;
			if (max_y < pt[i].y)
				max_y = pt[i].y;

			i++;
		}
	}
	auto hRegion = CreatePolygonRgn(pt, i, ALTERNATE);			// 多角形リージョンより生成

	// ウィンドウをリサイズ
	Window::Resize(max_x, max_y);

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
