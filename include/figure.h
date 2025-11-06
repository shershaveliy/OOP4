#ifndef FIGURE_H
#define FIGURE_H

#include "point.h"
#include <vector>
#include <memory>
#include <iostream>

template<Scalar T>
class Figure {
public:
    virtual ~Figure() = default;

    virtual double area() const = 0;
    virtual Point<T> center() const = 0;
    virtual std::vector<std::unique_ptr<Point<T>>> vertices() const = 0;

    virtual bool operator==(const Figure<T>& other) const = 0;
    
    virtual operator double() const { return area(); }

    virtual void print(std::ostream& os) const = 0;
    virtual void read(std::istream& is) = 0;
};

//Операторы для потокового ввода/вывода
template<Scalar T>
std::ostream& operator<<(std::ostream& os, const Figure<T>& fig){
    fig.print(os);
    return os;
}

template<Scalar T>
std::istream& operator>>(std::istream& is, Figure<T>& fig){
    fig.read(is);
    return is;
}

#endif
