//-GIANFRANCO CHIARIZIA SPD TP02 CERRADURA SPD-//
#include <LiquidCrystal.h>
#include <Keypad.h>



////      DEFINES


#define LARGO_PASSWORD 7
#define BOTON_CONFIGURACION A4
#define BOTON_RESET 12
#define BOTON_TEST_PASSWORD 11
#define LED_OK 9
#define LED_FAIL 10
#define TIEMPO_LIMITE_PARPADEO 5000

/*
================================================================================================
> VARIABLES
================================================================================================
*/
//	----------------------------------
//	----[CONFIGURACION CONTRASEÑA]----
//	----------------------------------
char contraseniaPorDefecto[LARGO_PASSWORD] = "2C2022";	// [ contraseña con la que se inicia la cerradura ]
char contrasenia[LARGO_PASSWORD];						// [ contraseña ingresada para comprobar ]
char caracterIngresado;									// [ caracter ingresado que compone la contraseña ]
int indice = 0;											// [ indice de la cadena de password 

///     KEYPAD
const byte FILAS = 4;					// [ numero de filas ]
const byte COLUMNAS = 4;				// [ numero de columnas ]
char teclas [FILAS][COLUMNAS] =			// [ configuracion del teclado con sus caracteres ]
{
    {'1','2','3','A'},
    {'4','5','6','B'},
    {'7','8','9','C'},
    {'*','0','#','D'},
};

byte pinFilas[FILAS] = {7,6,5,4};		// [ pines filas ]
byte pinColumnas[COLUMNAS] = {3,2,1,0}; // [ pines columnas ]

Keypad teclado(makeKeymap(teclas), pinFilas, pinColumnas,FILAS, COLUMNAS); // [ mapeo de teclado ]


// LCD

LiquidCrystal pantallaLCD(8, 13, A0, A1, A2, A3); // [ pines LCD ]


//	>> BOTON CONFIGURATION
int valorBotonConfiguracionAntes = 0;
//	>> BOTON RESET
int valorBotonResetAntes = 0;
//	>> BOTON TEST PASSWORD
int valorBotonTestPasswordAntes = 0;
//	>> ESTADO CONFIGURACION CONTRASEÑA CORRECTA
int password_Correcto = 0;
int banderaBotonConfiguracion = 0;

//	------------------------------------
//	----[CONFIGURACION PARPADEO LED]----
//	------------------------------------
int password_estado = 0;
unsigned long tiempoInicioParpadeo = 0;
unsigned long tiempo = 0;
int bandera_inicioParpadeo = 0;

int estado_mensaje = 0;

int estadoLed = LOW;
unsigned long tiempoAnterior = 0;
int parpadeoLed = 300;
int empezar_parpadeo = 0;
int bandera_apagarLed = 0;
int pinLed;

/*
================================================================================================
> SETUP
================================================================================================
*/
void setup()
{
  
  pinMode(BOTON_CONFIGURACION, INPUT);
  pinMode(BOTON_RESET,INPUT);
  pinMode(BOTON_TEST_PASSWORD,INPUT);
  
  
  pinMode(LED_OK,OUTPUT);
  pinMode(LED_FAIL,OUTPUT);
  
  //Inicio de pantalla LCD
  pantallaLCD.begin(16,2);
  
  mostrar_mensaje();
}



/// LOOP

void loop()
{
  sequence();			// [ secuenciador para parpadeo y borrado de pantalla ]
  
  
   
  delay(10); 
}
/*
================================================================================================
> FIN DEL PROGRAMA
================================================================================================
*/



/*
================================================================================================
//  > FUNCIONES
================================================================================================
*/








//-----------------------------------------------
/// @brief captura el tiempo inicial del parpadeo, y lo detiene cuando pasen los 5 segundos
void sequence(void)
{
  tiempo = millis(); 

  if((password_Correcto == 1 || password_Correcto == -1) && bandera_inicioParpadeo == 1)  // [ Si se corrabora el password por correcto o incorrecto ]
  {
    tiempoInicioParpadeo = tiempo;  // [ Capturo el tiempo en el que inicia el parpadeo ]

    if(password_Correcto == 1)
    {
      password_Correcto = 2;
    }

    bandera_inicioParpadeo = 0;
    bandera_apagarLed = 1;
  }
  
  if(tiempoInicioParpadeo != 0 && tiempo >= (tiempoInicioParpadeo + TIEMPO_LIMITE_PARPADEO)) // [ Si supero el tiempo desde el inicio del parpadeo y el limite de 5000 mseg]
  {
    estado_mensaje = 0;
    mostrar_mensaje();
    tiempoInicioParpadeo = 0;
    password_Correcto = 0;
    bandera_apagarLed = 0;
  }
}

/// PRINT MENSAJES

/// @brief muestra los mensajes en el display segun el estado de la contraseña

void mostrar_mensaje (void)
{
  pantallaLCD.clear();
  pantallaLCD.setCursor(0,0);	

  switch(estado_mensaje)
  {
    case 1: 
        pantallaLCD.print("Password new:");
        pantallaLCD.setCursor(0,1);	
        break;
    case 2: 
        pantallaLCD.print("PASSWORD OK");
        break;
    case 3: 
        pantallaLCD.print("PASSWORD FAIL");
        break;
    case 4: 
        pantallaLCD.print("Password changed");
        break;
    default: 
        pantallaLCD.print("Password:");
        break;
  }
  
  indice = 0;
}
//-----------------------------------------------
