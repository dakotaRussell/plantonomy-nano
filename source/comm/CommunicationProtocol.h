#ifndef COMMUNICATION_PROTOCOL_H
#define COMMUNICATION_PROTOCOL_H

#include <string>

struct CommConfig {
    std::string name = "UnnamedComm";
    std::string address = "0x48";
};

class CommunicationProtocol {
public:
    CommunicationProtocol();
    CommunicationProtocol(CommConfig* commConfig);
    virtual ~CommunicationProtocol() = default;

private:
    CommConfig* config;
};

#endif // COMMUNICATION_PROTOCOL_H

