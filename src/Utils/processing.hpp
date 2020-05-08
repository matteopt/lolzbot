#pragma once
#include <Windows.h>
#include <cstdint>
#include <vector>
#include <opencv2/core/mat.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

namespace Processing {
	
	struct HDC_t {
		int w, h;
		HDC hdc;
		HDC hcdc;
		HBITMAP hbmp;
		BITMAPINFOHEADER bi;

		HDC_t() {};

		HDC_t(HDC hdc, int w, int h) {
			this->w = w;
			this->h = h;
			this->hdc = hdc;
			hcdc = CreateCompatibleDC(hdc);
			hbmp = CreateCompatibleBitmap(hdc, w, h);
			SelectObject(hcdc, hbmp);

			ZeroMemory(&bi, sizeof(BITMAPINFOHEADER));
			bi.biSize = sizeof(BITMAPINFOHEADER);
			bi.biWidth = w;
			bi.biHeight = -h;
			bi.biPlanes = 1;
			bi.biBitCount = 32;
			bi.biCompression = BI_RGB;
		}
	};

	void GetRGB(const COLORREF color, uint8_t& r, uint8_t& g, uint8_t& b);
	bool CompareRGB(const COLORREF color, const uint8_t r, const uint8_t g, const uint8_t b);
	cv::Mat Screenshot(const HDC_t dc);
	double MatchTemplate(cv::Mat img, const char* const tmpl_fn);
	void ClosestEnemyMinion(cv::Mat img, int& x, int& y);
}
