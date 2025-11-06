#ifndef TRIANGLE_H
#define TRIANGLE_H

#include "figure.h"
#include <cmath>
#include <stdexcept>
#include <vector>
#include <memory>


// Triangle<T> — хранит 3 вершины как unique_ptr<Point<T>>.
template<Scalar T>
class Triangle : public Figure<T> {
private:
    std::vector<std::unique_ptr<Point<T>>> verts_;
    //Площадь по координатам
    static double areaByCoords(const Point<T>& a, const Point<T>& b, const Point<T>& c) {
        double x1 = static_cast<double>(a.x()), y1 = static_cast<double>(a.y());
        double x2 = static_cast<double>(b.x()), y2 = static_cast<double>(b.y());
        double x3 = static_cast<double>(c.x()), y3 = static_cast<double>(c.y());
        return std::abs((x1*(y2-y3) + x2*(y3-y1) + x3*(y1-y2)) / 2.0);
    }

public:
    //Инициализация нулевыми точками
    Triangle(){
        verts_.resize(3);
        for (int i = 0; i < 3; ++i){
            verts_[i] = std::make_unique<Point<T>>(T{}, T{});
        }
    }
    //Конструктор из 3-х точек
    Triangle(const Point<T>& a, const Point<T>& b, const Point<T>& c){
        verts_.clear();
        verts_.push_back(std::make_unique<Point<T>>(a.x(), a.y()));
        verts_.push_back(std::make_unique<Point<T>>(b.x(), b.y()));
        verts_.push_back(std::make_unique<Point<T>>(c.x(), c.y()));
        if (areaByCoords(*verts_[0], *verts_[1], *verts_[2]) <= 0.0)
            throw std::invalid_argument("Triangle: вершины коллинеарны или неверны");
    }

    //Конструктор копирования
    Triangle(const Triangle& other){
        verts_.clear();
        for (const auto& p : other.verts_){
            verts_.push_back(std::make_unique<Point<T>>(p->x(), p->y()));
        }
    }
    //Перемещающий конструктор
    Triangle(Triangle&& other) noexcept = default;

    //Оператор присваивания копированием
    Triangle& operator=(const Triangle& other){
        if (this != &other){
            verts_.clear();
            for (const auto& p : other.verts_){
                verts_.push_back(std::make_unique<Point<T>>(p->x(), p->y()));
            }
        }
        return *this;
    }
    //Move-assign по умолчанию
    Triangle& operator=(Triangle&& other) noexcept = default;

    //Площадь — используем вспомогательную функцию
    double area() const override{
        return areaByCoords(*verts_[0], *verts_[1], *verts_[2]);
    }
    //Центр — среднее по координатам вершин
    Point<T> center() const override {
        T cx = (verts_[0]->x() + verts_[1]->x() + verts_[2]->x()) / static_cast<T>(3);
        T cy = (verts_[0]->y() + verts_[1]->y() + verts_[2]->y()) / static_cast<T>(3);
        return Point<T>(cx, cy);
    }
    //Возвращаем копии вершин (unique_ptr)
    std::vector<std::unique_ptr<Point<T>>> vertices() const override{
        std::vector<std::unique_ptr<Point<T>>> res;
        for (const auto& p : verts_){
            res.push_back(std::make_unique<Point<T>>(p->x(), p->y()));
        }
        return res;
    }
    //Сравнение — приводим other к Triangle через dynamic_cast и сравниваем вершины????
    bool operator==(const Figure<T>& other) const override{
        const Triangle<T>* ot = dynamic_cast<const Triangle<T>*>(&other);
        if (!ot) return false;
        for (int i = 0; i < 3; ++i){
            if (!(*verts_[i] == *ot->verts_[i])) return false;
        }
        return true;
    }

    void print(std::ostream& os) const override{
        os << "Треугольник: ";
        for (const auto& p : verts_){
            os << "(" << p->x() << ", " << p->y() << ") ";
        }
    }

    void read(std::istream& is) override{
        verts_.clear();
        verts_.resize(3);
        T x, y;
        for (int i = 0; i < 3; ++i){
            if (!(is >> x >> y)) throw std::invalid_argument("Неверные координаты для треугольника");
            verts_[i] = std::make_unique<Point<T>>(x, y);
        }
        if (area() <= 0.0) throw std::invalid_argument("Треугольник: точки коллинеарны");
    }
};

#endif
