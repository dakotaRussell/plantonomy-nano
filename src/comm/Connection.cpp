#include "Connection.h"

Connection::Connection()
{
    //ctor
}

Connection::Connection(const char* deviceAddr)
{
    //ctor
    addr = deviceAddr;
}

Connection::~Connection()
{
    //dtor
}

void Connection::open(const unsigned char *configOptions, size_t len){}

double Connection::read()
{
    return 0;
}

ssize_t Connection::write(const unsigned char *buf, size_t len)
{
    return 0;
}
