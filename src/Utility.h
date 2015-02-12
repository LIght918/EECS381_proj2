#ifndef  UTILITY_H
#define UTILITY_H

#include <iosfwd>

/* Utility functions, constants, and classes used by more than one other modules */

class String;

// a simple class for error exceptions - msg points to a C-string error message
struct Error {
	Error(const char* msg_ = "") :
		msg(msg_)
		{}
	const char* msg;
};


void get_command_char( std::ifstream& is );



#endif