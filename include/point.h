#ifndef POINT_H
#define POINT_H

#include <concepts>
#include <type_traits>

template<typename T>
concept Scalar = std::is_scalar_v<T>;

template<Scalar T>
class Point {
private:
    T x_, y_;
public:
    Point() : x_(T{}), y_(T{}) {}
    Point(T x, T y) : x_(x), y_(y) {}

    T x() const { return x_; }
    T y() const { return y_; }

    void setX(T x) { x_ = x; }
    void setY(T y) { y_ = y; }

    bool operator==(const Point& other) const {
        return x_ == other.x_ && y_ == other.y_;
    }
};


template <Scalar T>
std::ostream& operator<<(std::ostream& os, const Point<T>& p) {
    os << "(" << p.x() << ", " << p.y() << ")";
    return os;
}

#endif
