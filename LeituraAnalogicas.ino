

void readAnalogSmooth( ) { /* function readAnalogSmooth */
  ////Test routine for AnalogSmooth
  /*
  Serial.print(F("valor PT")); Serial.println(PTV);
  Serial.print(F("valor CD600")); Serial.println(MV_YEWM);
  Serial.print(F("valor S71200")); Serial.println(MV_S71200M);
  Serial.print(F("valor ARDUINO")); Serial.println(MV_ARDUINOM);
  Serial.print(F("valor ESP32")); Serial.println(MV_ESP32M);
  Serial.print(F("valor RASPB")); Serial.println(MV_RASPM);
  */
}
void analogR(){
  PTV         = analogRead(PT);
  MV_YEWM     = analogRead(MV_YEW);      
  MV_S71200M  = analogRead(MV_S71200);   
  MV_ARDUINOM = analogRead(MV_ARDUINO);  
  MV_ESP32M   = analogRead(MV_ESP32);    
  MV_RASPM    = analogRead(MV_RASP); 
}

long smooth() { /* function smooth */
  ////Perform average on sensor readings
  long average;
  // subtract the last reading:
  total = total - readings[readIndex];
  // read the sensor:
  readings[readIndex] = analogRead(PT);
  // add value to total:
  total = total + readings[readIndex];
  // handle index
  readIndex = readIndex + 1;
  if (readIndex >= numReadings) {
    readIndex = 0;
  }
  // calculate the average:
  average = total / numReadings;

  return average;
}

long smooth1() { /* function smooth */
  ////Perform average on sensor readings
  long average1;
  // subtract the last reading:
  total1 = total1 - readings1[readIndex1];
  // read the sensor:
  readings1[readIndex1] = analogRead(MV_YEW);
  // add value to total:
  total1 = total1 + readings1[readIndex1];
  // handle index
  readIndex1 = readIndex1 + 1;
  if (readIndex1 >= numReadings1) {
    readIndex1 = 0;
  }
  // calculate the average:
  average1 = total1 / numReadings1;

  return average1;
}

long smooth2() { /* function smooth */
  ////Perform average on sensor readings
  long average2;
  // subtract the last reading:
  total2 = total2 - readings2[readIndex2];
  // read the sensor:
  readings2[readIndex2] = analogRead(MV_S71200);
  // add value to total:
  total2 = total2 + readings2[readIndex2];
  // handle index
  readIndex2 = readIndex2 + 1;
  if (readIndex2 >= numReadings2) {
    readIndex2 = 0;
  }
  // calculate the average:
  average2 = total2 / numReadings2;

  return average2;
}

long smooth3 () { /* function smooth */
  ////Perform average on sensor readings
  long average3;
  // subtract the last reading:
  total3 = total3 - readings3[readIndex];
  // read the sensor:
  readings3[readIndex3] = analogRead(MV_ARDUINO);
  // add value to total:
  total3 = total3 + readings3[readIndex3];
  // handle index
  readIndex3 = readIndex3 + 1;
  if (readIndex3 >= numReadings3) {
    readIndex3 = 0;
  }
  // calculate the average:
  average3 = total3 / numReadings3;

  return average3;
}

long smooth4() { /* function smooth */
  ////Perform average on sensor readings
  long average4;
  // subtract the last reading:
  total4 = total4 - readings4[readIndex4];
  // read the sensor:
  readings4[readIndex4] = analogRead(MV_ESP32);
  // add value to total:
  total4 = total4 + readings4[readIndex4];
  // handle index
  readIndex4 = readIndex4 + 14;
  if (readIndex4 >= numReadings4) {
    readIndex4 = 0;
  }
  // calculate the average:
  average4 = total4 / numReadings4;

  return average4;
}

long smooth5() { /* function smooth */
  ////Perform average on sensor readings
  long average5;
  // subtract the last reading:
  total5 = total5 - readings5[readIndex5];
  // read the sensor:
  readings5[readIndex5] = analogRead(MV_RASP);
  // add value to total:
  total5 = total5 + readings5[readIndex5];
  // handle index
  readIndex5 = readIndex5 + 1;
  if (readIndex5 >= numReadings5) {
    readIndex5 = 0;
  }
  // calculate the average:
  average5 = total5 / numReadings5;

  return average5;
}
