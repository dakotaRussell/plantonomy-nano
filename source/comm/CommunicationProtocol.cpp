#include "CommunicationProtocol.h"

CommunicationProtocol::CommunicationProtocol(){
   CommConfig def;
   config = &def;
}

CommunicationProtocol::CommunicationProtocol(CommConfig* commConfig){
    if (commConfig == nullptr) return;
    config = commConfig;
}
