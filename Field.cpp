#include "Field.hpp"
#include "Checker.hpp"

#include <QDebug>

Field::Field(QObject *parent) : QObject(parent)
{
    m_w = 8;
    m_h = 8;
    m_activeChecker = 0;
    m_whiteTeamTurn = true;
    m_cutMode = false;
    placeCheckers();
    m_gameState = InGame;
}

Checker *Field::checkerAt(int x, int y)
{
    if (!Vector2D(x, y).inRange(m_w, m_h)) {
        return 0;
    }
    for (Checker* ch : m_checkers) {
        if (ch->x() == x && ch->y() == y) { return ch; }
    }
    return 0;
}

Checker *Field::checkerAt(Vector2D vector)
{
    if(!vector.inRange(m_w, m_h)){
        return 0;
    }
    for (Checker* ch : m_checkers) {
        if (ch->pos() == vector) { return ch; }
    }
    return 0;
}

void Field::destroyChecker(Checker *ch)
{
    m_checkers.removeOne(ch);
    emit chekersCountChanged(m_checkers.count());
    delete ch;
}

void Field::setGameState(Field::GameState st)
{
    if(m_gameState == st){ return; }
    m_gameState = st;
    emit gameStateChanged(m_gameState);
}

void Field::setWhiteTeamTurn(bool st)
{
    if(m_whiteTeamTurn == st){ return; }
    m_whiteTeamTurn = st;
    emit whiteTeamTurnChanged(m_whiteTeamTurn);
}

bool Field::isOnTurn()
{
    return m_activeChecker != 0;
}

void Field::placeCheckers()
{
    m_fieldReady = false;
    emit fieldReadyChanged(m_fieldReady);
    for (Checker* ch : m_checkers) {
        destroyChecker(ch);
    }
    for (int y = 0; y < 3; y++) {
        for (int x = 0; x < 8; x++) {
            if (y%2==0) {
                if (x%2==0) {
                    m_checkers.append(new Checker(x, y, Checker::White));
                }
            } else {
                if (x%2!=0) {
                    m_checkers.append(new Checker(x, y, Checker::White));
                }
            }
        }
    }
    for (int y = 5; y < 8; y++) {
        for (int x = 0; x < 8; x++) {
            if (y%2 == 0) {
                if (x%2 == 0) {
                    m_checkers.append(new Checker(x, y ,Checker::Black));
                }
            } else {
                if(x%2!=0) {
                    m_checkers.append(new Checker(x, y, Checker::Black));
                }
            }
        }
    }
    setGameState(InGame);
    setWhiteTeamTurn(true);
    emit chekersCountChanged(m_checkers.count());
    m_fieldReady = true;
    emit fieldReadyChanged(m_fieldReady);
}

void Field::checkWin()
{
    bool blackWin = true;
    bool whiteWin = true;
    for (Checker* ch : m_checkers) {
        if (ch->side() == Checker::Black) {
            whiteWin = false;
        } else {
            blackWin = false;
        }
        if (!blackWin && !whiteWin) {
            break;
        }
    }
    if (blackWin) {
        setGameState(BlackWin);
        qDebug() << "Black WIN";;
    } else if (whiteWin) {
        setGameState(WhiteWin);
        qDebug() << "White WIN";
    }
}

void Field::setActiveChecker(Checker *checker)
{
    if (isOnTurn()) { return; }
    if (checker->side() == Checker::White && !m_whiteTeamTurn) { return; }
    if (checker->side() == Checker::Black && m_whiteTeamTurn) { return; }
    if (m_cutMode) { return; }
    m_activeChecker = checker;
    m_activeChecker->setActive(true);
}

