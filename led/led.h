/*************************************************************************
	> File Name: led.h
	> Author: Guiwen Zhou
	> Mail: 
	> Created Time: Mon 13 Nov 2017 04:14:18 AM PST
 ************************************************************************/

#ifndef _LED_H
#define _LED_H

#define GPC0CON 0xE0200060
#define GPC0DAT 0xE0200064
#define LED_MAGIC 'l'
#define LED_OFF _IO(LED_MAGIC,0)
#define LED_ON _IO(LED_MAGIC,1)

#endif
