#ifndef FIELD_HPP
#define FIELD_HPP

#include <QObject>
#include <QDebug>

class Checker;
class Vector2D;

class Field : public QObject
{
    Q_OBJECT
    Q_PROPERTY(int size READ size NOTIFY sizeChanged)
    Q_PROPERTY(int chekersCount READ getChekersCount NOTIFY chekersCountChanged)
    Q_PROPERTY(bool fieldReady READ isFieldReady NOTIFY fieldReadyChanged)
    Q_PROPERTY(bool whiteTeamTurn READ whiteTeamTurn NOTIFY whiteTeamTurnChanged)
    Q_PROPERTY(GameState gameState READ gameState NOTIFY gameStateChanged)

public:

    enum GameState {
        InGame,
        WhiteWin,
        BlackWin
    };
    Q_ENUM(GameState)

    explicit Field(QObject *parent = 0);

    int size() const { return m_h; }
    int getChekersCount(){ return m_checkers.count(); }
    bool isFieldReady() const { return m_fieldReady; }
    bool whiteTeamTurn() const { return m_whiteTeamTurn; }
    GameState gameState() const { return m_gameState; }

    Q_INVOKABLE Checker* getChecker(int index){ return m_checkers[index]; }

protected:
    Checker* checkerAt(int x, int y);
    Checker* checkerAt(Vector2D vector);
    void destroyChecker(Checker* ch);

    void setGameState(GameState st);
    void setWhiteTeamTurn(bool st);

signals:
    void sizeChanged(int newSize);
    void chekersCountChanged(int newCheckersCount);
    void fieldReadyChanged(bool newState);
    void whiteTeamTurnChanged(bool newState);
    void gameStateChanged(GameState newGameState);


public slots:
    bool isOnTurn();
    void setActiveChecker(Checker *checker);
    void makeTurn(int x, int y);
    void dropSelection();
    void changeCurrentSide();
    void placeCheckers();

private slots:
    void checkWin();

private:
    int m_w;
    int m_h;
    bool m_fieldReady;
    bool m_whiteTeamTurn;
    bool m_cutMode;
    QList<Checker*> m_checkers;
    Checker *m_activeChecker;
    GameState m_gameState;
};

#endif // FIELD_HPP
