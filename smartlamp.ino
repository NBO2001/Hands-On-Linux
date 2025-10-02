// Defina os pinos de LED e LDR
// Defina uma variável com valor máximo do LDR (4000)
// Defina uma variável para guardar o valor atual do LED (10)
int ledPin = 23;
int ledValue;

int ldrPin = 36;
// Faça testes no sensor ldr para encontrar o valor maximo e atribua a variável ldrMax
int ldrMax;

int max_led = 15;

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

    int analogValue = analogRead(ldrPin);
    Serial.print("Analog Value = ");
    Serial.print(analogValue);   // the raw analog reading
    Serial.print("\n");
    if(max_led <= 0) return;
    
    digitalWrite(ledPin, HIGH);
    Serial.printf("LIGADO...\n");

    delay(3000);
    
    digitalWrite(ledPin, LOW);
    Serial.printf("Desligado...\n");
    max_led--;
    delay(3000);
}


void processCommand(String command) {
    // compare o comando com os comandos possíveis e execute a ação correspondente      
}

// Função para atualizar o valor do LED
void ledUpdate() {
    // Valor deve convertar o valor recebido pelo comando SET_LED para 0 e 255
    // Normalize o valor do LED antes de enviar para a porta correspondente
}

// Função para ler o valor do LDR
int ldrGetValue() {
    // Leia o sensor LDR e retorne o valor normalizado entre 0 e 100
    // faça testes para encontrar o valor maximo do ldr (exemplo: aponte a lanterna do celular para o sensor)       
    // Atribua o valor para a variável ldrMax e utilize esse valor para a normalização
}
