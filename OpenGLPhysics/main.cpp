#include <filesystem>
#include "Window.h"


int main()
{
#ifdef PROJECT_DIR
	std::filesystem::current_path(PROJECT_DIR);
#endif // PROJECT_DIR

	//doesnt need to be a pointer
	auto window = std::make_unique<OpenGLWindow>();
	window->run();
	return 0;
}
