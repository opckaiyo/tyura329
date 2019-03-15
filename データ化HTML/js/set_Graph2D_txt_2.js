function set_Graph2D_txt_2()
{
     my_id=[];
     my_F1=[];
     my_F2=[];
     my_F3=[];
     my_F4=[];
    var i=0;
for(i=0;i<cnt_b;i++){
//    /console.log("cnt_b");
    //console.log(cnt_b);
    my_id[i]=data_obj[i]["id"];
    my_F1[i]=data_obj[i]["F1"];
    my_F2[i]=data_obj[i]["F2"];
    my_F3[i]=data_obj[i]["F3"];
    my_F4[i]=data_obj[i]["F4"];
}

var ctx2 = document.getElementById("myLineChart2");
    
  var myLineChart2 = new Chart(ctx2, {
    type: 'line',
    data: {
        //console.log(my_id);
      labels: my_id,
      datasets: [

        {
          label: 'F1',
          data: my_F1,
          borderColor: "rgba(0,50,255,1)",
          backgroundColor: "rgba(0,0,0,0)"
        },
        {
          label: 'F2',
          data: my_F2,
          borderColor: "rgba(0,100,255,1)",
          backgroundColor: "rgba(0,0,0,0)"
        },
        {
          label: 'F3',
          data: my_F3,
          borderColor: "rgba(0,200,255,1)",
          backgroundColor: "rgba(0,0,0,0)"
        },
          {
          label: 'F4',
          data: my_F4,
          borderColor: "rgba(0,250,255,1)",
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
           　labelString: '流量計回転数',  //ラベル
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