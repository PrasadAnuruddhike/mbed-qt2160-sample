#ifndef QT2160_H
#define QT2160_H

#include "mbed.h"

#define QT_I2C_ADDRESS (0x44 << 1)

#define QT_CHANGE_PIN p18

#define RIGHT_KEY_CONTROL 0
#define MIDDLE_KEY_CONTROL 1
#define LEFT_KEY_CONTROL 2
// #define qt_address (0x44 << 1)

#define QT_REGISTER_ADDRESS_CALIBRATE               10
#define QT_REGISTER_ADDRESS_LP_MODE                 12
#define QT_REGISTER_ADDRESS_BURST_REPETITION        13
#define QT_REGISTER_ADDRESS_NEGATIVE_DRIFT          15
#define QT_REGISTER_ADDRESS_POSITIVE_DRIFT          16
#define QT_REGISTER_ADDRESS_NORMAL_DI               17
#define QT_REGISTER_ADDRESS_NEGATIVE_RECAL_DELAY    18
#define QT_REGISTER_ADDRESS_DRIFT_HOLD_TIME         19
#define QT_REGISTER_ADDRESS_SLIDER_CONTROL          20
#define QT_REGISTER_ADDRESS_SLIDER_OPTIONS          21
//-----------------------------------------------------
#define QT_REGISTER_ADDRESS_KEY_CONTROL0            22
#define QT_REGISTER_ADDRESS_KEY_CONTROL1            23
#define QT_REGISTER_ADDRESS_KEY_CONTROL2            24
#define QT_REGISTER_ADDRESS_KEY_CONTROL3            25
#define QT_REGISTER_ADDRESS_KEY_CONTROL4            26
#define QT_REGISTER_ADDRESS_KEY_CONTROL5            27
#define QT_REGISTER_ADDRESS_KEY_CONTROL6            28
#define QT_REGISTER_ADDRESS_KEY_CONTROL7            29
#define QT_REGISTER_ADDRESS_KEY_CONTROL8            30
#define QT_REGISTER_ADDRESS_KEY_CONTROL9            31
#define QT_REGISTER_ADDRESS_KEY_CONTROL10           32
#define QT_REGISTER_ADDRESS_KEY_CONTROL11           33
#define QT_REGISTER_ADDRESS_KEY_CONTROL12           34
#define QT_REGISTER_ADDRESS_KEY_CONTROL13           35
#define QT_REGISTER_ADDRESS_KEY_CONTROL14           36
#define QT_REGISTER_ADDRESS_KEY_CONTROL15           37
//-----------------------------------------------------
#define QT_REGISTER_ADDRESS_NEGATIVE_THRESHOLD0     38
#define QT_REGISTER_ADDRESS_NEGATIVE_THRESHOLD1     39
#define QT_REGISTER_ADDRESS_NEGATIVE_THRESHOLD2     40
#define QT_REGISTER_ADDRESS_NEGATIVE_THRESHOLD3     41
#define QT_REGISTER_ADDRESS_NEGATIVE_THRESHOLD4     42
#define QT_REGISTER_ADDRESS_NEGATIVE_THRESHOLD5     43
#define QT_REGISTER_ADDRESS_NEGATIVE_THRESHOLD6     44
#define QT_REGISTER_ADDRESS_NEGATIVE_THRESHOLD7     45
#define QT_REGISTER_ADDRESS_NEGATIVE_THRESHOLD8     46
#define QT_REGISTER_ADDRESS_NEGATIVE_THRESHOLD9     47
#define QT_REGISTER_ADDRESS_NEGATIVE_THRESHOLD10    48
#define QT_REGISTER_ADDRESS_NEGATIVE_THRESHOLD11    49
#define QT_REGISTER_ADDRESS_NEGATIVE_THRESHOLD12    50
#define QT_REGISTER_ADDRESS_NEGATIVE_THRESHOLD13    51
#define QT_REGISTER_ADDRESS_NEGATIVE_THRESHOLD14    52
#define QT_REGISTER_ADDRESS_NEGATIVE_THRESHOLD15    53
//-----------------------------------------------------
#define QT_REGISTER_ADDRESS_BURST_LENGTH0           54
#define QT_REGISTER_ADDRESS_BURST_LENGTH1           55
#define QT_REGISTER_ADDRESS_BURST_LENGTH2           56
#define QT_REGISTER_ADDRESS_BURST_LENGTH3           57
#define QT_REGISTER_ADDRESS_BURST_LENGTH4           58
#define QT_REGISTER_ADDRESS_BURST_LENGTH5           59
#define QT_REGISTER_ADDRESS_BURST_LENGTH6           60
#define QT_REGISTER_ADDRESS_BURST_LENGTH7           61
#define QT_REGISTER_ADDRESS_BURST_LENGTH8           62
#define QT_REGISTER_ADDRESS_BURST_LENGTH9           63
#define QT_REGISTER_ADDRESS_BURST_LENGTH10          64
#define QT_REGISTER_ADDRESS_BURST_LENGTH11          65
#define QT_REGISTER_ADDRESS_BURST_LENGTH12          66
#define QT_REGISTER_ADDRESS_BURST_LENGTH13          67
#define QT_REGISTER_ADDRESS_BURST_LENGTH14          68
#define QT_REGISTER_ADDRESS_BURST_LENGTH15          69

