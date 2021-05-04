/*
 * Compra.c
 *
 *  Created on: 2 may. 2021
 *      Author: Blanco Julián Agustín
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <float.h>
#include <limits.h>
#include "Compra.h"
#include "Cliente.h"
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
 * \brief Inicializa el array .
 * \param Aviso list, Es el puntero al array.
 * \param int len, es el limite de array.
 * \return (-1) Error / (0) Ok
 */
int compra_init(Compra* list, int len)
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
 * \brief Realiza el alta solo si el indice corresponde a un espacio vacio (isEmpty == 0)
 * \param Aviso* list, Es el puntero al array.
 * \param int len, es el limite de array.
 * \param Cliente* listCliente, Es el puntero al array.
 * \param int lenCliente, es el limite de array.
 * \param int id, indica el id del elemento.
 * \return (-1) Error / (0) Ok
 */
int compra_add(Compra* list, int len, Cliente* listCliente, int lenCliente, Color listColor,int lenColor)
{
	int retorno = -1;
	int index;
	int idCliente;
	int idColor;
	int indexCliente;
	int indexColor;
	Compra buffer;

	if(list != NULL && len > 0 && listCliente != NULL && lenCliente  > 0 && listColor != NULL)
	{
		cli_print(listCliente, lenCliente);
		if( utn_getNumberInt(&idCliente, "Ingrese el id del cliente que publicara el aviso: ", "Error.\n", 1, INT_MAX, 2) == 0 &&
			cli_findById(listCliente, lenCliente, idCliente, &indexCliente) == 0 &&
			compra_findFree(list, len, &index) == 0 && index < len &&
			utn_getNumberInt(&idColor, "Ingrese el color del barbijo: \n1 - Amarillo\n2 - Rojo\n3 - Blanco\n4 - Negro\n5 - Verde\n", "Rubro invalido.\n", 1, QTY_COL, 2) == 0 &&
			col_findById(listColor, lenCliente, idColor, &indexColor) == 0 &&
			utn_getNumberInt(&buffer.cantidadBarbijos, "\nIngrese la cantidad de barbijo(maximo 10): ", "Rubro invalido.\n", 1, 10, 5) == 0 &&
			col_colorFindById(listColor, QTY_COL, buffer.idColorBarbijos, buffer.colorBarbijos) == 0 &&
			utn_getNumberFloat(&buffer.precio,"\nIngrese importe de la compra(maximo 1000.00):","\Precio invalido",1,1000,5) == 0 &&
			utn_getText(buffer.direccion, "Ingrese la direccion: ", "Direccion invalido.\n", 2, LONG_DIRECTION) == 0)
		{
			buffer.isEmpty = 0;
			buffer.estado = COBRADO;
			buffer.idCompra = generateNewId();
			list[index] = buffer;
			list[index].idCliente = listCliente[indexCliente].idCliente;
			list[index].idColorBarbijos = listColor[indexColor].idColorBarbijos;
			avi_showAds(list, index);
			retorno = 0;
		}
		else
		{
			printf("El id seleccionado no existe.\n");
		}
	}
	return retorno;
}

/**
 * \brief Elimina el elemento que de encuentra en el indice recibido.
 * \param Compra* list, Es el puntero al array.
 * \param int len, es el limite de array.
 * \param Cliente* listCliente, Es el puntero al array.
 * \param int lenCliente, es el limite de array.
 * \return (-1) Error / (0) Ok
 */
int compra_clientAndBuysRemove(Compra* list, int len, Cliente* listCliente, int lenCliente)
{
	int retorno = -1;
	int idClienteRemove;
	int indexClienteRemove;
	int respuesta;
	int i;

	if(list != NULL && len > 0 && listCliente != NULL && lenCliente  > 0)
	{
		cli_print(listCliente, lenCliente);
		if( utn_getNumberInt(&idClienteRemove, "Ingrese el id del cliente que se quiere eliminar: ", "ID invalido.\n", 1, INT_MAX, 2) == 0 &&
			cli_findById(listCliente, lenCliente, idClienteRemove, &indexClienteRemove) == 0 && listCliente[indexClienteRemove].isEmpty == 0 &&
			compra_printByIdCliente(list, len, listCliente, lenCliente, idClienteRemove) == 0 &&
			utn_getNumberInt(&respuesta, "El cliente y sus avisos se borraran ¿Desea continuar? (1 - Si/2 - No): ", "Error.\n", SI, NO, 2) == 0)
 		{
			if(respuesta == 1)
			{
				for (i = 0; i < len; i++)
				{
					if(list[i].idCliente == idClienteRemove)
					{
						list[i].isEmpty = 1;
					}
				}
				cli_remove(listCliente, lenCliente, idClienteRemove);
				retorno = 0;
			}
			else
			{
				printf("Se cancelo la eliminación del cliente.\n");
			}
		}
		else
		{
			printf("No se puede borrar el cliente seleccionado.\n");
		}
	}
	return retorno;
}

