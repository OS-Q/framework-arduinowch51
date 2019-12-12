/****************************???????*********************************/


extern U8 Rxflag;
extern U8 systatus;
extern U8 xdata data_store[256];
extern U8 xdata data_received[64];
extern U8 ptr;
extern U8 begin_flag ;
extern U8 led_number;
extern U8 led_lck ;
extern U8 num;

void Init_I2C(void);
void I2C_Error(void);
void I2C_Process(UINT8 u8DAT);

void i2c_send_task(void);
void i2c_wait_task(void);