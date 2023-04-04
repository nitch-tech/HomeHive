//
// Created by dave on 23/03/23.
//

#include "Logger.h"

/*
Logger::Logger() {
	Logger::_log_header = "HomeHive";
	Logger::_out_stream = std::cout;
	this->_next_is_begin = true;

}*/
void Logger::log(std::string message) {

}

Logger::~Logger() {

}

Logger *Logger::getInstance() {
	return nullptr;
}

void Logger::debug(std::string message) {
//	instance  << message.c_str(); //  << std::endl;
}

void Logger::info(std::string message) {

}

void Logger::warn(std::string message) {

}

void Logger::error(std::string message) {

}

