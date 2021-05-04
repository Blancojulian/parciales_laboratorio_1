/*
 * Color.c
 *
 *  Created on: 4 may. 2021
 *      Author: Blanco Julián Agustín
 */


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <float.h>
#include <limits.h>
#include "Color.h"
#include "utn.h"

static int generateNewId(void);

/**
 * \brief Incrementa el id y lo retorna.
 * \return Retorna el id
 */
static int generateNewId(void)
{
	static int id = 0;

	id++;
	return id;
}

/**
 * \brief Inicializa el array.
 * \param Color list, Es el puntero al array.
 * \param int len, es el limite de array.
 * \return (-1) Error / (0) Ok
 */
int col_init(Color* list, int len)
{
	int retorno = -1;
	int i;

	if (list != NULL && len > 0)
	{
		for (i = 0; i < len; i++)
		{
			list[i].isEmpty = 1;
		}
		retorno = 0;
	}
	return retorno;
}

/**
 * \brief Realiza un alta forzada de un elemento.
 * \param Color* list, Es el puntero al array.
 * \param int len, es el limite de array
 * \param char* color, Puntero al espacio de memoria.
 * \return (-1) Error / (0) Ok
 */
int col_altaForzada(Color* list, int len, char* color)
{
    int retorno = -1;
    int index;

    if(list != NULL && len > 0 && color != NULL)
    {
		if(cli_findFree(list, len, &index) == 0)
		{
			strncpy(list[index].colorBarbijos, color, LONG_COLOUR);
			list[index].idColorBarbijos = generateNewId();
			list[index].isEmpty = 0;
			retorno = 0;
		}
    }
    return retorno;
}

/**
 * \brief Busca un espacio libre en el array.
 * \param Color* list, Es el puntero al array.
 * \param int len, es el limite de array.
 * \param int* pIndex, puntero al espacio de memoria.
 * \return (-1) Error / (0) Ok
 */
int col_findFree(Color* list, int len, int* pIndex)
{
	int retorno = -1;
	int i;

	if (list != NULL && len > 0 && pIndex!= NULL)
	{
		for (i = 0; i < len; i++)
		{
			if(list[i].isEmpty == 1)
			{
				*pIndex = i;
				retorno = 0;
				break;
			}
		}
	}
	return retorno;
}

/**
 * \brief Busca el elemento por id y se guarda su indice en un puntero.
 * \param Color list, Es el puntero al array.
 * \param int len, es el limite de array.
 * \param int id, es el limite de array.
 * \param int* pIndex, puntero al espacio de memoria.
 * \return Retorna el indice
 */
int col_findById(Color* list, int len, int id, int* pIndex)
{
	int retorno = -1;
	int i;

	if (list != NULL && len > 0 && pIndex != NULL)
	{
		for (i = 0; i < len; i++)
		{
			if(list[i].isEmpty == 0 && list[i].idColorBarbijos == id)
			{
				*pIndex = i;
				retorno = 0;
				break;
			}
		}
	}
	return retorno;
}
/**
 * \brief Busca el elemento por id y se guarda el color en un puntero.
 * \param Color list, Es el puntero al array.
 * \param int len, es el limite de array.
 * \param int id, es el limite de array.
 * \param char* color, puntero al espacio de memoria.
 * \return Retorna el color
 */
int col_colorFindById(Color* list, int len, int id, char* color)
{
	int retorno = -1;
	int i;

	if (list != NULL && len > 0 && id != NULL)
	{
		for (i = 0; i < len; i++)
		{
			if(list[i].isEmpty == 0 && list[i].idColorBarbijos == id)
			{
				strncpy(list[i].colorBarbijos, color, LONG_COLOUR);
				retorno = 0;
				break;
			}
		}
	}
	return retorno;
}
/**
 * \brief Realiza el alta solo si el indice corresponde a un espacio vacio (isEmpty == 0).
 * \param Cliente* list, Es el puntero al array.
 * \param int len, es el limite de array.
 * \param int id, indica el id del elemento.
 * \return (-1) Error / (0) Ok
 */
int col_add(Color* list, int len)
{
	int retorno = -1;
	int index;
	Color buffer;

	if(list != NULL && len > 0)
	{
		if( cli_findFree(list, len, &index) == 0 && index < len &&
			utn_getText(buffer.colorBarbijos, "Ingrese el color del barbijo: ", "Color invalido.\n", 2, LONG_COLOUR - 1) == 0)
		{
			buffer.isEmpty = 0;
			buffer.idColorBarbijos = generateNewId();
			list[index] = buffer;
			cli_showClient(list, index);
			retorno = 0;
		}
	}
	return retorno;
}
