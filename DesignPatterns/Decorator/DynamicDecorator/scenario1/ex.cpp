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
class ColoredShape: public Shape {
    private:
        Shape &shape; /* Aggregate the base class. */
        string color;

    public:
        ColoredShape(Shape& shape,const string& color): shape(shape), color(color) {}

        string str() const {
            ostringstream oss;

            oss << shape.str()
                << ", has a color " << color
                << endl;

            return oss.str();
        }
};

/* Decorator pattern: Enhance the Shape to add transparency */
class TransparentShape: public Shape {
    Shape &shape;
    unsigned char transparency;

    public:
    TransparentShape(Shape &shape, unsigned char t): shape(shape), transparency(t) {}

    string str() const {
        ostringstream oss;
        oss << shape.str()
            << ", has a transparency " << static_cast<float>(transparency)
            << endl;

        return oss.str();
    }
};

int main() 
{
    Circle circle(5);
    Square square(5);
    cout << circle.str() << endl;

    cout << square.str() << endl;

    ColoredShape red_square(square, "red");
    cout << red_square.str() << endl;

    TransparentShape t_square(square, 8);
    cout << t_square.str() << endl;

    TransparentShape t_red_square(red_square, 10);
    cout << t_red_square.str() << endl;

    ColoredShape yellow_t_square(t_square, "yellow");
    cout << yellow_t_square.str() << endl;

    return 0;
}
