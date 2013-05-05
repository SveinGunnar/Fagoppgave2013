/**
 * Alf-Andre Walla, Svein Fagerheim
 * s181087			s181086
 * 
 * Every time an error happens somewhere in the code, then that error will be written to a log file
**/

#ifndef __LOG_H
#define __LOG_H

#include <fstream>
#include <string>

namespace platformer
{
	typedef enum{ LINFO, LWARN, LERR } log_level_t;
	
class Log
{
	std::ofstream file;
	
	public:
		Log(std::string);
		~Log();
		bool write(log_level_t, std::string);
};

}

#endif
