#ifndef RECTANGLE_H
#define RECTANGLE_H

#include "figure.h"
#include <cmath>
#include <stdexcept>
#include <vector>
#include <memory>

template<Scalar T>
class Rectangle : public Figure<T> {
private:
    std::vector<std::unique_ptr<Point<T>>> verts_;

    static double dist(const Point<T>& a, const Point<T>& b){
        double dx = static_cast<double>(a.x() - b.x());
        double dy = static_cast<double>(a.y() - b.y());
        return std::sqrt(dx*dx + dy*dy);
    }

    static double dot(const Point<T>& a, const Point<T>& b, const Point<T>& c){
        double ax = static_cast<double>(b.x() - a.x());
        double ay = static_cast<double>(b.y() - a.y());
        double bx = static_cast<double>(c.x() - b.x());
        double by = static_cast<double>(c.y() - b.y());
        return ax*bx + ay*by;
    }

public:
    Rectangle(){
        verts_.resize(4);
        for (int i = 0; i < 4; ++i){
            verts_[i] = std::make_unique<Point<T>>(T{}, T{});
        }
    }

    Rectangle(const Point<T>& a, const Point<T>& b, const Point<T>& c, const Point<T>& d){
        verts_.clear();
        verts_.push_back(std::make_unique<Point<T>>(a.x(), a.y()));
        verts_.push_back(std::make_unique<Point<T>>(b.x(), b.y()));
        verts_.push_back(std::make_unique<Point<T>>(c.x(), c.y()));
        verts_.push_back(std::make_unique<Point<T>>(d.x(), d.y()));
        // Проверка: противоположные стороны равны и углы 90 градусов
        double s1 = dist(*verts_[0], *verts_[1]);
        double s2 = dist(*verts_[1], *verts_[2]);
        double s3 = dist(*verts_[2], *verts_[3]);
        double s4 = dist(*verts_[3], *verts_[0]);
        if(std::abs(s1 - s3) > 1e-6 || std::abs(s2 - s4) > 1e-6){
            throw std::invalid_argument("Rectangle: противоположные стороны не равны");
        }            
        double dotp = dot(*verts_[0], *verts_[1], *verts_[2]);
        if(std::abs(dotp) > 1e-6) throw std::invalid_argument("Rectangle: соседние стороны не перпендикулярны");
    }

    Rectangle(const Rectangle& other){
        verts_.clear();
        for (const auto& p : other.verts_){
            verts_.push_back(std::make_unique<Point<T>>(p->x(), p->y()));
        }
    }

    Rectangle(Rectangle&& other) noexcept = default;

    Rectangle& operator=(const Rectangle& other){
        if (this != &other) {
            verts_.clear();
            for (const auto& p : other.verts_){
                verts_.push_back(std::make_unique<Point<T>>(p->x(), p->y()));
            }
        }
        return *this;
    }
    Rectangle& operator=(Rectangle&& other) noexcept = default;

    double area() const override{
        double w = dist(*verts_[0], *verts_[1]);
        double h = dist(*verts_[1], *verts_[2]);
        return w * h;
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
        const Rectangle<T>* orr = dynamic_cast<const Rectangle<T>*>(&other);
        if (!orr) return false;
        for (int i = 0; i < 4; ++i){
            if (!(*verts_[i] == *orr->verts_[i])){
                return false;
            }
        }
        return true;
    }

    void print(std::ostream& os) const override{
        os << "Прямоугольник: ";
        for (const auto& p : verts_){
            os << "(" << p->x() << ", " << p->y() << ") ";
        }
    }

    void read(std::istream& is) override{
        verts_.clear();
        verts_.resize(4);
        T x,y;
        for (int i = 0; i < 4; ++i){
            if (!(is >> x >> y)) throw std::invalid_argument("Неверные координаты для прямоугольника");
            verts_[i] = std::make_unique<Point<T>>(x,y);
        }
        double s1 = dist(*verts_[0], *verts_[1]);
        double s2 = dist(*verts_[1], *verts_[2]);
        double s3 = dist(*verts_[2], *verts_[3]);
        double s4 = dist(*verts_[3], *verts_[0]);
        if (std::abs(s1 - s3) > 1e-6 || std::abs(s2 - s4) > 1e-6){
            throw std::invalid_argument("Прямоугольник: противоположные стороны не равны");
        }
        double dotp = dot(*verts_[0], *verts_[1], *verts_[2]);
        
        if (std::abs(dotp) > 1e-6) throw std::invalid_argument("Прямоугольник: соседние стороны не перпендикулярны");
    }
};

#endif
