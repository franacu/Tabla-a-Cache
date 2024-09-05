#include "stdio.h"
#include "helper.h"
int main()
{
    TablaHash *tabla = newTablaHash();
    Cache *cache = newCache(5);

    insertarEnTabla(tabla, newAutos("Mercedes", 32325));
    insertarEnTabla(tabla, newAutos("Ferrari", 38877));
    insertarEnTabla(tabla, newAutos("Aston martin", 124412));
    insertarEnTabla(tabla, newAutos("Ford", 5674787));
    mostrarTabla(tabla);
    printf("Transfiriendo:\n");

    transferirACache(tabla, cache, 32325);
    transferirACache(tabla, cache, 38877);

    Autos *aux = cache->cache;
    while (aux != NULL) {
        printf("Usuario: %s, ID: %d\n", aux->marca, aux->placa);
        aux = aux->sig;
    }
    return 0;
}
