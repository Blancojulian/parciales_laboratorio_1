/*
 * Compra.c
 *
 *  Created on: 2 may. 2021
 *      Author: Planton1911
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <float.h>
#include <limits.h>
#include "Compra.h"
#include "Cliente.h"
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
