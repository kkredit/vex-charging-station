/*
 * @file i2c-control.h
 * 
 * @brief I2C communication header file
 */

#ifndef __I2C_HDR__
#define __I2C_HDR__

typedef enum {
  MSGID_VOLT_READING = 0,
} message_id_t;

typedef struct {
  message_id_t  id;
  short         data;
} message_t;

class I2c_Controller
{
public:
  I2c_Controller() {};
  void init();
  bool hasMessage();
  message_t *getMessage();
  void sendVoltage(unsigned short voltage);

private:
  unsigned short m_address;
  message_t m_latestMessage;
};

#endif

