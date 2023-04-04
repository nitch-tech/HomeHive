//
// Created by dave on 23/03/23.
//

#ifndef HOMEHIVE_LOGGER_H
#define HOMEHIVE_LOGGER_H

#include <string>
#include <iostream>
#include <chrono>

class Logger {
	private:
		static Logger* instance;

		Logger() = default;
		~Logger();
	std::ostream& _out_stream;
	bool         _next_is_begin;

	const std::string _log_header;

	public:
	static const std::string default_log_header;

	public:
		static Logger* getInstance();
		void log(std::string message);

		void debug(std::string message);
		void info(std::string message);
		void warn(std::string message);
		void error(std::string message);

	//Overload for anything else:
	template<typename T>
	Logger& operator<< (const T& data)
	{
		if (data == std::endl) {
			_next_is_begin = true;
		}

		auto now        = std::chrono::system_clock::now();
		auto now_time_t = std::chrono::system_clock::to_time_t( now ); //Uhhg, C APIs...
		auto now_tm     = std::localtime( &now_time_t ); //More uhhg, C style...

		if( _next_is_begin )
			_out_stream << _log_header << "(" << now_tm->tm_hour << ":" << now_tm->tm_min << ":" << now_tm->tm_sec << "): " << data;
		else
			_out_stream << data;

		_next_is_begin = false;

		return *this;
	}
};


#endif //HOMEHIVE_LOGGER_H
