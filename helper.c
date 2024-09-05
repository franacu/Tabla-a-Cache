//
// Created by Fran on 04/09/2024.
//
#include <stdio.h>
#include "stdlib.h"
#include "string.h"
#include "helper.h"
Autos *newAutos(char *marca,int placa)
{
    Autos *aux= malloc(sizeof(Autos));
    if(aux==NULL)
    {
        printf("Sin memoria suficiente\n");
        exit(-1);
    }
    strcpy(aux->marca,marca);
    aux->placa=placa;
    aux->sig=NULL;
    aux->ant=NULL;
    return aux;
}
TablaHash *newTablaHash()
{
    TablaHash *aux= malloc(sizeof(TablaHash));
    if(aux==NULL)
    {
        printf("Sin memoria suficiente\n");
        exit(-1);
    }
    for(int i=0;i<TAM;i++)
    {
        aux->pos[i]=NULL;
    }
    return aux;
}
Cache *newCache(int capacidad)
{
    Cache *aux= malloc(sizeof(Cache));
    if(aux==NULL)
    {
        printf("Sin memoria suficiente\n");
        exit(-1);
    }
    aux->cache=NULL;
    aux->capacidad=capacidad;
    aux->tamanio=0;
    return aux;
}
int Fhash(int id)
{
    return id%TAM;
}
void insertarEnTabla(TablaHash*tabla,Autos* autoAI)
{
    int i=Fhash(autoAI->placa);
    while (tabla->pos[i]!=NULL)
    {
        i=(i+1)%TAM;
    }
    tabla->pos[i]=autoAI;
}
Autos *hash[TAM]= {NULL};
void eliminar(Cache*cache)
{
    if (cache->cache == NULL) return;

    Autos *act = cache->cache;
    while (act->sig != NULL) {
        act = act->sig;
    }

    if (act->ant != NULL) {
        act->ant->sig = NULL;
    } else {
        cache->cache = NULL;
    }

    hash[act->placa] = NULL;
    free(act);
    cache->tamanio--;
}
void apilar(Cache*cache,Autos*autoAI)
{
    if (cache->cache != NULL) {
        cache->cache->ant = autoAI;
    }
    autoAI->sig = cache->cache;
    cache->cache = autoAI;
    autoAI->ant = NULL;
    hash[autoAI->placa] = autoAI;
    cache->tamanio++;
}

void transferirACache(TablaHash*tabla,Cache*cache,int placa)
{
    int i = Fhash(placa);
    Autos *act = tabla->pos[i];
    Autos *ant = NULL;

    while (act != NULL) {
        if (act->placa == placa) {
            // Eliminar el auto de la tabla hash
            if (ant == NULL) {
                tabla->pos[i] = act->sig;
            } else {
                ant->sig = act->sig;
            }

            if (hash[placa] == NULL) {
                if (cache->tamanio == cache->capacidad) {
                    eliminar(cache);
                }
                apilar(cache, act);
            } else {
                if(cache->cache!=act)
                {
                    if(act->sig!=NULL)
                    {
                        act->ant->sig=act->sig;
                    }
                    if(act->ant!=NULL)
                    {
                        act->sig->ant=act->ant;
                    }
                }
                cache->tamanio--;
                apilar(cache, act);
            }
        }
        ant = act;
        act = act->sig;
    }
}

void mostrarTabla(TablaHash*tabla)
{
    for (int i = 0; i < TAM; ++i)
    {
        Autos *act = tabla->pos[i];
        while (act != NULL) {
            printf("Marca: %s\nPlaca: %d\n", act->marca, act->placa);
            act = act->sig;
        }
    }
}