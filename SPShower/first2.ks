////////////////////////////////////////////////////////////////////////////
// Demo script of SPShower Alpha 0.8
//
// Author: Ken.J
// Date: 2012-08-19
////////////////////////////////////////////////////////////////////////////

// Setting a screen
@screen{
	name:"sicily"
};

@component{
	name:"black"
	background_color: 0xFF000000
	width:800
	height:600
	layer:1
};

// Set picture box
@picture{ name:"sicily" src:"data/images/sicily.jpg" };
@pictureBox{
	name:			"哈"
	picture:		"sicily"
	fill_mode:		"Positioning"
	position_mode:	"CenterAll"
	width:800
	height:600
	layer:2
};

// Set a component
@component{
	name : "com"
	layer : 3
	width : 728
	height : 728
	background_color : 0x00000000
	background_image : "data/images/st_01.png"
};

////////////////////////////////////////////////////////////////////////////

@sound{ name:"bg" src:"bgm09.ogg" control:"Play" loop: -1};

// Add a begin tag
@tag{name:"begin"};

// Set another screen
@screen{
	name: "display"
};

// Define a font
@registerFont{src:"font/FZMWFont.ttf"};
@font{name:"wm" size:30 font:"方正喵呜体" weight:9};

// Define a font
@font{name:"yh" size:40 font:"微软雅黑" weight:"Bold"};

// Set a text box 
@textBox{ 
	name:"text"
	layer:2
	padding:20
	background_color: 0x11000000
	width: 400
	height:300
	x:100
	y:100
	layer:5
	rotation_center_x: 100
	rotation_center_y: 100
	word_space: 0.2
	line_space: 0.2
	color: 0xFFFFFFFF
	font:"yh"
};

/////////////////////////////////////////////////////////////////////////////

// Add text to text box
@addText{
	box:"text"
	content:"大家好，欢迎使用SPShower图文演示系统Alpha0.8。"
};

/////////////////////////////////////////////////////////////////////////////

// Wait for clicking
@waitClick;

