var my_alldata=[];
function setSelect( idName, elementName, menu )
{
    var id = document.getElementById(idName);
    for ( var i in menu ) 
    {
        var element = document.createElement(elementName);
        element.setAttribute('value', i);
        element.innerHTML = menu[i];
        id.appendChild( element );
    }
}

function label_data_ajax(){
    var value = document.formName.selectName.value;
$.ajax({
    type: 'GET',
    url: './myphpread_select.php',
    data: {name: value},
    dataType: 'json',
    success: function(data,dataType)  {
        console.log(data);
        console.log(typeof(data));
        
        //console.log(Object.keys(data));
        //my_alldata=Object.keys(data);
        
         console.log("iiiii");
         //for(var i=0;i<data.length;i++)menu_1[data[i]] = data[i];
         
        max_id=Object.keys(data).length;
        set_up();
        my_alldata=data;
       // my_alldata=Object.entries(data);
        //console.log(my_alldata);
         for(var i=0;i<max_id;i++){
            my_id[i]=data[i]["id"];
            my_PWM1[i]=data[i]["PWM1"];
            my_PWM2[i]=data[i]["PWM2"];
            my_PWM3[i]=data[i]["PWM3"];
            my_PWM4[i]=data[i]["PWM4"];
            my_PWM5[i]=data[i]["PWM5"];
            my_PWM6[i]=data[i]["PWM6"];
            my_M1[i]=data[i]["M1"];
            my_M2[i]=data[i]["M2"];
            
            my_M3[i]=data[i]["M3"];
            my_M4[i]=data[i]["M4"];
            my_M5[i]=data[i]["M5"];
            my_M6[i]=data[i]["M6"];
            my_T1[i]=data[i]["T1"];
            my_T2[i]=data[i]["T2"];
            my_T3[i]=data[i]["T3"];
            my_T4[i]=data[i]["T4"];
            my_T5[i]=data[i]["T5"];
            my_T6[i]=data[i]["T6"];
            my_T7[i]=data[i]["T7"];
            my_V1[i]=data[i]["V1"];
            my_C1[i]=data[i]["C1"];
            my_C2[i]=data[i]["C2"];
            my_C3[i]=data[i]["C3"];
            my_C4[i]=data[i]["C4"];
            my_F1[i]=data[i]["F1"];
            my_F2[i]=data[i]["F2"];
            my_F3[i]=data[i]["F3"];
            my_F4[i]=data[i]["F4"];
            my_9DX[i]=data[i]["9DX"];
            my_9DY[i]=data[i]["9DY"];
            my_9DZ[i]=data[i]["9DZ"];     
            MM_L[i]=data[i]["MM_L"];
            MM_R[i]=data[i]["MM_R"];
            MM_XL[i]=data[i]["MM_XL"];
            MM_XR[i]=data[i]["MM_XR"];
            MM_ZL[i]=data[i]["MM_ZL"];
            MM_ZR[i]=data[i]["MM_ZR"];
            my_PS1[i]=data[i]["PS1"];

            if(my_PWM1[i]!=0)z_3d_val=z_3d_val-Math.cos((my_9DX[i])*Math.PI/180);
            if(my_PWM1[i]!=0)x_3d_val=x_3d_val+Math.sin((my_9DX[i])*Math.PI/180);
            y_3d_val=1000-my_PS1[i]-350;
            data_ar.push({x: x_3d_val, y: y_3d_val, z: z_3d_val});
            my_z_3d_val[i]=z_3d_val;
            my_x_3d_val[i]=x_3d_val;
        }


        console.log(data_ar);
        console.log(z_3d_val);
        var my_id2= [];
        max_id=Object.keys(my_id).length;
        
                },
    error:function() {
        console.log("nononononono");
    }
    });
   
     //
}

function txt_make()
{
    console.log("txt_make");
    console.log(my_alldata);
    console.log(typeof(my_alldata));
     console.log(my_alldata[1]["M3"]);
}

$(function() {
    var click_count = 0;    // ボタンカウント用変数

    if (typeof Blob !== "undefined") {
        // alert('このブラウザに対応しています');
    } else {
        alert('このブラウザには対応していません');
    }

    $("#count").click(function(){
        click_count++; // ボタンを押した数をカウント
        // text_boxクラスのテキストの値を変更
        $("#contents_sample_wrap .text_box").text("ボタンが" + click_count + "回クリックされました");
    });

    $("#export").click(function(){  // 出力ボタンを押した場合は、setBlobUrl関数に値を渡して実行
        setBlobUrl("download", JSON.stringify(my_alldata));
    });
});


function setBlobUrl(id, content) {

 // 指定されたデータを保持するBlobを作成する。
    var blob = new Blob([ content ], { "type" : "application/x-msdownload" });
 
 // Aタグのhref属性にBlobオブジェクトを設定し、リンクを生成
    window.URL = window.URL || window.webkitURL;
    $("#" + id).attr("href", window.URL.createObjectURL(blob));
    $("#" + id).attr("download", "tmp.txt");
}

function datatime_label(){
    //var value = document.formName.selectName.value;
$.ajax({
    type: 'GET',
    url: './myphpread_datatime.php',
    //data: {name: value},
    dataType: 'json',
    success: function(data)  {
        console.log(data);
        my_datatime=data;
         console.log("iiiii");
         //for(var i=0;i<data.length;i++)menu_1[data[i]] = data[i];
         
        max_id=Object.keys(data).length;
        set_up();
         for(var i=0;i<max_id;i++){
            //my_id[i]=data[i]["id"];
           
        }


        console.log("");
    
        //max_id=Object.keys(my_id).length;
        
                },
    error:function() {
        console.log("nononononono");
    }
    });
   
     //
}


function init()
{
    $.ajax({
    type: 'GET',
    url: './myphpread_data_and_time.php',
    dataType: 'json',
    success: function(data)  {
        
        console.log("hyhy");
        menu_1={};
        for(var i=0;i<data.length;i++)menu_1[data[i]] = data[i];
         console.log(menu_1);
        //var arr ={"01": "1111","02": "112","03": "1113"};
         setSelect( 'select', 'option',menu_1 );
                },
    error:function() {
        console.log("nononononono");
    }
    });

}

function t_alert()
{
    value = document.formName.selectName.value;
    label_data_ajax();
    //var str = document.formName.selectName.value;
    //alert(str);
    setTimeout(function() { datatime_label(); }, 100);
    console.log("t_arat");
    console.log(menu_1[value]);
    console.log(menu_1);
}

function t_alert2()
{
    //var str = document.formName.selectName.value;
    //alert(str);
    
    console.log("t_arat2");
    console.log(menu_1[value]);
    console.log(my_datatime[menu_1[value]]);
    document.getElementById("datatime_1").innerHTML = "記録日時　: "+my_datatime[menu_1[value]];   
}






function set_up2( )
{
     var ctx = $('#resultChart');
    ctx = document.getElementById("myLineChart");
    if( myLineChart){
 myLineChart.destroy();
 
 }
    if(flg_1!=0)myLineChart.removeData( );
    flg=1;
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
         
        text: '12月3日'
      },
         animation: false,
      scales: {
        yAxes: [{
          ticks: {
            suggestedMax: 40,
            suggestedMin: 0,
            stepSize: 10,
            callback: function(value, index, values){
              return  value +  '度'
            }
          }
        }]
      },
    }
  });

 
    console.log(cnt_a);

      console.log('a start.');
}
function simulation2_3D()
{
console.log(my_PS1);
console.log("hey");    
}
