function set_Graph3D_txt1()
{
console.log("hyhy");

}

function set_Graph3D_txt() {
    

    var g = new canvasGraph( "graph" );
	g.drawAxis();
	g.drawInfo();
	
    if(data_obj[cnt_b]["PWM1"]!=0)kyori+=Math.abs(Math.cos((data_obj[cnt_b]["9DX"])*Math.PI/180)/1.1);
    if(data_obj[cnt_b]["PWM1"]!=0)kyori+=Math.abs(Math.sin((data_obj[cnt_b]["9DX"])*Math.PI/180)/1.1);
    if(data_obj[cnt_b]["PWM1"]!=0)z_3d_val=z_3d_val-Math.cos((data_obj[cnt_b]["9DX"])*Math.PI/180)*2;
    if(data_obj[cnt_b]["PWM1"]!=0)x_3d_val=x_3d_val+Math.sin((data_obj[cnt_b]["9DX"])*Math.PI/180)*2;
    /*if(data_obj[cnt_b]["PWM1"]!=0){
        if(0<Math.cos((data_obj[cnt_b]["9DX"])*Math.PI/180)){
            speed_z=speed_z+0.1;
            
        }
        speed_z=z_3d_val-Math.cos((data_obj[cnt_b]["9DX"])*Math.PI/180)*2;
    }
*/
    
        z_3d_val=z_3d_val+speed_z;
        x_3d_val=x_3d_val+speed_x;
        
        console.log("z :"+speed_z)
        console.log("x :"+speed_x)
    
    
    y_3d_val=200
    data_ar.push({x: x_3d_val, y: y_3d_val, z: z_3d_val});
    //my_z_3d_val[i]=z_3d_val;
    //my_x_3d_val[i]=x_3d_val;
    
	///// データ /////
    my_xyz["x"] = x_3d_val;;
    my_xyz["y"] = data_obj[cnt_b]["PS1"];
    my_xyz["z"] = z_3d_val;
    
    var val=[];
	var data = [
		{ x: 100, y: 500, z: 100 },
		{ x: 200, y: 400, z: 200 },
		{ x: 300, y: 300, z: 300 },
		{ x: 400, y: 400, z: 400 },
		{ x: 500, y: 500, z: 500 }
	];

    data.unshift(my_xyz);
    
    //console.log(typeof(data));
   // console.log(my_PS1[cnt_b]);
    //console.log(cnt_b);
    //console.log(data);
    //console.log(my_9DX[cnt_b]);
    var data2=[data_ar[cnt_b]];
    g.drawGraph( data2);
    //console.log(data_ar.length-2);
    
    //console.log(data_ar[0]);
    simulation_3D_document();  /////////////////////////////////////////////////////////////////////

   
    max_id=Object.keys(my_id).length;
    if(cnt_b<=data_obj.length-2){
        cnt_b=cnt_b+1;
        //console.log(cnt_b);
        setTimeout(function() { set_Graph3D_txt(),spn2(),set_Graph2D_txt_2(),set_Graph2D_txt_3(); }, 10);
        }else {
            simulation_3D_reset();
        }
   
}

function simulation_3D_set() {

    
    }

function simulation_3D_reset() {
        cnt_b=0;
        x_3d_val=300;
        z_3d_val=   500;
        data_ar=[];
        kyori=0;
    }

function simulation_3D_document() {
    document.getElementById("demo").innerHTML = "時間 : "+data_obj[cnt_b]["id"]/10+"[s]";
    document.getElementById("demo_x").innerHTML =  "座標(x , z)　("+x_3d_val.toFixed(0);
    document.getElementById("demo_z").innerHTML =  ","+z_3d_val.toFixed(0)+")";
    document.getElementById("demo_kyori").innerHTML =  "合計距離 : "+(kyori/10/3).toFixed(2)+"[m](推定)"+"<br>"+"スピード一定0.5m/s";
    
    document.getElementById("demo_MEMO1").innerHTML =  "合計回転数";
    document.getElementById("demo_PWM1").innerHTML =  "推進モータPWM1: "+data_obj[cnt_b]["PWM1"];
    document.getElementById("demo_PWM2").innerHTML =  "旋回モータPWM2: "+data_obj[cnt_b]["PWM2"];
    document.getElementById("demo_PWM3").innerHTML =  "潜水モータPWM3: "+data_obj[cnt_b]["PWM3"];
    document.getElementById("demo_M1").innerHTML =  "推進モータM1_R: "+data_obj[cnt_b]["M1"]/10+"[回転]";
    document.getElementById("demo_M2").innerHTML =  "推進モータM2_L: "+data_obj[cnt_b]["M2"]/10+"[回転]";
    document.getElementById("demo_F1").innerHTML =  "流量計F1_XL : "+data_obj[cnt_b]["F1"]+"[回転]";
    document.getElementById("demo_F2").innerHTML =  "流量計F2_XR : "+data_obj[cnt_b]["F2"]+"[回転]";
    document.getElementById("demo_F3").innerHTML =  "流量計F3_L : "+data_obj[cnt_b]["F3"]+"[回転]";
    document.getElementById("demo_F4").innerHTML =  "流量計F4_R : "+data_obj[cnt_b]["F4"]+"[回転]";
    
    document.getElementById("demo_T1").innerHTML =  "温度計T1_ZR: "+data_obj[cnt_b]["T1"]+"[℃]";
    document.getElementById("demo_T2").innerHTML =  "温度計T2_ZL: "+data_obj[cnt_b]["T2"]+"[℃]";
    document.getElementById("demo_T3").innerHTML =  "温度計T3_R : "+data_obj[cnt_b]["T3"]+"[℃]";
    document.getElementById("demo_T4").innerHTML =  "温度計T4_L : "+data_obj[cnt_b]["T4"]+"[℃]";
    document.getElementById("demo_T5").innerHTML =  "温度計T5_XR : "+data_obj[cnt_b]["T5"]+"[℃]";
    document.getElementById("demo_T6").innerHTML =  "温度計T6_XL : "+data_obj[cnt_b]["T6"]+"[℃]";
    document.getElementById("demo_T7").innerHTML =  "温度計T7_Body: "+data_obj[cnt_b]["T7"]+"[℃]";
    
    document.getElementById("demo_C1").innerHTML =  "潜水電流計C1_ZL : "+data_obj[cnt_b]["C1"]+"[A]";
    document.getElementById("demo_C2").innerHTML =  "潜水電流計C2_ZR : "+data_obj[cnt_b]["C2"]+"[A]";
    document.getElementById("demo_C3").innerHTML =  "推進モータC3_L : "+data_obj[cnt_b]["C3"]+"[A]";
    document.getElementById("demo_C4").innerHTML =  "推進モータC4_R : "+data_obj[cnt_b]["C4"]+"[A]";
    
    document.getElementById("demo_PS1").innerHTML =  "圧力計PS1 : "+data_obj[cnt_b]["PS1"]+"[圧力]";
    document.getElementById("demo_V1").innerHTML =  "バッテリー残量V1 : "+data_obj[cnt_b]["V1"]+"[V]";

    }
