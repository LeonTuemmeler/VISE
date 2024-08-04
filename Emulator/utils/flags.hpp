#pragma once
#define SETUP_ENUM_AS_FLAG(T) \
	inline T operator~ (T a) { return (T)~(int)a; } \
	inline T operator| (T a, T b) { return (T)((int)a | (int)b); } \
	inline T operator& (T a, T b) { return (T)((int)a & (int)b); } \
	inline T operator^ (T a, T b) { return (T)((int)a ^ (int)b); } \
	inline T& operator|= (T& a, T b) { return (T&)((int&)a |= (int)b); } \
	inline T& operator&= (T& a, T b) { return (T&)((int&)a &= (int)b); } \
	inline T& operator^= (T& a, T b) { return (T&)((int&)a ^= (int)b); }

#define HAS_FLAG(A, B) ((A & B) != 0)