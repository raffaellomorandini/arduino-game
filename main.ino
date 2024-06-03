#include <LiquidCrystal.h>

int indice = 0;
const int dim = 32;
int campo[dim];
const int btnPin = 7;
int btnVal = 0;
int preBtnVal = 0;
bool gameOver = false;
int checkGame = 0;

void caricaCampo(int v[], int partenza, int fine){
  for(int i = partenza; i < fine; i++){
    
    if((v[i-2] == 0) && (v[i-1] == 0) && (v[i-3] == 0))
      v[i] = random(2);
  }
}

LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

void setup()
{
  Serial.begin(9600);
  randomSeed(analogRead(0));
  lcd.begin(16, 2); 
  
  caricaCampo(campo, 6, dim);
}

void loop()
{
  checkGame = 0;
  lcd.setCursor(0, 1);
  btnVal = digitalRead(btnPin);

  if(indice >= dim && indice % dim == 0){
  	caricaCampo(campo,16,32);
  }else if(indice >= dim && indice % dim == 15){
  	caricaCampo(campo,0,15);
  }
  
  for(int i = indice; i < indice+16; i++){
    if(campo[i%dim]){
      lcd.print("O");
      if(!btnVal && checkGame == 1) gameOver = true;
    }
  		
    else
      lcd.print(".");
    checkGame +=1;
  }
  for(int i = 0; i < 16; i++){
    lcd.setCursor(i, 0);
    lcd.print(".");
  }
  lcd.setCursor(1, 1-btnVal);
  lcd.print("N");
  
  
  if(!gameOver){
    indice+=1;
  }else{
    lcd.setCursor(0, 0);
    lcd.print("   Game Over   ");
    lcd.setCursor(0, 1);
    lcd.print(" Press Restart ");
  }
  delay(500); 
}