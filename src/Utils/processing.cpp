#pragma once
#include "processing.hpp"

void Processing::GetRGB(const COLORREF color, uint8_t& r, uint8_t& g, uint8_t& b) {
	r = GetRValue(color);
	g = GetGValue(color);
	b = GetBValue(color);
	printf("%d %d %d\n", r, g, b);
}

bool Processing::CompareRGB(const COLORREF color, const uint8_t r, const uint8_t g, const uint8_t b) {
	uint8_t _r, _g, _b;
	GetRGB(color, _r, _g, _b);
	return (_r == r && _g == g && _b == b);
}

cv::Mat Processing::Screenshot(const HDC_t dc) {
	cv::Mat img = cv::Mat(dc.h, dc.w, CV_8UC4);
	BitBlt(dc.hcdc, 0, 0, dc.w, dc.h, dc.hdc, 0, 0, SRCCOPY);
	GetDIBits(dc.hcdc, dc.hbmp, 0, dc.h, img.data, (BITMAPINFO*)&dc.bi, DIB_RGB_COLORS);
	return img;
}

double Processing::MatchTemplate(cv::Mat img, const char* const tmpl_fn) {
	cv::cvtColor(img, img, cv::COLOR_BGRA2GRAY);

	cv::Mat tmpl = cv::imread(tmpl_fn, 0);
	cv::Mat score;

	cv::matchTemplate(img, tmpl, score, cv::TM_CCOEFF_NORMED);

	double maxVal;
	minMaxLoc(score, 0, &maxVal);

	return maxVal;
}
