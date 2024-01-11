 #include <SFML/Graphics.hpp>
#include <iostream>
#include <fstream>
#include <string.h>
#include <vector>

class Coordinate
{
    float x, y;
    public:
        Coordinate(float x, float y)
        : x(x)
        , y(y)
        {};
        float getX(){return x;}
        float getY(){return y;}

        void print()
        {
            std::cout << x << " " << y;
        }
};

class Color
{
    int r, g, b;
    public:
        Color(int r, int g, int b)
        : r(r), g(g), b(b)
        {};
        int getR(){return r;}
        int getG(){return g;}
        int getB(){return b;}
        void print()
        {
            std::cout << r << " " << g << " " << b;
        }
};

class Rectangle
{
    std::string name;
    Coordinate pos, speed, size;
    Color col;
    public:
        Rectangle(std::string name, Coordinate pos, Coordinate speed, Coordinate size, Color col)
        : name(name), pos(pos), speed(speed), size(size), col(col)
        {};
        std::string getName(){return name;}
        Coordinate getPos(){return pos;}
        Coordinate getSpeed(){return speed;}
        Coordinate getSize(){return size;}
        Color getColor(){return col;}

        void setPos(const Coordinate& p){pos = p;}
        void setSpeed(const Coordinate& s){speed = s;}

        void print()
        {
            std::cout << name << " " << "position ";
            pos.print();
            std::cout << " speed ";
            speed.print();
            std::cout << " size ";
            size.print();
            std::cout << " color ";
            col.print();
            std::cout << std::endl;
        }
};

class Circle
{
    std::string name;
    Coordinate pos, speed;
    Color col;
    float radius;
    public:
        Circle(std::string name, Coordinate pos, Coordinate speed, float radius, Color col)
        : name(name), pos(pos), speed(speed), radius(radius), col(col)
        {};
        std::string getName(){return name;}
        Coordinate getPos(){return pos;}
        Coordinate getSpeed(){return speed;}
        float getRadius(){return radius;}
        Color getColor(){return col;}

        void setPos(const Coordinate& p){pos = p;}
        void setSpeed(const Coordinate& s){speed = s;}

        void print()
        {
            std::cout << name << " " << "position ";
            pos.print();
            std::cout << " speed ";
            speed.print();
            std::cout << " radius " << radius;
            std::cout << " color ";
            col.print();
            std::cout << std::endl;
        }
};