/**
 * \brief Cambia el estado del aviso a pausado o activo segun corresponda.
 * \param Aviso* list, Es el puntero al array
 * \param int len, es el limite de array
 * \param Cliente* listCliente, Es el puntero al array.
 * \param int lenCliente, es el limite de array.
 * \param int state, indica el estado de los avisos.
 * \return (-1) Error / (0) Ok
 */
int compra_changeStatus(Compra* list, int len, Cliente* listCliente, int lenCliente, int state)
{
	int retorno = -1;
	int idChange;
	int indexChange;
	int indexCliente;
	int respuesta;

	if(list != NULL && len > 0 && listCliente != NULL && lenCliente  > 0 && (state >= 0 || state <= 1))
	{
		compra_mostrarComprasCobradasOPausadas(list, len, !state);
		if( ((state == 1 && utn_getNumberInt(&idChange, "Ingrese el ID del aviso que quiere reanudar: ", "ID invalido.\n", 1, INT_MAX, 2) == 0 &&
			compra_findById(list, len, idChange, &indexChange) == 0 && list[indexChange].estado != state &&
			cli_findById(listCliente, lenCliente, list[indexChange].idCliente, &indexCliente) == 0 && cli_showClient(listCliente, indexCliente) == 0)
				||
			(state == 0 && utn_getNumberInt(&idChange, "Ingrese el id del aviso que quiere pausar: ", "ID invalido.\n", 1, INT_MAX, 2) == 0 &&
			compra_findById(list, len, idChange, &indexChange) == 0 && list[indexChange].estado != state &&
			cli_findById(listCliente, lenCliente, list[indexChange].idCliente, &indexCliente) == 0 && cli_showClient(listCliente, indexCliente) == 0)) &&
			utn_getNumberInt(&respuesta, "¿Desea cambiar el estado del aviso? (1- Si/2- No): ", "Error.\n", SI, NO, 2) == 0)
		{
			if(respuesta == 1)
			{
				list[indexChange].estado = state;
				retorno = 0;
			}
			else
			{
				printf("Se cancelo el cambio de estado del aviso.\n");
			}
		}
		else
		{
			printf("No se puede cambiar el estado del ID seleccionado.\n");
		}
	}
	return retorno;
}

/**
 * \brief Muestra un elemento del array por el indice recibido.
 * \param Cliente* list, Es el puntero al array.
 * \param int len, es el limite de array.
 * \param int index, recibe un indice del array.
 * \return (-1) Error / (0) Ok
 */
int compra_showBuys(Compra* list,int index)
{
	int retorno = -1;
	char estadoAviso[20];

	if(list != NULL && index >= 0)
	{
		if(list[index].isEmpty==0)
		{
			if(list[index].estado == COBRADO)
			{
				snprintf(estadoAviso, 20, "COBRADO");
			}
			else
			{
				snprintf(estadoAviso, 20, "PENDIENTE");
			}
			printf("ID cliente: %-1d - ID compra: %-1d - Cantidad barbijos: %-1d - Color barbijos: %-50s - Precio: %-2f - Direccion: %-50s - Estado: %s.\n",
					list[index].idCliente, list[index].idCompra, list[index].cantidadBarbijos, list[index].colorBarbijos, list[index].precio, list[index].direccion, estadoAviso);
			retorno = 0;
		}
	}
	return retorno;
}

/**
 * \brief Imprime los datos cargados.
 * \param Compra* list, Es el puntero al array
 * \param int len, es el limite de array
 * \param Cliente* listCliente, Es el puntero al array.
 * \param int lenCliente, es el limite de array.
 * \param int id, recibira el id del cliente.
 * \return (-1) Error / (0) Ok
 */
int compra_printByIdCliente(Compra* list, int len, Cliente* listCliente, int lenCliente, int id)
{
	int retorno = -1;
	int i;
	char estadoAviso[20];

	if(list != NULL && len > 0 && listCliente != NULL && lenCliente  > 0 && id > 0)
	{
		for (i = 0; i < len; i++)
		{
			if(list[i].isEmpty == 0 && list[i].idCliente == id)
			{
				if(list[i].estado == COBRADO)
							{
								snprintf(estadoAviso, 20, "COBRADO");
							}
							else
							{
								snprintf(estadoAviso, 20, "PENDIENTE");
							}
				printf("ID cliente: %-1d - ID compra: %-1d - Cantidad barbijos: %-1d - Color barbijos: %-50s - Precio: %-2f - Direccion: %-50s - Estado: %s.\n",
									list[i].idCliente, list[i].idCompra, list[i].cantidadBarbijos, list[i].colorBarbijos, list[i].precio, list[i].direccion, estadoAviso);

			}
		}
		retorno = 0;
	}
	return retorno;
}

