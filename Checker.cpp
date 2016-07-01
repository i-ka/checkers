#include "Checker.hpp"

Checker::Checker(QObject *parent):
    QObject(parent),
    m_position(Vector2D(0,0))
{

}

Checker::Checker(int x, int y, Side side, QObject *parent) :
    QObject(parent),
    m_position(Vector2D(x, y)),
    m_side(side)
{
    m_active = false;
    m_isKing = false;
}

void Checker::makeKing()
{
    if(m_isKing){ return; }
    m_isKing = true;
    emit isKingChanged(m_isKing);
}

void Checker::setActive(bool active)
{
    if(m_active == active)return;
    m_active = active;

    emit isActiveChanged(m_active);
}

void Checker::move(int x, int y)
{
    m_position = Vector2D(x, y);
    emit xChanged(m_position.x());
    emit yChanged(m_position.y());
}

void Checker::move(Vector2D newpos)
{
    m_position = newpos;
    emit xChanged(m_position.x());
    emit yChanged(m_position.y());
}
