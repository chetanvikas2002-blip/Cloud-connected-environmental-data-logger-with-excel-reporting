#ifndef _ESP01_H_
#define _ESP01_H_

int esp01_connectAP_AT(void); 
int esp01_connectAP_ATE0(void);
int esp01_connectAP_TCP_MODE(void);
int esp01_connectAP_QUIT_AP(void);
int esp01_connectAP_JOIN_AP(void);
int esp01_sendToThingspeak(int ,int );
void update_data(int ,int num);
void init_esp01(void);
#endif
