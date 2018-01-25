

void draw(signed short x_b,signed short y_b,signed short x_o,signed short y_o,char inverse);
void draw_rectangle(signed short x_b,signed short y_b,signed short x_o,signed short y_o,char solid,char inverse);	   
void draw_ptr(char x_b,char y_b,char ptr,char vol);
void plot(signed short x_b,signed short y_b,unsigned long data,signed short len,char inverse);
void graphic_print(signed short x_b,signed short y_b,signed short x_l,signed short y_l,signed short x_d,signed short y_d,const char* adress,char inverse);
void graphic_print_text(signed short x_b,signed short y_b,const char* bgnd,signed short num,signed short data,signed short des,signed short pos,char inverse);
void graphic_print_text_text(signed short x_b,signed short y_b,const char* bgnd,signed short num,signed short data,signed short des,signed short pos,char inverse);
