#ifndef ALIGPUCOMMONFAIRLOGGER_H
#define ALIGPUCOMMONFAIRLOGGER_H

#if defined(GPUCA_STANDALONE) || defined(GPUCA_ALIROOT_LIB) || defined(GPUCA_GPULIBRARY)

#include <iostream>
#define LOG(type) std::cout
namespace FairLogger {
	static constexpr const char* endl = "\n";
}

#else

#include <FairLogger.h>

#endif

#endif
