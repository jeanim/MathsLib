#pragma once
#ifndef __INC_ASSERT_H_
#define __INC_ASSERT_H_


#include <cassert>


/// Custom assert macro, where a is condition and b error description
#define Assert(a, b) assert(a && b)


#endif