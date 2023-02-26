#include "log.h"

#include <ostream>

using namespace log;

LogStream log::v;
LogStream log::i;
LogStream log::w;
LogStream log::e;

void log::endl(LogStream& stream)
{
	stream << std::endl;
}

void log::startm(LogStream& stream)
{
	stream.addModifier(LogModifier::italic);
	stream << ' ';
}

void log::endm(LogStream& stream)
{
	stream.resetModifiers();
	stream << std::endl << std::endl;
}

void log::initialize()
{
	log::v = LogStream(LogModifier::grey);
	log::i = LogStream();
	log::w = LogStream(LogModifier::yellow);
	log::e = LogStream(LogModifier::red);
}