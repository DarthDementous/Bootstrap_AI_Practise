#include "_2017_07_17_AIPractise_stoyApp.h"

int main() {
	
	// allocation
	auto app = new _2017_07_17_AIPractise_stoyApp();

	// initialise and loop
	app->run("AIE", 1280, 720, false);

	// deallocation
	delete app;

	return 0;
}