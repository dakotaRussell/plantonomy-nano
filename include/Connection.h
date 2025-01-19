#ifndef CONNECTION_H
#define CONNECTION_H

#include <iostream>

class Connection
{
    public:
        Connection();
        Connection(const char* addr);
        virtual ~Connection();
        virtual void open(const unsigned char *configOptions, size_t len);
        virtual double read();
        virtual ssize_t write(const unsigned char *buf, size_t len);

    protected:
        ssize_t buf_size = 0;
        const char* addr;

    private:
};

#endif // CONNECTION_H
