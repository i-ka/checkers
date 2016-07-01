import QtQuick 2.5
import GameComponents 1.0

Column{
    width: gameField.width
    height: gameField.height + gameInfo.height
    Row{
        id: gameInfo
        height:  60
        width: parent.width
        Text{
            width: parent.width/3
            height: parent.height
            text:{
                if(field.gameState == Field.InGame){
                    return field.whiteTeamTurn?"White turns":"Black turns"
                } else {
                    if(field.gameState == Field.BlackWin){
                        return "Black wins! Press red button to restart the game"
                    } else if (field.gameState == Field.WhiteWin) {
                        return "White wins! Press red button to restart the game"
                    }
                }
            }
            font.pixelSize: height*0.25
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
            wrapMode: Text.WordWrap
        }
        Rectangle{
            width: parent.width/3
            height: parent.height
            color: "#06f927"
            border.color: "#000000"
            Text{
                anchors.fill:parent
                text:"Drop Selection"
                font.pixelSize: height/3
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
            }
            MouseArea{
                anchors.fill: parent
                onClicked: field.dropSelection()
            }
        }
        Rectangle{
            width: parent.width/3
            height: parent.height
            color: "#ff0004"
            border.color: "black"
            Text{
                anchors.fill:parent
                text:"Start New Game"
                font.pixelSize: height/3
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
            }
            MouseArea{
                anchors.fill: parent
                onClicked: field.placeCheckers()
            }
        }
    }
    Item {
        id:gameField
        width: fieldGrid.width
        height: fieldGrid.height
        Field{
            id:field
        }
        Grid{
            id: fieldGrid
            columns: field.size
            rows:field.size
            property int cellSize: 86
            Repeater{
                model: field.size*field.size
                Rectangle{
                    property int row: Math.floor(index/field.size)
                    property int col: index%field.size
                    width:fieldGrid.cellSize
                    height: width
                    color: {
                        if(row % 2 == 0) {
                            if(col % 2 == 0) {
                                return "black"
                            } else {
                                return "white"
                            }
                        } else {
                            if(col % 2 != 0) {
                                return "black"
                            } else {
                                return "white"
                            }
                        }
                    }

                    border.color: "black"
                    MouseArea{
                        anchors.fill: parent
                        acceptedButtons: Qt.LeftButton | Qt.RightButton
                        onClicked: {
                            if (mouse.button == Qt.LeftButton){
                                field.makeTurn(col, row)
                            }
                            if(mouse.button == Qt.RightButton){
                                field.dropSelection()
                            }
                        }
                    }
                }

            }
        }
        Repeater{
            model: field.fieldReady?field.chekersCount:0
            CheckerItem {
                checker: field.getChecker(index)
                size:fieldGrid.cellSize
                MouseArea{
                    anchors.fill: parent
                    acceptedButtons: Qt.LeftButton | Qt.RightButton
                    onClicked: {
                        if(mouse.button == Qt.LeftButton){
                            if(field.isOnTurn()){
                                field.makeTurn(checker.x, checker.y)
                            }else{
                                field.setActiveChecker(checker)
                            }
                        }
                        if(mouse.button == Qt.RightButton){
                            field.dropSelection()
                        }
                    }
                }
            }
        }
    }
}
