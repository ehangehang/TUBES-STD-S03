#include "adtmll.h"

int main()
{
    listParent P;
    listGames G;

    //init list
    createListParent(P);
    createListGame(G);

    int userChoice;
    login(userChoice, P, G);
/*
    dataGame data;
    data.judul = "Just Cause";
    data.studio = "Square Enix";
    data.tahun = "2014";
    data.description = "Action RPG Roleplay Adventure";
    data.rating = 4;
    data.harga = 400000;
    addGameLast(G, data);

    data.judul = "The Witcher";
    data.studio = "CD Projekt Red";
    data.tahun = "2012";
    data.description = "Action RPG Roleplay Adventure";
    data.rating = 5;
    data.harga = 600000;
    addGameLast(G, data);

    data.judul = "Skyrim";
    data.studio = "Bethesda";
    data.tahun = "2010";
    data.description = "Action RPG Roleplay Adventure";
    data.rating = 5;
    data.harga = 700000;
    addGameLast(G, data);

    data.judul = "Final Fantasy";
    data.studio = "Square Enix";
    data.tahun = "2009";
    data.description = "Action RPG Roleplay Adventure";
    data.rating = 3;
    data.harga = 900000;
    addGameLast(G, data);

    adrGames helperG = G.firstGames;
    int i = 1;
    while (helperG != NULL) {
        cout << "Data ke-" << i << endl;
        cout << "Judul      : " << helperG->info.judul << endl;
        cout << "Studio     : " << helperG->info.studio << endl;
        cout << "Tahun      : " << helperG->info.tahun << endl;
        cout << "Description: " << helperG->info.description << endl;
        cout << "Rating     : " << helperG->info.rating << "/5" << endl;
        cout << "Harga      : " << helperG->info.harga << endl << endl;
        helperG = helperG->nextGame;
        i++;
    }

    addChildToParentFirst(P, G, "Action", "Skyrim");
    addChildToParentFirst(P, G, "Action", "Just Cause");
    addChildToParentFirst(P, G, "Action", "The Witcher");
    addChildToParentFirst(P, G, "RPG", "The Witcher");
    addChildToParentFirst(P, G, "RPG", "Final Fantasy");
    adrParent helperPC = P.firstParent;
    while (helperPC != NULL) {
        cout << helperPC->genre << "->";
        adrChild helperC = helperPC->firstChild;
        while (helperC != NULL) {
            cout << helperC->infoChild->info.judul << ", ";
            helperC = helperC->nextChild;
        }
        helperPC = helperPC->nextParent;
        cout << endl;
    }
    cout << endl;
*/
    return 0;
}
