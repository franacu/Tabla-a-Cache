//
// Created by Fran on 04/09/2024.
//

#ifndef UNTITLED37_HELPER_H
#define UNTITLED37_HELPER_H
#define TAM 10
typedef struct autos
{
    struct autos *sig;
    struct autos *ant;
    char marca[65];
    int placa;
}Autos;
typedef struct TablaHash
{
    Autos *pos[TAM];
}TablaHash;
typedef struct Cache
{
    Autos *cache;
    int capacidad;
    int tamanio;
}Cache;
Autos *newAutos(char *marca,int placa);
TablaHash *newTablaHash();
Cache *newCache(int capacidad);

void insertarEnTabla(TablaHash*tabla,Autos* autoAI);
void transferirACache(TablaHash*tabla,Cache*cache,int placa);
void mostrarTabla(TablaHash*tabla);
#endif //UNTITLED37_HELPER_H
