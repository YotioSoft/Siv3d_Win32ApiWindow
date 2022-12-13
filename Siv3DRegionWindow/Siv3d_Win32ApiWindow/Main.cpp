#include <Siv3D.hpp> // OpenSiv3D v0.6.6
#include <Siv3D/Windows/Windows.hpp>

void Main()
{
	// 標準機能で枠なしウィンドウを作成
	Window::SetStyle(WindowStyle::Frameless);

	// 背景色は白に
	Scene::SetBackground(Color(Palette::White));

	Window::Resize(600, 600);

	// Windowハンドル取得
	auto hWnd = static_cast<HWND>(s3d::Platform::Windows::Window::GetHWND());

	// 星型リージョンの生成
	POINT pt[100];
	int r = 300;
	s3d::Polygon polygon = Shape2D::Star(r, Scene::Center()).asPolygon();
	// 図形ポリゴンの座標をptにコピー
	int i = 0;
	for (const auto& point : polygon.outer()) {
		if (i > 100) {
			break;
		}
		pt[i].x = point.x;
		pt[i].y = point.y;
		i++;
	}

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
		Print << U"Hello star window!";
	}
}
