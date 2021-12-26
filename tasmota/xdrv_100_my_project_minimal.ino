/*
  xdrv_100_my_project_minimal.ino - My IoT device support for Tasmota
*/


#ifdef USE_MY_PROJECT
/*********************************************************************************************\
 * My IoT Device bare minimum
 *
 *
\*********************************************************************************************/

#warning **** My IoT Device Driver is included... ****

#define XDRV_100 100


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
bool Xdrv100(uint8_t function)
{


  bool result = false;

  switch (function) {
    case FUNC_INIT:
      MyProjectInit();
      AddLog(LOG_LEVEL_DEBUG_MORE, PSTR("My project init is done..."));
      break;
//    Select suitable interval for polling your function
//    case FUNC_EVERY_SECOND:
    case FUNC_EVERY_250_MSECOND:
//    case FUNC_EVERY_200_MSECOND:
//    case FUNC_EVERY_100_MSECOND:
      MyProjectProcessing();
      break;
  }

  return result;
}

#endif  // USE_MY_PROJECT
