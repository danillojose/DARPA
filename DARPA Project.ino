#include <LiquidCrystal.h>
#include <DS1307.h>
#include <Servo.h>

//Configuracoes do botao
int const botao = 7;
int estadoBotao = 0;
int aux_botao = 0;

//Inicializacao do servo
#define SERVO 6 // Porta Digital 6 PWM

Servo s; //Variável Servo
int pos = 0; //Posição Servo
int passo = 42;
int i = 0;
int aux_servo = 0;
   
//Inicializacao do display  
LiquidCrystal lcd(12, 11, 5, 4, 3, 2); 

//Modulo RTC DS1307 ligado as portas A4 e A5 do Arduino 
DS1307 rtc(A4, A5); 
   
//Configuracoes LCD 16x2  
int screenWidth = 16;  
int screenHeight = 2;  

String line1 = "DESP. IDOSOS";
String nome_do_remedio;
   
//Flags de referencia
int stringStart, stringStop = 0;  
int scrollCursor = screenWidth;  
int tamanho = 0;
int aux = 0, aux2 = 0;

//Frequencia do buzzer 
int frequencia = 528;   //Dó
   
void setup(){  
  //Define botao
  pinMode(botao,INPUT);
  
  //Aciona o servo
  s.attach(SERVO);
  Serial.begin(9600);
  s.write(0);
  
  //Aciona o relogio
  rtc.halt(false);

  //As linhas abaixo setam a data e hora do modulo
  //e podem ser comentada apos a primeira utilizacao
  //rtc.setDOW(WEDNESDAY);      //Define o dia da semana
  rtc.setTime(12, 23, 50);     //Define o horario
  //rtc.setDate(14, 3, 2018);   //Define o dia, mes e ano
  
  //Definicoes do pino SQW/Out
  rtc.setSQWRate(SQW_RATE_1);
  rtc.enableSQW(true);
  
  //Inicializacao do display  
  lcd.begin(screenWidth,screenHeight);  
}


void alarm_setup(String time2, String alarm_name){
  String t = rtc.getTimeStr();    //hora atual
  aux_botao = 0;
  aux = 0;
  //aux2 = 0;
  
  //Só entra na condição abaixo quando acontecer o alarme
  //Repete até alcançar 50x ou o botão estiver acionado
  //if((t.equals(time2) && aux<50 && !aux_botao) || aux2==1){    //(MÉTODO FALHO)
  if(t.equals(time2)){
    nome_do_remedio = alarm_name;
    while((!aux_botao) && aux<50){
      estadoBotao = digitalRead(botao); //Leitura do estado do botao
      Serial.print(estadoBotao);
      lcd.clear();
      //condicao de parada do buzzer
      if(estadoBotao == HIGH)
        aux_botao = 1;
  
      //rotina de scroll dos nomes dos remédios e hora
      lcd.setCursor(scrollCursor, 0);  
      lcd.print(nome_do_remedio.substring(stringStart,stringStop));  
      lcd.setCursor(4, 1);  
      lcd.print(rtc.getTimeStr());
      
      delay(200);   //controle de tempo de permanência no IF
        
      //if(!aux_botao){
        play_buzzer(); //aciona buzzer
      //}
      
      if(aux_servo){    //IF de controle para abertura
        pos += passo;
        abrir(); //abrir compartimento
        aux_servo = 0;
      }
  
      scroll_sup(); //Chama a rotina que executa o scroll
      //Verifica o tamanho da string  
      tamanho = nome_do_remedio.length();  
      if (stringStart == tamanho){  
        stringStart = 0;  
        stringStop = 0;  
      }
  
      //flags auxiliares de início e término da condição IF
      aux++;
      /*aux2 = 1;
      if(aux==100){
        aux2 = 0;
        aux_botao = 0;
      }*/
    }
  }
  else{
    default_display();
    aux_servo = 1;
    scrollCursor = screenWidth;  
  }
  
}

//Funcao para abrir o compartimento
void abrir(){   
  s.write(pos);
  if(pos == passo*4){
    pos = 0;
    delay(2000);
    s.write(0);
  }
}

void loop(){  
  int j = 0;
  const char *alarm_time[4];
  const char *alarm_name[4];
  
  alarm_time[0] = "12:24:00";          //hora do alarme
  alarm_name[0] = "DIPIRONA";                         //nome do alarme
  
  alarm_time[1] = "12:24:10";          //hora do alarme
  alarm_name[1] = "MIOFLEX A";                        //nome do alarme
  
  alarm_time[2] = "12:24:20";          //hora do alarme
  alarm_name[2] = "GLAUCOTRAT";                       //nome do alarme
  
  alarm_time[3] = "12:24:30";          //hora do alarme
  alarm_name[3] = "ALGUM REMEDIO AI";                 //nome do alarme
  
  for(j=0;j<4;j++){
    alarm_setup(alarm_time[j], alarm_name[j]);
  }
}  

//Função de scroll do display
void scroll_sup(){  
  lcd.clear();  
  if(stringStart == 0 && scrollCursor > 0){  
    scrollCursor--;  
    stringStop++;  
  } else if (stringStart == stringStop){  
    stringStart = stringStop = 0;  
    scrollCursor = screenWidth;  
  } else if (stringStop == line1.length() && scrollCursor == 0) {  
    stringStart++;  
  } else {  
    stringStart++;  
    stringStop++;  
  }  
}

//Função de estado DEFAULT
void default_display(){
  //lcd.clear();
  lcd.setCursor(2, 0); 
  lcd.print("DESP. IDOSOS"); 
  lcd.setCursor(4, 1); 
  lcd.print(rtc.getTimeStr());
}

//Função que aciona o buzzer
void play_buzzer(){
  tone(9, frequencia, 50);
  delay(100);
  tone(9, frequencia, 50);
  delay(100);
  tone(9, frequencia, 50);
  delay(100);
  tone(9, frequencia, 50);
  delay(200);
}

