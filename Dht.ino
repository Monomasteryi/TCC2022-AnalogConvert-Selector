/*
void leituraDhts(){
  delay(500);
  Serial.print("Temperatura 🌡 😎 = ");
  Serial.print(Temperatura);
  Serial.print(" --- Umidade 🌧 🥶 = ");
  Serial.println(Umidade);
}

void dht22e(){
  delay(200);
  sensors_event_t event;

  dht.temperature().getEvent(&event); 
  if (isnan(event.temperature)){
    Serial.println("Erro na leitura da Temperatura!");
  }else {
    Temperatura = event.temperature;
  }
  dht.humidity().getEvent(&event); 
  if (isnan(event.relative_humidity)){
    Serial.println("Erro na leitura da Umidade!");
  }else {
    Umidade = event.relative_humidity;
  }
  return;
}
*/
