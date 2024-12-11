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
const double FRAME_PER_SECOND = 1.0 / 60.0;
const float C_SIDE = 1.3; //cube sides
const float R_SPEED = 1.0f/1000.0f; //revolution per second
const double PI = 3.14159265358979323846f;
