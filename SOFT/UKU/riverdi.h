
#define PD_LOW 		LPC_GPIO2->FIODIR|=(1<<8);	LPC_GPIO2->FIOCLR|=(1<<8);
#define PD_HIGH 	LPC_GPIO2->FIODIR|=(1<<8);	LPC_GPIO2->FIOSET|=(1<<8);

#define RIV_CS 20
#define RIV_CS_ON       LPC_GPIO0->FIODIR|=(1UL<<RIV_CS);LPC_GPIO0->FIOCLR|=(1UL<<RIV_CS);
#define RIV_CS_OFF      LPC_GPIO0->FIODIR|=(1UL<<RIV_CS);LPC_GPIO0->FIOSET|=(1UL<<RIV_CS);

void delayus(int us);
void spi1_config(void);
void spi1_unconfig(void);
char spi1(char in);

//-----------------------------------------------
char rd8(long addr);
//-----------------------------------------------
short rd16(long addr);
//-----------------------------------------------
int rd32(long addr);
//-----------------------------------------------
char wr8(long addr, char in);
//-----------------------------------------------
char wr16(long addr, short in);
//-----------------------------------------------
char wr32(long addr, int in);
//-----------------------------------------------
void command_active(void);
//-----------------------------------------------
void host_command(char cmd);




#define INTERNAL_OSC 	0x48
#define EXTERNAL_OSC 	0x44
#define SLEEP 			0x42

#define SYSCLK_72M 		0x06
#define SYSCLK_60M 		0x05
#define SYSCLK_48M 		0x04
#define SYSCLK_36M 		0x03
#define SYSCLK_24M 		0x02
#define CORE_RESET  	0x68


#define REG_ID			0x302000
#define REG_FREQUENCY  	0x30200C
#define REG_HCYCLE		0x30202C
#define REG_HOFFSET		0x302030
#define REG_HSYNC0		0x302038
#define REG_HSYNC1		0x30203c
#define REG_VCYCLE		0x302040
#define REG_VOFFSET		0x302044
#define REG_VSYNC0		0x30204C
#define REG_VSYNC1		0x302050
#define REG_SWIZZLE		0x302064
#define REG_PCLK_POL	0x30206C
#define REG_HSIZE		0x302034
#define REG_VSIZE		0x302048
#define REG_CSPREAD  	0x302068
#define REG_DITHER		0x302060
#define REG_GPIO_DIR 	0x302090
#define REG_GPIO 		0x302094
#define REG_GPIOX_DIR 	0x302098
#define REG_GPIOX  		0x30209C
#define REG_DLSWAP	 	0x302054
#define REG_PCLK		0x302070 

#define REG_CTOUCH_TOUCH0_XY 3154212UL
#define REG_CTOUCH_TOUCH4_X  3154284UL
#define REG_CTOUCH_TOUCH4_Y  3154208UL
#define REG_CTOUCH_TOUCH1_XY 3154204UL
#define REG_CTOUCH_TOUCH2_XY 3154316UL
#define REG_CTOUCH_TOUCH3_XY 3154320UL
#define REG_CYA_TOUCH        3154280UL

#define REG_TOUCH_ADC_MODE   3154184UL
#define REG_TOUCH_CHARGE     3154188UL
#define REG_TOUCH_DIRECT_XY  3154316UL
#define REG_TOUCH_DIRECT_Z1Z2 3154320UL
#define REG_TOUCH_FAULT      3154288UL
#define REG_TOUCH_MODE       3154180UL
#define REG_TOUCH_OVERSAMPLE 3154196UL
#define REG_TOUCH_RAW_XY     3154204UL
#define REG_TOUCH_RZ         3154208UL
#define REG_TOUCH_RZTHRESH   3154200UL
#define REG_TOUCH_SCREEN_XY  3154212UL
#define REG_TOUCH_SETTLE     3154192UL
#define REG_TOUCH_TAG        3154220UL
#define REG_TOUCH_TAG1       3154228UL
#define REG_TOUCH_TAG1_XY    3154224UL
#define REG_TOUCH_TAG2       3154236UL
#define REG_TOUCH_TAG2_XY    3154232UL
#define REG_TOUCH_TAG3       3154244UL
#define REG_TOUCH_TAG3_XY    3154240UL
#define REG_TOUCH_TAG4       3154252UL
#define REG_TOUCH_TAG4_XY    3154248UL
#define REG_TOUCH_TAG_XY     3154216UL
#define REG_TOUCH_TRANSFORM_A 3154256UL
#define REG_TOUCH_TRANSFORM_B 3154260UL
#define REG_TOUCH_TRANSFORM_C 3154264UL
#define REG_TOUCH_TRANSFORM_D 3154268UL
#define REG_TOUCH_TRANSFORM_E 3154272UL
#define REG_TOUCH_TRANSFORM_F 3154276UL

#define DispWidth 		800
#define DispHeight 		480
#define DispHCycle 		1056
#define DispHOffset 	46
#define DispHSync0 		0
#define DispHSync1 		10
#define DispVCycle 		525
#define DispVOffset 	23
#define DispVSync0 		0
#define DispVSync1 		10
#define DispPCLK 		2
#define DispSwizzle 	0
#define DispPCLKPol 	0


#define RAM_DL          0x300000
#define DLSWAP_FRAME         2UL
#define BITMAPS              1UL
#define POINTS             2UL


