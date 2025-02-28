#include "Debugger.h"

//redeclare static variables
Debugger::MessageType Debugger::currentSev = MessageType::TYPE_NONE;
std::string Debugger::outputName = "";

void Debugger::OnCreate(const std::string& name_)
{
	outputName = name_ + ".txt";
	std::ofstream out; //creates and writes to file
	out.open(outputName.c_str(), std::ios::out);
	out.close();
	currentSev = MessageType::TYPE_INFO;
}

void Debugger::SetSeverity(MessageType type_)
{
	currentSev = type_; //sets severity variable
}

void Debugger::Info(const std::string& message_, const std::string& fileName_, const int line_)
{
	Log(MessageType::TYPE_INFO, "[INFO]: " + message_, fileName_, line_);
}

void Debugger::Trace(const std::string& message_, const std::string& fileName_, const int line_)
{
	Log(MessageType::TYPE_TRACE, "[TRACE]: " + message_, fileName_, line_);
}

void Debugger::Warning(const std::string& message_, const std::string& fileName_, const int line_)
{
	Log(MessageType::TYPE_WARNING, "[WARNING]: " + message_, fileName_, line_);
}

void Debugger::Error(const std::string& message_, const std::string& fileName_, const int line_)
{
	Log(MessageType::TYPE_ERROR, "[ERROR]: " + message_, fileName_, line_);
}

void Debugger::FatalError(const std::string& message_, const std::string& fileName_, const int line_)
{
	Log(MessageType::TYPE_FATAL_ERROR, "[FATAL_ERROR]: " + message_, fileName_, line_);
}

void Debugger::Log(const MessageType type_, const std::string& message_, const std::string& fileName_, const int line_)
{
	if (type_ <= currentSev && currentSev > MessageType::TYPE_NONE)
	{
		std::ofstream out;
		out.open(outputName.c_str(), std::ios::app | std::ios::out);
		out << message_ << "in: " << fileName_ << "on line: " << line_ << std::endl;
		out.flush();
		out.close();
	}
}
