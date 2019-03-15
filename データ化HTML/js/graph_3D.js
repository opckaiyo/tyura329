function simulation_3D()
{
console.log(cnt_a);
cnt_a=cnt_a+1;

console.log(data_ar);

}

function simulation3_3D() {
    

    var g = new canvasGraph( "graph" );
	g.drawAxis();
	g.drawInfo();
	
	///// データ /////
    my_xyz["x"] = x_3d_val;;
    my_xyz["y"] = my_PS1[cnt_a];
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
    console.log(my_PS1[cnt_a]);
    //console.log(cnt_a);
    //console.log(data);
    //console.log(my_9DX[cnt_a]);
    var data2=[data_ar[cnt_a]];
    g.drawGraph( data2);
    console.log(data_ar.length-2);
    
    
    //console.log(data_ar[0]);
    document.getElementById("demo").innerHTML = "cnt : "+cnt_a;
    document.getElementById("demo_x").innerHTML =  "x : "+my_x_3d_val[cnt_a].toFixed(0);
    document.getElementById("demo_z").innerHTML =  "z : "+my_z_3d_val[cnt_a].toFixed(0);
    document.getElementById("demo_PWM1").innerHTML =  "PWM1: "+my_PWM1[cnt_a];
    document.getElementById("demo_F1").innerHTML =  "F1 : "+my_F1[cnt_a];
   
    max_id=Object.keys(my_id).length;
    if(cnt_a<=data_ar.length-2){
        cnt_a=cnt_a+1;
        console.log(cnt_a);
        setTimeout(function() { simulation3_3D(),spn(); }, 100);
        }else cnt_a=0;
   
}

function simulation_3D_set() {

    
    }

