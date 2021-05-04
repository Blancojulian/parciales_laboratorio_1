/*
 * utn.c
 *
 *  Created on: 2 may. 2021
 *      Author: Blanco Julián Agustín
 */


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "utn.h"

static int myGets(char* cadena, int len); // Se utiliza en getFloat y getInt.
static int getInt(int *pResultado);	// Se utiliza en utn_getNumberInt
static int isNumberInt(char* cadena, int len); // Se utiliza en getInt.
static int getFloat(float *pResultado); // Se utiliza en utn_getFloat.
static int isFloat(char* cadena, int len); // Se utiliza en getFloat.
static int getName(char* pResultado,int len); // Se utilizo en utn_getName.
static int isName(char* cadena,int len); // Se utilizo en getName.
static int getCuit(char* pResultado,int len); // Se utilizo en utn_getCuit.
static int isCuit(char* cadena,int len); // Se utilizo en getCuit.
static int getText(char* pResultado,int len); // Se utilizo en utn_getText.

/**
 * \brief	Lee el stdin hasta que encuentra un '\0' o hasta que haya copiado en cadena
 * 			un maximo de 'len - 1' caracteres.
 * \param	char* cadena, Puntero al espacio de memoria donde se dejara el valor obtenido.
 * \param	char len, Define el tamaño de la cadena.
 * \return	Retorna 0 (exito) si se obtiene una cadena y -1 (error) si no se obtiene.
 */
static int myGets(char* cadena, int len)
{
	int retorno = -1;
	char bufferString[LEN_BUFFER_STRING];

	if(cadena != NULL && len > 0)
	{
		fflush(stdin);
		// file get string.
		if(fgets(bufferString,sizeof(bufferString), stdin) != NULL)
		{
			if(bufferString[strnlen(bufferString,sizeof(bufferString)) - 1] == '\n')
			{
				bufferString[strnlen(bufferString,sizeof(bufferString)) - 1] = '\0';
			}
			if(strnlen(bufferString,sizeof(bufferString)) <= len)
			{
				strncpy(cadena, bufferString,len);
				retorno = 0;
			}
		}
	}
	return retorno;
}
/*
 * \ brief - Obtiene un numero entero.
 * \ param - int* pResultado, Puntero al espacio de memoria donde se dejara el valor obtenido.
 * \ return - (-1) en caso de error / (0) en caso de funcionar.
 */
static int getInt(int* pResultado)
{
	int retorno	= -1;
	char bufferString[LEN_BUFFER_STRING];

	if(pResultado != NULL)
	{
		if( myGets(bufferString, sizeof(bufferString)) == 0 &&
			isNumberInt(bufferString, LEN_BUFFER_STRING)  == 1)
		{
			retorno = 0;
			*pResultado = atoi(bufferString);
		}
	}
	return retorno;
}
/*
 * \ brief - Obtiene un Flotante.
 * \ param - char* pResultado, puntero a dirección de memoria.
 * \ return - (-1) en caso de error / (0) en caso de funcionar.
 */
static int getFloat(float* pResultado)
{
	int retorno	= -1;
	char bufferString[LEN_BUFFER_STRING];

	if(pResultado != NULL)
	{
		if( myGets(bufferString, sizeof(bufferString)) == 0 &&
			isFloat(bufferString, LEN_BUFFER_STRING)  == 1)
		{
			retorno = 0;
			*pResultado = atof(bufferString);
		}
	}
	return retorno;
}
/*
 * \ brief - Obtiene un Nombre.
 * \ param - char* pResultado, puntero a dirección de memoria.
 * \ param - int len, indica la cantidad de letras maximas de la cadena.
 * \ return - (-1) en caso de error / (0) en caso de funcionar.
 */
