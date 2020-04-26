#ifndef FILESYSTEM_HPP
#define FILESYSTEM_HPP
#include "GlobalHeader.hpp"
#include <vector>
#include <string>
namespace DreamEngine
{
namespace GameSystem
{
class FileSystem
{
  public:
	FileSystem();
	~FileSystem();

	/**
	 * @brief Initializes a zip file as a mount point to search for files
	 * 
	 * @param Path 
	 * @param mountpoint 
	 */
	void InitPath(const std::string &Path, const std::string &mountpoint);
	
	/**
	 * @brief Gets a char array from a file present in a directory or a loaded zip file
	 * 
	 * @param path 
	 * @param buffer (this is the char array that will be filled with the file data)
	 * @param size (this is the size of the char array)
	 * @return EXIT_FAILURE if failed, EXIT_SUCCESS if success
	 */
	static int GetBytesFromFile(const std::string &path, char *&buffer, Sint64 &size);

  private:
	std::vector<std::string> paths;
};
};
};
#endif