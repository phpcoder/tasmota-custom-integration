/*
  xdrv_101_my_project_with_commands.ino - My IoT device support for Tasmota
*/


#ifdef USE_MY_PROJECT_CMD
/*********************************************************************************************\
 * My IoT Device with command support
 *
 *
\*********************************************************************************************/

#warning **** My IoT Device Driver with commands is included... ****

#define XDRV_101 101


/*********************************************************************************************\
 * My IoT Device Functions
\*********************************************************************************************/

// This variable will be set to true after initialization
bool initSuccess = false;

/* 
  Optional: if you need to pass any command for your device 
  Commands are issued in Console or Web Console
  Commands:
    Say_Hello  - Only prints some text. Can be made something more useful...
    SendMQTT   - Send a MQTT example message
    Help       - Prints a list of available commands  
*/

const char MyProjectCommands[] PROGMEM = "|"  // No Prefix
  "Say_Hello|" 
  "SendMQTT|"
  "Help";

void (* const MyProjectCommand[])(void) PROGMEM = {
  &CmdSay_Hello, &CmdSendMQTT, &CmdHelp };

void CmdSay_Hello(void) {
  AddLog(LOG_LEVEL_INFO, PSTR("Say_Hello: Hello!"));
  ResponseCmndDone();
}

char payload[200];
char topic[100];

void CmdSendMQTT(void) {
  AddLog(LOG_LEVEL_INFO, PSTR("Sending MQTT message."));

  snprintf_P(topic, sizeof(topic), PSTR("tasmota/myproject"));

  snprintf_P(payload, sizeof(payload), 
            PSTR("{\"" D_JSON_TIME "\":\"%s\",\"name\":\"My Project\"}"), 
            GetDateAndTime(DT_LOCAL).c_str()
  );

  // retain = true
  MqttPublishPayload(topic, payload, strlen(payload), false);

  ResponseCmndDone();
}

void CmdHelp(void) {
  AddLog(LOG_LEVEL_INFO, PSTR("Help: Accepted commands - Say_Hello, SendMQTT, Help"));
  ResponseCmndDone();
}

/*********************************************************************************************\
 * Tasmota Functions
\*********************************************************************************************/



void MyProjectInit()
{

  /*
    Here goes My Project setting.
    Usually this part is included into setup() function
  */


  AddLog(LOG_LEVEL_DEBUG_MORE, PSTR("My Project init..."));

  Serial.begin(115200);

  // Set initSuccess at the very end of the init process
  // Init is successful
  initSuccess = true;

}



void MyProjectProcessing(void)
{

  /*
    Here goes My Project code.
    Usually this part is included into loop() function
  */

}






/*********************************************************************************************\
 * Interface
\*********************************************************************************************/
bool Xdrv101(uint32_t function)
{


  bool result = false;

  if (FUNC_INIT == function) {
    MyProjectInit();
    AddLog(LOG_LEVEL_DEBUG_MORE, PSTR("My project init is done..."));
  }
  else if (initSuccess) {

    switch (function) {
      // Select suitable interval for polling your function
//    case FUNC_EVERY_SECOND:
      case FUNC_EVERY_250_MSECOND:
//    case FUNC_EVERY_200_MSECOND:
//    case FUNC_EVERY_100_MSECOND:
        MyProjectProcessing();
        break;

      // Command support
      case FUNC_COMMAND:
        AddLog(LOG_LEVEL_DEBUG_MORE, PSTR("Calling My Project Command..."));
        result = DecodeCommand(MyProjectCommands, MyProjectCommand);
        break;

    }

  }

  return result;
}

#endif  // USE_MY_PROJECT_CMD