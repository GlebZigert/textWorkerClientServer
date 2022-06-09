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
        backend.request(flNm)



    }
    onRejected: {
        console.log("Canceled")

    }
    Component.onCompleted: visible = true
}
Button{
    onPressed: {
    console.log("беру путь к файлу и шлю запрос на сервер")
        fileDialog.open()

    }

}

Column {
    Repeater {
        model: model
        Rectangle{
        width: 80
        height: 20
         border.width: 1
        color: "lightgray"
        Text { text: model.len+" "+model.count }
        }


     //
    }
}

Component.onCompleted: {
    fileDialog.close();



}

function update(){
    console.log(backend.data)
  //  console.log(backend.data.values.count)
    var job= JSON.parse(backend.data);

    console.log(job.type)
    console.log(job.first)
    console.log(job.second)
    console.log(Object.keys(job.values).length)

    for(var i=0;i<Object.keys(job.values).length;i++){
    console.log(job.values[i].len+" "+job.values[i].count)
    }

//  var str =  '{"a":"A whatever, run","b":"B fore something happens"}'

 //   console.log(str)
//var JsonObject= JSON.parse(str);

model.clear()
    for(var i=0;i<Object.keys(job.values).length;i++)
  model.append({len:job.values[i].len, count:job.values[i].count });

}



}
