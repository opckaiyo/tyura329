
function getValue(idname){
  // value値を取得する
  var result = document.getElementById(idname).value; //テキストボックス値取得
  var value2 = document.formName.selectName.value;    //セレクトボックス選択値取得
  var select_logmerter=value2;
 
  // Alertで表示する
  alert("value値は「" + result + "」です");    /////////////
    
    
var value = result;
$.ajax({
    type: "POST",
    url: "db_update.php",
    data: {"item": value,"item2": value2},
        success: function(html){
            alert(html);                    /////////////
            alert("select log="+value2)  //////////////
        }
    });
    
}