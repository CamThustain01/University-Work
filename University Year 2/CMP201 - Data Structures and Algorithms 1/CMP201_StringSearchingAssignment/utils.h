#ifndef UTILS_H
#define UTILS_H

#include <string>

/** Integer type that can hold a position within an array.
	The standard type for this is size_t, but that's an unsigned type,
	and we need to be able to represent -1 for "not found" too.
	(POSIX provides ssize_t for this but Windows doesn't.) */
using Position = long long int;

/** Print an error message and abort the program. */
void die(const std::string& msg);

/** Load the whole of a text file into str. */
void load_file(const std::string& filename, std::string& str);

/** Load the text of "The Jute Industry" into str. */
void load_jute_book(std::string& str);

/** Show the contents of str around the position pos.
	Control characters (e.g. \n) are shown as @s. */
void show_context(const std::string& str, Position pos);

#endif

