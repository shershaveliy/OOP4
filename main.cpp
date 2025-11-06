#include <iostream>
#include <memory>
#include <limits>
#include <iomanip>

#include "include/point.h"
#include "include/figure.h"
#include "include/triangle.h"
#include "include/square.h"
#include "include/rectangle.h"
#include "include/array.h"

void printMenu() {
    std::cout << "\n=== ГЛАВНОЕ МЕНЮ ===\n";
    std::cout << "1. Добавить фигуру (через вершины)\n";
    std::cout << "2. Показать все фигуры (центр, вершины, площадь)\n";
    std::cout << "3. Общая площадь всех фигур\n";
    std::cout << "4. Удалить фигуру по индексу\n";
    std::cout << "5. Вывести тестовый массив squares (Array<Square<double>>)\n";
    std::cout << "6. Очистить список фигур\n";
    std::cout << "0. Выход\n";
    std::cout << "Выберите пункт: ";
}

template<typename T>
double totalArea(const Array<std::shared_ptr<Figure<T>>>& arr){
    double sum = 0.0;
    for (std::size_t i = 0; i < arr.size(); ++i){
        if (arr[i]) sum += arr[i]->area();
    }
    return sum;
}

template<typename T>
void printAll(const Array<std::shared_ptr<Figure<T>>>& arr){
    if(arr.empty()){
        std::cout << "Список фигур пуст.\n";
        return;
    }
    std::cout << std::fixed << std::setprecision(6);
    for(std::size_t i = 0; i < arr.size(); ++i){
        const auto& f = arr[i];
        std::cout << "\nИндекс: " << i << "\n";
        f->print(std::cout);
        auto c = f->center();
        std::cout << "\n  Центр: (" << c.x() << ", " << c.y() << ")\n";
        std::cout << "  Площадь: " << f->area() << "\n";

        auto verts = f->vertices();
        std::cout << "  Вершины:";
        for (const auto& p : verts) std::cout << " (" << p->x() << ", " << p->y() << ")";
        std::cout << "\n";
    }
}

int main(){
    Array<std::shared_ptr<Figure<double>>> figures;

    try{
        auto tri = std::make_shared<Triangle<double>>(
            Point<double>(0.0, 0.0),
            Point<double>(2.0, 0.0),
            Point<double>(1.0, 2.0)
        );
        figures.push_back(tri);

        auto sq = std::make_shared<Square<double>>(
            Point<double>(0.0, 0.0),
            Point<double>(0.0, 2.0),
            Point<double>(2.0, 2.0),
            Point<double>(2.0, 0.0)
        );
        figures.push_back(sq);

        auto rect = std::make_shared<Rectangle<double>>(
            Point<double>(0.0, 0.0),
            Point<double>(3.0, 0.0),
            Point<double>(3.0, 1.0),
            Point<double>(0.0, 1.0)
        );
        figures.push_back(rect);

    } catch (const std::exception& e) {
        std::cerr << "Ошибка при создании фигур: " << e.what() << "\n";
        return 1;
    }

    std::cout << "Добавлены 3 фигуры по умолчанию (вершины заданы).\n";

    Array<Square<double>> squares;

    squares.push_back(Square<double>(
        Point<double>(0.0, 0.0),
        Point<double>(0.0, 2.0),
        Point<double>(2.0, 2.0),
        Point<double>(2.0, 0.0)
    ));
    squares.push_back(Square<double>(
        Point<double>(1.0, 1.0),
        Point<double>(1.0, 3.0),
        Point<double>(3.0, 3.0),
        Point<double>(3.0, 1.0)
    ));

    while (true){
        printMenu();
        int choice;
        if (!(std::cin >> choice)){
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Неверный ввод. Попробуйте снова.\n";
            continue;
        }

        if (choice == 0) break;

        switch (choice){
            case 1:{
                std::cout << "Выберите тип фигуры:\n1 - Треугольник (3 вершины)\n2 - Квадрат (4 вершины)\n3 - Прямоугольник (4 вершины)\nВыбор: ";
                int t;
                std::cin >> t;
                try{
                    if (t == 1){
                        std::cout << "Введите 3 вершины (x y) по очереди:\n";
                        double x,y;
                        Point<double> a,b,c;
                        std::cin >> x >> y; a = Point<double>(x,y);
                        std::cin >> x >> y; b = Point<double>(x,y);
                        std::cin >> x >> y; c = Point<double>(x,y);
                        auto p = std::make_shared<Triangle<double>>(a,b,c);
                        figures.push_back(std::move(p));
                        std::cout << "Треугольник добавлен.\n";
                    }
                    else if (t == 2){
                        std::cout << "Введите 4 вершины квадрата (x y) по очереди:\n";
                        double x,y;
                        Point<double> a,b,c,d;
                        std::cin >> x >> y; a = Point<double>(x,y);
                        std::cin >> x >> y; b = Point<double>(x,y);
                        std::cin >> x >> y; c = Point<double>(x,y);
                        std::cin >> x >> y; d = Point<double>(x,y);
                        auto p = std::make_shared<Square<double>>(a,b,c,d);
                        figures.push_back(std::move(p));
                        std::cout << "Квадрат добавлен.\n";
                    }
                    else if (t == 3){
                        std::cout << "Введите 4 вершины прямоугольника (x y) по очереди:\n";
                        double x,y;
                        Point<double> a,b,c,d;
                        std::cin >> x >> y; a = Point<double>(x,y);
                        std::cin >> x >> y; b = Point<double>(x,y);
                        std::cin >> x >> y; c = Point<double>(x,y);
                        std::cin >> x >> y; d = Point<double>(x,y);
                        auto p = std::make_shared<Rectangle<double>>(a,b,c,d);
                        figures.push_back(std::move(p));
                        std::cout << "Прямоугольник добавлен.\n";
                    }
                    else{
                        std::cout << "Неверный тип фигуры.\n";
                    }
                }
                catch (const std::exception& e) {
                    std::cout << "Ошибка при добавлении фигуры: " << e.what() << "\n";
                }
                break;
            }

            case 2:
                printAll(figures);
                break;

            case 3:
                std::cout << "Общая площадь: " << totalArea(figures) << "\n";
                break;

            case 4:{
                std::cout << "Введите индекс удаляемой фигуры (0 - " << (figures.size() ? figures.size()-1 : 0) << "): ";
                std::size_t idx;
                if (!(std::cin >> idx)){
                    std::cout << "Неверный индекс ввода\n";
                    std::cin.clear();
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                }
                else{
                    try{
                        figures.erase(idx);
                        std::cout << "Фигура " << idx << " удалена.\n";
                    } catch (const std::exception& e) {
                        std::cout << "Ошибка: " << e.what() << "\n";
                    }
                }
                break;
            }
            
            case 5:{
                std::cout << "Содержимое массива squares (Array<Square<double>>):\n";
                for (std::size_t i = 0; i < squares.size(); ++i) {
                    std::cout << "Квадрат #" << i << ":\n";
                    squares[i].print(std::cout);
                    std::cout << "Площадь: " << static_cast<double>(squares[i]) << "\n";
                    std::cout << "Центр: " << squares[i].center() << "\n\n";
                }
                break;
            }

            case 6:{
                while (!figures.empty()) figures.erase(0);
                std::cout << "Список фигур очищен.\n";
                break;
            }            

            default:
                std::cout << "Неверный пункт меню.\n";
                break;
        }
    }

    std::cout << "Выход из программы.\n";
    return 0;
}
