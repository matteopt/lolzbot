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

void Processing::ClosestEnemyMinion(cv::Mat img, int& x, int& y) {
	cv::cvtColor(img, img, cv::COLOR_BGRA2BGR);
	cv::cvtColor(img, img, cv::COLOR_BGR2HSV);

	cv::Mat red_hp_bars;
	cv::inRange(img, cv::Scalar(0, 139, 208), cv::Scalar(0, 140, 209), red_hp_bars);

	std::vector<std::vector<cv::Point>> contours;
	std::vector<cv::Vec4i> hierarchy;
	findContours(red_hp_bars, contours, hierarchy, CV_RETR_TREE, CV_CHAIN_APPROX_SIMPLE, cv::Point(0, 0));

	int dist = -1;
	for (int i = 0; i < contours.size(); i++) {
		cv::Rect rect = cv::boundingRect(contours.at(i));
		int cdist = sqrt(pow(640 - rect.x, 2) + pow(360 - rect.y, 2));
		if (dist < 0 || cdist < dist) {
			dist = cdist;
			x = rect.x + 5;
			y = rect.y + 10;
		}
	}
}
