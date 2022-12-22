#include <mbed.h>
#include "QT2160/QT2160.h"
#include "RGB_Controller/TLC59116.h"

#define I2C_SDA p28
#define I2C_SCL p27
#define RGB_I2C_ADDR_1 0x63      // U2 RGB LED DRIVER I2C Address

#define BLUE_LEFT     0
#define GREEN_LEFT    1
#define RED_LEFT      2

#define BLUE_MIDDLE   3
#define GREEN_MIDDLE  4
#define RED_MIDDLE    5

#define BLUE_RIGHT    6
#define GREEN_RIGHT   7
#define RED_RIGHT     8

I2C i2c(I2C_SDA, I2C_SCL);     // sda, sc1
InterruptIn change_pin(QT_CHANGE_PIN);
Touch_Manager touch_manager(&i2c);

TLC59116 ledDriver(i2c, (RGB_I2C_ADDR_1 << 1));

Timer touch_1_timer;
Timer touch_2_timer;
Timer touch_3_timer;

Thread qt_thread;
EventQueue qt_queue;

bool right_touch_act_flag = true;
bool left_touch_act_flag = true;
bool middle_touch_act_flag = true;

bool flag = false;
int activity_rgb_timer = 1500; // inactive time in miliseconds
int model = 3;                 // Select Gang, 1 --> 1 Gang, 2 --> 2 Gang, 3 --> 3 Gang

void qt_isr_cb();
void qt_isr()
{
  qt_queue.call(qt_isr_cb);
}

int main() {

  uint8_t chip_id = 0;
  uint8_t code_version = 0;

  printf("---------------------QT2160---------------------\n");

  change_pin.mode(PullUp);
  qt_thread.start(callback(&qt_queue, &EventQueue::dispatch_forever));

  // change pin call back
  change_pin.fall(qt_isr);

  // Clear Status registry
  qt_isr_cb();

  // get chip info
  touch_manager.qt_get_chip_id(&chip_id);
  touch_manager.qt_get_code_version(&code_version);

  // set LED to OFF
  float value = 0;
  ledDriver.setChannel(RED_RIGHT, value);
  ledDriver.setChannel(RED_MIDDLE, value);
  ledDriver.setChannel(RED_LEFT, value);

  while(1) 
  {
    auto _touch_1_time =(chrono::duration_cast<chrono::milliseconds>(touch_1_timer.elapsed_time())).count();
    if( _touch_1_time > activity_rgb_timer && right_touch_act_flag == false)
    { 
      ledDriver.setChannel(RED_RIGHT, 0);
      right_touch_act_flag = true;
      touch_1_timer.stop();
      touch_1_timer.reset();
    }

    auto _touch_2_time =(chrono::duration_cast<chrono::milliseconds>(touch_2_timer.elapsed_time())).count();
    if( _touch_2_time > activity_rgb_timer && middle_touch_act_flag == false)
    {  
      ledDriver.setChannel(RED_MIDDLE, 0);
      middle_touch_act_flag = true;
      touch_2_timer.stop();
      touch_2_timer.reset();
    }
    
    auto _touch_3_time =(chrono::duration_cast<chrono::milliseconds>(touch_3_timer.elapsed_time())).count();
    if( _touch_3_time > activity_rgb_timer && left_touch_act_flag == false)
    {  
      ledDriver.setChannel(RED_LEFT, 0);
      left_touch_act_flag = true;
      touch_3_timer.stop();
      touch_3_timer.reset();
    }
  }
}



void qt_isr_cb()
{
  Touch_Manager::QTStatusFlag status_flag;
  touch_manager.qt_read_status(&status_flag);

  char new_button_status = status_flag.status;

  float value = 127;
  printf("QT read [status] 0x%02X, [KS1] 0x%02X\n", status_flag.status, status_flag.ks1);

  if(model == 3 || model == 2)
  {
    if(right_touch_act_flag)
    {
      if ((new_button_status & 0x01) == 1) 
      {
        ledDriver.setChannel(RED_RIGHT, value);
        printf("Touch Right\n");
        right_touch_act_flag = false;
        touch_1_timer.start();
      }
    }

    if(left_touch_act_flag)
    {
      if ((new_button_status & 0x04) == 4) 
      {
        ledDriver.setChannel(RED_LEFT, value);
        printf("Touch Left\n");
        left_touch_act_flag = false;
        touch_3_timer.start();
      }
    }
  }

  if(model != 2)
  {
    if(middle_touch_act_flag)
    {
      if ((new_button_status & 0x02) == 2) 
      {
        ledDriver.setChannel(RED_MIDDLE, value);
        printf("Touch Middle\n");
        middle_touch_act_flag = false;
        touch_2_timer.start();
      }
    }
  }
}
