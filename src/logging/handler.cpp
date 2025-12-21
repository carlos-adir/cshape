
#include "cshape/logging.h"

CoutHandler::CoutHandler(){}

CoutHandler::~CoutHandler(){}


void CoutHandler::write(const LogMessage& message) const
{
    std::cout << message << std::endl;
}


FileHandler::FileHandler(const Filepath& filepath) :
    stream(*new std::ofstream(filepath)),
    filepath(filepath)
{
}

FileHandler::~FileHandler()
{
    stream.close();
    delete &stream;
}

void FileHandler::write(const LogMessage& message) const
{
    std::cout << "Writing on file: '" << filepath << "'" << std::endl;
    stream << message << std::endl;
}

static std::unique_ptr<std::map<const Filepath, const std::shared_ptr<FileHandler>>> files;

std::shared_ptr<FileHandler> FileHandler::getInstance(const Filepath& filename)
{
    if (files == nullptr)
        files = std::make_unique<std::map<const Filepath, const std::shared_ptr<FileHandler>>>();
    if (!files->count(filename))
    {
        auto pointer = std::shared_ptr<FileHandler>(new FileHandler(filename));
        files->insert({filename, pointer});
    }
    return files->at(filename);
}


TransmiterHandler::TransmiterHandler(){}

TransmiterHandler::~TransmiterHandler(){}


void TransmiterHandler::write(const LogMessage& message) const
{
    for (const auto& handler : handlers)
        if (handler->is_active)
            handler->write(message);
}

bool TransmiterHandler::operator+=(const std::shared_ptr<IHandler> ptr)
{
    for (const auto& handler : handlers)
        if (ptr == handler)
            return false;
    this->handlers.push_back(ptr);
    return true;
}

bool TransmiterHandler::operator-=(const std::shared_ptr<IHandler> ptr)
{
    for (size_t i = 0; i < handlers.size(); ++i)
        if (handlers[i] == ptr)
        {
            handlers.erase(handlers.begin() + i);
            return true;
        }
    return false;
}
