#pragma once


struct color
{
	double r;
	double g;
	double b;
};

namespace Colors
{
	color Black = { 0, 0, 0 };
	color White = { 255, 255, 255 };
	color Red = { 255, 0, 0 };
	color Green = { 0, 255, 0 };
	color Blue = { 0, 0, 255 };
	color Gray = { 128, 128, 128 };
	color LightGray = { 181, 178, 178 };
}