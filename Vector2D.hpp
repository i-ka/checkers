#ifndef VECTOR2D_HPP
#define VECTOR2D_HPP


class Vector2D
{
public:
    Vector2D(int x, int y);
    Vector2D();

    Vector2D operator+(Vector2D other);
    Vector2D operator*(int a);
    void operator+=(Vector2D other);
    bool operator==(Vector2D other);

    int x()const{ return m_x; }
    int y()const{ return m_y; }

    bool inRange(int w, int h) const;
    Vector2D delta (Vector2D b);

private:
    int m_x;
    int m_y;
};

#endif // VECTOR2D_HPP