/**
 * \brief Imprime las compras cobradas o pendientes.
 * \param Compra* list, Es el puntero al array
 * \param int len, es el limite de array
 * \param int state, indica el estado de los avisos.
 * \return (-1) Error / (0) Ok
 */
int compra_mostrarComprasCobradasOPausadas(Compra* list, int len, int state)
{
    int retorno = -1;

    if(list != NULL && len > 0 && (state >= 0 || state <= 1))
    {
        for(int i=0;i<len;i++)
        {
            if(list[i].estado == state && list[i].isEmpty == 0)
            {
            	avi_showAds(list, i);
                retorno = 0;
            }
        }
    }
    return retorno;
}

/**
 * \brief Imprime las compras cobradas o pendientes.
 * \param Compra* list, Es el puntero al array
 * \param int len, es el limite de array
 * \param int state, indica el estado de las compras.
 * \return (-1) Error / (0) Ok
 */
int compra_mostrarComprasCobradasOPausadasPorId(Compra* list, int len, int state, int id)
{
    int retorno = -1;

    if(list != NULL && len > 0 && (state >= 0 || state <= 1))
    {
        for(int i=0;i<len;i++)
        {
            if(list[i].estado == state && list[i].isEmpty == 0 && list[i].idCliente == id)
            {
            	avi_showAds(list, i);
                retorno = 0;
            }
        }
    }
    return retorno;
}

/**
 * \brief Busca el elemento por id y se guarda su indice en un puntero.
 * \param Compra list, Es el puntero al array.
 * \param int len, es el limite de array.
 * \param int id, es el limite de array.
 * \param int* pIndex, puntero al espacio de memoria.
 * \return Retorna el indice
 */
int compra_findById(Compra* list, int len, int id, int* pIndex)
{
	int retorno = -1;
	int i;

	if (list != NULL && len > 0 && pIndex != NULL)
	{
		for (i = 0; i < len; i++)
		{
			if(list[i].isEmpty == 0 && list[i].idCompra == id)
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
 * \brief Busca un espacio libre en el array.
 * \param Compra* list, Es el puntero al array.
 * \param int len, es el limite de array.
 * \param int* pIndex, puntero al espacio de memoria.
 * \return (-1) Error / (0) Ok
 */
int compra_findFree(Compra* list, int len, int* pIndex)
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
 * \brief Busca un espacio ocupado en el array.
 * \param Compra* list, Es el puntero al array.
 * \param int len, es el limite de array.
 * \param int* pIndex, puntero al espacio de memoria.
 * \return (-1) Error / (0) Ok
 */
int compra_findBusy(Compra* list, int len)
{
	int retorno = -1;
	int i;

	if (list != NULL && len > 0)
	{
		for (i = 0; i < len; i++)
		{
			if(list[i].isEmpty == 0)
			{
				retorno = 0;
				break;
			}
		}
	}
	return retorno;
}

/**
 * \brief Realiza un alta forzada de un elemento.
 * \param Compra* list, Es el puntero al array.
 * \param Color* listColor, Es el puntero al array.
 * \param int len, es el limite de array
 * \param int idCliente, indica el id del cliente.
 * \param floar precio, indica el id del cliente.
 * \param int cantidadBarbijos, indica la cantidad de barbijos.
 * \param int idColor, indica el color de los barbijos.
 * \param char* direccion, Puntero al espacio de memoria.
 * \return (-1) Error / (0) Ok
 */
int compra_altaForzada(Compra* list, Color listColor, int len, int idCliente, float precio,int cantidadBarbijos, int idColor, char* direccion)
{
    int retorno = -1;
    int index;

    if(list != NULL && len > 0 && idCliente > 0 && direccion != NULL)
    {
		if(compra_findFree(list, len, &index) == 0)
		{
			strncpy(list[index].direccion, direccion, LONG_DIRECTION);
			list[index].idCliente = idCliente;
			list[index].cantidadBarbijos = cantidadBarbijos;
			list[index].precio = precio;
			list[index].idColorBarbijos = idColor;
			list[index].estado = COBRADO;
			list[index].idCompra = generateNewId();
			list[index].isEmpty = 0;
			col_colorFindById(listColor,LONG_COLOUR, idColor, list[index].colorBarbijos);
			retorno = 0;
		}
    }
    return retorno;
}
