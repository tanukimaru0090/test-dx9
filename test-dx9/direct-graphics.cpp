#include "direct-graphics.hpp"
#include "define.hpp"
#include "global.hpp"
#include "error.hpp"
// �R���X�g���N�^
DirectGraphics::DirectGraphics() :_hwnd(NULL) {
	::ZeroMemory(&pDevice, sizeof(pDevice));
	::ZeroMemory(&pD3D, sizeof(pD3D));
	::ZeroMemory(&d3dpp, sizeof(d3dpp));
}
// �f�X�g���N�^
DirectGraphics::~DirectGraphics() {
	if (pD3D != NULL && pDevice != NULL) {
		pDevice->Release(); pD3D->Release();
	}
}

// �E�B���h�E�v���[�W��
LRESULT CALLBACK DirectGraphics::WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
	switch (msg) {
	case WM_PAINT: {
		PAINTSTRUCT ps;
		HDC hdc = ::BeginPaint(hwnd, &ps);
		::EndPaint(hwnd, &ps);
		break;
	}
	case WM_CLOSE:
		::DestroyWindow(hwnd);
		break;
	case WM_DESTROY:
		::PostQuitMessage(0);
		break;
	default:
		return ::DefWindowProc(hwnd, msg, wParam, lParam);
	}
	return 0;
}

// �e�N�X�`���̏�����
HRESULT DirectGraphics::initializeD3DX9TEXTURE() { return 0; }
// DirectX9�̏�����
HRESULT DirectGraphics::initializeD3DX9() {
	pD3D = Direct3DCreate9(D3D_SDK_VERSION);
	if (pD3D == NULL) {
		::OutputDebugString(Error::fmtErrorCode("DirectX3D�̍쐬�Ɏ��s���܂���", NULL).c_str());
		return -1;
	}
	d3dpp.AutoDepthStencilFormat = D3DFMT_D24S8;
	d3dpp.EnableAutoDepthStencil = TRUE;
	d3dpp.FullScreen_RefreshRateInHz = 0;
	d3dpp.BackBufferWidth = 1280;
	d3dpp.BackBufferHeight = 800;
	d3dpp.BackBufferCount = 1;
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	d3dpp.Windowed = TRUE;

	D3DDISPLAYMODE dm;
	HRESULT phr = pD3D->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &dm);
	if (FAILED(phr)) {
		::OutputDebugString(Error::fmtErrorCode("DirectX3D�̍쐬�Ɏ��s���܂���", phr).c_str());
		return -1;
	}
	HRESULT hr = pD3D->CreateDevice(
		D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, _hwnd,
		D3DCREATE_SOFTWARE_VERTEXPROCESSING, &d3dpp, &pDevice);
	if (FAILED(hr)) {
		::OutputDebugString(Error::fmtErrorCode("DirectX3DDevice�̍쐬�Ɏ��s���܂���", hr).c_str());
		return -1;
	}
	return hr;
}
// WINAPI�̏�����
void DirectGraphics::initialzieWINAPI(WNDCLASSEX* wcEx) {
	if (!RegisterClassEx(wcEx)) {
		::OutputDebugString(
			Error::fmtErrorCode("�E�B���h�E�N���X�̓o�^�Ɏ��s���܂���",
				NULL)
			.c_str());
		return;
	}
}
// ���b�Z�[�W���[�v
void DirectGraphics::messageLoop(std::function<void()>rendererFunc) {
	MSG msg; bool done = false; while (!done) {
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
			if (msg.message == WM_QUIT) { done = true; }
			else { ::TranslateMessage(&msg); ::DispatchMessage(&msg); }
		}
		else {
			// ���b�Z�[�W���Ȃ��Ƃ��ɕ`�揈�����s�� 
			rendererFunc(); // �t���[�����[�g�̐�����s���i�K�v�ɉ����āj 
		}
	}
}
// �E�B���h�E���쐬
void DirectGraphics::createWindow(HINSTANCE hInstance, const std::string& className,
	const std::string& title, int x, int y, int rWidth,
	int rHeight, HWND hWndParent , HMENU hMenu , LPVOID lpParam) {
	_hwnd = ::CreateWindow(
		className.c_str(), title.c_str(),
		WS_VISIBLE | WS_SYSMENU | WS_CAPTION | WS_MINIMIZEBOX | WS_CLIPCHILDREN | WS_CLIPSIBLINGS, x, y,
		rWidth, rHeight, hWndParent, hMenu, hInstance, lpParam);
	if (_hwnd == NULL) {
		::OutputDebugString(
			Error::fmtErrorCode("�E�B���h�E�̍쐬�Ɏ��s���܂���", NULL)
			.c_str());
		return;
	}
}
// �E�B���h�E��\��
void DirectGraphics::showWindow() { ::ShowWindow(_hwnd, SW_SHOW); }