static int getName(char* pResultado,int len)
{
	int retorno = -1;
	char bufferString[LEN_BUFFER_STRING];
	if(pResultado != NULL && len > 0)
	{
		fflush(stdin);
		if(	myGets(bufferString,sizeof(bufferString)) == 0 &&
			isName(bufferString,LEN_BUFFER_STRING) == 1)
		{
			strncpy(pResultado,bufferString,len);
			retorno = 0;
		}
	}
	return retorno;
}
/*
 * \ brief - Obtiene un Cuit.
 * \ param - int* pResultado, Puntero al espacio de memoria donde se dejara el valor obtenido.
 * \ return - (-1) en caso de error / (0) en caso de funcionar.
 */
static int getCuit(char* pResultado,int len)
{
	int retorno = -1;
	char bufferString[LEN_BUFFER_STRING];
	if(pResultado != NULL && len > 0)
	{
		fflush(stdin);
		if(	myGets(bufferString,sizeof(bufferString)) == 0 &&
			isCuit(bufferString,LEN_BUFFER_STRING) == 1)
		{
			strncpy(pResultado,bufferString,len);
			retorno = 0;
		}
	}
	return retorno;
}
/*
 * \ brief - Obtiene un texto.
 * \ param - int* pResultado, Puntero al espacio de memoria donde se dejara el valor obtenido.
 * \ return - (-1) en caso de error / (0) en caso de funcionar.
 */
static int getText(char* pResultado,int len)
{
	int retorno = -1;
	char bufferString[LEN_BUFFER_STRING];
	if(pResultado != NULL && len > 0)
	{
		fflush(stdin);
		if(	myGets(bufferString,sizeof(bufferString)) == 0)
		{
			strncpy(pResultado,bufferString,len);
			retorno = 0;
		}
	}
	return retorno;
}
/*
 * \ brief - Verifica una cadena recibida como parametro para determinar
 * 	         si es un nombre valido.
 * \ param - char* cadena, cadena a analizar.
 * \ param - int len, indica la cantidad de letras maximas de la cadena.
 * \ return - (1) Indica que es un nombre valido / (0) Indica que no es un nombre valido.
 */
static int isName(char* cadena,int len)
{
	int respuesta = 1; // Todo bien.

	for (int i = 0; i <= len && cadena[i] != '\0'; i++)
	{
		if(	(cadena[i] < 'A' || cadena[i] > 'Z' ) &&
			(cadena[i] < 'a' || cadena[i] > 'z' ))
		{
			respuesta = 0;
			break;
		}
	}
	return respuesta;
}
/*
 * \ brief - Verifica una cadena recibida como parametro para determinar
 * 	         si es un cuit valido.
 * \ param - char* cadena, cadena a analizar.
 * \ param - int len, indica la cantidad de letras maximas de la cadena.
 * \ return - (1) Indica que es un cuit valido / (0) Indica que no es un cuit valido.
 */
static int isCuit(char* cadena,int len)
{
	int respuesta = 0; // Todo bien.

	for (int i = 0; i <= len && cadena[i] != '\0'; i++)
	{
		if( (cadena[2] == '-' && cadena[11] == '-') &&
			(cadena[i] >= '0' && cadena[i] <= '9'))
		{
			respuesta = 1;
			break;
		}
	}
	return respuesta;
}
/*
 * \ brief - Verifica una cadena recibida como parametro para determinar
 * 	         si es un entero valido.
 * \ param - char* cadena, cadena a analizar.
 * \ param - int len, indica la cantidad de numeros maximas de la cadena.
 * \ return - (1) Indica que es un entero valido / (0) Indica que no es un entero valido.
 */
static int isNumberInt(char* cadena, int len)
{
	int respuesta = 1; // Todo bien.
	int i = 0;

	if(cadena[0] == '-')
	{
		i = 1;
	}
	for ( ; i <= len && cadena[i] != '\0'; i++)
	{
		if(cadena[i] < '0' || cadena[i] > '9' )
		{
			respuesta = 0;
			break;
		}
	}
	return respuesta;
}
/*
 * \ brief - Verifica una cadena recibida como parametro para determinar
 * 	         si es un flotante valido.
 * \ param - char* cadena, cadena a analizar.
 * \ param - int len, indica la cantidad de numeros maximas de la cadena.
 * \ return - (1) Indica que es un flotante valido / (0) Indica que no es un flotante valido.
 */
