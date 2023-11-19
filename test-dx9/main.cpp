#include "define.hpp"
#include "direct-graphics.hpp"
#include "error.hpp"
#include "global.hpp"
#pragma comment(lib, "d3dx9.lib")
#pragma comment(lib, "d3d9.lib")
#pragma comment(lib, "user32.lib")
// 定数
const int WINDOW_WIDTH = 1280;
const int WINDOW_HEIGHT = 800;
const char* WINDOW_TITLE = "てすとウィンドウ";
const char* WINDOW_CLASS_NAME = "test";

// 頂点の情報
#define D3DFVF_TLVERTEX		(D3DFVF_XYZRHW|D3DFVF_DIFFUSE|D3DFVF_TEX1)

// 頂点構造体
typedef struct _D3DTLVERTEX {
	float	x, y, z;									// 頂点のXYZ座標
	float	rhw;									// 描画時にXYZから割られる数（小難しい話なのでここは常に1となると覚えよう）
	DWORD	color;									// 頂点の色(32bitアルファ値あり)
	float	tu, tv;									// 頂点に割り当てるテクスチャのUV値
} D3DTLVERTEX, * LPD3DTLVERTEX;

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
		   LPSTR lpCmdLine, int nCmdShow) {
	
	LPD3DXSPRITE pSprite = NULL;
	DirectGraphics gh;  // グラフィックスの初期化用のクラス変数
	LPDIRECT3DTEXTURE9 pTexture = NULL;   // テクスチャ用変数
	D3DTLVERTEX				v[4] = { 0 };	// 頂点バッファ用変数 4頂点分
	WNDCLASSEX wc;
	D3DXVECTOR3 center(100.0f, 100.0f, 0.0f);
	D3DXVECTOR3 pos(200.0f, 300.0f, 0.0f);

	ZeroMemory(&wc, sizeof(wc));
	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wc.cbSize = sizeof(WNDCLASSEX);
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = hInstance;
	wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wc.lpszMenuName = NULL;
	wc.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.lpfnWndProc = DirectGraphics::WndProc;
	wc.lpszClassName = WINDOW_CLASS_NAME;
	gh.initialzieWINAPI(&wc);
	gh.createWindow(hInstance, WINDOW_CLASS_NAME, WINDOW_TITLE, 0, 0,
			WINDOW_WIDTH, WINDOW_HEIGHT);
	auto res = gh.initializeD3DX9();
	if (FAILED(res)) {
		::OutputDebugString(
			Error::fmtErrorCode("DirectX9の初期化に失敗しました", res)
			.c_str());
		return -1;
	}
	auto tex_res = D3DXCreateTextureFromFileEx(
	    gh.getDevice(),		// デバイスへのポインター
	    "assets/sample-image.png",	// ファイル名
	    D3DX_DEFAULT,		// 幅をファイルから取得
	    D3DX_DEFAULT,		// 高さをファイルから取得
	    1,		     // ミップマップレベルを自動生成
	    0,		     // 使用法を指定しない
	    D3DFMT_UNKNOWN,  // ピクセル形式をファイルから取得
	    D3DPOOL_MANAGED,  // メモリクラスを管理されたものにする
	    D3DX_FILTER_POINT,	// フィルタリング方法をデフォルトにする
	    D3DX_FILTER_NONE,  // ミップマップのフィルタリング方法をデフォルトにする
	    0,		 // カラーキーを使わない
	    NULL,	 // ソースイメージの情報を受け取らない
	    NULL,	 // パレットを受け取らない
	    &pTexture	 // テクスチャへのポインターのアドレス
	);
	if (FAILED(tex_res)) {
		::OutputDebugString(Error::fmtErrorCode(
				      "テクスチャの作成に失敗しました", tex_res)
				      .c_str());
		return -1;
	}

	auto sp_rs = D3DXCreateSprite(gh.getDevice(), &pSprite);
	if (FAILED(sp_rs)) {
		::OutputDebugString(Error::fmtErrorCode(
			"スプライトの作成に失敗しました", tex_res)
			.c_str());
		return -1;
	}
	// 頂点の初期化
	::ZeroMemory(&v, sizeof(v));

	gh.getDevice()->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	gh.getDevice()->SetRenderState(D3DRS_ZENABLE, D3DZB_TRUE);
	gh.showWindow();
	gh.messageLoop([&] {
	
		// バックバッファのクリア
		gh.getDevice()->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER | D3DCLEAR_STENCIL, D3DCOLOR_XRGB(50, 50, 50), 1.0f, 0);
		// シーンの開始
		gh.getDevice()->BeginScene();
		
		// テクスチャの描画
		// テクスチャのセット
		//gh.getDevice()->SetTexture(0, pTexture);

		// 使用する頂点フォーマットのセット
		//gh.getDevice()->SetFVF(D3DFVF_TLVERTEX);
		// 頂点リストの描画
		//gh.getDevice()->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, 2, v, sizeof(D3DTLVERTEX));
		
		// スプライトの描画
		pSprite->Begin(D3DXSPRITE_ALPHABLEND);
		pos.x += 20;
		pSprite->Draw(pTexture, NULL, &center, &pos, 0xffffffff);
		pSprite->End();
		// シーンの終了
		gh.getDevice()->EndScene();

		// フリップして実際に画面に反映
		gh.getDevice()->Present(NULL, NULL, NULL, NULL);

		
		::Sleep(15);
	});
	pSprite->Release();
	pTexture->Release();
	return 0;
}
