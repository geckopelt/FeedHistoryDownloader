#pragma once

#include "Exceptions/GuardException.hxx"

#define CHECK(condition, message) { if (!(condition)) { throw GuardException((message), __FILE__, __LINE__); } }