static int isFloat(char* cadena, int len)
{
	int respuesta = 1; // Todo bien.
	int i = 0;
	int contadorPuntos = 0;

	if(cadena[0] == '-' || cadena[0] == '+')
	{
		i = 1;
	}
	for ( ; i <= len && cadena[i] != '\0'; i++)
	{
		if(cadena[i] < '0' || cadena[i] > '9' )
		{
			if(cadena[i] == '.' && contadorPuntos == 0)
			{
				contadorPuntos++;
			}
			else
			{
				respuesta = 0;
				break;
			}
		}
	}
	return respuesta;
}
/*
 * \ brief - Solicita un string al usuario.
 * \ param - char* mensaje, Mensaje a ser mostrado al usuario para solicitarle el dato.
 * \ param - char* mensajeError, Mensaje a ser mostrado al usuario para indicarle que el valor ingresado no es correcto.
 * \ param - char* pResultado, Puntero al espacio de memoria donde se dejara el valor obtenido.
 * \ param - int reintentos, Cantidad de oportunidades para ingresar el dato.
 * \ param - int len, indica la cantidad de letras maxima del nombre.
 * \ return - (-1) en caso de error / (0) en caso de funcionar.
 */
int utn_getName(char *pResultado, char *mensaje, char *mensajeError, int reintentos, int len)
{
	int retorno = -1;
	char bufferString[LEN_BUFFER_STRING];

	if( 	pResultado != NULL &&
			mensaje != NULL &&
			mensajeError != NULL &&
			reintentos >= 0 &&
			len > 1)
	{
		do
		{
			printf("%s",mensaje);
			fflush(stdin);
			if(	getName(bufferString, LEN_BUFFER_STRING) == 0 &&
				strnlen(bufferString, sizeof(bufferString)-1) <= len)
			{
				retorno = 0;
				strncpy(pResultado,bufferString,len);
				break;
			}
			else
			{
				printf("%s",mensajeError);
				reintentos--;
			}
		}while(reintentos >= 0);
	}
	return retorno;
}
/*
 * \ brief - Solicita un numero entero al usuario y, luego de verificarlo, devuelve el resultado.
 * \ param - char* mensaje, Mensaje a ser mostrado al usuario para solicitarle el dato.
 * \ param - char* mensajeError, Mensaje a ser mostrado al usuario para indicarle que el valor ingresado no es correcto.
 * \ param - int* pResultado, Puntero al espacio de memoria donde se dejara el valor obtenido.
 * \ param - int reintentos, Cantidad de oportunidades para ingresar el dato.
 * \ param - int minimo, valor minimo admitido.
 * \ param - int maximo, valor maximo admitido.
 * \ return - (-1) en caso de error / (0) en caso de funcionar.
 */
int utn_getNumberInt(int *pResultado, char *mensaje, char *mensajeError, int minimo, int maximo, int reintentos)
{
	int retorno = -1;
	int bufferInt;

	if( 	pResultado != NULL &&
			mensaje != NULL &&
			mensajeError != NULL &&
			reintentos >= 0)
	{
		do
		{
			printf("%s",mensaje);
			fflush(stdin);
			if(	getInt(&bufferInt) == 0 &&
				bufferInt >= minimo &&
				bufferInt <= maximo)
			{
				retorno = 0;
				*pResultado = bufferInt;
				break;
			}
			else
			{
				printf("%s",mensajeError);
				reintentos--;
			}
		}while(reintentos >= 0);
	}
	return retorno;
}
/*
 * \ brief - Solicita un flotante al usuario y, luego de verificarlo, devuelve el resultado.
 * \ param - char* mensaje, Mensaje a ser mostrado al usuario para solicitarle el dato.
 * \ param - char* mensajeError, Mensaje a ser mostrado al usuario para indicarle que el valor ingresado no es correcto.
 * \ param - int* pResultado, Puntero al espacio de memoria donde se dejara el valor obtenido.
 * \ param - int reintentos, Cantidad de oportunidades para ingresar el dato.
 * \ param - int minimo, valor minimo admitido.
 * \ param - int maximo, valor maximo admitido.
 * \ return - (-1) en caso de error / (0) en caso de funcionar.
 */
