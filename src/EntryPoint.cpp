#pragma once
#include <iostream>
#include "Application.h"

int main() {
	Application app(1280, 720, "Push The Box");
	app.run(100);
	return 0;
}