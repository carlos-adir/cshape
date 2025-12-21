
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
    stream << message << std::endl;
}

static std::unique_ptr<std::map<const Filepath, const std::shared_ptr<FileHandler>>> files;

std::shared_ptr<FileHandler> FileHandler::getInstance(const Filepath& filepath)
{
    if (files == nullptr)
        files = std::make_unique<std::map<const Filepath, const std::shared_ptr<FileHandler>>>();
    if (!files->count(filepath))
    {
        auto pointer = std::shared_ptr<FileHandler>(new FileHandler(filepath));
        files->insert({filepath, pointer});
    }
    return files->at(filepath);
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
    std::cout << "Pushback ptr " << ptr << std::endl;
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
