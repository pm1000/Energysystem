//
// Created by yabr on 30.04.21.
//

#ifndef ZENTRALE_UDPCALLBACK_H
#define ZENTRALE_UDPCALLBACK_H

using namespace std;

/**
 * UDP callback for incoming udp messages
 */
 class UDPCallback {
 public:
     virtual void processMessage (std::string) = 0;

 };


#endif //ZENTRALE_UDPCALLBACK_H
