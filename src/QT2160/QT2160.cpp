#include "QT2160/QT2160.h"

Touch_Manager::Touch_Manager(I2C *i2c):
_i2c(i2c)
{}

void Touch_Manager::qt_setup() {

  printf("QT Setup Init Start\n");
  _i2c->start();

  char touch_write_buffer[2];

  touch_write_buffer[0] = 10;
  touch_write_buffer[1] = 1;
  _i2c->write(QT_I2C_ADDRESS, touch_write_buffer, 2);  // calibarate mode
  wait_us(50000);
  // printf(".");

  touch_write_buffer[0] = 12;
  touch_write_buffer[1] = LP_MODE;
  _i2c->write(QT_I2C_ADDRESS, touch_write_buffer, 2);  // LP mode
  wait_us(50000);
  // printf(".");

  touch_write_buffer[0] = 13;
  // touch_write_buffer[1] = BREP; // 2
  touch_write_buffer[1] = BURST_REPETITION;
  _i2c->write(QT_I2C_ADDRESS, touch_write_buffer, 2);  // burst repatition
  wait_us(50000);
  // printf(".");

  touch_write_buffer[0] = 15;
  // touch_write_buffer[1] = NDRIFT; //4
  touch_write_buffer[1] = NEGATIVE_DRIFT;
  _i2c->write(QT_I2C_ADDRESS, touch_write_buffer, 2);  // negativr drift
  wait_us(50000);
  // printf(".");

  touch_write_buffer[0] = 16;
  // touch_write_buffer[1] = PDRIFT; // 1
  touch_write_buffer[1] = POSITIVE_DRIFT;
  _i2c->write(QT_I2C_ADDRESS, touch_write_buffer, 2);  // positive drift
  wait_us(50000);
  // printf(".");

  touch_write_buffer[0] = 17;
  // touch_write_buffer[1] = NDIL;
  touch_write_buffer[1] = DETECT_INTEGRATOR;
  _i2c->write(QT_I2C_ADDRESS, touch_write_buffer, 2);  // detectr intergator
  wait_us(50000);                                   // di
  // printf(".");

  touch_write_buffer[0] = 18;
  touch_write_buffer[1] = NEGATIVE_DELAY;
  _i2c->write(QT_I2C_ADDRESS, touch_write_buffer, 2);  // neative delay
  wait_us(50000);
  // printf(".");

  touch_write_buffer[0] = 19;
  touch_write_buffer[1] = DRIFT_HOLD_WAKEUP;
  _i2c->write(QT_I2C_ADDRESS, touch_write_buffer, 2);  // Drift hold wake up
  wait_us(50000);
  // printf(".");

  touch_write_buffer[0] = 20;
  touch_write_buffer[1] = SLIDER_CONTROL;
  _i2c->write(QT_I2C_ADDRESS, touch_write_buffer, 2);  // Slider control
  wait_us(50000);
  // printf(".");

  touch_write_buffer[0] = 21;
  touch_write_buffer[1] = SLIDER_OPTION;
  _i2c->write(QT_I2C_ADDRESS, touch_write_buffer, 2);  // slidr options
  wait_us(50000);
  // printf(".");

  touch_write_buffer[0] = 22;
  touch_write_buffer[1] = KEY_CONTROL_ASK;
  _i2c->write(QT_I2C_ADDRESS, touch_write_buffer, 2);  // key control ask group 22-37
  wait_us(50000);
  // printf(".");

  touch_write_buffer[0] = 23;
  touch_write_buffer[1] = KEY_CONTROL_ASK;
  _i2c->write(QT_I2C_ADDRESS, touch_write_buffer, 2);  //
  wait_us(50000);
  // printf(".");

  touch_write_buffer[0] = 24;
  touch_write_buffer[1] = KEY_CONTROL_ASK;
  _i2c->write(QT_I2C_ADDRESS, touch_write_buffer, 2);  //
  wait_us(50000);
  // printf(".");

  touch_write_buffer[0] = 38;
  // touch_write_buffer[1] = NTHR_1;
  touch_write_buffer[1] = NEGATIVE_THRESHOLD_RIGHT_KEY;
  _i2c->write(QT_I2C_ADDRESS, touch_write_buffer, 2);  // negative threshold
  wait_us(50000);
  // printf(".");
  touch_write_buffer[0] = 39;
  // touch_write_buffer[1] = NTHR_2;
  touch_write_buffer[1] = NEGATIVE_THRESHOLD_MIDDLE_KEY;
  _i2c->write(QT_I2C_ADDRESS, touch_write_buffer, 2);
  wait_us(50000);
  // printf(".");
  touch_write_buffer[0] = 40;
  // touch_write_buffer[1] = NTHR_3;
  touch_write_buffer[1] = NEGATIVE_THRESHOLD_LEFT_KEY;
  _i2c->write(QT_I2C_ADDRESS, touch_write_buffer, 2);
  wait_us(50000);
  // printf(".");

  touch_write_buffer[0] = 54;
  // touch_write_buffer[1] = BL;
  touch_write_buffer[1] = BURST_LEBGTH_RIGHT_KEY;
  _i2c->write(QT_I2C_ADDRESS, touch_write_buffer, 2);  // burst length
  wait_us(50000);
  // printf(".");

  touch_write_buffer[0] = 55;
  // touch_write_buffer[1] = BL;
  touch_write_buffer[1] = BURST_LEBGTH_MIDDLE_KEY;
  _i2c->write(QT_I2C_ADDRESS, touch_write_buffer, 2);
  wait_us(50000);
  // printf(".");

  touch_write_buffer[0] = 56;
  // touch_write_buffer[1] = BL;
  touch_write_buffer[1] = BURST_LEBGTH_LEFT_KEY;
  _i2c->write(QT_I2C_ADDRESS, touch_write_buffer, 2);
  wait_us(50000);
  // printf(".\n");

  // disable all other keys by setting burst length 0
  for(uint8_t a = 57; a <= 69; a++)
  {
    touch_write_buffer[0] = a;
    touch_write_buffer[1] = DISABLE_KEY;
    _i2c->write(QT_I2C_ADDRESS, touch_write_buffer, 2);
    wait_us(50000);
  }

  touch_write_buffer[0] = 10;
  touch_write_buffer[1] = 0;
  _i2c->write(QT_I2C_ADDRESS, touch_write_buffer, 2);  // end callibaration
  wait_us(50000);

  _i2c->stop();
  printf("QT Setup Finish\n");
  // printf("Calibration - [OK].\n");
}