#define LP_MODE                                     1
#define BURST_REPETITION                            2
#define NEGATIVE_DRIFT                              4
#define POSITIVE_DRIFT                              1
#define DETECT_INTEGRATOR                           4
#define NEGATIVE_DELAY                              35
#define DRIFT_HOLD_WAKEUP                           25
#define SLIDER_CONTROL                              0
#define SLIDER_OPTION                               0
#define KEY_CONTROL_ASK                             1
#define NEGATIVE_THRESHOLD_RIGHT_KEY                7
#define NEGATIVE_THRESHOLD_MIDDLE_KEY               7
#define NEGATIVE_THRESHOLD_LEFT_KEY                 7
#define BURST_LEBGTH_RIGHT_KEY                      12
#define BURST_LEBGTH_MIDDLE_KEY                     12
#define BURST_LEBGTH_LEFT_KEY                       12
#define DISABLE_KEY                                 0

class Touch_Manager{
  public:
  Touch_Manager(I2C *i2c);
  struct QTStatusFlag {
    unsigned char status;
    unsigned char ks1;
    unsigned char ks2;
    unsigned char slider_pos;
    unsigned char gpiod;
  };

  struct QTSettings
  {
    char burst_length;
    char negative_threashold; 
    char burst_repetition;
    char negative_drift; 
    char positive_drift; 
    char detect_integrator;
  };
  
    struct QTRawData
  {
    uint16_t ref_left;
    uint16_t ref_middle;
    uint16_t ref_right;
    uint16_t sig_left;
    uint16_t sig_middle;
    uint16_t sig_right;
  };

  // void qt_setup(int model, int device_type);
  // void qt_read(char *data, QT_Registers reg, int size);
  // void qt_read_status(QTStatusFlag *status_flag);

  // void qt_attach(Callback<void()> cb);  //
  void qt_setup();
  void qt_read(char* data);
  void qt_read_status(QTStatusFlag* status_flag);
//   bool qt_settings_verification(QTSettings* qt_settings, uint8_t comp_id);

//   void qt_soft_reset();

//   void qt_set_sleep_mode(uint8_t sleep_value);
//   void qt_get_sleep_mode(uint8_t* sleep_value);

//   void qt_read_raw_data(QTRawData* qt_raw_data);

  void qt_get_chip_id(uint8_t* chip_id);
  void qt_get_code_version(uint8_t* code_version);

//   void qt_set_recalib_time(uint8_t recalib_time);
//   void qt_get_recalib_time(uint8_t* recalib_time);


  private:
  I2C *_i2c;

};

#endif