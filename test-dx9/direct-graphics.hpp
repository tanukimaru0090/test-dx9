#pragma once
#include <Windows.h>
#include <d3d9.h>
#include <format>
#include <functional>
#include <string>
#include <d3dx9.h>

// Window管理とグラフィックスの初期化やら
class DirectGraphics {
public:
	DirectGraphics();
	~DirectGraphics();
	static LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);
	HRESULT initializeD3DX9TEXTURE();
	HRESULT initializeD3DX9();
	void initialzieWINAPI(WNDCLASSEX* wcEx);

	void messageLoop(std::function<void()>rendererFunc);
	void createWindow(HINSTANCE hInstance, const std::string& className,
		const std::string& title, int x, int y, int rWidth,
		int rHeight, HWND hWndParent = NULL, HMENU hMenu = NULL, LPVOID lpParam = NULL);
	void showWindow();
	LPDIRECT3DDEVICE9 getDevice() { return pDevice; }
	LPDIRECT3D9 getDirectX9() { return pD3D; }
	D3DPRESENT_PARAMETERS getDirectXParam() { return d3dpp; }
private:
	HWND _hwnd;
	D3DPRESENT_PARAMETERS d3dpp;
	LPDIRECT3DDEVICE9 pDevice;
	LPDIRECT3D9 pD3D;
};

