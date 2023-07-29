#pragma once

struct Vector2;

struct Point
{
	//float a = 1 / 100.f;
	Point();
	Point(float x, float y);

	static float Distance(Point p1, Point p2);
	
	Point	operator+(const Vector2& other);
	Point	operator-(const Vector2& other);
					
	void	operator+=(const Vector2& other);
	void	operator-=(const Vector2& other);

	Vector2 operator-(const Point& other);

	float x = 0.f;
	float y = 0.f;
};
