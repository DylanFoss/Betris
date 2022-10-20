#include "Vec2d.h"

template<typename T>
Vec2d<T>::Vec2d()
	:x(0), y(0)
{
}

template<typename T>
Vec2d<T>::Vec2d(T x, T y)
	: x(x), y(y)
{
}

template<typename T>
Vec2d<T>::Vec2d(const Vec2d& vec)
	: x(vec.x), y(vec.y)
{
}