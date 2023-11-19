#include "define.hpp"
#include "direct-graphics.hpp"
#include "error.hpp"
#include "global.hpp"
#pragma comment(lib, "d3dx9.lib")
#pragma comment(lib, "d3d9.lib")
#pragma comment(lib, "user32.lib")
// �萔
const int WINDOW_WIDTH = 1280;
const int WINDOW_HEIGHT = 800;
const char* WINDOW_TITLE = "�Ă��ƃE�B���h�E";
const char* WINDOW_CLASS_NAME = "test";

// ���_�̏��
#define D3DFVF_TLVERTEX		(D3DFVF_XYZRHW|D3DFVF_DIFFUSE|D3DFVF_TEX1)

// ���_�\����
typedef struct _D3DTLVERTEX {
	float	x, y, z;									// ���_��XYZ���W
	float	rhw;									// �`�掞��XYZ���犄���鐔�i������b�Ȃ̂ł����͏��1�ƂȂ�Ɗo���悤�j
	DWORD	color;									// ���_�̐F(32bit�A���t�@�l����)
	float	tu, tv;									// ���_�Ɋ��蓖�Ă�e�N�X�`����UV�l
} D3DTLVERTEX, * LPD3DTLVERTEX;

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
		   LPSTR lpCmdLine, int nCmdShow) {
	
	LPD3DXSPRITE pSprite = NULL;
	DirectGraphics gh;  // �O���t�B�b�N�X�̏������p�̃N���X�ϐ�
	LPDIRECT3DTEXTURE9 pTexture = NULL;   // �e�N�X�`���p�ϐ�
	D3DTLVERTEX				v[4] = { 0 };	// ���_�o�b�t�@�p�ϐ� 4���_��
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
			Error::fmtErrorCode("DirectX9�̏������Ɏ��s���܂���", res)
			.c_str());
		return -1;
	}
	auto tex_res = D3DXCreateTextureFromFileEx(
	    gh.getDevice(),		// �f�o�C�X�ւ̃|�C���^�[
	    "assets/sample-image.png",	// �t�@�C����
	    D3DX_DEFAULT,		// �����t�@�C������擾
	    D3DX_DEFAULT,		// �������t�@�C������擾
	    1,		     // �~�b�v�}�b�v���x������������
	    0,		     // �g�p�@���w�肵�Ȃ�
	    D3DFMT_UNKNOWN,  // �s�N�Z���`�����t�@�C������擾
	    D3DPOOL_MANAGED,  // �������N���X���Ǘ����ꂽ���̂ɂ���
	    D3DX_FILTER_POINT,	// �t�B���^�����O���@���f�t�H���g�ɂ���
	    D3DX_FILTER_NONE,  // �~�b�v�}�b�v�̃t�B���^�����O���@���f�t�H���g�ɂ���
	    0,		 // �J���[�L�[���g��Ȃ�
	    NULL,	 // �\�[�X�C���[�W�̏����󂯎��Ȃ�
	    NULL,	 // �p���b�g���󂯎��Ȃ�
	    &pTexture	 // �e�N�X�`���ւ̃|�C���^�[�̃A�h���X
	);
	if (FAILED(tex_res)) {
		::OutputDebugString(Error::fmtErrorCode(
				      "�e�N�X�`���̍쐬�Ɏ��s���܂���", tex_res)
				      .c_str());
		return -1;
	}

	auto sp_rs = D3DXCreateSprite(gh.getDevice(), &pSprite);
	if (FAILED(sp_rs)) {
		::OutputDebugString(Error::fmtErrorCode(
			"�X�v���C�g�̍쐬�Ɏ��s���܂���", tex_res)
			.c_str());
		return -1;
	}
	// ���_�̏�����
	::ZeroMemory(&v, sizeof(v));

	gh.getDevice()->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	gh.getDevice()->SetRenderState(D3DRS_ZENABLE, D3DZB_TRUE);
	gh.showWindow();
	gh.messageLoop([&] {
	
		// �o�b�N�o�b�t�@�̃N���A
		gh.getDevice()->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER | D3DCLEAR_STENCIL, D3DCOLOR_XRGB(50, 50, 50), 1.0f, 0);
		// �V�[���̊J�n
		gh.getDevice()->BeginScene();
		
		// �e�N�X�`���̕`��
		// �e�N�X�`���̃Z�b�g
		//gh.getDevice()->SetTexture(0, pTexture);

		// �g�p���钸�_�t�H�[�}�b�g�̃Z�b�g
		//gh.getDevice()->SetFVF(D3DFVF_TLVERTEX);
		// ���_���X�g�̕`��
		//gh.getDevice()->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, 2, v, sizeof(D3DTLVERTEX));
		
		// �X�v���C�g�̕`��
		pSprite->Begin(D3DXSPRITE_ALPHABLEND);
		pos.x += 20;
		pSprite->Draw(pTexture, NULL, &center, &pos, 0xffffffff);
		pSprite->End();
		// �V�[���̏I��
		gh.getDevice()->EndScene();

		// �t���b�v���Ď��ۂɉ�ʂɔ��f
		gh.getDevice()->Present(NULL, NULL, NULL, NULL);

		
		::Sleep(15);
	});
	pSprite->Release();
	pTexture->Release();
	return 0;
}
