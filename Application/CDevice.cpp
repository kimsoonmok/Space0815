#include "CDevice.h"

CDevice   g_device;

CDevice::CDevice()
{
	m_pD2DFactory = nullptr;
	m_pRenderTarget = nullptr;
	m_pWICFactory = nullptr;
}

CDevice::~CDevice()
{
	
}

bool CDevice::InitDevice(HWND _hWnd)
{
	HRESULT hr = S_OK;
	hr = D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, &m_pD2DFactory);

	D2D1_SIZE_U   sizeU = { 100, 100 };
	RECT rc;
	GetClientRect(_hWnd, &rc);

	hr = m_pD2DFactory->CreateHwndRenderTarget(
		D2D1::RenderTargetProperties(),
		D2D1::HwndRenderTargetProperties(_hWnd, D2D1::SizeU(rc.right - rc.left, rc.bottom - rc.top)),
		&m_pRenderTarget);
	if (FAILED(hr)) return hr;

	CoInitialize(NULL); //****
	hr = CoCreateInstance(CLSID_WICImagingFactory, NULL, // 고유 아이디를 사용하는곳이 있는지 ****
		CLSCTX_INPROC_SERVER, IID_PPV_ARGS(&m_pWICFactory));
	if (FAILED(hr)) return hr;


	return true;
}

ID2D1Bitmap* CDevice::LoadBitmapFromFile(PCWSTR _wcFileName)
{
	HRESULT hr = S_OK;
	IWICBitmapDecoder* pDecoder = nullptr;
	ID2D1Bitmap* pBitmap = nullptr ;
	//return pBitmap;   // return 0 ;

	// Load Image
	hr = m_pWICFactory->CreateDecoderFromFilename(
		_wcFileName,
		NULL,
		GENERIC_READ,
		WICDecodeMetadataCacheOnLoad,
		&pDecoder);

	if (FAILED(hr)) return nullptr;

	// 0번 프레임 얻기 // 프레임을 얻는다는것이 한장을 얻는다는 것인가 ?****
	IWICBitmapFrameDecode* pFrame = nullptr;
	hr = pDecoder->GetFrame(0, &pFrame);
	if (FAILED(hr)) return nullptr;

	// 컨버터 생성
	IWICFormatConverter* pConverter = nullptr;
	hr = m_pWICFactory->CreateFormatConverter(&pConverter);
	if (FAILED(hr)) return nullptr;

	hr = pConverter->Initialize(pFrame, GUID_WICPixelFormat32bppPBGRA,
		WICBitmapDitherTypeNone,
		NULL,
		0.0f,
		WICBitmapPaletteTypeCustom);
	if (FAILED(hr)) return nullptr;

	hr = m_pRenderTarget->CreateBitmapFromWicBitmap(
		pConverter,
		NULL,
		&pBitmap);

	if (FAILED(hr)) return nullptr;

	if (pConverter) { pConverter->Release(); pConverter = nullptr; }
	if (pFrame) { pFrame->Release(); pFrame = nullptr; }
	if (pDecoder) { pDecoder->Release(); pDecoder = nullptr; }

	return pBitmap;
}

void CDevice::CleanupDevice(void)
{
	if (m_pWICFactory) CoUninitialize();
	if (m_pRenderTarget) m_pRenderTarget->Release();
	if (m_pD2DFactory) m_pD2DFactory->Release();
}
