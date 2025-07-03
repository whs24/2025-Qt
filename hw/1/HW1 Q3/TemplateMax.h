#pragma once

#include <string>
template <typename T>

T Max(T x, T y) {
	if (x > y) {
		return x;
	}
	return y;
}

const char* Max(const char* x, const char* y) {
	if (strcmp(x, y) > 0)
		return x;
	return y;
}
