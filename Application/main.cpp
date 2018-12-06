/* Entry point for the example application.
 */

#include <Application.h>


static const char* kApplicationVersion = "0.0.3";


int main(int argc, char* argv[])
{
	// Create a non-GUI application
	ExampleApplication app(argc, argv);

	// Set the application version
	app.setApplicationVersion(kApplicationVersion);

	// Run the event loop, and exit when it terminates.
	return app.exec();
}
