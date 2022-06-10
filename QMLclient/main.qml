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
    title: qsTr("Hello World")

Backend{
id: backend

onDataChanged: {

    console.log("QML: onDataChanged")
    supreme.update()
}


}

ListModel{
id: model
}

FileDialog {
    id: fileDialog
    selectMultiple: false
      nameFilters: [ "Text files (*.txt)" ]
    title: "Please choose a file"
    folder: shortcuts.home
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
    Component.onCompleted: visible = true
}



Column{

    anchors.fill: parent

    Row{
        id: head
    width: parent.width
     height: 20
Button{
    id: btn
    width: 50
    height: parent.height
    text: "Файл"
    onPressed: {
    console.log("беру путь к файлу и шлю запрос на сервер")
        fileDialog.open()

    }
}
    Text {
        id :filePath;


        text: "" }

    }






Rectangle{
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







Component.onCompleted: {
    fileDialog.close();



}

function update(){

     model.clear()
    console.log(backend.data)
  //  console.log(backend.data.values.count)
    var job= JSON.parse(backend.data);


     console.log("res.length: "+Object.keys(job.res).length)


    for(var i=0;i<Object.keys(job.res).length;i++){


        console.log("type  : "+job.res[i].type)
        console.log("first : "+job.res[i].first)
        console.log("second: "+job.res[i].second)

         model.append({len:job.res[i].first, count:job.res[i].second });

 console.log("res.value["+i+"]length: "+Object.keys(job.res[i].values).length)

        for(var j=0;j<Object.keys(job.res[i].values).length;j++){



        console.log(job.res[i].values[j].len+" "+job.res[i].values[j].count)

         model.append({len:job.res[i].values[j].len, count:job.res[i].values[j].count })
        }

    }


//  var str =  '{"a":"A whatever, run","b":"B fore something happens"}'

 //   console.log(str)
//var JsonObject= JSON.parse(str);


}



}
