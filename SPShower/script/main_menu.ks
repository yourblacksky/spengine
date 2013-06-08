////////////////////////////////////////////////////////////////////////////
// Demo script of SPShower Beta 0.82
//
// Author: Ken.J
// Date: 2012-09-25
////////////////////////////////////////////////////////////////////////////

// 起始标记
@tag{ name:"进入主菜单" }

////////////////////////////////////////////////////////////////////////////

// 播放菜单音乐
@track{ 
	name:"背景音乐" 
	src:"data/sounds/bgm01.ogg" 
	loop:-1 control:"Play" 
}

@track{
	name:"音效"
	loop:0
}

// 设置主菜单
@screen{ name:"主菜单"}

// 设置菜单背景
@component{
	name:"背景"
	width:1280
	height:720
	x:0
	transparency:0
	y:0
	background_image:"data/images/bg_classroom_02.png"
	layer:0
}

@component{
	name:"背景2"
	width:1280
	height:720
	x:0
	transparency:0
	y:0
	background_image:"data/images/bg_menu.png"
	background_color:0x00888888
	layer:1
}

@component{
	name:"标题"
	width:1000
	height:300
	x:0
	y:50
	transparency:0
	background_image:"data/images/logo_sicily_02.png"
	background_color:0x00FFFFFF
	layer:2
}

@component{
	name:"copyright"
	width:256
	height:20
	x:287
	y:700
	transparency:0
	background_image:"data/images/copyright.png"
	background_color:0x00FFFFFF
	on_click:[ @execute{file:"http://www.sprabbit.com"} ]
	layer:2
}

@component{
	name:"转盘"
	layer:4
	width:700
	height:700
	rotation_center_x:1280
	rotation_center_y:720
	x:930
	y:370
	rotation:0
	transparency:0
	background_image:"data/images/round_menu.png"
}

// 设置按钮初始位置
@component{
	name:"按钮1"
	width:350
	height:80
	x:-150
	transparency:0
	y:280
	layer:3
	background_y:0
	background_image:"data/images/button_restart.png"
	background_color:0x00FFFFFF
	on_mouse:[ 
		@component{name:"按钮1" background_y:-80} 
		@animation{ component:"转盘" transparency:1 rotation:0 time:0.3 add_mode:"Merge"} 
		@animation{ component:"按钮1下划线" x:0 time:0.3 add_mode:"Merge"} 
	]
	on_mouse_in:[
		@track{ name:"音效" src:"data/sounds/select.wav" loop:0 control:"Play" }
	]
	on_mouse_out:[ 
		@component{name:"按钮1" background_y:0} 		
		@animation{ component:"转盘" transparency:0 time:0.3} 
		@animation{ component:"按钮1下划线" x:-500 time:0.3 add_mode:"Merge"} 		
	]
	on_click:[ 
		@include{file:"script/main_menu_out.ks"} 
		@goTo{file:"script/sicily_init.ks"}
	]
}

@component{
	name:"按钮1下划线"
	width:500
	height:20
	x:-500
	y:340
	layer:3
	background_image:"data/images/menu_button_line.png"	
	background_color:0x00FFFFFF
}

PI = 3.1415926;

@component{
	name:"按钮2"
	width:350
	height:80
	x:-120
	transparency:0
	y:360
	layer:3
	background_y:0
	background_image:"data/images/button_continue.png"
	background_color:0x00FFFFFF
	on_mouse:[ 
		@component{name:"按钮2" background_y:-80} 
		@animation{ component:"转盘" transparency:1 rotation: -PI / 2 time:0.3 add_mode:"Merge"} 
		@animation{ component:"按钮2下划线" x:0 time:0.3 add_mode:"Merge"} 
	]
	on_mouse_in:[
		@track{ name:"音效" src:"data/sounds/select.wav" loop:0 control:"Play" }
	]
	on_mouse_out:[ 
		@component{name:"按钮2" background_y:0} 
		@animation{ component:"转盘" transparency:0 time:0.3} 
		@animation{ component:"按钮2下划线" x:-500 time:0.3 add_mode:"Merge"} 
	]
	on_click:[ 
		@include{file:"script/main_menu_out.ks"} 
		@goTo{file:"script/sicily_init.ks"} 
	]
}

