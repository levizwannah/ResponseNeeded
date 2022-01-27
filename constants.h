#pragma once

/*
* Defines the colors for the cubes
*/
enum class Color {
	RED,
	GREEN,
	BLUE,
	YELLOW
};

// settings
const unsigned int SCR_WIDTH = 1000;
const unsigned int SCR_HEIGHT = 600;
const int C_SIDE = 10; //cube sides
const float R_SPEED = 0.1f; //revolution per second
const double PI = 2 * acos(0.0);
