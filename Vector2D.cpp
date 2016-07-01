#include "Vector2D.hpp"

Vector2D::Vector2D(int x, int y)
{
    m_x = x;
    m_y = y;
}

Vector2D::Vector2D():
    m_x(0),
    m_y(0)
{

}

Vector2D Vector2D::operator+(Vector2D other)
{
    return Vector2D(m_x + other.x(), m_y + other.y());
}

Vector2D Vector2D::operator*(int a)
{
    return Vector2D(m_x * a, m_y*a);
}

void Vector2D::operator+=(Vector2D other)
{
    m_x += other.x();
    m_y += other.y();
}

bool Vector2D::operator==(Vector2D other)
{
    return m_x == other.x() && m_y == other.y();
}

bool Vector2D::inRange(int w, int h) const
{
    return (m_x < w && m_y < h && m_y >= 0 && m_x >= 0);
}

Vector2D Vector2D::delta(Vector2D b)
{
    return Vector2D(m_x - b.x(), m_y - b.y());
}
