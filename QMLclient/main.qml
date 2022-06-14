import QtQuick 2.12
import QtQuick.Window 2.12
import QtWebSockets 1.0
import Backend 1.0
import QtQuick.Controls 2.15
import QtQuick.Dialogs 1.3
Window {
    id: supreme
    width: 640
    height: 480

    visible: true
    title: qsTr("")

Backend{
id: backend

onDataChanged: {

    console.log("QML: onDataChanged")
    supreme.update()
}

onConnectionChanged: {

    console.log("onConnectionChanged: "+backend.connection)

    if(backend.connection){
        ip_input.visible=false
        textFieldip.enabled=false

        head.visible=true
        btn.enabled=true
        db_btn.enabled=true
        dataview.visible=true



    }else{
        ip_input.visible=true
        textFieldip.enabled=true

        head.visible=false
        btn.enabled=false
        db_btn.enabled=false
        dataview.visible=false
    }

}


}


ListModel{
id: db_model
}


ListModel{
id: model
}

FileDialog {
    id: fileDialog
    selectMultiple: false

      nameFilters: [ "Text files (*.txt)" ]
    title: "Please choose a file"
    folder: shortcuts.current
    visible: false
    onAccepted: {
        const fileName = fileDialog.fileUrl;

        //rm file://
        const flNm=fileName.toString().replace("file://","")
        console.log("You chose: " + flNm)
        filePath.text=flNm;
        backend.request(flNm)



    }
    onRejected: {
        console.log("Canceled")

    }
    //Component.onCompleted: visible = true
}


Rectangle{
anchors.fill: parent
color:"lightblue"
Column{

    anchors.fill: parent

    Row{
        id: head
    width: parent.width
     height: 20
     visible: false

     Button{
         id: db_btn
         width: 100
         height: parent.height
         text: "База"
         enabled: false
         onPressed: {
         console.log("шлю запрос БД")
             backend.request_db()


         }
     }
Button{
    id: btn
    width: 100
    height: parent.height
    text: "Файл"
    enabled: false
    onPressed: {
    console.log("беру путь к файлу и шлю запрос на сервер")
        fileDialog.open()

    }
}
Rectangle{
    width: parent.width-btn.width-db_btn.width
    height: parent.height
    color:"white"
    Text {
        id :filePath
     anchors.fill: parent




        text: "" }

    }
    }


    Rectangle{
       id: db_dataview
       width: parent.width
       height: parent.height-head.height
    color:"lightblue"
    visible: false

    ScrollView {
        width: parent.width
        height : parent.height
        contentWidth: column.width    // The important part
        contentHeight: column.height  // Same
        clip : true
    Column {
    anchors.fill: parent

        Repeater {
    anchors.fill: parent
            model: db_model

                Row{
                width: parent.width
                Rectangle{
                    x:0
                width: parent.width/3
                height: 30
                 border.width: 1
                 border.color: "white"
                color: "lightgray"
                Text {
                     x:5
                     y:parent.height/5


                    text: model.dt }
                }
                Rectangle{
                    x: parent.width/3
                width: parent.width/3
                height: 30
                border.width: 1
                border.color: "white"
                color: "lightblue"
                Text {
                    x:5
                    y:parent.height/5

                    text: model.ipaddr }

                }
                Rectangle{
                    x: 2*parent.width/3
                width: parent.width/3
                height: 30
                border.width: 1
                border.color: "white"
                color: "lightblue"
                Text {
                    x:5
                    y:parent.height/5

                    text: model.count }

                }

             //
            }
        }
    }
    }
}


Rectangle{
   id: dataview
   width: parent.width
   height: parent.height-head.height
color:"lightblue"




    ScrollView {
        width: parent.width
        height : parent.height
        contentWidth: column.width    // The important part
        contentHeight: column.height  // Same
        clip : true
    Column {
    anchors.fill: parent

        Repeater {
    anchors.fill: parent
            model: model

                Row{
                width: parent.width
                Rectangle{
                    x:0
                width: parent.width/2
                height: 30
                 border.width: 1
                 border.color: "white"
                color: "lightgray"
                Text {
                     x:5
                     y:parent.height/5


                    text: model.len }
                }
                Rectangle{
                    x: parent.width/2
                width: parent.width/2
                height: 30
                border.width: 1
                border.color: "white"
                color: "lightblue"
                Text {
                    x:5
                    y:parent.height/5

                    text: model.count }

                }


             //
            }
        }
    }
    }





}
}



Rectangle{
    id: ip_input
   anchors.centerIn: parent
width: 200
height: 50
color:white

Column{
    anchors.fill: parent
Text{
    id: iptxt
    width:parent.width
    height:20
    text:"Введите адрес сервера "


}
Row{
    width:parent.width
    height:30
TextField {
    width: parent.width-50
    height: 30
            id: textFieldip
            validator: RegExpValidator {
                regExp:  /^((?:[0-1]?[0-9]?[0-9]|2[0-4][0-9]|25[0-5])\.){0,3}(?:[0-1]?[0-9]?[0-9]|2[0-4][0-9]|25[0-5])$/
            }
            text: "127.0.0.1"
            inputMethodHints: Qt.ImhFormattedNumbersOnly

            onEditingFinished: {
            console.log("Ввел айпи адрес")
                backend.start(textFieldip.text)

            }
        }

Button{
    width:50
    height:30
    text:"ОК"
    onClicked:  {
    console.log("Ввел айпи адрес")
        backend.start(textFieldip.text)

    }
}

}

}
}

}


Component.onCompleted: {

  //  backend.start("")

    fileDialog.close();



}

function update(){


    console.log(backend.data)
  //  console.log(backend.data.values.count)
    var job= JSON.parse(backend.data);


    console.log("job.type: ",job.type)



if(job.type=="result"){

    db_dataview.visible=false
    dataview.visible=true

       model.clear()

    console.log("res.length: "+Object.keys(job.res).length)

    for(var i=0;i<Object.keys(job.res).length;i++){

    //    console.log("type  : "+job.res[i].type)
   //     console.log("first : "+job.res[i].first)
    //    console.log("second: "+job.res[i].second)

    //    model.append({len:job.res[i].first, count:job.res[i].second });

        console.log("res.value["+i+"]length: "+Object.keys(job.res[i].values).length)

        for(var j=0;j<Object.keys(job.res[i].values).length;j++){

            console.log(job.res[i].values[j].len+" "+job.res[i].values[j].count)

            model.append({len:job.res[i].values[j].len, count:job.res[i].values[j].count })
        }
    }
}

if(job.type=="db"){

    db_dataview.visible=true
    dataview.visible=false

    db_model.clear()

     console.log("data length: "+Object.keys(job.data).length)
        for(var j=0;j<Object.keys(job.data).length;j++){

            console.log(job.data[j].dt+" "+job.data.ipaddr+" "+job.data.count)

            db_model.append({dt:job.data[j].dt, ipaddr:job.data[j].ipaddr,count:job.data[j].count })
        }

}


}



}
