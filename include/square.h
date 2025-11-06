#ifndef SQUARE_H
#define SQUARE_H

#include "figure.h"
#include <cmath>
#include <stdexcept>
#include <vector>
#include <memory>

template<Scalar T>
class Square : public Figure<T> {
private:
    std::vector<std::unique_ptr<Point<T>>> verts_;

    static double dist(const Point<T>& a, const Point<T>& b) {
        double dx = static_cast<double>(a.x() - b.x());
        double dy = static_cast<double>(a.y() - b.y());
        return std::sqrt(dx*dx + dy*dy);
    }

public:
    Square() {
        verts_.resize(4);
        for (int i = 0; i < 4; ++i) verts_[i] = std::make_unique<Point<T>>(T{}, T{});
    }

    //Конструктор из 4 вершин (в порядке обхода)
    Square(const Point<T>& a, const Point<T>& b, const Point<T>& c, const Point<T>& d){
        verts_.clear();
        verts_.push_back(std::make_unique<Point<T>>(a.x(), a.y()));
        verts_.push_back(std::make_unique<Point<T>>(b.x(), b.y()));
        verts_.push_back(std::make_unique<Point<T>>(c.x(), c.y()));
        verts_.push_back(std::make_unique<Point<T>>(d.x(), d.y()));
        //проверка: все стороны равны и диагонали равны
        double s1 = dist(*verts_[0], *verts_[1]);
        double s2 = dist(*verts_[1], *verts_[2]);
        double s3 = dist(*verts_[2], *verts_[3]);
        double s4 = dist(*verts_[3], *verts_[0]);
        double d1 = dist(*verts_[0], *verts_[2]);
        double d2 = dist(*verts_[1], *verts_[3]);
        if (s1 <= 0 || s2 <= 0 || std::abs(s1 - s2) > 1e-6 || std::abs(s1 - s3) > 1e-6 || std::abs(d1 - d2) > 1e-6)
            throw std::invalid_argument("Square: вершины не образуют корректный квадрат (или не в порядке)");
    }

    Square(const Square& other){
        verts_.clear();
        for (const auto& p : other.verts_){
            verts_.push_back(std::make_unique<Point<T>>(p->x(), p->y()));
        }
    }

    Square(Square&& other) noexcept = default;

    Square& operator=(const Square& other){
        if (this != &other) {
            verts_.clear();
            for (const auto& p : other.verts_){
                verts_.push_back(std::make_unique<Point<T>>(p->x(), p->y()));
            }
        }
        return *this;
    }

    Square& operator=(Square&& other) noexcept = default;

    double area() const override{
        double side = dist(*verts_[0], *verts_[1]);
        return side * side;
    }

    Point<T> center() const override{
        T sx = T{}, sy = T{};
        for (const auto& p : verts_){
            sx += p->x();
            sy += p->y();
        }
        return Point<T>(sx / static_cast<T>(4), sy / static_cast<T>(4));
    }

    std::vector<std::unique_ptr<Point<T>>> vertices() const override{
        std::vector<std::unique_ptr<Point<T>>> res;
        for (const auto& p : verts_){
            res.push_back(std::make_unique<Point<T>>(p->x(), p->y()));
        }
        return res;
    }

    bool operator==(const Figure<T>& other) const override{
        const Square<T>* os = dynamic_cast<const Square<T>*>(&other);
        if (!os) return false;
        for (int i = 0; i < 4; ++i){
            if (!(*verts_[i] == *os->verts_[i])) return false;
        }
        return true;
    }

    void print(std::ostream& os) const override{
        os << "Квадрат: ";
        for (const auto& p : verts_){
            os << "(" << p->x() << ", " << p->y() << ") ";
        }
    }

    void read(std::istream& is) override{
        verts_.clear();
        verts_.resize(4);
        T x,y;
        for (int i = 0; i < 4; ++i){
            if (!(is >> x >> y)) throw std::invalid_argument("Неверные координаты для квадрата");
            verts_[i] = std::make_unique<Point<T>>(x,y);
        }
        // Проверка как в конструкторе
        double s1 = dist(*verts_[0], *verts_[1]);
        double s2 = dist(*verts_[1], *verts_[2]);
        double s3 = dist(*verts_[2], *verts_[3]);
        double d1 = dist(*verts_[0], *verts_[2]);
        double d2 = dist(*verts_[1], *verts_[3]);
        if (s1 <= 0 || std::abs(s1 - s2) > 1e-6 || std::abs(s1 - s3) > 1e-6 || std::abs(d1 - d2) > 1e-6)
            throw std::invalid_argument("Квадрат: вершины не образуют корректный квадрат");
    }
};

#endif
