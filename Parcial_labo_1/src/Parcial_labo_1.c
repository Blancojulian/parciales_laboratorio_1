/*
 ============================================================================
 Name        : Parcial_labo_1.c
 Author      : Blanco Julián Agustín
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Compra.h"
#include "Cliente.h"
#include "Informe.h"
#include "Color.h"
#include "utn.h"

int main(void) {

		setbuf(stdout,NULL);
		Cliente listCliente[QTY_CLI];
		Compra listAviso[QTY_COM];
		Color listColor[QTY_COL];
		int optionMain;
		int optionReport;

		col_init(listColor, QTY_COM);
		cli_init(listCliente, QTY_CLI);
		compra_init(listAviso, QTY_COM);

		// CLIENTES
		col_altaForzada(listColor, QTY_COL,"Amarillo");//id 1
		col_altaForzada(listColor, QTY_COL,"Rojo");//id 2
		col_altaForzada(listColor, QTY_COL,"Blanco");//id 3
		col_altaForzada(listColor, QTY_COL,"Negro");//id 4
		col_altaForzada(listColor, QTY_COL,"Verde");//id 5

	return EXIT_SUCCESS;
}
