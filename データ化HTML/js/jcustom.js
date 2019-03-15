$(function(){
	$("#s01 img").rotate({angle:cnt_2});
                    cnt_2=cnt_2+10
	console.log("1");
	var angle = 0;
	setInterval(function(){
				angle+=3;
			 $("#s02 img").rotate(angle);
	},10);//
        
	
	var s03 = function (){
		 $("#s03 img").rotate({
				angle: 0, 
				animateTo: 360, 
				callback: s03
		 });
	}
	s03();

	$("#s04 img").rotate({ 
		bind: 
			{ 
				click: function(){
					$(this).rotate({
						angle: 0,
						animateTo: 360,
						easing: $.easing.easeInOutExpo
					})
				}
			} 
	});
	

	$("#s05 img").rotate({ 
	bind: 
		{ 
			mouseover : function() { 
				$(this).rotate({
					animateTo: 360
				})
			},
			mouseout : function() { 
				$(this).rotate({
					animateTo: 0
				})
			}
		} 	 
	});
	
});

function spn()
{
    $("#s01 img").rotate({angle:parseFloat(my_9DX[cnt_a])});
    cnt_2=cnt_2+10;
    console.log(parseFloat(my_9DX[cnt_a]));
    console.log(cnt_2);
    //document.write(my_M2.length);
    //for(var i=0;i<my_M2.length;i++){
    //    document.write(my_PWM2[i]);
    //    document.write("<br>");
   //対象データへのアクセスは data[i] の様な形式
    //}
}
