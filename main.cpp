#include "gui/App.h"

int main(int argc, char** argv) {
	App* app = new App();
	app->Start(argc, argv);

	int status = app->GetStatus();
	delete app;

	return status;
}
