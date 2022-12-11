#include <Siv3D.hpp> // OpenSiv3D v0.6.6
#include <Siv3D/Windows/Windows.hpp>

void Main()
{
	// 標準機能で枠なしウィンドウを作成
	//Window::SetStyle(WindowStyle::Frameless);

	// 背景色は白に
	Scene::SetBackground(Color(Palette::White));

	// Windowハンドル取得
	auto hWnd = static_cast<HWND>(s3d::Platform::Windows::Window::GetHWND());

	// 現在のウィンドウスタイルを取得
	auto nIndex = GetWindowLongA(hWnd, GWL_STYLE);

	// タイトルバーを非表示に
	//SetWindowLongA(hWnd, GWL_STYLE, nIndex & ~WS_CAPTION);			// タイトルバー非表示
	SetWindowLongA(hWnd, GWL_STYLE, nIndex & ~WS_SYSMENU);			// 最小化・最大化・閉じるボタン非表示
	//SetWindowLongA(hWnd, GWL_STYLE, nIndex & ~WS_MINIMIZEBOX);			// 閉じるボタンだけ

	auto nIndexEx = GetWindowLongA(hWnd, GWL_EXSTYLE);
	// ?
	//SetWindowLongA(hWnd, GWL_STYLE, nIndex & ~WS_MINIMIZEBOX);
	//SetWindowLongA(hWnd, GWL_EXSTYLE, nIndexEx | WS_EX_CONTEXTHELP);
	// タイトルバーを左右逆に
	//SetWindowLongA(hWnd, GWL_EXSTYLE, nIndexEx | WS_EX_LAYOUTRTL);
	// 短めのタイトルバー（フローティング ツールバー）
	//SetWindowLongA(hWnd, GWL_EXSTYLE, nIndexEx | WS_EX_TOOLWINDOW);

	while (System::Update()) {
		Print << U"Hello!";
	}
}
