#ifndef PAINTEREXCEPTIONS_H
#define PAINTEREXCEPTIONS_H
#include <exception>

class BaseException : public std::exception
{
protected:
    char err_info[512];


public:
    BaseException() noexcept = default;
    explicit BaseException(const char *msg) noexcept;
    virtual ~BaseException() = default;

    const char *what() const noexcept override;
};

class FewToCloseExcpetion : public BaseException
{
public:
    FewToCloseExcpetion(const char *info = "Few points to close figure") noexcept
        : BaseException(info){};
};

class NotAllClosedException : public BaseException
{
public:
    NotAllClosedException(const char *info = "Not all figures closed") noexcept
        : BaseException(info){};

};

class NoPointsException : public BaseException
{
public:
    NoPointsException(const char *info = "There is no points in figure") noexcept
        : BaseException(info){};

};

#endif // PAINTEREXCEPTIONS_H