int utn_getNumberFloat(float *pResultado, char *mensaje, char *mensajeError, float minimo, float maximo, int reintentos)
{
	int retorno = -1;
	float bufferFloat;

	if( 	pResultado != NULL &&
			mensaje != NULL &&
			mensajeError != NULL &&
			reintentos >= 0)
	{
		do
		{
			printf("%s",mensaje);
			fflush(stdin);
			if(	getFloat(&bufferFloat) == 0 &&
				bufferFloat >= minimo &&
				bufferFloat <= maximo)
			{
				retorno = 0;
				*pResultado = bufferFloat;
				break;
			}
			else
			{
				printf("%s",mensajeError);
				reintentos--;
			}
		}while(reintentos >= 0);
	}
	return retorno;
}
/*
 * \ brief - Solicita un CUIT al usuario.
 * \ param - char* mensaje, Mensaje a ser mostrado al usuario para solicitarle el dato.
 * \ param - char* mensajeError, Mensaje a ser mostrado al usuario para indicarle que el valor ingresado no es correcto.
 * \ param - char* pResultado, Puntero al espacio de memoria donde se dejara el valor obtenido.
 * \ param - int reintentos, Cantidad de oportunidades para ingresar el dato.
 * \ param - int len, indica la cantidad de letras maxima del nombre.
 * \ return - (-1) en caso de error / (0) en caso de funcionar.
 */
int utn_getCuit(char *pResultado, char *mensaje, char *mensajeError, int reintentos, int len)
{
	int retorno = -1;
	char bufferString[LEN_BUFFER_STRING];

	if( 	pResultado != NULL &&
			mensaje != NULL &&
			mensajeError != NULL &&
			reintentos >= 0 &&
			len > 1)
	{
		do
		{
			printf("%s",mensaje);
			fflush(stdin);
			if(	getCuit(bufferString, LEN_BUFFER_STRING) == 0 &&
				strnlen(bufferString, sizeof(bufferString)-1) <= len)
			{
				retorno = 0;
				strncpy(pResultado,bufferString,len);
				break;
			}
			else
			{
				printf("%s",mensajeError);
				reintentos--;
			}
		}while(reintentos >= 0);
	}
	return retorno;
}
/*
 * \ brief - Solicita un texto al usuario.
 * \ param - char* mensaje, Mensaje a ser mostrado al usuario para solicitarle el dato.
 * \ param - char* mensajeError, Mensaje a ser mostrado al usuario para indicarle que el valor ingresado no es correcto.
 * \ param - char* pResultado, Puntero al espacio de memoria donde se dejara el valor obtenido.
 * \ param - int reintentos, Cantidad de oportunidades para ingresar el dato.
 * \ param - int len, indica la cantidad de letras maxima del nombre.
 * \ return - (-1) en caso de error / (0) en caso de funcionar.
 */
int utn_getText(char *pResultado, char *mensaje, char *mensajeError, int reintentos, int len)
{
	int retorno = -1;
	char bufferString[LEN_BUFFER_STRING];

	if( 	pResultado != NULL &&
			mensaje != NULL &&
			mensajeError != NULL &&
			reintentos >= 0 &&
			len > 1)
	{
		do
		{
			printf("%s",mensaje);
			fflush(stdin);
			if(	getText(bufferString, LEN_BUFFER_STRING) == 0 &&
				strnlen(bufferString, sizeof(bufferString)-1) <= len)
			{
				retorno = 0;
				strncpy(pResultado,bufferString,len);
				break;
			}
			else
			{
				printf("%s",mensajeError);
				reintentos--;
			}
		}while(reintentos >= 0);
	}
	return retorno;
}
