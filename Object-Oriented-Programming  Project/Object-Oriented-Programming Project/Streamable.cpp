#include "Stremable.h"

namespace seneca
{
    Streamable:: ~Streamable() {}

    std::ostream& operator<<(std::ostream& os, const Streamable& obj) {
        if (obj) obj.write(os);
        
        return os;
    }

    std::istream& operator>>(std::istream& is, Streamable& obj) {
        return obj.read(is);
    }
}