@script{content:"	

	@clearText{
		box:'text'
		content:'这里测试内部脚本调用。'
	};

	@waitClick;

"};

// Add text to text box
@clearText{
	box:"text"
	content:"这里是可以显示文字的文字框。"
};

/////////////////////////////////////////////////////////////////////////////

// Wait for clicking
@waitClick;

// Add text to text box
@clearText{
	box:"text"
	content:"这样演示可能比较单调，"
	color:0xFFAAFFFF
};

/////////////////////////////////////////////////////////////////////////////

// Wait for clicking
@waitClick;

// Add text to text box
@addText{
	box:"text"
	content:"我们先添加一个视频背景组件吧。"
	color:0xFFFFAAFF
};

// Wait for clicking
@waitClick;

@video{name:"bgv" src:"bgv.mov" loop:-1 control:"Play" flip:"None"};

@picture{
	name : "bgi"
	src : "data/images/bg_01.jpg"
	video : "bgv"
};

// Set a component
@pictureBox{
	name : "background"
	layer : 0
	width : 800
	height : 600
	background_color : 0x00000000
	picture : "bgi"
	fill_mode : "FitHeight"
};

@picture{
	name:"animeP"
	src:"data/images/loading.png"
	row:2
	col:4
	fps:30
};

@pictureBox{
	name:"anime"
	picture:"animeP"
	x:400
	y:300
	layer:10
};

/////////////////////////////////////////////////////////////////////////////

// Wait for clicking
@waitClick;

// Add text to text box
@addText{
	box:"text"
	content:"然后添加一个人物。"
};

// Wait for clicking
@waitClick;

// Set a component
@component{
	name : "com"
	layer : 1
	width : 728
	height : 728
	background_color : 0x00000000
	//background_image : "data/images/st_01.png"
	background_x : -100
	background_y : -100
	background_fill_mode : "Fill"
	//on_mouse : "@component{name : 'com' background_image : 'data/images/st_01.png'};"
	on_mouse_out : "@component{name : 'com' background_image : 'data/images/st_01.png'};"
	on_down : "@component{name : 'com' background_image : 'data/images/st_03.png'};"
	on_up : "@component{name : 'com' background_image : 'data/images/st_01_01.png'};"
};

/////////////////////////////////////////////////////////////////////////////

// Wait for clicking
@waitClick;

// Add text to text box
@addText{
	box:"text"
	content:"再加点文字特效。"
};

// Wait for clicking
@waitClick;

@textBox{
	name: "text"
	font: "wm"
	text_effect_front: "TextStroke"
	text_effect_front_tex: "data/images/black.png"
	text_effect_front_level: 2
	text_effect_front_opacity: 0.9
	text_effect_front_quality: 0.3
	text_effect_back: "TextGlow"
	text_effect_back_tex:"data/images/blue.png"
	text_effect_back_level: 15
	text_effect_back_opacity: 0.7
};

/////////////////////////////////////////////////////////////////////////////

// Wait for clicking
@waitClick;

// Set a component
@component{
	name : "com"
	//background_image : "data/images/st_01_01.png"
};

// Wait for clicking
@waitClick;

@animation{
	component: "text"
	x: 400
	y: 200
	width: 250
	height: 150
	background_color: 0xAAAAAAFF
	time: 2
	replay: "FastInOut"
};

@clearText{
	box:"text"
	content:"大家好，我是罗罗娜。"
	color:0xFFFFFFAA
};

// Go to begin, so that program not exit.
@goTo{src:"target_script.ks"};

/////////////////////////////////////////////////////////////////////////////

@waitClick;

@component{
	name : "com"
	background_image : "data/images/st_01.png"
};

@clearText{
	box:"text"
	content:"下面为大家演示图层叠加以及图像变换。"
};

@animation{
	component: "text"
	x: 20
	y: 20
	width: 400
	height: 200
	background_color: 0xAAAAAAFF
	time: 2
};

/////////////////////////////////////////////////////////////////////////////

@waitClick;

@clearText{
	box:"text"
	content:"首先是图层叠加。"
};

/////////////////////////////////////////////////////////////////////////////

@waitClick;

@clearText{
	box:"text"
	content:"右边这幅立绘是不包括Alpha通道的JPG。"
};

// Set a mixed picture
@picture{ name:"st_02" src:"data/images/st_02.jpg" };

// Set picture box
@pictureBox{
	name : "st"
	picture : "st_02"
	fill_mode :	"ResizeBox"
	position_mode : "Normal"
	x : 100
	y : -100
	layer : 2
};

/////////////////////////////////////////////////////////////////////////////

// Wait for clicking
@waitClick;

@clearText{
	box:"text"
	content:"然后叠加一幅黑白图上去。"
};

// Wait for clicking
@waitClick;

@mixPicture{ layer:1 src:"data/images/mask_st_02.jpg" };

////////////////////////////////////////////////////////////////////////////

// Wait for clicking
@waitClick;

@clearText{
	box:"text"
	content:"如果我们设置的叠加模式，就可以把两张图以某种方式混合。"
};

@waitClick;

@clearText{
	box:"text"
	content:"比如这样。"
};

// Wait for clicking
@waitClick;

@mixPicture{ layer:1 src:"data/images/mask_st_02.jpg" mix_mode:"Mask"};

////////////////////////////////////////////////////////////////////////////

// Set another picture
@picture{ name:"st_03" src:"data/images/st_03.png" };

// Set picture box
@pictureBox{
	name : "st"
	picture : "st_03"
	fill_mode :	"ResizeBox"
	position_mode : "Normal"
};

/////////////////////////////////////////////////////////////////////////////

// Wait for clicking
@waitClick;

@component{
	name : "com"
	background_image : "data/images/st_01_01.png"
};

@clearText{
	box:"text"
	content:"不好意思- -|||"
};

////////////////////////////////////////////////////////////////////////////

// Wait for clicking
@waitClick;

@clearText{
	box:"text"
	content:"应该是这样"
};

// Set picture box
@pictureBox{
	name : "st"
	picture : "st_02"
};

////////////////////////////////////////////////////////////////////////////

// Wait for clicking
@waitClick;

@clearText{
	box:"text"
	content:"除此之外，还有很多PS中的叠加样式。"
};

@component{
	name : "com"
	background_image : "data/images/st_01.png"
};

////////////////////////////////////////////////////////////////////////////

// Wait for clicking
@waitClick;

@clearText{
	box:"text"
	content:"比如下面这些。"
};

@picture{ name:"st_02" src:"data/images/st_02.jpg" };

////////////////////////////////////////////////////////////////////////////

@mixPicture{ layer:1 src:"data/images/mask_st_02.jpg" mix_mode:"ColorBurn"};

@waitTime{time:1};

////////////////////////////////////////////////////////////////////////////

@mixPicture{ layer:1 src:"data/images/mask_st_02.jpg" mix_mode:"Darken"};

@waitTime{time:1};

////////////////////////////////////////////////////////////////////////////

@mixPicture{ layer:1 src:"data/images/mask_st_02.jpg" mix_mode:"Difference"};

@waitTime{time:1};

////////////////////////////////////////////////////////////////////////////

@mixPicture{ layer:1 src:"data/images/mask_st_02.jpg" mix_mode:"Mask"};

////////////////////////////////////////////////////////////////////////////

// Wait for clicking
@waitClick;

@clearText{
	box:"text"
	content:"下面演示图像变换。"
};

////////////////////////////////////////////////////////////////////////////

// Wait for clicking
@waitClick;

@clearText{
	box:"text"
	content:"可以从一个人变成另一个人哦。"
};

////////////////////////////////////////////////////////////////////////////

// Wait for clicking
@waitClick;

// Switch picture with transformation
@switchPicture{
	box:"st" 
	target:"st_03"
	trans:"Fade" 
	time:5
};

////////////////////////////////////////////////////////////////////////////

// Wait for clicking
@waitClick;

@clearText{
	box:"text"
	content:"不过场景只能有一个吗？"
};

////////////////////////////////////////////////////////////////////////////

// Wait for clicking
@waitClick;

@clearText{
	box:"text"
	content:"当然不是，我们现在换到另一个屏幕吧。"
};

////////////////////////////////////////////////////////////////////////////

// Wait for clicking
@waitClick;

@clearText{
	box:"text"
	content:"点击鼠标换屏。。。"
};

PI = 3.1415926;

// Set an animation to the component
@animation{
	component: "text"
	x: 0
	y: 0
	width: 800
	height: 200
	rotation: 2 * PI
	rotation_center_x: 0
	rotation_center_y: 0
	background_color: 0x66FFFF00
	time:4
};

@animation{
	component: "text"
	x: 30
	y: 430
	width: 740
	height: 150
	background_color: 0xAAAAAAFF
	time:4
};

////////////////////////////////////////////////////////////////////////////

// Wait for clicking
@waitClick;

// Switch the screen with transformation
@switchScreen{ target:"sicily" trans:"Fade" time:5 };

// Wait for switching
@waitTime{time:5};

////////////////////////////////////////////////////////////////////////////

// Set a text box 
@textBox{ 
	name:"text"
	layer:4
	padding:20
	x: 30
	y: 430
	width: 740
	height: 150
	background_color: 0xAAAAAAFF
	word_space:0
	font: "wm"
};

@clearText{
	box:"text"
	content:"现在已经转换到另外一个屏幕了！"
};

@component{
	name : "com"
	background_image : "data/images/st_01_01.png"
};

////////////////////////////////////////////////////////////////////////////

@waitClick;

@clearText{
	box:"text"
	content:"现在我们来做更加有趣的事情！"
};

////////////////////////////////////////////////////////////////////////////

@waitClick;

@clearText{
	box:"text"
	content:"为这幅风景画添加特效！"
};

@component{
	name : "com"
	background_image : "data/images/st_01.png"
};

////////////////////////////////////////////////////////////////////////////

@waitClick;

@effect{
	component:"哈"
	effect:"Mask"
	time:5
	level:10
	effect_tex:"mask/mask_040.png"
};

@effect{
	component:"哈"
	effect:"Mask"
	time:5
	level:2
	effect_tex:"mask/mask_011.png"
};

@waitTime{time:10};

////////////////////////////////////////////////////////////////////////////

@waitClick;

@clearText{
	box:"text"
	content:"是不是很有趣！"
};

////////////////////////////////////////////////////////////////////////////

@waitClick;

@clearText{
	box:"text"
	content:"现在我们试下为他添加滤镜特效！"
};

////////////////////////////////////////////////////////////////////////////

@waitClick;

@clearText{
	box:"text"
	content:"这个是所谓的圆形马赛克"
};

@effect{
	component:"哈"
	effect:"Mosaic"
	time:5
	level:2
};

@waitTime{time:5};

////////////////////////////////////////////////////////////////////////////

@waitClick;

@clearText{
	box:"text"
	content:"我们来看看另外一种马赛克效果"
};

@effect{
	component:"哈"
	effect:"MosaicAll"
	time:5
	level:2
};

@waitTime{time:5};

////////////////////////////////////////////////////////////////////////////

@waitClick;

@clearText{
	box:"text"
	content:"除此之外还有很多风格化的滤镜效果"
};

@effect{
	component:"哈"
	effect:"Posure"
	time:3
	level:2
};

@waitTime{time:3};

////////////////////////////////////////////////////////////////////////////

@effect{
	component:"哈"
	effect:"Relievo"
	time:3
	level:2
};

@waitTime{time:3};

////////////////////////////////////////////////////////////////////////////

@effect{
	component:"哈"
	effect:"Pencil"
	time:3
	level:2
};

@waitTime{time:3};

////////////////////////////////////////////////////////////////////////////

@effect{
	component:"哈"
	effect:"Gray"
	time:3
	level:2
};

@waitTime{time:3};

////////////////////////////////////////////////////////////////////////////

@effect{
	component:"哈"
	effect:"Gauss"
	time:3
	level:2
};

@waitTime{time:3};

////////////////////////////////////////////////////////////////////////////

@clearText{
	box:"text"
	content:"演示到此结束，"
};

@addText{
	box:"text"
	content:"希望你能写出更有趣的脚本！"
};

////////////////////////////////////////////////////////////////////////////

// Go to begin, so that program not exit.
@goTo{tag:"begin"};

@exit;