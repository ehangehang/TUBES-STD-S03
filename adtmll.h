#ifndef ADTMLL_H_INCLUDED
#define ADTMLL_H_INCLUDED

#include <iostream>
#include <stdlib.h>
#include <conio.h>
#include <string>
using namespace std;

typedef struct elmParent *adrParent;
typedef struct elmChild *adrChild;
typedef struct elmGames *adrGames;
struct dataGame {
    string judul;
    string studio;
    string genre;
    string tahun;
    string description;
    int rating;
    int harga;
};
struct elmParent {
    string genre;
    adrParent nextParent;
    adrChild firstChild;
};
struct elmChild {
    adrGames infoChild;
    adrChild nextChild;
};
struct elmGames {
    dataGame info;
    adrGames nextGame;
    adrGames prevGame;
};
struct listParent {
    adrParent firstParent;
    adrParent lastParent;
};
struct listGames {
    adrGames firstGames;
    adrGames lastGames;
};

/*
STEAM MLL
-user class (admin, customer)
    -admin:
        1. nambah genre
        2. nambah game
        3. menghapus genre
        4. menghapus game
        5. mencari genre
        6. mencari game
        7. menghitung jumlah game per genre (v)
    -customer:
        1. mencari genre
        2. mencari game dari genre
        3. mencari game berdasarkan judul (menampilkan data game + genre nya) (v)
        4. mencari berdasarkan spesifikasi (v)
        5. memasukkan game ke keranjang
        6. menghitung keranjang
*/

//INIT
void createListParent(listParent &P);
void createListGame(listGames &G);
adrParent newGenre(string genre);
adrGames newGame(dataGame game);

//ADD
void addParentFirst(listParent &P, string genre);
void addGameLast(listParent &P, listGames &G, dataGame game);
adrParent searchGenre(listParent &P, string genre);
adrGames searchGameJudul(listGames &G, string gameJudul);
void addChildToParentFirst(listParent &P, listGames G);

//DELETE
void deleteGenre(listParent &P, string genre, adrParent &storeP);
void deleteGame(listGames &G, string judulGame, adrGames &storeG);
//deleteChild belum dibuat
void deleteChild(listParent &P, listGames &G, string judulGame);

//PRINTING
void printParent(listParent P);
void printListGame(listGames G);
void printParentChild(listParent P);

//MENU
void login(int userChoice, listParent &P, listGames &G);
void menuChoices(int userChoice);
void menuAdmin(int user, listParent &P, listGames &G);
void menuCustomer(int user, listParent &P, listGames &G);

#endif // ADTMLL_H_INCLUDED
