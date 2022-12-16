void touchacquisition(){

  touchValue = touchRead(T0);
  T = millis();

  if(touchValue<20 || digitalRead(25) == HIGH) {
    BT = HIGH;
  }else {
    BT = LOW;
    TB = T;
  }
  
  if(BT == HIGH && TAC == LOW && T-TB > 300) {
    contarT0 = contarT0+1;
    TAC = HIGH;
    TR = T;
    Serial.println("Touch acionado");
  }

  if(BT == LOW && TAC == HIGH && T-TR > 1000) {
    TAC = LOW;
  }
}
