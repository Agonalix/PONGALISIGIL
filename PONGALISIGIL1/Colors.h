#pragma once


struct color
{
	double r;
	double g;
	double b;
	double a;
};

namespace colors
{
	color BLACK = { 0, 0, 0, 1 };
	color WHITE = { 1, 1, 1, 1 };
	color RED = { 1, 0, 0, 1 };
	color GREEN = { 0, 1, 0, 1 };
	color BLUE = { 0, 0, 1, 1 };
	color GRAY = { 0.361, 0.361, 0.361, 1 };
	color LIGHTGRAY = { 0.659, 0.659, 0.659, 1 };
}