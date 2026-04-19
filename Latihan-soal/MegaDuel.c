#include <stdio.h>
#include "MegaDuel.h"

void runMegaDuel(LabTrack *L)
{
    while (length(*L) > 1)
    {
        MegaNimons first = getElmt(*L, firstIdx(*L));
        MegaNimons last = getElmt(*L, lastIdx(*L));

        printf("\n== DUEL ROUND ==\n");

        duelOnce(first, last);
        MegaNimons winner = resolveDuel(first, last);

        if (first.id == winner.id)
        {
            deleteLast(L, &last);
        }
        else
        {
            deleteFirst(L, &first);
        }
    }

    printf("\n== The Champion: %s ==\n", getElmt(*L, 0).name);
}