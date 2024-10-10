#include <iostream>

template <typename Target>
u_int bufferToUint16 (const char buffer[]) {
    return 
        (static_cast<u_int>(static_cast<Target>(buffer[0])) << 8) | 
        static_cast<u_int>(static_cast<Target>(buffer[1]))
    ;
}