void Touch_Manager::qt_read(char* data) {
  char touch_write_buffer[2];

  touch_write_buffer[0] = 0x02;
  _i2c->write(QT_I2C_ADDRESS, touch_write_buffer, 1);
  wait_us(1000);
  _i2c->read(QT_I2C_ADDRESS, data, 5);
  wait_us(1000);
  touch_write_buffer[0] = 0x03;
  _i2c->write(QT_I2C_ADDRESS, touch_write_buffer, 1);
  wait_us(1000);
  _i2c->read(QT_I2C_ADDRESS, data, 2);
  wait_us(1000);
}

void Touch_Manager::qt_read_status(QTStatusFlag* status_flag) {
  char touch_read_buffer[5];
  qt_read(touch_read_buffer);
  status_flag->status = touch_read_buffer[0];
  status_flag->ks1 = touch_read_buffer[1];
  status_flag->ks2 = touch_read_buffer[2];
  status_flag->slider_pos = touch_read_buffer[3];
  status_flag->gpiod = touch_read_buffer[4];
  // printf("status read\n");
}

void Touch_Manager::qt_get_chip_id(uint8_t* chip_id)
{
  char touch_write_buffer[2];
  char temp_data[2];

  touch_write_buffer[0] = 0x00;
  _i2c->write(QT_I2C_ADDRESS, touch_write_buffer, 1);
  wait_us(1000);
  _i2c->read(QT_I2C_ADDRESS, temp_data, 1);
  wait_us(5000);


  *chip_id = temp_data[0];
  printf("Chip ID: 0x%2X\n", *chip_id);
}

void Touch_Manager::qt_get_code_version(uint8_t* code_version)
{
  char touch_write_buffer[2];
  char temp_data[2];

  touch_write_buffer[0] = 0x01;
  _i2c->write(QT_I2C_ADDRESS, touch_write_buffer, 1);
  wait_us(1000);
  _i2c->read(QT_I2C_ADDRESS, temp_data, 1);
  wait_us(1000);

  *code_version = temp_data[0];
  printf("Code version : %d.%d\n", (*code_version >> 0x04), (*code_version && 0x0F));
}