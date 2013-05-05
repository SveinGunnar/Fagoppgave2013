/**
 * Alf-Andre Walla, Svein Fagerheim
 * s181087			s181086
 * 
 * Log implementation
**/

#include "log.h"

#include <ctime>
#include <iostream>
#include <sstream>

using namespace std;

namespace platformer
{
	Log::Log(std::string filename)
	{
		this->file.open(filename.c_str(), ios::app | ios::out);
	}
	
	Log::~Log()
	{
		// close file, if open
		this->file.close();
	}
	
	Log& operator<<(Log& out, const std::string text)
	{
		return out << text;
	}
	
	bool Log::write(log_level_t level, std::string text)
	{
		if (!this->file.is_open()) return false;
		
		stringstream ss;
		
		time_t rawtime;
		time(&rawtime);
		tm* t = gmtime(&rawtime);
		
		if (t)
		{
			ss << "[" << t->tm_hour << ":" << t->tm_min << ":" << t->tm_sec << "] ";
		}
		
		switch (level)
		{
		case LINFO:
			ss << "INFO"; break;
		case LWARN:
			ss << "WARNING"; break;
		case LERR:
			ss << "ERROR"; break;
		}
		
		ss << ": " << text << endl;
		// to console
		cout << ss.str();
		// to file
		this->file << ss.str();
		return true;
	}
	
}