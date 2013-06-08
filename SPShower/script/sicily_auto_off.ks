////////////////////////////////////////////////////////////////////////////
// Demo script of SPEShow Beta 0.82
// SPEShow 0.82 演示脚本之二
// 将演示一个简易的AVG场景脚本
//
// Author: Ken.J
// Date: 2012-10-02
////////////////////////////////////////////////////////////////////////////

// 关闭自动模式
@skip{ set_on:false mode:"Auto" auto_time:等待时间 }

@component{ 
	name:"自动按钮" 
	background_y:-26
	background_image:"data/images/dialog_button_auto.png" 
	on_click:[ 
		自动模式开启 = false; 
		@include{ file:"script/sicily_auto_on.ks" }
	]
}