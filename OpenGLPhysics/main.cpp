#include <filesystem>

int main()
{
#ifdef PROJECT_DIR
	std::filesystem::current_path(PROJECT_DIR);
#endif // PROJECT_DIR
}
