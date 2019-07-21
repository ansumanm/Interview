#include<iostream>
#include<sstream>
using namespace std;

class Shape {
    public:
        virtual string str() const = 0;
};

/* Circle class */
class Circle: public Shape {
    private:
        float radius;

    public:
        Circle() {}
        ~Circle() {}

        Circle(float radius): radius(radius) {}

        string str() const {
            ostringstream oss;

            oss << "This is a circle of radius "
                << radius
                << endl;
            return oss.str();
        }

        void resize(float factor) {
            radius *= factor;
        }
};

/* Square class */
class Square: public Shape {
    private:
        float size;

    public:
        Square() {}
        ~Square() {}

        Square(float size): size(size) {}

        string str() const {
            ostringstream oss;

            oss << "This is a square with side "
                << size
                << endl;
            return oss.str();
        }
};

/* Decorator pattern: Enhance the Shape to add a Color */
template <typename T>
class ColoredShape: public T
{
    /* To check:
    static_assert(is_base_of<Shape, T>::value,
           "Template argument must be a Shape" );
           */
    string color;

    public:
    /* Need to declare variadic template constructor */
    template <typename... Args>
    ColoredShape(const string& color, Args ...args)
    : T(std::forward<Args>(args)...), color(color) {}

    string str() const {
        ostringstream oss;

        oss << T::str()
            << "Has a color " << color
            << endl;

        return oss.str();
    }
};

template <typename T>
class TransparentShape: public T
{
    float transparency;

    public:
    /* Constructor using variadic template. */
    template <typename... Args>
    TransparentShape(float t, Args ...args)
    : T(std::forward<Args>(args)...), transparency(t) {}

    string str() const {
        ostringstream oss;

        oss << T::str()
            << "Has a transparency " << transparency
            << endl;

        return oss.str();
    }
};

int main() 
{
    ColoredShape<Circle> green_circle("green", 5);
    green_circle.resize(1.5);

    cout << green_circle.str();

    TransparentShape<ColoredShape<Square>> t_c_square(2.5, "blue", 10);
    cout << t_c_square.str();

    return 0;
}
