

void setup() {

  Serial.begin(115200);

 
  pinMode(9, OUTPUT);
}


String readString;
void loop() {



  while (Serial.available()) { //返回串口缓冲区中当前剩余的字符个数
    char c = Serial.read(); //读取数据
    readString += c;
    delay(2);
  }

  if (readString.length() > 0) { //串口接收到了数据，可以读取
    Serial.println(readString);
     analogWrite(9, readString.toInt());

    readString = "";
  }


}
