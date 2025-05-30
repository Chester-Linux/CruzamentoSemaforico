// B1 e B2 = INT0
// B3 e B4 = INT1
//PORTX |= (1<<PDY);
//PORTX &= ~(1<<PDY);
// Vermelho, Amarelo, Verde

volatile int ct = 0;
volatile int ctAtraso = 760;

bool B1eB2 = false;
bool B3eB4 = false;

void setup() {

  //Entradas e saídas  
  DDRD = 0b11100000; //Semaforo 1
  DDRB = 0b00000111; //Semaforo 2

  //Ativando Pullup
  PORTD |= (1<<PD2);
  PORTD |= (1<<PD3);

  //Tipo de gatilho para interrupção - Borda de subida
  EICRA = 0b00001111;

  //Habilitando a interrupção dos pinos
  EIMSK = 0b00000011;

  //Configurar TIMER2 no modo CTC
  TCCR2A = 0b00000010;

  //Prescale = 256 com t_COMP = 4ms
  TCCR2B = 0b00000110;

  //Habilita interrupção por comparação
  TIMSK2 = 0b00000010;

  //Carrega o valor TOP e limita  contagem
  OCR2A = 249;

  //Habilita interrupções gerais
  sei();

  //Ativar serial
  Serial.begin(9600);
}

//4 * X = tempo(milis)
// tempo(milis)/ 4 = X
void loop()
{
  if(ctAtraso > 750)
  {
  Serial.println("Contador do Semaforo: " + String(ct));
  }

  if(ctAtraso <= 750)
  {
  Serial.println("Contador do Atraso: " + String(ctAtraso));
  }

  if(ctAtraso > 750 && B1eB2 == true)
  {
    ct = 2001;
    B1eB2 = false;        
  }

  if(ctAtraso > 750 && B3eB4 == true)
  {
    ct = 5251;
    B3eB4 = false;        
  }

  //Semaforo Looping
  if (ct <= 2000)
  {
    //Semaforo 1
    PORTD |= (1<<PD5);
    PORTD &= ~(1<<PD6);
    PORTD &= ~(1<<PD7);

    //Semaforo 2
    PORTB &= ~(1<<PB0);
    PORTB &= ~(1<<PB1);
    PORTB |= (1<<PB2);
  }

  if ((ct > 2000) and (ct <= 2750))
  {
    //Semaforo 1
    PORTD &= ~(1<<PD5);
    PORTD |= (1<<PD6);
    PORTD &= ~(1<<PD7);


    //Semaforo 2
    PORTB &= ~(1<<PB0);
    PORTB &= ~(1<<PB1);
    PORTB |= (1<<PB2);
  }

  if ((ct > 2750) and (ct <= 3250))
  {
    //Semaforo 1
    PORTD &= ~(1<<PD5);
    PORTD &= ~(1<<PD6);
    PORTD |= (1<<PD7);


    //Semaforo 2
    PORTB &= ~(1<<PB0);
    PORTB &= ~(1<<PB1);
    PORTB |= (1<<PB2);
  }

  if ((ct > 3250) and (ct <= 5250))
  {
    //Semaforo 1
    PORTD &= ~(1<<PD5);
    PORTD &= ~(1<<PD6);
    PORTD |= (1<<PD7);

    //Semaforo 2
    PORTB |= (1<<PB0);
    PORTB &= ~(1<<PB1);
    PORTB &= ~(1<<PB2);
  }

  if ((ct > 5250) and (ct <= 6000))
  {
    //Semaforo 1
    PORTD &= ~(1<<PD5);
    PORTD &= ~(1<<PD6);
    PORTD |= (1<<PD7);

    //Semaforo 2
    PORTB &= ~(1<<PB0);
    PORTB |= (1<<PB1);
    PORTB &= ~(1<<PB2);
  }

  if ((ct > 6000) and (ct <= 6500))
  {
    //Semaforo 1
    PORTD &= ~(1<<PD5);
    PORTD &= ~(1<<PD6);
    PORTD |= (1<<PD7);

    //Semaforo 2
    PORTB &= ~(1<<PB0);
    PORTB &= ~(1<<PB1);
    PORTB |= (1<<PB2);
  }

  if (ct >= 6500)
  {
    ct = 0;
  }

}

ISR(INT0_vect) // Interrupcao de pino INT0
{
  ctAtraso = 0;
  B1eB2 = true;
}

ISR(INT1_vect) // Interrupcao de pino INT0
{
  ctAtraso = 0;
  B3eB4 = true;
}

ISR(TIMER2_COMPA_vect)
{
  if(ctAtraso > 750)
  {
  ct++;
  }

  if(ctAtraso <= 750)
  {
  ctAtraso++;
  }
}