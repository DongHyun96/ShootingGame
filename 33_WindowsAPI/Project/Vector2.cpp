#include "Framework.h"
#include "Vector2.h"

Vector2::Vector2()
{
}

Vector2::Vector2(float x, float y)
	:x(x), y(y)
{
}

float Vector2::Length()
{
	return sqrtf(powf(x, 2) + powf(y, 2));
}

Vector2 Vector2::GetNormal()
{
	return *this / Length();
}

void Vector2::Normalize()
{
	*this = GetNormal();
}

float Vector2::Dot(const Vector2& v1, const Vector2 v2)
{
	return v1.x * v2.x + v1.y * v2.y;
}

float Vector2::Cross(const Vector2& v1, const Vector2 v2)
{
	return v1.x * v2.y - v1.y * v2.x;
}

Vector2 Vector2::operator+(const Vector2& other)
{
	return Vector2(this->x + other.x, this->y + other.y);
}

Vector2 Vector2::operator-(const Vector2& other)
{
	return Vector2(this->x - other.x, this->y - other.y);
}

Vector2 Vector2::operator*(const float& value)
{
	return Vector2(this->x * value, this->y * value);
}

Vector2 Vector2::operator/(const float& value)
{
	return Vector2(this->x / value, this->y / value);
}

void Vector2::operator+=(const Vector2& other)
{
	this->x += other.x;
	this->y += other.y;
}

void Vector2::operator-=(const Vector2& other)
{
	this->x -= other.x;
	this->y -= other.y;
}

void Vector2::operator*=(const float& value)
{
	this->x *= value;
	this->y *= value;
}

void Vector2::operator/=(const float& value)
{
	this->x /= value;
	this->y /= value;
}

bool Vector2::IsBetween(const Vector2& factor, const Vector2& v1, const Vector2 v2)
{
	// Factor가 들어가는 순서도 일정해야 함
	return Cross(factor, v1) * Cross(factor, v2) < 0;
}
