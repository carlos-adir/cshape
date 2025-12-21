#ifndef LOGGING_HANDLER_H
#define LOGGING_HANDLER_H

#include <ctime>
#include <fstream>
#include <iostream>
#include <sstream>
#include <map>
#include <vector>
#include <memory>
#include "message.h"

class IHandler 
{
    public:
        bool is_active = true;
        virtual void write(const LogMessage& message) const = 0;
};

class CoutHandler : public IHandler
{
    public:
        CoutHandler();
        ~CoutHandler();
        void write(const LogMessage& message) const override;
};

class FileHandler : public IHandler
{
    private:
        FileHandler(const Filepath& filepath);
        std::ofstream& stream;
        
    public:
        const Filepath filepath;
        ~FileHandler();
        static std::shared_ptr<FileHandler> getInstance(const Filepath& filepath); 
        void write(const LogMessage& message) const override;
};

class TransmiterHandler : public IHandler
{
    private:
        std::vector<std::shared_ptr<IHandler>> handlers = {};
    public:
        TransmiterHandler();
        ~TransmiterHandler();
        void write(const LogMessage& message) const override;
        bool operator+=(const std::shared_ptr<IHandler> ptr);
        bool operator-=(const std::shared_ptr<IHandler> ptr);
};

#endif