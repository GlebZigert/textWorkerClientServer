import QtQuick 2.12
import QtQuick.Window 2.12
import QtWebSockets 1.0
import Backend 1.0

Window {
    width: 640
    height: 480
    visible: true
    title: qsTr("Hello World")

Backend{
id: backend

}

ListModel{
id: model
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


    for(var i=0;i<Object.keys(job.values).length;i++)
  model.append({len:job.values[i].len, count:job.values[i].count });


}



}
