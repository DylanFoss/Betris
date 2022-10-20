#pragma once
template<typename T>
class Vec2d
{
public:
	T x, y;

	Vec2d();
	Vec2d(T x, T y);
	Vec2d(const Vec2d& vec);
};