#define VERTEX2F(x,y) ((1UL<<30)|(((x)&32767UL)<<15)|(((y)&32767UL)<<0))
#define VERTEX2II(x,y,handle,cell) ((2UL<<30)|(((x)&511UL)<<21)|(((y)&511UL)<<12)|(((handle)&31UL)<<7)|(((cell)&127UL)<<0))
#define BITMAP_SOURCE(addr) ((1UL<<24)|(((addr)&4194303UL)<<0))
#define CLEAR_COLOR_RGB(red,green,blue) ((2UL<<24)|(((red)&255UL)<<16)|(((green)&255UL)<<8)|(((blue)&255UL)<<0))
#define TAG(s) ((3UL<<24)|(((s)&255UL)<<0))
#define COLOR_RGB(red,green,blue) ((4UL<<24)|(((red)&255UL)<<16)|(((green)&255UL)<<8)|(((blue)&255UL)<<0))
#define BITMAP_HANDLE(handle) ((5UL<<24)|(((handle)&31UL)<<0))
#define CELL(cell) ((6UL<<24)|(((cell)&127UL)<<0))
#define BITMAP_LAYOUT(format,linestride,height) ((7UL<<24)|(((format)&31UL)<<19)|(((linestride)&1023UL)<<9)|(((height)&511UL)<<0))
#define BITMAP_SIZE(filter,wrapx,wrapy,width,height) ((8UL<<24)|(((filter)&1UL)<<20)|(((wrapx)&1UL)<<19)|(((wrapy)&1UL)<<18)|(((width)&511UL)<<9)|(((height)&511UL)<<0))
#define ALPHA_FUNC(func,ref) ((9UL<<24)|(((func)&7UL)<<8)|(((ref)&255UL)<<0))
#define STENCIL_FUNC(func,ref,mask) ((10UL<<24)|(((func)&7UL)<<16)|(((ref)&255UL)<<8)|(((mask)&255UL)<<0))
#define BLEND_FUNC(src,dst) ((11UL<<24)|(((src)&7UL)<<3)|(((dst)&7UL)<<0))
#define STENCIL_OP(sfail,spass) ((12UL<<24)|(((sfail)&7UL)<<3)|(((spass)&7UL)<<0))
#define POINT_SIZE(size) ((13UL<<24)|(((size)&8191UL)<<0))
#define LINE_WIDTH(width) ((14UL<<24)|(((width)&4095UL)<<0))
#define CLEAR_COLOR_A(alpha) ((15UL<<24)|(((alpha)&255UL)<<0))
#define COLOR_A(alpha) ((16UL<<24)|(((alpha)&255UL)<<0))
#define CLEAR_STENCIL(s) ((17UL<<24)|(((s)&255UL)<<0))
#define CLEAR_TAG(s) ((18UL<<24)|(((s)&255UL)<<0))
#define STENCIL_MASK(mask) ((19UL<<24)|(((mask)&255UL)<<0))
#define TAG_MASK(mask) ((20UL<<24)|(((mask)&1UL)<<0))
#define BITMAP_TRANSFORM_A(a) ((21UL<<24)|(((a)&131071UL)<<0))
#define BITMAP_TRANSFORM_B(b) ((22UL<<24)|(((b)&131071UL)<<0))
#define BITMAP_TRANSFORM_C(c) ((23UL<<24)|(((c)&16777215UL)<<0))
#define BITMAP_TRANSFORM_D(d) ((24UL<<24)|(((d)&131071UL)<<0))
#define BITMAP_TRANSFORM_E(e) ((25UL<<24)|(((e)&131071UL)<<0))
#define BITMAP_TRANSFORM_F(f) ((26UL<<24)|(((f)&16777215UL)<<0))
#define SCISSOR_XY(x,y) ((27UL<<24)|(((x)&2047UL)<<11)|(((y)&2047UL)<<0))
#define SCISSOR_SIZE(width,height) ((28UL<<24)|(((width)&4095UL)<<12)|(((height)&4095UL)<<0))
#define CALL(dest) ((29UL<<24)|(((dest)&65535UL)<<0))
#define JUMP(dest) ((30UL<<24)|(((dest)&65535UL)<<0))
#define BEGIN(prim) ((31UL<<24)|(((prim)&15UL)<<0))
#define COLOR_MASK(r,g,b,a) ((32UL<<24)|(((r)&1UL)<<3)|(((g)&1UL)<<2)|(((b)&1UL)<<1)|(((a)&1UL)<<0))
#define CLEAR(c,s,t) ((38UL<<24)|(((c)&1UL)<<2)|(((s)&1UL)<<1)|(((t)&1UL)<<0))
#define VERTEX_FORMAT(frac) ((39UL<<24)|(((frac)&7UL)<<0))
#define BITMAP_LAYOUT_H(linestride,height) ((40UL<<24)|(((linestride)&3UL)<<2)|(((height)&3UL)<<0))
#define BITMAP_SIZE_H(width,height) ((41UL<<24)|(((width)&3UL)<<2)|(((height)&3UL)<<0))
#define PALETTE_SOURCE(addr) ((42UL<<24)|(((addr)&4194303UL)<<0))
#define VERTEX_TRANSLATE_X(x) ((43UL<<24)|(((x)&131071UL)<<0))
#define VERTEX_TRANSLATE_Y(y) ((44UL<<24)|(((y)&131071UL)<<0))
#define NOP() ((45UL<<24))
#define END() ((33UL<<24))
#define SAVE_CONTEXT() ((34UL<<24))
#define RESTORE_CONTEXT() ((35UL<<24))
#define RETURN() ((36UL<<24))
#define MACRO(m) ((37UL<<24)|(((m)&1UL)<<0))
#define DISPLAY() ((0UL<<24))

#define OPT_CENTER           1536UL