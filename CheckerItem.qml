import QtQuick 2.0
import GameComponents 1.0

Rectangle{
    property Checker checker: null
    property int size: 64
    x: checker.x*size
    y: checker.y*size
    width:size
    height: width
    radius: width
    color: (checker.side === Checker.White)?"white":"black"
    border.width: 5
    border.color: checker.isActive?"red":"grey"
    Rectangle{
        visible: checker.isKing
        width: parent.width/2
        height: width
        radius: width
        anchors.centerIn: parent
        color: "#f3d702"
    }
}
