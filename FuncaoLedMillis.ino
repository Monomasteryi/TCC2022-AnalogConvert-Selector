void ledpisca() {
if(millis()- tA >= tP){
  tA = millis();
  digitalWrite(LEDST1, eL);
  eL = !eL;
  }
}
