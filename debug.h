#ifndef DEBUG_H
#define DEBUG_H

#define _DEBUG

#ifdef _DEBUG
#include <iostream>
#define DEBUG_MESSAGE(x) (std::cout << x << std::endl);
#else
#define DEBUG_MESSAGE(x) ;
#endif

#endif // DEBUG_H
