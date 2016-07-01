#ifndef CHECKER_HPP
#define CHECKER_HPP

#include <QObject>
#include "Vector2D.hpp"

class Checker : public QObject
{
    Q_OBJECT

    Q_PROPERTY(int x READ x NOTIFY xChanged)
    Q_PROPERTY(int y READ y NOTIFY yChanged)
    Q_PROPERTY(Side side READ side NOTIFY sideChanged)
    Q_PROPERTY(bool isActive READ isActive NOTIFY isActiveChanged)
    Q_PROPERTY(bool isKing READ isKing NOTIFY isKingChanged)

public:
    enum Side{
        Black,
        White
    };
    Q_ENUM(Side)
    explicit Checker(QObject *parent = 0);
    explicit Checker(int x, int y, Side side, QObject *parent = 0);

    int x() const { return m_position.x(); }
    int y() const { return m_position.y(); }
    Vector2D pos() const { return m_position; }

    Side side() const { return m_side; }
    bool isActive() const { return m_active; }
    bool isKing() const { return m_isKing; }
    void makeKing();
    void setActive(bool active);
    void move(int x, int y);
    void move(Vector2D newpos);

signals:
    void xChanged(int newX);
    void yChanged(int newY);
    void isActiveChanged(bool active);
    void sideChanged(Side newSide);
    void isKingChanged(bool newState);

public slots:

private:
    Vector2D m_position;
    bool m_active;
    Side m_side;
    bool m_isKing;
};

#endif // CHECKER_HPP
