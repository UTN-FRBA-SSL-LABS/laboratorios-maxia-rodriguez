#include <stdio.h>
#include "../src/carrito.h"
#include "minunit/minunit.h"

/*
 * Tests de integracion: verifican que las funciones trabajan bien
 * en combinacion, no de forma aislada.
 */

/* ═══════════════════════════════════════════════════════════════════════════
 *  PARTE D — Escribir el test guiado (ver README.md, Parte 8)
 * ═══════════════════════════════════════════════════════════════════════════ */

void test_compra_con_descuento(void) {
    printf("\n[compra con descuento]\n");
    
    Carrito c;
    carrito_init(&c);
    
    Producto pan = {"Pan", 200, 3};
    carrito_agregar(&c, pan);
    
    Producto leche = {"Leche", 350, 2};
    carrito_agregar(&c, leche);
    
    // Obtenemos el total y lo verificamos
    int total_calculado = carrito_total(&c);
    ASSERT_IGUAL(1300, total_calculado); 
    
    // Pasamos el total a la función aislada de descuento
    ASSERT_IGUAL(1170, carrito_descuento(total_calculado, 10));
}

/* ═══════════════════════════════════════════════════════════════════════════
 *  PARTE E — Disenar un test propio (ver README.md, Parte 9)
 * ═══════════════════════════════════════════════════════════════════════════ */

 void test_agregar_hasta_llenar(void) {
    printf("\n[agregar hasta llenar]\n");
    
    Carrito c;
    carrito_init(&c);
    Producto p = {"Cafe", 500, 1};

    // Llenamos el carrito hasta la capacidad máxima
    for (int i = 0; i < MAX_ITEMS; i++) 
    {
        ASSERT_IGUAL(1, carrito_agregar(&c, p));
    }

    // Verificamos usando la interfaz pública del .h
    ASSERT_IGUAL(MAX_ITEMS, carrito_contar(&c)); 

    // Verificamos el rebote (falla intencional)
    ASSERT_IGUAL(0, carrito_agregar(&c, p));

    // Verificamos que el conteo siga intacto
    ASSERT_IGUAL(MAX_ITEMS, carrito_contar(&c));
}

int main(void) {
    printf("=== Tests de integracion ===");
    RESUMEN();
    return EXIT_CODE();
}
