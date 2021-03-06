#pragma once
#include "Vec2.h"

template <typename T> 
class Rect_
{
public:
	Rect_(int left_in, int right_in, int top_in, int bottom_in)
		:
		left(left_in),
		right(right_in),
		top(top_in),
		bottom(bottom_in)
	{
	}

	Rect_(const Vec2_<T>& topLeft, const Vec2_<T>& bottomRight)
		:
		Rect_(topLeft.x, bottomRight.x, topLeft.y, bottomRight.y)
	{
	}

	Rect_(const Vec2_<T>& topLeft, int width, int height)
		:
		Rect_<T>(topLeft, topLeft + Vec2_<T>(width, height))
	{
	}

	bool IsOverlappingWith(const Rect_& other) const
	{
		return right > other.left && left < other.right
			&& bottom > other.top && top < other.bottom;
	}

	bool IsContainedBy(const Rect_& other) const
	{
		return left >= other.left && right <= other.right &&
			top >= other.top && bottom <= other.bottom;
	}

	bool Contains(const Vec2_<T>& point) const
	{
		return point.x >= left && point.x < right && point.y >= top && point.y < bottom;
	}

	Rect_ FromCenter(const Vec2_<T>& center, int halfWidth, int halfHeight)
	{
		const Vec2_<T> half(halfWidth, halfHeight);
		return RectI(center - half, center + half);
	}
	Rect_ Move(Vei2 rhs)
	{
		return { left + rhs.x, right + rhs.x, top + rhs.y,bottom + rhs.y };
	}
	Rect_ GetExpanded(int offset) const
	{
		return Rect_(left - offset, right + offset, top - offset, bottom + offset);
	}

	Rect_ GetOverlap(const Rect_& B) const
	{
		return {
			std::max(left,B.left),
			std::min(right,B.right),
			std::max(top,B.top),
			std::min(bottom,B.bottom)
		};
	}

	Vec2_<T> GetCenter() const
	{
		return Vec2_<T>((left + right) / 2, (top + bottom) / 2);
	}

	int GetWidth()
	{
		return right - left;
	}

	int GetHeight()
	{
		return bottom - top;
	}
public:
	T left;
	T right;
	T top;
	T bottom;
};

typedef Rect_<int> RectI;