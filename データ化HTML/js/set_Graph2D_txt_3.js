function set_Graph2D_txt_3()
{
     my_id=[];
     my_F1=[];
     my_F2=[];
     my_F3=[];
     my_F4=[];
     my_M1=[];
     my_M2=[];
    var i=0;
for(i=0;i<cnt_b;i++){
//    /console.log("cnt_b");
    //console.log(cnt_b);
    my_id[i]=data_obj[i]["id"];
    my_M1[i]=data_obj[i]["M1"]/10;
    my_M2[i]=data_obj[i]["M2"]/10;
}

var ctx3 = document.getElementById("myLineChart3");
    
  var myLineChart3 = new Chart(ctx3, {
    type: 'line',
    data: {
        //console.log(my_id);
      labels: my_id,
      datasets: [

        {
          label: 'M1',
          data: my_M1,
          borderColor: "rgba(0,255,0,1)",
          backgroundColor: "rgba(0,0,0,0)"
        },
        {
          label: 'M2',
          data: my_M2,
          borderColor: "rgba(0,255,55,1)",
          backgroundColor: "rgba(0,0,0,0)"
        },
      ],
    },
    options: {
      title: {
        display: true,
         
        text: 'データ'
      },
         animation: false,
      scales: {
        yAxes: [{
            display: true,             //表示設定
            scaleLabel: {              //軸ラベル設定
           　display: true,          //表示設定
           　labelString: '推進モータ回転数',  //ラベル
             fontSize: 18               //フォントサイズ
            },
          ticks: {
            suggestedMax: 100,
            suggestedMin: 0,
            stepSize: 10,
            callback: function(value, index, values){
              return  value +  ''
            }
          }
        }],
          xAxes: [{                         //x軸設定
                    display: true,                //表示設定
                    barPercentage: 0.1,           //棒グラフ幅
                    categoryPercentage: 0.1,      //棒グラフ幅
                    scaleLabel: {                 //軸ラベル設定
                       display: true,             //表示設定
                       labelString: '[ms]',  //ラベル
                       fontSize: 18               //フォントサイズ
                    },
                    ticks: {
            Min: 100,
            Max: 300,
            stepSize: 10,
          },
                }],
      },
    }
  }); 
}