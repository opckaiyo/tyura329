function set_Graph2D_txt()
{
    my_id=[];
for(var i=0;i<data_obj.length;i++){
    console.log("cnt_b");
    my_id[i]=data_obj[i]["id"];
    my_PWM1[i]=data_obj[i]["PWM1"];
    my_PWM2[i]=data_obj[i]["PWM2"];
    my_PWM3[i]=data_obj[i]["PWM3"];
    my_PWM4[i]=data_obj[i]["PWM4"];
    my_PWM5[i]=data_obj[i]["PWM5"];
    my_PWM6[i]=data_obj[i]["PWM6"];
    my_M1[i]=data_obj[i]["M1"]/10;
    my_M2[i]=data_obj[i]["M2"]/10;
    my_M3[i]=data_obj[i]["M3"];
    my_M4[i]=data_obj[i]["M4"];
    my_M5[i]=data_obj[i]["M5"];
    my_M6[i]=data_obj[i]["M6"];
    my_T1[i]=data_obj[i]["T1"];
    my_T2[i]=data_obj[i]["T2"];
    my_T3[i]=data_obj[i]["T3"];
    my_T4[i]=data_obj[i]["T4"];
    my_T5[i]=data_obj[i]["T5"];
    my_T6[i]=data_obj[i]["T6"];
    my_T7[i]=data_obj[i]["T7"];
    my_V1[i]=data_obj[i]["V1"];
    my_C1[i]=data_obj[i]["C1"];
    my_C2[i]=data_obj[i]["C2"];
    my_C3[i]=data_obj[i]["C3"];
    my_C4[i]=data_obj[i]["C4"];
    my_F1[i]=data_obj[i]["F1"];
    my_F2[i]=data_obj[i]["F2"];
    my_F3[i]=data_obj[i]["F3"];
    my_F4[i]=data_obj[i]["F4"];
    my_9DX[i]=data_obj[i]["9DX"];
    my_9DY[i]=data_obj[i]["9DY"];
    my_9DZ[i]=data_obj[i]["9DZ"];     
    MM_L[i]=data_obj[i]["MM_L"];
    MM_R[i]=data_obj[i]["MM_R"];
    MM_XL[i]=data_obj[i]["MM_XL"];
    MM_XR[i]=data_obj[i]["MM_XR"];
    MM_ZL[i]=data_obj[i]["MM_ZL"];
    MM_ZR[i]=data_obj[i]["MM_ZR"];
    my_PS1[i]=data_obj[i]["PS1"];
}

 var ctx = document.getElementById("myLineChart");
    //var ctx = $('#resultChart');
// インスタンスがあれば破棄する
if( myLineChart ){
 myLineChart.destroy();
 }
  myLineChart = new Chart(ctx, {
    type: 'line',
    data: {
        //console.log(my_id);
      labels: my_id,
      datasets: [
        {
          label: 'PWM1',
          data: my_PWM1,
          borderColor: "rgba(255,0,0,1)",
          backgroundColor: "rgba(0,0,0,0)"
        },
          {
          label: 'PWM2',
          data: my_PWM2,
          borderColor: "rgba(255,100,0,1)",
          backgroundColor: "rgba(0,0,0,0)"
        },
        {
          label: 'PWM3',
          data: my_PWM3,
          borderColor: "rgba(255,200,0,1)",
          backgroundColor: "rgba(0,0,0,0)"
        },
          {
          label: 'M1',
          data: my_M1,
          //data: "",
          borderColor: "rgba(0,255,100,1)",
          backgroundColor: "rgba(0,0,0,0)"
        },
        {
          label: 'M2',
          data: my_M2,
          //data: "",
          borderColor: "rgba(0,255,200,1)",
          backgroundColor: "rgba(0,0,0,0)"
        },
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
        {
          label: 'C1',
          data: my_C1,
          borderColor: "rgba(0,250,255,1)",
          backgroundColor: "rgba(0,0,0,0)"
        },
        {
            label: 'C2',
            data: my_C2,
            borderColor: "rgba(0,250,255,1)",
            backgroundColor: "rgba(0,0,0,0)"
        },
        {
            label: 'C3',
            data: my_C3,
            borderColor: "rgba(0,250,255,1)",
            backgroundColor: "rgba(0,0,0,0)"
            },
        {
            label: 'C4',
            data: my_C4,
            borderColor: "rgba(0,250,255,1)",
            backgroundColor: "rgba(0,0,0,0)"
        },
                    {
          label: 'T1',
          data: my_T1,
          borderColor: "rgba(0,255,100,1)",
          backgroundColor: "rgba(0,0,0,0)"
        },
        {
          label: 'T2',
          data: my_T2,
          borderColor: "rgba(0,255,200,1)",
          backgroundColor: "rgba(0,0,0,0)"
        },
        {
          label: 'T3',
          data: my_T3,
          borderColor: "rgba(0,50,255,1)",
          backgroundColor: "rgba(0,0,0,0)"
        },
        {
          label: 'T4',
          data: my_T4,
          borderColor: "rgba(0,100,255,1)",
          backgroundColor: "rgba(0,0,0,0)"
        },
        {
          label: 'T5',
          data: my_T5,
          borderColor: "rgba(0,200,255,1)",
          backgroundColor: "rgba(0,0,0,0)"
        },
          {
          label: 'T6',
          data: my_T6,
          borderColor: "rgba(0,250,255,1)",
          backgroundColor: "rgba(0,0,0,0)"
        },
                    {
          label: 'T7',
          data: my_T7,
          borderColor: "rgba(0,250,255,1)",
          backgroundColor: "rgba(0,0,0,0)"
        },
        {
          label: '9DX',
          data: my_9DX,
          borderColor: "rgba(0,100,255,1)",
          backgroundColor: "rgba(0,0,0,0)"
        },
        {
          label: '9DY',
          data: my_9DY,
          borderColor: "rgba(0,200,255,1)",
          backgroundColor: "rgba(0,0,0,0)"
        },
        {
          label: 'PS1',
          data: my_PS1,
          borderColor: "rgba(0,0,0,1)",
          backgroundColor: "rgba(0,0,0,0)"
        },
                {
          label: 'V1',
          data: my_V1,
          borderColor: "rgba(0,0,0,1)",
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
           　labelString: 'value',  //ラベル
             fontSize: 18               //フォントサイズ
            },
          ticks: {
            suggestedMax: 40,
            suggestedMin: 0,
            stepSize: 10,
            callback: function(value, index, values){
              return  value +  ''
            }
          }
        }],
          xAxes: [{                         //x軸設定
                    display: true,                //表示設定
                    barPercentage: 0.4,           //棒グラフ幅
                    categoryPercentage: 0.4,      //棒グラフ幅
                    scaleLabel: {                 //軸ラベル設定
                       display: true,             //表示設定
                       labelString: '[100ms]',  //ラベル
                       fontSize: 18               //フォントサイズ
                    },
                    ticks: {
                        fontSize: 18             //フォントサイズ
                    },
                }],
      },
    }
  });
    
}