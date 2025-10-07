// Defina os pinos de LED e LDR
// Defina uma variável com valor máximo do LDR (4000)
// Defina uma variável para guardar o valor atual do LED (10)
int ledPin = 23;
int ledValue;

int ldrPin = 36;
// Faça testes no sensor ldr para encontrar o valor maximo e atribua a variável ldrMax
int ldrMax;

int max_led = 15;
int threshold = 50;

void setup() {
    Serial.begin(9600);
    pinMode(ledPin, OUTPUT);
    pinMode(ldrPin, INPUT);
    analogSetAttenuation(ADC_11db); 
    Serial.printf("SmartLamp Initialized.\n");
    
}

// Função loop será executada infinitamente pelo ESP32
  void loop() {
    //Obtenha os comandos enviados pela serial 
    //e processe-os com a função processCommand
    
    if(Serial.available() > 0)
    {
      String command = Serial.readStringUntil('\n');
      command.trim();
      processCommand(command);
    }
    else
    {
      int ldrValue = ldrGetValue();

      if(ldrValue < threshold)
      {
        ledUpdate(max_led);
      }
      else
      {
        ledUpdate(0);  
      }
      processCommand("GET_LDR");
      delay(2000);
    }
}

void processCommand(String command) 
{
    // compare o comando com os comandos possíveis e execute a ação correspondente

    int value = command.indexOf(" ");
    String comandoUser = command.substring(0, value);

    if(comandoUser == "SET_LED")
    {
      ledUpdate(command.substring(value).toInt());
    }
    else if(comandoUser == "GET_LED")
    {
      Serial.printf("RES GET_LED %d\n", ledValue);      
    }
    else if(comandoUser == "GET_LDR")
    {
      Serial.printf("RES GET_LDR %d\n", ldrGetValue());
    }
    else if(comandoUser == "SET_THRESHOLD")
    {
        int val = command.substring(value+1).toInt();

        if(val < 0) val = 0;

        if(val> 100) val = 100;

        threshold = val;

         Serial.printf("RES SET_THRESHOLD %d\n", threshold);
    }
    else if(comandoUser == "GET_THRESHOLD"){
       Serial.printf("RES GET_THRESHOLD %d\n", threshold);
    }
    else{
      Serial.printf("ERR Unknown command\n");
    }
}


// Função para atualizar o valor do LED
void ledUpdate(int valor)
{
    // Valor deve convertar o valor recebido pelo comando SET_LED para 0 e 255
    // Normalize o valor do LED antes de enviar para a porta correspondente

    int valorNormalizado = valor%256;
    digitalWrite(ledPin, valorNormalizado);
    ledValue = valorNormalizado;
}


// Função para ler o valor do LDR
int ldrGetValue() {
    // Leia o sensor LDR e retorne o valor normalizado entre 0 e 100
    // faça testes para encontrar o valor maximo do ldr (exemplo: aponte a lanterna do celular para o sensor)       
    // Atribua o valor para a variável ldrMax e utilize esse valor para a normalização

    double max_value = 4095.0;
    double analogValue = analogRead(ldrPin);
   
    int final_value = (int) ((analogValue/max_value)*100);
    return final_value;
    
}