int main()
{
    // Errors need to be handled properly

    // read config in the file
    std::ifstream fin("assignment/config.txt");
    std::string temp;

    std::vector<Rectangle> rectangles;
    std::vector<Circle> circles;

    int height, width, size;
    int r, g, b;
    float buf_float[6] = {0};
    int buf_int[3] = {0};
    std::string font_filename, name;

    while (fin >> temp)
    {
        if (temp.compare("Window")==0)
        {
            fin >> width >> height;
        }
        else if (temp.compare("Font")==0)
        {
            fin >> font_filename >> size >> r >> g >> b;
        }
        else if (temp.compare("Rectangle")==0)
        {
            fin >> name >> buf_float[0] >> buf_float[1] >> buf_float[2] >> buf_float[3];
            fin >> buf_int[0] >> buf_int[1] >> buf_int[2] >> buf_float[4] >> buf_float[5];
            Coordinate position(buf_float[0], buf_float[1]);
            Coordinate speed(buf_float[2], buf_float[3]);
            Coordinate size(buf_float[4], buf_float[5]);
            Color color(buf_int[0], buf_int[1], buf_int[2]);
            Rectangle rectangle(name, position, speed, size, color);
            rectangles.push_back(rectangle);
        }
        else if (temp.compare("Circle")==0)
        {
            fin >> name >> buf_float[0] >> buf_float[1] >> buf_float[2] >> buf_float[3];
            fin >> buf_int[0] >> buf_int[1] >> buf_int[2] >> buf_float[4];
            Coordinate position(buf_float[0], buf_float[1]);
            Coordinate speed(buf_float[2], buf_float[3]);
            Color color(buf_int[0], buf_int[1], buf_int[2]);
            Circle circle(name, position, speed, buf_float[4], color);
            circles.push_back(circle);
        }
    }

    std::cout << "Printing scene configuration\n --------------------------------------------------------- \n";
    std::cout << "Window size : height " << height << " width " << width << "\n";
    std::cout << "FOnt : file_name " << font_filename << " size " << size << " color Red " << r << " green " << g << " blue " << b << "\n";
    int count=0;
    for (auto c = circles.begin(); c != circles.end(); ++c)
    {
        count++;
        Circle circle=*c;
        std::cout << "Circle n° " << count << " : name " << circle.getName() << " position ";
        circle.getPos().print();
        std::cout << " speed ";
        circle.getSpeed().print();
        std::cout << " color ";
        circle.getColor().print();
        std::cout << " radius " << circle.getRadius() << "\n"; 
    }
    count=0;
    for (auto r = rectangles.begin(); r != rectangles.end(); ++r)
    {
        count++;
        Rectangle rectangle=*r;
        std::cout << "rectangle n° " << count << " : name " << rectangle.getName() << " position ";
        rectangle.getPos().print();
        std::cout << " speed ";
        rectangle.getSpeed().print();
        std::cout << " color ";
        rectangle.getColor().print();
        std::cout << " size ";
        rectangle.getSize().print();
        std::cout << "\n"; 
    }

    sf::RenderWindow window(sf::VideoMode(width, height), "SFML assignment 1");

    sf::Font font;
    if (!font.loadFromFile(font_filename))
    {
        std::cerr << "Error occured while loading the font file\n";
        return 1;
    }

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();
        for (auto c = circles.begin(); c != circles.end(); ++c)
        {
            Circle& circle=*c;

            sf::Text text;
            text.setFont(font);
            text.setString(circle.getName());
            text.setFillColor(sf::Color::White);
            text.setStyle(sf::Text::Bold);

            float pos_x = circle.getPos().getX();
            float pos_y = circle.getPos().getY();

            sf::CircleShape shape(circle.getRadius());
            shape.setFillColor(sf::Color(circle.getColor().getR(), circle.getColor().getG(), circle.getColor().getB()));
            shape.setPosition(sf::Vector2f(pos_x, pos_y));

            float shape_width = shape.getLocalBounds().width;
            float shape_height = shape.getLocalBounds().height;

            text.setCharacterSize(20);
            float text_width = text.getLocalBounds().width;
            float text_height = text.getLocalBounds().height;

            sf::FloatRect textBounds = text.getLocalBounds();
            text.setOrigin(textBounds.left + textBounds.width / 2.0f,
                            textBounds.top + textBounds.height / 2.0f);

            text.setPosition(sf::Vector2f(pos_x + shape_width / 2.0f,
                                          pos_y + shape_height / 2.0f));

            if (pos_x < 0 || pos_x + shape_width > width)
            {
                circle.setSpeed(Coordinate(-circle.getSpeed().getX(), circle.getSpeed().getY()));
            }
            if (pos_y < 0 || pos_y + shape_height > height)
            {
                circle.setSpeed(Coordinate(circle.getSpeed().getX(), -circle.getSpeed().getY()));
            }

            pos_x += circle.getSpeed().getX();
            pos_y += circle.getSpeed().getY();

            circle.setPos(Coordinate(pos_x, pos_y));
            window.draw(shape);
            window.draw(text);
        }

        // Rectangles
        for (auto r = rectangles.begin(); r != rectangles.end(); ++r)
        {
            Rectangle& rectangle=*r;

            sf::Text text;
            text.setFont(font);
            text.setString(rectangle.getName());
            text.setFillColor(sf::Color::White);
            text.setStyle(sf::Text::Bold);
            

            float pos_x = rectangle.getPos().getX();
            float pos_y = rectangle.getPos().getY();

            sf::RectangleShape shape(sf::Vector2f(rectangle.getSize().getX(), rectangle.getSize().getY()));
            shape.setFillColor(sf::Color(rectangle.getColor().getR(), rectangle.getColor().getG(), rectangle.getColor().getB()));
            shape.setPosition(sf::Vector2f(pos_x, pos_y));

            float shape_width = shape.getLocalBounds().width;
            float shape_height = shape.getLocalBounds().height;

            text.setCharacterSize(18);

            sf::FloatRect textBounds = text.getLocalBounds();
            text.setOrigin(textBounds.left + textBounds.width / 2.0f,
                            textBounds.top + textBounds.height / 2.0f);

            text.setPosition(sf::Vector2f(pos_x + shape_width / 2.0f,
                                          pos_y + shape_height / 2.0f));

            if (pos_x < 0 || pos_x + shape_width > width)
            {
                rectangle.setSpeed(Coordinate(-rectangle.getSpeed().getX(), rectangle.getSpeed().getY()));
            }
            if (pos_y < 0 || pos_y + shape_height > height)
            {
                rectangle.setSpeed(Coordinate(rectangle.getSpeed().getX(), -rectangle.getSpeed().getY()));
            }

            pos_x += rectangle.getSpeed().getX();
            pos_y += rectangle.getSpeed().getY();

            rectangle.setPos(Coordinate(pos_x, pos_y));

            window.draw(shape);
            window.draw(text);
        }
        window.display();
    }
    
    return 0;
}