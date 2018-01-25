
#define RX_BUFFER_SIZE2 1024
#define TX_BUFFER_SIZE2 1024

//#define BUFSIZE    		1024

#define IER_RBR		0x01
#define IER_THRE		0x02
#define IER_RLS		0x04

//#define PT	(UIB2[1]&0x80)
//#define C_D	(UIB2[1]&0x40)
//#define FR	(UIB2[1]&0x20)

#define IIR_PEND	0x01
#define IIR_RLS		0x03
#define IIR_RDA		0x02
#define IIR_CTI		0x06
#define IIR_THRE	0x01

#define LSR_RDR		0x01
#define LSR_OE		0x02
#define LSR_PE		0x04
#define LSR_FE		0x08
#define LSR_BI		0x10
#define LSR_THRE	0x20
#define LSR_TEMT	0x40
#define LSR_RXFE	0x80


extern char bRXIN2;
extern char UIB2[100];
extern char flag2;
extern char rx_buffer2[RX_BUFFER_SIZE2];
extern char tx_buffer2[TX_BUFFER_SIZE2];
extern unsigned short rx_wr_index2,rx_rd_index2,rx_counter2;
extern unsigned short tx_wr_index2,tx_rd_index2,tx_counter2;
extern char rx_buffer_overflow2;
extern char plazma_uart2;
extern char memo_out2[50];
extern char data_rs2[50];
extern char data_rs02[50];

void putchar2(char c);
void uart_out2 (char num,char data0,char data1,char data2,char data3,char data4,char data5);
void uart_out_adr2 (char *ptr, char len);
void uart0_init(void);
char getchar0(void);
__irq void uart0_interrupt(void);
void uart_in_an2(void);
signed short index_offset2 (signed short index,signed short offset);
char control_check2(signed short index);
void uart_in0(void);
void uart_out_adr2_block (unsigned long adress,char *ptr, char len);
uint32_t UART_2_Init(uint32_t baudrate );
void uart_in2(void); 


