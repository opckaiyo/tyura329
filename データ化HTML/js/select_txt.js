
var obj1 = document.getElementById("selfile");
//ダイアログでファイルが選択された時
obj1.addEventListener("change",function(evt){
  var file = evt.target.files;
  //FileReaderの作成
  var reader = new FileReader();
  //テキスト形式で読み込む
  reader.readAsText(file[0]);
  //読込終了後の処理
  reader.onload = function(ev){
    //テキストエリアに表示する
    document.test.txt.value = reader.result;
    try {
      data_obj = JSON.parse(reader.result);
      console.log(data_obj[1]["M2"]);
      console.log(data_obj);
      set_Graph2D_txt(); 
      console.log("json変換ok,2dGraph"　);
        
    } catch(error) {
        data_obj=reader.result;
        console.log(data_obj.length);
      console.log("エラー内容："　+ error);
        var result = data_obj.indexOf( '}' );
        console.log(result);
    }

      
  }
},false);
