#ifndef __EXCEPTIONS_H__
#define __EXCEPTIONS_H__

#include <exception>
#include <string>

class BaseException : public std::exception
{
protected:
    char err_info[512];

public:
    BaseException() noexcept = default;
    explicit BaseException(const char *msg) noexcept;
    BaseException(const char *filename,
                  const char *classname,
                  int line,
                  const char *info = "ERROR") noexcept;
    virtual ~BaseException() = default;

    const char *what() const noexcept override;
};

class NoSuitableAdapterException : public BaseException
{
public:
    NoSuitableAdapterException() noexcept
        : BaseException("No suitable adapter found"){};
    explicit NoSuitableAdapterException(const char *msg) noexcept
        : BaseException(msg){};
    NoSuitableAdapterException(const char *filename,
                               const char *classname,
                               int line,
                               const char *info = "No suitable adapter found") noexcept
        : BaseException(filename, classname, line, info){};
    virtual ~NoSuitableAdapterException() = default;
};

class NoSuitableFactoryException : public BaseException
{
public:
    NoSuitableFactoryException() noexcept
        : BaseException("No suitable factory found"){};
    explicit NoSuitableFactoryException(const char *msg) noexcept
        : BaseException(msg){};
    NoSuitableFactoryException(const char *filename,
                               const char *classname,
                               int line,
                               const char *info = "No suitable adapter found") noexcept
        : BaseException(filename, classname, line, info){};
    virtual ~NoSuitableFactoryException() = default;
};

class CameraNotSetException : public BaseException
{
public:
    CameraNotSetException() noexcept
        : BaseException("Camera not set"){};
    explicit CameraNotSetException(const char *msg) noexcept
        : BaseException(msg){};
    CameraNotSetException(const char *filename,
                               const char *classname,
                               int line,
                               const char *info = "Camera not set") noexcept
        : BaseException(filename, classname, line, info){};
    virtual ~CameraNotSetException() = default;
};

class SourceException : public BaseException
{
public:
    SourceException() noexcept
        : BaseException("Source exception"){};
    explicit SourceException(const std::string &msg)
        :SourceException(msg.c_str()){};
    explicit SourceException(const char *msg) noexcept
        : BaseException(msg){};
    SourceException(const char *filename,
                               const char *classname,
                               int line,
                               const char *info = "Source exception") noexcept
        : BaseException(filename, classname, line, info){};
    virtual ~SourceException() = default;
};

class ModelException : public BaseException
{
public:
    ModelException() noexcept
        : BaseException("Source exception"){};
    explicit ModelException(const std::string &msg)
        :ModelException(msg.c_str()){};
    explicit ModelException(const char *msg) noexcept
        : BaseException(msg){};
    ModelException(const char *filename,
                    const char *classname,
                    int line,
                    const char *info = "Source exception") noexcept
        : BaseException(filename, classname, line, info){};
    virtual ~ModelException() = default;
};

class CameraException : public BaseException
{
public:
    CameraException() noexcept
        : BaseException("Source exception"){};
    explicit CameraException(const std::string &msg)
        :CameraException(msg.c_str()){};
    explicit CameraException(const char *msg) noexcept
        : BaseException(msg){};
    CameraException(const char *filename,
                    const char *classname,
                    int line,
                    const char *info = "Source exception") noexcept
        : BaseException(filename, classname, line, info){};
    virtual ~CameraException() = default;
};

#endif // __EXCEPTIONS_H__