@component{
	name:"按钮2下划线"
	width:500
	height:20
	x:-500
	y:420
	layer:3
	background_image:"data/images/menu_button_line.png"	
	background_color:0x00FFFFFF
}

@component{
	name:"按钮3"
	width:350
	height:80
	x:-120
	transparency:0
	y:440
	layer:3
	background_y:0
	background_image:"data/images/button_configure.png"
	background_color:0x00FFFFFF
	on_mouse:[ 
		@component{name:"按钮3" background_y:-80} 
		@animation{ component:"转盘" transparency:1 rotation: -PI time:0.3 add_mode:"Merge"} 
		@animation{ component:"按钮3下划线" x:0 time:0.3 add_mode:"Merge"} 
	]
	on_mouse_in:[
		@track{ name:"音效" src:"data/sounds/select.wav" loop:0 control:"Play" }
	]
	on_mouse_out:[ 
		@component{name:"按钮3" background_y:0} 
		@animation{ component:"转盘" transparency:0 time:0.3}
		@animation{ component:"按钮3下划线" x:-500 time:0.3 add_mode:"Merge"}
	]
	on_click:[ 
		@execute{file:"http://www.sprabbit.com/spengine/tutorial.html"}
	]
}

@component{
	name:"按钮3下划线"
	width:500
	height:20
	x:-500
	y:500
	layer:3
	background_image:"data/images/menu_button_line.png"	
	background_color:0x00FFFFFF
}

@component{
	name:"按钮4"
	width:350
	height:80
	x:-100
	transparency:0
	y:520
	layer:3
	background_y:0
	background_image:"data/images/button_shutdown.png"
	background_color:0x00FFFFFF
	on_mouse:[ 
		@component{name:"按钮4" background_y:-80} 
		@animation{ component:"转盘" transparency:1 rotation: PI / 2 time:0.3 add_mode:"Merge"}
		@animation{ component:"按钮4下划线" x:0 time:0.3 add_mode:"Merge"} 
	]
	on_mouse_in:[
		@track{ name:"音效" src:"data/sounds/select.wav" loop:0 control:"Play" }
	]
	on_mouse_out:[
		@component{name:"按钮4" background_y:0} 
		@animation{ component:"转盘" transparency:0 time:0.3} 
		@animation{ component:"按钮4下划线" x:-500 time:0.3 add_mode:"Merge"}
	]
	on_click:[
		@include{file:"script/main_menu_out.ks"} 
		@exit; 
	]
}

@component{
	name:"按钮4下划线"
	width:500
	height:20
	x:-500
	y:580
	layer:3
	background_image:"data/images/menu_button_line.png"	
	background_color:0x00FFFFFF
}

////////////////////////////////////////////////////////////////////////////

// 背景动画
@animation{
	component:"背景"
	transparency:1
	time:1
	replay:"FastIn"
	can_skip:false
}

@animation{
	component:"背景2"
	transparency:1
	time:1
	replay:"FastIn"
	can_skip:false
}

// 标题动画
@animation{
	component:"标题"
	transparency:1
	time:1
	x:-100
	replay:"FastIn"
	can_skip:false
}

// LOGO动画
@animation{
	component:"copyright"
	layer:1
	transparency:1
	time:1
	replay:"FastIn"
	can_skip:false
}

// 按钮1飞出动画
@animation{
	component:"按钮1"
	x:50
	transparency:1
	time:1
	replay:"FastIn"
	can_skip:false
}

@waitTime{ time:0.2 }

// 按钮2飞出动画
@animation{
	component:"按钮2"
	x:80
	transparency:1
	time:1
	replay:"FastIn"
	can_skip:false
}

@waitTime{ time:0.2 }

// 按钮3飞出动画
@animation{
	component:"按钮3"
	x:110
	transparency:1
	time:1
	replay:"FastIn"
	can_skip:false
}

@waitTime{ time:0.2 }

// 按钮4飞出动画
@animation{
	component:"按钮4"
	x:80
	transparency:1
	time:1
	replay:"FastIn"
	can_skip:false
}