#pragma once
#include "processing.hpp"
#include "../Game/game.hpp"

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

double Processing::MatchTemplate(cv::Mat img, const char* const tmpl_fn, cv::Point* const loc) {
	cv::cvtColor(img, img, cv::COLOR_BGRA2GRAY);

	cv::Mat tmpl = cv::imread(tmpl_fn, 0);
	cv::Mat score;

	cv::matchTemplate(img, tmpl, score, cv::TM_CCOEFF_NORMED);

	double maxVal;
	minMaxLoc(score, NULL, &maxVal, NULL, loc);

	return maxVal;
}

std::vector<std::vector<cv::Point>> Processing::MinionHealthBarContours(cv::Mat img, Game::Side side) {
	cv::cvtColor(img, img, cv::COLOR_BGRA2BGR);
	cv::cvtColor(img, img, cv::COLOR_BGR2HSV);

	cv::Mat red_hp_bars;
	if (side == Game::Side::RED)
		cv::inRange(img, cv::Scalar(0, 139, 208), cv::Scalar(0, 140, 209), red_hp_bars);
	// todo: blue hsv range

	std::vector<std::vector<cv::Point>> contours;
	std::vector<cv::Vec4i> hierarchy;
	findContours(red_hp_bars, contours, hierarchy, CV_RETR_TREE, CV_CHAIN_APPROX_SIMPLE, cv::Point(0, 0));

	return contours;
}

template <typename RectOp> bool Processing::MinionLowestComparison(cv::Mat img, int& x, int& y, Game::Side side, RectOp rect_op) {
	std::vector<std::vector<cv::Point>> contours = Processing::MinionHealthBarContours(img, side);
	
	int param = -1;
	for (int i = 0; i < contours.size(); i++) {
		cv::Rect rect = cv::boundingRect(contours.at(i));

		// height should always be 1 for what we're checking
		if (rect.height != 1)
			continue;

		int cparam = rect_op(rect);
		if (param < 0 || cparam < param) {
			param = cparam;
			// centered health bar coordinates (max health is 60x4)
			x = rect.x + 30;
			y = rect.y + 2;
		}
	}

	// if no minions are found, return false
	return param > 0;
}

bool Processing::ClosestMinion(cv::Mat img, int& x, int& y, Game::Side side) {
	auto dist_comp = [](cv::Rect rect) { return sqrt(pow(640 - rect.x, 2) + pow(360 - rect.y, 2)); };
	return Processing::MinionLowestComparison(img, x, y, side, dist_comp);
}

bool Processing::LowestHpMinion(cv::Mat img, int& x, int& y, Game::Side side) {
	auto hp_comp = [](cv::Rect rect) { return rect.width; };
	return Processing::MinionLowestComparison(img, x, y, side, hp_comp);
}

bool Processing::FindTurret(cv::Mat img, int& x, int& y, Game::Side& enemy) {
	cv::Point loc;
	
	// find outer turret health bar matches (assumed to only be 1 at a time on the screen)
	// the red turret template is used but it doesn't matter as it's read as grayscale
	if (Processing::MatchTemplate(img, "rturret.png", &loc) > 0.7f) {
		cv::cvtColor(img, img, cv::COLOR_BGRA2BGR);
		cv::cvtColor(img, img, cv::COLOR_BGR2HSV);
		
		// get health bar color
		int hue = img.at<cv::Vec3b>(cv::Point(loc.x + 20, loc.y + 9))[0];
		
		// if hue < 10 it should be a red health bar
		enemy = static_cast<Game::Side>(hue < 10);
		// centered health bar coordinates (template is 270x25)
		x = loc.x + 135;
		y = loc.y + 12;

		return true;
	}

	return false;
}
