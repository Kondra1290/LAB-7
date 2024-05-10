import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import QtQuick.Dialogs
import Qt.labs.qmlmodels
import QtQuick.Controls.Material
import ListModel

Window {
    visible: true
        width: 1200
        height: 480
        title: qsTr("Hello World")

        ColumnLayout {
            anchors.fill: parent
            anchors.margins: 0
            /*
            HorizontalHeaderView {
                id: horizontalHeader0
                anchors.left: rowLayout.left
                //anchors.top: parent.top
                syncView: rowLayout
                clip: true
                model: ["Книга", "Автор", "Жанр", "Публикаия", "Цена", "Кличество"]
                //model: ["Книга", "Автор", "Жанр", "Публикаия", "Цена", "Кличество"]
            }*/
            RowLayout {
                id: rowLayout
                anchors.top: parent.top
                anchors.left: parent.left
                anchors.right: parent.right
                anchors.margins: 5

                spacing: 10

                Text {text: qsTr("Книга")}
                TextField { id: bookField}
                Text {text: qsTr("Автор")}
                TextField { id: authorField}
                Text {text: qsTr("Жанр")}
                TextField { id: genreField}
                Text {text: qsTr("Цена")}
                TextField {
                    id: priceField
                    inputMask: "9999.99"
                }
                Text { text: qsTr("Количество")}
                TextField {
                    id: amountField
                    inputMask: "999999"
                }

                Button {
                    text: qsTr("Дабавить")

                    onClicked: {
                        sqlitedatabase.inserIntoTable(bookField.text, authorField.text, genreField.text, priceField.text, amountField.text)
                        myModel.updateModel()
                        bookField.text = "";
                        authorField.text = "";
                        genreField.text = "";
                        priceField.text = "";
                        amountField.text = "";
                    }
                }

                Button {
                    text: 'Изменить'
                    id:editButton
                    width: 80
                    height: 25
                    //Layout.fillWidth: true
                    onClicked: {
                        if (tableView.selectedId != -1){
                            editForm.note_id = tableView.selectedId

                            bookChange.text = bookField.text
                            authorChange.text = authorField.text
                            genreChange.text = genreField.text
                            priceChange.text = priceField.text
                            amountChange.text = amountField.text

                            editForm.open();
                        } else {
                            console.log('sdf');
                        }
                    }
                }

                Button {
                    width: 80
                    text: qsTr("Удалить")
                    onClicked: {
                        dialogDelete.open()
                    }
                }
            }

            RowLayout {
                id: filter
                //anchors.left: parent.left
                //anchors.margins: 5

                spacing: 10

                Text {text: qsTr("")}
                TextField { id: filtField}

                Button {
                    text: 'Поиск'
                    id: findButton
                    width: 80
                    height: 25
                    //Layout.fillWidth: true
                    onClicked: {
                        myModel.search(filtField.text);
                        //myModel.updateModel()
                    }
                }
            }

            HorizontalHeaderView {
                id: horizontalHeader
                anchors.left: tableView.left
                //anchors.top: parent.top
                syncView: tableView
                clip: true
                model: ["id", "Книга","Жанр", "Автор", "Цена", "Кличество"]
            }

            TableView {
                id: tableView
                anchors.left: parent.left
                anchors.top: horizontalHeader.bottom
                anchors.right: parent.right
                anchors.bottom: parent.bottom
                columnSpacing: 10

                //Layout.alignment:Qt.AlignHCenter

                clip: true

                property int selectedRow: -1
                property int selectedId: -1

                model: myModel

                columnWidthProvider: function () { return parent.width/6}

                delegate: ItemDelegate {
                    //implicitWidth: parent.width/3
                    //id:item

                    highlighted: tableView.selectedRow != -1 && row == tableView.selectedRow
                    onClicked: {tableView.selectedRow = row; tableView.selectedId = id}
                    //text: column == 0 ? Title : column == 1 ? Author : column == 2 ? Genre :column == 3 ? Year : column == 4 ? Price: Amount
                    text: column == 0 ? id : column == 1 ? Title : column == 2 ? Author : column ==3 ? Genre :column == 4 ? Price: Amount
                    background: Rectangle {
                                    color: highlighted ? palette.light : palette.window
                                }

                    palette.light: "skyblue"
                    palette.highlightedText: "black"
                    palette.text: "black"
                    palette.window: "lightgrey"

                }


            }
        }
        function getDate(){
            return gridm.selectedDate;
        }

        function filterData() {
                    var searchTerm = filtField.text.toLowerCase();
                    myModel.updateModel()
                    for (var i = 0; i < tableView.count; i++) {
                        var data = tableView.get(i).modelData.toLowerCase();
                        if (data.includes(searchTerm)) {
                            tableView.currentIndex = i;
                            tableView.contentItem.children[i].visible = true;
                        } else {
                            tableView.contentItem.children[i].visible = false;
                        }
                    }
                }

        MessageDialog {
            id: dialogDelete
            title: qsTr("Remove record")
            text: qsTr("Confirm the deletion of log entries")
            //icon: StandardIcon.Warning
            buttons: StandardButton.Ok | StandardButton.Cancel

            // If the answer ...
            onAccepted: {
                if(tableView.selectedId != -1){
                    sqlitedatabase.removeRecord(myModel.getId(tableView.selectedRow))
                    myModel.updateModel();
                }
            }
        }

        Popup {
                id: editForm
                property int note_id
                modal: true
                focus: true
                closePolicy: Popup.CloseOnEscape | Popup.CloseOnPressOutsideParent
                anchors.centerIn: Overlay.overlay
                width: 900
                height: 200

                ColumnLayout {
                    RowLayout {
                        id: rowLayout0
                        anchors.top: parent.top
                        anchors.left: parent.left
                        anchors.right: parent.right
                        anchors.margins: 5

                        spacing: 10

                        Text {text: qsTr("Книга")}
                        TextField { id: bookChange}
                        Text {text: qsTr("Автор")}
                        TextField { id: authorChange}
                        Text {text: qsTr("Жанр")}
                        TextField { id: genreChange}
                        Text {text: qsTr("Цена")}
                        TextField {
                            id: priceChange
                            inputMask: "9999.99"
                        }
                        Text { text: qsTr("Количество")}
                        TextField {
                            id: amountChange
                            inputMask: "999999"
                        }
                    }

                    Button {
                        text: 'Изменить'
                        id:editFormAddButton
                        width: 80
                        height: 25
                        Layout.fillWidth: true
                        onClicked: {
                            sqlitedatabase.updateRecord(editForm.note_id, bookChange.text, authorChange.text, genreChange.text, priceChange.text, amountChange.text);
                            tableView.model.updateModel();
                        }
                    }
                    Button {
                        text: 'Закрыть'
                        id:rejectButtonEditForm
                        width: 80
                        height: 25
                        Layout.fillWidth: true
                        onClicked: { editForm.close() }
                    }
                }

        }

}
