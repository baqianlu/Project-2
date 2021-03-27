#include <JC_Button.h>



Button myBtn(7);


void setup() {

  Serial.begin(115200);

  myBtn.begin();
  pinMode(6, OUTPUT);


}


String readString;
int p = 0;
bool pState = true;
unsigned long pressedTime  = 0;
unsigned long releasedTime = 0;
int currentState = true;
int ledState = false;
void loop() {
  myBtn.read();

  if ( myBtn.wasPressed() )  //释放按钮
  {

    releasedTime = millis();
    Serial.println(releasedTime - pressedTime);
    currentState = true;
    if (releasedTime - pressedTime < 300) {//按下的时间小于300 视为短按
      //      if (ledState) {
      //        analogWrite(6, 255);
      //        ledState=false;
      //      } else {
      //        analogWrite(6, 0);
      //        ledState=true;
      //      }

      if (p < 10) {
        analogWrite(6, 255);
        p = 255;
      } else {
        analogWrite(6, 0);
        p = 0;
      }

    }

  }
  if ( myBtn.isPressed() )
  {


  }
  else
  {

    if (currentState) {
      pressedTime = millis();
      currentState = false;
    }

    releasedTime = millis();

    if (releasedTime - pressedTime > 300) {
      analogWrite(6, p);
      delay(10);
      if (p == 0) {
        pState = true;

      }
      if (p == 255) {
        pState = false;

      }
      if (pState) {
        p++;
      } else {
        p--;

      }



    }



  }

  while (Serial.available()) { //返回串口缓冲区中当前剩余的字符个数
    char c = Serial.read(); //读取数据
    readString += c;
    delay(2);
  }

  if (readString.length() > 0) { //串口接收到了数据，可以读取
    Serial.println(readString);
    analogWrite(6, readString.toInt());

    readString = "";
  }


}
