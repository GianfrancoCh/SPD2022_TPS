//-GIANFRANCO CHIARIZIA SPD-//
///CORREGIDO, FUNCIONA BOTON RESET, CORRECION COMMIT
//--- Defines ---//

//  =========
#define ZERO 0      // Inicio contador
#define BUTTON_START 2      // Boton start
#define BUTTON_RESET 3      // Boton reinicio
#define FIRST_LED 4         // Primer pin de leds
#define LAST_LED 13         // Ultimo pin de leds
#define BASE_MILLI_SECONDS 1000 // Segundos en milisegundos
#define MAX_SECONDS 1023    // Fin contador
#define LEN 10              // Tamaño vector binario y vector leds

//--- End Defines ---//

//*Variables*//

int arrayEnteros[LEN];
int leds[LEN];
int contador = ZERO;  
int button_before_reset = LOW;
int button_before = LOW;
int flag = 0;
unsigned long millis_before = 0; 


void setup()
{
    Serial.begin(9600);
  	Serial.println("START PARA INICIAR");
  
    for(int i = FIRST_LED; i <= LAST_LED; i++)
    {
        pinMode(i, OUTPUT);
    }
  
    pinMode(BUTTON_START, INPUT);
    pinMode(BUTTON_RESET, INPUT); 
  
    set_array(arrayEnteros, LEN);                
    set_leds (leds, LEN, FIRST_LED);  

}

//* Main Loop * //

void loop()
{   
  	sequence();
    boton_start();        
    boton_reset(BUTTON_RESET);     
    delay(80);      
}



// Funciones //

/**
* @brief Secuencia, llama otra funciones dentro de ella
*/
void sequence()
{
    unsigned long millis_now = millis();  
  	if(millis_now >=(millis_before + BASE_MILLI_SECONDS) && flag == 1 ) 
    {
        if(contador <= MAX_SECONDS) 
        {           
            decimalAbinario(contador, arrayEnteros);            
            turnLeds(arrayEnteros, leds, LEN);
            
         	
          	Serial.print ("Segundos: ");
          	Serial.print(contador);             
            Serial.print(" | ");         
            imprimirArray(arrayEnteros, LEN); 
            contador++;          	
        }
      	millis_before = millis_now;   
    }
}



/**
 * @brief  Inicializa array 
 * @param  arrayEnteros: el array a inicializar
 * @param  len : tamaño del array
 */

void set_array(int arrayEnteros[],int len)
{
  	for(int i=0; i<len; i++)
  	{
    	arrayEnteros[i]=0;	
  	}
}
/**
* @brief Inicializa el array de led desde el primer pin hasta el ultimo
* @param leds[] array que se inicializa
* @param tam tamaño array
* @param first_led el primer led que se inicializa
*/

void set_leds(int leds[], int tam, int first_led)
{
  	for(int i=0; i<=tam-1; i++)
  	{
    	leds[i]=first_led;
    	first_led++;
  	}
}


/**
* @brief funcion del boton de start/pause 
*/

void boton_start()
{    
    int button_now = digitalRead(BUTTON_START);
  	if(button_now == 1 && button_before==LOW)
    {          
        if(flag == 0)
        {
          flag = 1;  
        }
        else
        {
          flag = 0;
        }                   
  	}  
  	button_before = button_now;
}

/**
* @brief funcion para resetear el cronometro, reinicia el contador
*/    
void  boton_reset(int pinReset)
{
    
    int button_reset_now = digitalRead(pinReset);
  	if(button_reset_now == HIGH && button_before_reset==LOW)
    {       
      
      contador = ZERO;
       	
      for(int i=0; i<LEN; i++)
      {
      	arrayEnteros[i]=0;
      }         
      
    }  	
  
  	button_before_reset = button_reset_now;  
  
}


/**
* @brief transforma decimal a binario
* @param contador contador de decimales 
* @param arrayEnteros[] array donde se guardan los binarios
*/
void decimalAbinario(int contador, int arrayEnteros[])				
{
   	short numeroBin = 0;
	int ultimoIndice = LEN-1;
    
    // Arma cadena binaria en el array
    while(contador > 0){
        numeroBin = contador % 2;
        contador /= 2;
        arrayEnteros[ultimoIndice] = numeroBin;
        ultimoIndice--;
    }

    // rellenar con 0 hacia la izquierda.
    while(ultimoIndice >= 0){
        arrayEnteros[ultimoIndice] = 0;
        ultimoIndice--;
    }							
}


/**
* @brief lee un las posiciones de un array y prende los leds 
* 	si el numero es 1 y los apaga si el numero es 0
* @param arrayEnteros[] array donde esta el numero binario
* @param leds[] array de los leds 
* @param len tamaño de los arrays
*/
void turnLeds(int arrayEnteros[], int leds[], int len)
{
 
  int num;
  int pos;
  
  pos = leds[0];
  
	for (int i = LEN-1; i >= 0; i--)
	{
  		num = arrayEnteros[i];
    	
    	if(num == 1)
  		{
        	digitalWrite(leds[pos - 4], 1);
  		}
      
      if(num == 0)
      {
        digitalWrite(leds[pos - 4], 0);
      }      
      pos++;
	}
}


/**
* @brief Imprime array de binarios 
*/

void imprimirArray(int arrayEnteros[], int len)
{
  	Serial.print("Binario: [");
  
  	for (int i=0; i<len; i++)
  	{
    	Serial.print(arrayEnteros[i]);
  	}
  	Serial.println("]");
}

