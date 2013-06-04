#include "global.h"
#include "../AntTweakBar/AntTweakBar.h"
#include "../util.h"

#include <Windows.h>
#include <string>

using namespace std;

const static char sBarName[] = "rpyEditor";

static TwBar* s_bar;

void add_AntTweakBar(){

	//AntTweakBarを初期化
	TwInit(TW_DIRECT3D9, g_D3DDev);

	TwWindowSize(640,480);

	// Create a tweak bar
	s_bar = TwNewBar(sBarName);
    TwDefine(" GLOBAL help='th125RpyEditor\n 日本後テスト !' "); // Message added to the help bar.
	
	string bar_define = from_format("%s color='128 224 160' text=dark ",sBarName);
    TwDefine(bar_define.c_str()); // Change TweakBar color and use dark text

    /*// Add 'numSec' to 'bar': it is a modifiable (RW) variable of type TW_TYPE_INT32. Its shortcuts are [s] and [S].
    TwAddVarRW(bar, "NumSec", TW_TYPE_INT32, &numSec, 
               " label='Strip length' min=1 max=1000 keyIncr=s keyDecr=S help='Number of segments of the strip.' ");

    // Add 'color' to 'bar': it is a modifiable variable of type TW_TYPE_COLOR3F (3 floats color)
    TwAddVarRW(bar, "Color", TW_TYPE_COLOR3F, &color, " label='Strip color' ");

    // Add 'bgColor' to 'bar': it is a modifiable variable of type TW_TYPE_COLOR32 (32 bits color)
    TwAddVarRW(bar, "BgColor", TW_TYPE_COLOR32, &bgColor, " label='Background color' ");
	*/
}