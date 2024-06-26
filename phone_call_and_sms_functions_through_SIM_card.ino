String smsSD1;
String smsSD2;
void check_SMS() {
  if (sim.available()) {
    sms = sim.readStringUntil('\n');
    //setPhoneNumber_Threshold(sms);                              // Đọc và cập nhật số điện thoại và ngưỡng cảnh báo nếu có
    Serial.println("SMS: " + sms);
    if (sms == "TU DONG\r") {
      autoo = 1;
      manual = 0;
      phanhoi(0);
      Serial.println("Che do tu dong");
      delay(200);
    }
    else if (sms == "DIEU KHIEN\r") {
      autoo = 0;
      manual = 1;
      phanhoi(1);
      Serial.println("Che do dieu khien");
      delay(200);
    }
    else if (sms == "MO CUA\r") {
      door_open();
      y++;
      delay(200);
      phanhoi(2);
      Serial.println("Gui tin mo cua");
    }
    else if (sms == "DONG CUA\r") {
      door_close();
      y++;
      delay(200);
      phanhoi(3);
      Serial.println("Gui tin dong cua");
    }
    else if (sms == "BAT QUAT HUT\r") {
      relay1_on();
      z++;
      delay(200);
      phanhoi(4);
      Serial.println("Gui tin bat quat");
    }
    else if (sms == "TAT QUAT HUT\r") {
      relay1_off();
      z++;
      delay(200);
      phanhoi(5);
      Serial.println("Gui tin tat quat");
    }
    else if (sms == "BAT MAY BOM\r") {
      relay2_on();
      x++;
      delay(200);
      phanhoi(6);
      Serial.println("Gui tin bat bom");
    }
    else if (sms == "TAT MAY BOM\r") {
      relay2_off();
      x++;
      delay(200);
      phanhoi(7);
      Serial.println("Gui tin tat bom");
    }
    else if (sms == "GAS\r") {
      phanhoi(8);
      Serial.println("Gui khi Gas");
    }
    else if (sms == "SDT\r") {
      phanhoi(9);
      Serial.println("Gui so dien thoai");
    }
    else if (sms == "CHE DO\r") {
      phanhoi(11);
      Serial.println("Gui che do hien tai");
    }
    else if (sms == "SO DU\r") {
      sim.println("ATD*101#;"); 
      delay(1000);
      for (int i=0; i<9; i++) {
        smsSD1 = sim.readStringUntil('\n');
        if (smsSD1 != "OK\r") {
          smsSD2 = smsSD1;
        }
        delay(200);
      }
      sim.println("AT+CMGF=1");
      delay(1000);
      sim.println("AT+CMGS=\"" + phoneNumber + "\"\r");         // Gửi tin nhắn đến số điện thoại
      delay(1000);
      sim.println("smsSD2");
      Serial.println("Check so du");
    }
    delay(50);
    setPhoneNumber_Threshold(sms);                              // Đọc và cập nhật số điện thoại và ngưỡng cảnh báo nếu có
  }
}

void SendMessage (int tipe)                                     // chuong trình con nhăn tin 
{
  Serial.println ("Gui tin nhan den dien thoai");
  sim.println("AT+CMGF=1");    
  delay(1500);
  sim.println("AT+CMGS=\"" + phoneNumber + "\"\r");             // Gui tin nhăn đen so dien thoai
  delay(1000);
  switch (tipe) 
  {
    case 0:
      sim.println("He Thong Phat Hien Co Lua !!!");
      delay(100);
      sim.println((char)26);
      delay(500);
      break;
    case 1:
      sim.println("He Thong Phat Hien Khi Gas Vuot Nguong !!!");
      delay(100);
      sim.println((char)26);
      delay(500);
      break;
    case 2:
      sim.println("He Thong Canh Bao Ro Ri Khi Gas, Co Chay. NGUY HIEM !!!");
      delay(100);
      sim.println((char)26);
      delay(500);
      break;   
  }
}

void callNumber1() {                                          // Chuong trinh con gọi dien
  sim.print (F("ATD"));
  sim.print (phoneNumber);
  sim.print (F(";\r\n"));
  Serial.println("Thuc hien cuoc goi");
  Serial.println("SMS: " + sim.readStringUntil('\n'));
}

String smokePre;
void phanhoi(int tipe) {
  sim.println("AT+CMGF=1");
  delay(1000);
  sim.println("AT+CMGS=\"" + phoneNumber + "\"\r");           // Gửi tin nhắn đến số điện thoại
  switch (tipe) 
  {
    case 0:
      sim.println("Che do TU DONG");
      delay(100);
      sim.println((char)26);
      delay(1000);
      break;
    case 1:
      sim.println("Che do DIEU KHIEN");
      delay(100);
      sim.println((char)26);
      delay(1000);
      break;
    case 2:
      sim.println("Mo Cua");
      delay(100);
      sim.println((char)26);
      delay(1000);
      break; 
    case 3:
      sim.println("Dong Cua");
      delay(100);
      sim.println((char)26);
      delay(1000);
      break;  
    case 4:
      sim.println("Bat Quat Hut");
      delay(100);
      sim.println((char)26);
      delay(1000);
      break;
    case 5:
      sim.println("Tat Quat Hut");
      delay(100);
      sim.println((char)26);
      delay(1000);
      break;
    case 6:
      sim.println("Bat May Bom");
      delay(100);
      sim.println((char)26);
      delay(1000);
      break; 
    case 7:
      sim.println("Tat May Bom");
      delay(100);
      sim.println((char)26);
      delay(1000);
      break;  
    case 8:
      smokePre = String (smoke);
      sim.println("Gas: \"" + smokePre + "\"\r");
      delay(100);
      sim.println((char)26);
      delay(1000);
      break;
    case 9:
      phoneNumber = readPhoneNumber();
      sim.println("SDT: \"" + phoneNumber + "\"\r");
      delay(100);
      sim.println((char)26);
      delay(1000);
      break;
    case 10:
      smokePre = String (readGasThreshold());
      sim.println("Nguong Canh Bao: \"" + smokePre + "\"\r");
      delay(100);
      sim.println((char)26);
      delay(1000);
      break;
    case 11:
      if (autoo == 1 && manual == 0){
        sim.println("Che do TU DONG");
        Serial.println("Che do Auto");
        delay(100);
        sim.println((char)26);
        delay(1000);
      }
      else if (autoo == 0 && manual == 1){
        sim.println("Che do DIEU KHIEN");
        Serial.println("Che do Manual");
        delay(100);
        sim.println((char)26);
        delay(1000);
      }
      break;
  }
}
