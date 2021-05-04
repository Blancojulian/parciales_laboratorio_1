/*
 * utn.h
 *
 *  Created on: 2 may. 2021
 *      Author: Blanco Julián Agustín
 */

#ifndef UTN_H_
#define UTN_H_

#define LEN_BUFFER_STRING 4096
int utn_getName(char *pResultado, char *mensaje, char *mensajeError, int reintentos, int len);
int utn_getCuit(char *pResultado, char *mensaje, char *mensajeError, int reintentos, int len);
int utn_getText(char *pResultado, char *mensaje, char *mensajeError, int reintentos, int len);
int utn_getNumberInt(int *pResultado, char *mensaje, char *mensajeError, int minimo, int maximo, int reintentos);
int utn_getNumberFloat(float *pResultado, char *mensaje, char *mensajeError, float minimo, float maximo, int reintentos);

#endif /* UTN_H_ */
