#include "GameSystem/FileSystem.hpp"
#include "Misc/Debug.hpp"
using namespace std;
using namespace DreamEngine::GameSystem;
FileSystem::FileSystem() : paths(vector<std::string>())
{
    PHYSFS_init(NULL);
}
FileSystem::~FileSystem()
{
    for (auto path : paths)
    {
        PHYSFS_unmount(path.c_str());
    }
    PHYSFS_deinit();
}

void FileSystem::InitPath(const std::string &Path, const std::string &mountpoint)
{
    for (auto path : paths)
    {
        if (path == Path)
        {
            return;
        }
    }

    if (!PHYSFS_mount(Path.c_str(), mountpoint.c_str(), 0))
    {
        Debug::Log::PrintLine("failed to load the current mountpoint " + Path);
    }
    paths.push_back(Path);
}
int FileSystem::GetBytesFromFile(const string &path, char *&buffer, Sint64 &size)
{
    PHYSFS_File *tempmemory = PHYSFS_openRead(path.c_str());
    if (tempmemory)
    {

        size =  Sint64(PHYSFS_fileLength(tempmemory));

        //checks if the buffer contains data, if yes, make it empty in order to fill it with new data
        if (buffer)
        {
            delete[] buffer;
            buffer = nullptr;
        }

        //creates a buffer with the correct length for the file
        buffer = new char[size];
        if (PHYSFS_readBytes(tempmemory, buffer, size) == size)
        {
            Debug::Log::PrintLine("The file " + path + " has been successfully loaded");
            PHYSFS_close(tempmemory);
            return EXIT_SUCCESS;
        }
        else
        {
            Debug::Log::PrintLine("An error occured when trying to get the bytes of the file " + path);
            PHYSFS_close(tempmemory);
        }
    }
    else
    {
        Debug::Log::PrintLine("An error occured while trying to open the file " + path);
    }

    return EXIT_FAILURE;
}
