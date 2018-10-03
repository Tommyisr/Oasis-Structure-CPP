#ifndef EXCEPTIONS_H
#define EXCEPTIONS_H

#include <exception>
#include "Player.h"
#include "Clan.h"
#define NEW_EXCEPTION(exp, from) \
    class exp : public from{\
    public: \
        virtual const char* what() const throw(){\
            return #exp;\
    }}

namespace mvne{
    
    NEW_EXCEPTION(OasisException, std::exception);
    NEW_EXCEPTION(MemoryException,OasisException);
    NEW_EXCEPTION(ClanException,OasisException);
    NEW_EXCEPTION(PlayerException,OasisException);
    NEW_EXCEPTION(ClanAlreadyExists,ClanException);
    NEW_EXCEPTION(ClanNotFound,ClanException);
    NEW_EXCEPTION(PlayerAlreadyExists,PlayerException);
    NEW_EXCEPTION(PlayerNotFound,PlayerException);
    NEW_EXCEPTION(InvalidInput,OasisException);

//    class Player;
////
//    class Clan;


}
#endif //MTM4_EXCEPTIONS_H
