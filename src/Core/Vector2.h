#pragma once
#include <SFML/Graphics.hpp>
#include <string>

template <typename T>
struct vec2
{
	T x;
	T y;

	vec2() {
		x = 0;
		y = 0;
	}

	vec2(T x, T y) {
		this->x = x;
		this->y = y;
	}

	void set(T x, T y) {
		this->x = x;
		this->y = y;
	}

	inline bool is_zero() const {
		return x == 0 && y == 0;
	}

	inline vec2& Add(const vec2& vec) {
		x += vec.x;
		y += vec.y;
		return *this;
	}
	inline vec2& Subtract(const vec2& vec) {
		x -= vec.x;
		y -= vec.y;
		return *this;
	}
	inline vec2& Multiply(const vec2& vec) {
		x *= vec.x;
		y *= vec.y;
		return *this;
	}
	inline vec2& Divide(const vec2& vec) {
		x /= vec.x;
		y /= vec.y;
		return *this;
	}

	inline friend vec2 operator+(vec2 v1, const vec2& v2) {
		return v1.Add(v2);
	}
	inline friend vec2 operator-(vec2 v1, const vec2& v2) {
		return v1.Subtract(v2);
	}
	inline friend vec2 operator*(vec2 v1, const vec2& v2) {
		return v1.Multiply(v2);
	}
	inline friend vec2 operator/(vec2 v1, const vec2& v2) {
		return v1.Divide(v2);
	}

	inline vec2& operator+=(const vec2& vec) {
		return Add(vec);
	}
	inline vec2& operator-=(const vec2& vec) {
		return Subtract(vec);
	}
	inline vec2& operator*=(const vec2& vec) {
		return Multiply(vec);
	}
	inline vec2& operator/=(const vec2& vec) {
		return Divide(vec);
	}

	inline vec2 operator+(double s) {
		T ts = static_cast<T>(s);
		return vec2(x + ts, y + ts);
	}
	inline vec2 operator-(double s) {
		T ts = static_cast<T>(s);
		return vec2(x - ts, y - ts);
	}
	inline vec2 operator*(double s) {
		T ts = static_cast<T>(s);
		return vec2(x * ts, y * ts);
	}
	inline vec2 operator/(double s) {
		T ts = static_cast<T>(s);
		return vec2(x / ts, y / ts);
	}

	inline vec2& operator+=(double s) {
		x += s;
		y += s;
		return *this;
	}
	inline vec2& operator-=(double s) {
		x -= s;
		y -= s;
		return *this;
	}
	inline vec2& operator*=(double s) {
		x *= s;
		y *= s;
		return *this;
	}
	inline vec2& operator/=(double s) {
		x /= s;
		y /= s;
		return *this;
	}

	inline operator vec2<float>() {
		return { static_cast<float>(x), static_cast<float>(y) };
	}
	inline operator vec2<double>() {
		return { static_cast<double>(x), static_cast<double>(y) };
	}
	inline operator vec2<int>() {
		return { static_cast<int>(x), static_cast<int>(y) };
	}
	inline operator vec2<unsigned int>() {
		return { static_cast<unsigned int>(x), static_cast<unsigned int>(y) };
	}

	inline bool operator==(const vec2& vec) const {
		return (x == vec.x) && (y == vec.y);
	}

	inline bool operator!=(const vec2& vec) const {
		return (x != vec.x) || (y != vec.y);
	}

	inline friend std::ostream& operator<<(std::ostream& os, const vec2& vec) {
		os << '(' << vec.x << ", " << vec.y << ')';
		return os;
	}

	inline operator std::string() {
		return '(' + std::to_string(x) + ", " + std::to_string(y) + ')';
	}

	inline operator sf::Vector2<T>() {
		return { x, y };
	}
};

using vec2f = vec2<float>;
using vec2d = vec2<double>;
using vec2i = vec2<int>;
using vec2u = vec2<unsigned int>;