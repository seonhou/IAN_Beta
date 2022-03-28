#pragma once

template<typename T>
bool is_infinite(const T &value)	// if INFINITE -> return 1
{
	// Since we're a template, it's wise to use std::numeric_limits<T>
	//
	// Note: std::numeric_limits<T>::min() behaves like DBL_MIN, and is the smallest absolute value possible.
	//

	T max_value = std::numeric_limits<T>::max();
	T min_value = -max_value;

	return !(min_value <= value && value <= max_value);
}

template<typename T>
bool is_nan(const T &value)	// if NAN -> return 1
{
	// True if NAN
	return value != value;
}

template<typename T>
bool is_valid(const T &value)
{
	return !is_infinite(value) && !is_nan(value);
}