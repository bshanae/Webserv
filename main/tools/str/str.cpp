#include "str.h"
#include <string>
void markEmptyLines(std::string& target, const std::string& endl)
{
	replaceAll(target, endl + endl, endl + "$" + endl);

	const size_t lastEndlOffset = target.length() - endl.length();
	if (target.compare(lastEndlOffset, endl.length(), endl) == 0)
		target.replace(lastEndlOffset, endl.length(), endl + "$");
}

void replaceAll(std::string& target, const std::string& search, const std::string& replace)
{
	size_t i = 0;
	while ((i = target.find(search, i)) != std::string::npos)
	{
		target.replace(i, search.length(), replace);
		i += replace.length();
	}
}

void Trim(std::string& out_line)
{
    size_t trimmed_end = out_line.find_first_of(";#");
    if (trimmed_end != std::string::npos)
        out_line.erase(trimmed_end);
	trimmed_end = out_line.find_first_not_of("\n\t\r ");
	out_line.erase(0, trimmed_end);
	trimmed_end = out_line.find_last_not_of("\n\t\r ");
    if (trimmed_end != std::string::npos)
	{
		out_line.erase(trimmed_end + 1);
	}
    
}