void Field::makeTurn(int x, int y)
{
    if(!isOnTurn()) { return; }

    Vector2D moveVector(x, y);
    Vector2D deltaMove = moveVector.delta(m_activeChecker->pos());

    QVector<Vector2D> dirrections;
    dirrections.append(Vector2D(1,1));
    dirrections.append(Vector2D(1,-1));
    dirrections.append(Vector2D(-1,1));
    dirrections.append(Vector2D(-1,-1));

    bool turnSuccess = false;
    int possibleCuts = 0;
    if (!m_activeChecker->isKing()) {
        if (!m_cutMode) {
            if (m_activeChecker->side() == Checker::Black) {
                if ((deltaMove == dirrections[3] || deltaMove == dirrections[1]) && checkerAt(moveVector) == 0) {
                    m_activeChecker->move(moveVector);
                    turnSuccess = true;
                }
            }
            if (m_activeChecker->side() == Checker::White) {
                if ((deltaMove == dirrections[2] || deltaMove == dirrections[0]) && checkerAt(moveVector) == 0){
                    m_activeChecker->move(moveVector);
                    turnSuccess = true;
                }
            }
        }
        for (Vector2D dir : dirrections) {
            Vector2D dest = m_activeChecker->pos() + dir;
            if (checkerAt(dest) != 0 && checkerAt(dest + dir) == 0) {
                if (checkerAt(dest)->side() != m_activeChecker->side() && moveVector == dest + dir) {
                    m_activeChecker->move(moveVector);
                    destroyChecker(checkerAt(dest));
                    turnSuccess = true;
                    m_cutMode = true;
                }
            }
        }
        if (m_cutMode) {
            for (Vector2D dir : dirrections) {
                Vector2D dest = m_activeChecker->pos() + dir;
                if (checkerAt(dest) != 0 && checkerAt(dest + dir) == 0 && (dest + dir).inRange(m_w, m_h)) {
                    if (checkerAt(dest)->side() != m_activeChecker->side()) {
                        possibleCuts++;
                    }
                }
            }
        }
    } else {
        for (Vector2D dir : dirrections) {
            if (turnSuccess) { break; }
            Vector2D curDest = m_activeChecker->pos() + dir;
            bool blocked = false;
            bool canCut = false;
            Checker* checkerToCut = 0;
            while (curDest.inRange(m_w, m_h) && !blocked){
                if(checkerAt(curDest) != 0){
                    if(checkerAt(curDest)->side() == m_activeChecker->side()){
                        break;
                    }
                    if (canCut){
                        blocked = true;
                    }
                    if(checkerAt(curDest + dir) == 0){
                        checkerToCut = checkerAt(curDest);
                        canCut = true;
                    } else {
                        blocked = true;
                    }
                }
                if (curDest == moveVector && checkerAt(curDest) == 0){
                    m_activeChecker->move(moveVector);
                    if (checkerToCut != 0) {
                        destroyChecker(checkerToCut);
                        m_cutMode = true;
                    }
                    turnSuccess = true;
                    break;
                }
                curDest+=dir;
            }
        }

        for (Vector2D dir : dirrections) {
            Vector2D curDest = m_activeChecker->pos() + dir;
            bool blocked = false;
            bool canCut = false;
            while (curDest.inRange(m_w, m_h) && !blocked){
                if(checkerAt(curDest) != 0){
                    if(checkerAt(curDest)->side() == m_activeChecker->side()){
                        break;
                    }
                    if (canCut){
                        blocked = true;
                    }
                    if(checkerAt(curDest + dir) == 0  && (curDest + dir).inRange(m_w, m_h)){
                        possibleCuts ++;
                        canCut = true;
                    } else {
                        blocked = true;
                    }
                }
                curDest+=dir;
            }
        }
    }
    if (possibleCuts == 0){
        m_cutMode = false;
    }
    if ((m_activeChecker->side() == Checker::Black && m_activeChecker->y() == 0) ||
            (m_activeChecker->side()==Checker::White && m_activeChecker->y() == 7)) {
        m_activeChecker->makeKing();
    }
    if (turnSuccess && !m_cutMode){
        dropSelection();
        changeCurrentSide();
    }
    checkWin();
}

void Field::dropSelection()
{
    if (!isOnTurn()){ return; }
    if (m_cutMode){
        changeCurrentSide();
    }
    m_activeChecker->setActive(false);
    m_activeChecker = 0;
}

void Field::changeCurrentSide()
{
    m_cutMode = false;
    m_whiteTeamTurn = !m_whiteTeamTurn;
    emit whiteTeamTurnChanged(m_whiteTeamTurn);
}
