#include "adtmll.h"

void createListParent(listParent &P) {
    P.firstParent = NULL;
    P.lastParent = NULL;
}

void createListGame(listGames &G) {
    G.firstGames = NULL;
    G.lastGames = NULL;
}

adrParent newGenre(string genre) {
    adrParent newParent = new elmParent;

    newParent->genre = genre;
    newParent->nextParent = NULL;
    newParent->firstChild = NULL;

    return newParent;
}

adrGames newGame(dataGame game) {
    adrGames newGames = new elmGames;

    newGames->info = game;
    newGames->nextGame = NULL;
    newGames->prevGame = NULL;

    return newGames;
}

void addParentFirst(listParent &P, string genre) {
    adrParent adrP = newGenre(genre);

    if (P.firstParent == NULL) {
        P.firstParent = adrP;
        P.lastParent = adrP;
    } else {
        adrP->nextParent = P.firstParent;
        P.firstParent = adrP;
    }
}

void addGameLast(listParent &P, listGames &G, dataGame game) {
    adrGames adrG = newGame(game);

    if (G.firstGames == NULL) {
        G.firstGames = adrG;
        G.lastGames = adrG;
        addChildToParentFirst(P, G);
    } else {
        G.lastGames->nextGame = adrG;
        adrG->prevGame = G.lastGames;
        G.lastGames = adrG;
        addChildToParentFirst(P, G);
    }
}

adrGames searchGameJudul(listGames &G, string gameJudul) {
    if (G.firstGames == NULL) {
        return NULL;
    } else {
        adrGames helper = G.firstGames;
        while (helper != NULL) {
            if (helper->info.judul == gameJudul) {
                return helper;
            }
            helper = helper->nextGame;
        }
        return NULL;
    }
}

adrParent searchGenre(listParent &P, string genre) {
    if (P.firstParent == NULL) {
        return NULL;
    } else {
        adrParent helper = P.firstParent;
        while (helper != NULL) {
            if (helper->genre == genre) {
                return helper;
            }
            helper = helper->nextParent;
        }
        return NULL;
    }
}

/**
    ADD TO MULTIPLE PARENT (...)
*/
void addChildToParentFirst(listParent &P, listGames G) {
    adrChild C = new elmChild;
    adrGames tobeG = G.lastGames;

    bool foundGenre = false;

    C->infoChild = tobeG;
    C->nextChild = NULL;

    if (P.firstParent == NULL) {
        addParentFirst(P, C->infoChild->info.genre);
        C->nextChild = P.firstParent->firstChild;
        P.firstParent->firstChild = C;
    } else {
        adrParent tobeP = P.firstParent;
        while (tobeP != NULL && foundGenre) {
            if (tobeP->genre == C->infoChild->info.genre) {
                C->nextChild = tobeP->firstChild;
                tobeP->firstChild = C;
                foundGenre = true;
            }
            tobeP = tobeP->nextParent;
        }
        if (foundGenre == false) {
            addParentFirst(P, C->infoChild->info.genre);
            C->nextChild = P.firstParent->firstChild;
            P.firstParent->firstChild = C;
        }
    }
}

void deleteGenre(listParent &P, string genre, adrParent &storeP) {
    bool found = false;

    if (P.firstParent == NULL) {
        cout << "List kosong!" << endl;
        storeP = NULL;
    } else {
        if (P.firstParent->genre == genre) {
            storeP = P.firstParent;
            P.firstParent = P.firstParent->nextParent;
            storeP->nextParent = NULL;
            found = true;
        } else if (P.lastParent->genre == genre) {
            adrParent helperP = P.firstParent;
            while (helperP->nextParent != P.lastParent) {
                helperP = helperP->nextParent;
            }
            storeP = P.lastParent;
            P.lastParent = helperP;
            helperP->nextParent = NULL;
            found = true;
        } else {
            adrParent helperA = P.firstParent;
            adrParent helperB = P.firstParent;
            while (helperB != NULL && found == false) {
                if (helperB->genre == genre) {
                    helperA->nextParent = helperB->nextParent;
                    helperB->nextParent = NULL;
                    storeP = helperB;
                    found = true;
                }
                helperA = helperB;
                helperB = helperB->nextParent;
            }
        }

        if (found == false) {
            cout << "Genre tidak ditemukan!" << endl;
        }
    }
}

void deleteGame(listGames &G, string judulGame, adrGames &storeG) {
    bool found = false;

    if (G.firstGames == NULL) {
        cout << "List kosong!" << endl;
        storeG = NULL;
    } else {
        if (G.firstGames->info.judul == judulGame) {
            storeG = G.firstGames;
            G.firstGames = G.firstGames->nextGame;
            storeG->nextGame = NULL;
            G.firstGames->prevGame = NULL;
            found = true;
        } else if (G.lastGames->info.judul == judulGame) {
            storeG = G.lastGames;
            G.lastGames = G.lastGames->prevGame;
            storeG->prevGame = NULL;
            G.lastGames->nextGame = NULL;
            found = true;
        } else {
            adrGames helperG = G.firstGames;
            while (helperG != NULL && found == false) {
                if (helperG->info.judul == judulGame) {
                    helperG->prevGame->nextGame = helperG->nextGame;
                    helperG->nextGame->prevGame = helperG->prevGame;
                    helperG->nextGame = NULL;
                    helperG->prevGame = NULL;
                    storeG = helperG;
                    found = true;
                }
                helperG = helperG->nextGame;
            }
        }

        if (found == false) {
            cout << "Game tidak ditemukan!" << endl;
        }
    }
}

void printParent(listParent P) {
    if (P.firstParent == NULL) {
        cout << "List genre kosong!" << endl;
    } else {
        int i = 1;
        adrParent helperP = P.firstParent;
        while (helperP != NULL) {
            cout << "Genre " << i << ": " << helperP->genre << endl;
            i++;
            helperP = helperP->nextParent;
        }
    }
}

void printListGame(listGames G) {
    if (G.firstGames == NULL) {
        cout << "List game kosong!" << endl;
    } else {
        adrGames helperG = G.firstGames;
        int i = 1;
        while (helperG != NULL) {
            cout << "Data game ke-" << i << endl;
            cout << "Judul      : " << helperG->info.judul << endl;
            cout << "Studio     : " << helperG->info.studio << endl;
            cout << "Tahun      : " << helperG->info.tahun << endl;
            cout << "Genre      : " << helperG->info.genre << endl;
            cout << "Description: " << helperG->info.description << endl;
            cout << "Rating     : " << helperG->info.rating << "/5" << endl;
            cout << "Harga      : " << helperG->info.harga << endl << endl;
            helperG = helperG->nextGame;
            i++;
        }
    }
}

void printParentChild(listParent P) {
    if (P.firstParent == NULL) {
        cout << "List kosong!" << endl;
    } else {
        adrParent helperPC = P.firstParent;
        int i = 1;
        while (helperPC != NULL) {
            cout << helperPC->genre << ":" << endl;
            adrChild helperC = helperPC->firstChild;
            while (helperC != NULL) {
                cout << i << ". " << helperC->infoChild->info.judul << endl;
                helperC = helperC->nextChild;
                i++;
            }
            helperPC = helperPC->nextParent;
        }
    }
}

void login(int userChoice, listParent &P, listGames &G) {
    //init list
    createListParent(P);
    createListGame(G);

    cout << "Login sebagai?" << endl;
    cout << "1. Admin" << endl;
    cout << "2. Customer" << endl;
    cout << "Pilih: "; cin >> userChoice;

    /**
        belum dikasi throw error (if choice is not 1 or 2)
    */
    switch(userChoice) {
    case 1:
        menuAdmin(userChoice, P, G);
        break;
    case 2:
        menuCustomer(userChoice, P, G);
        break;
    }
}

void menuChoices(int userChoice) {
    if (userChoice == 1) {
        cout << "====== MENU ADMIN ======" << endl;
        cout << "1. Tambah beberapa genre baru" << endl;
        cout << "2. Tambah game baru" << endl;
        cout << "3. Hapus genre tertentu" << endl;
        cout << "4. Hapus game tertentu" << endl;
        cout << "5. Tampilkan daftar genre" << endl;
        cout << "6. Tampilkan daftar game" << endl;
        cout << "7. Tampilkan jumlah game tiap genre" << endl;
        cout << "0. Exit" << endl;
    } else if (userChoice == 2) {
        cout << "====== MENU ADMIN ======" << endl;
        cout << "1. Tampilkan semua game dengan genre tertentu" << endl;
        cout << "2. Tampilkan game berdasarkan judul" << endl;
        cout << "3. Masukkan game ke keranjang" << endl;
        cout << "4. Menghitung harga keranjang" << endl;
    }
}

void menuAdmin(int user, listParent &P, listGames &G) {
    system("cls");

    menuChoices(user);
    int choice;
    //case 1 variables
    string genre;
    int n;
    //case 2 variables
    dataGame gameData;
    char yono = 'N';
    //case 3 variables
    string tobeDelGenre;
    adrParent storeP;
    //case 4 variables
    string tobeDelGame;
    adrGames storeG;
    //enter to finish
    char enter;
    cout << "Pilih menu: "; cin >> choice;
    while (choice != 0) {
        switch (choice) {
        case 1:
            system("cls");
            cout << "Mau menambah berapa genre: "; cin >> n;
            for (int i = 1; i <= n; i++) {
                cout << "Genre ke-" << i << ": "; cin >> genre;
                addParentFirst(P, genre);
            }
            cout << endl << "Selesai! Tekan enter untuk kembali ke menu utama" << endl;
            getch();

            system("cls");
            menuChoices(user);
            cout << "Pilih menu: "; cin >> choice;
            break;
        case 2:
            while (yono != 'Y') {
                system("cls");
                cout << "Masukkan data game baru:" << endl;
                cout << "Judul game : "; getline(cin >> std::ws, gameData.judul);
                cout << "Studio     : "; getline(cin >> std::ws, gameData.studio);
                cout << "Genre      : "; cin >> gameData.genre;
                cout << "Tahun rilis: "; cin >> gameData.tahun;
                cout << "Description: "; getline(cin >> std::ws, gameData.description);
                cout << "Rating     : "; cin >> gameData.rating;
                cout << "Harga      : "; cin >> gameData.harga;
                system("cls");
                cout << "Judul game : " << gameData.judul << endl;
                cout << "Studio     : " << gameData.studio << endl;
                cout << "Genre      : " << gameData.genre << endl;
                cout << "Tahun rilis: " << gameData.tahun << endl;
                cout << "Description: " << gameData.description << endl;
                cout << "Rating     : " << gameData.rating << endl;
                cout << "Harga      : " << gameData.harga << endl;
                cout << endl << "Data sudah benar? (Y/N)"; cin >> yono;
            }

            if (yono == 'Y') {
                addGameLast(P, G, gameData);
                yono = 'N';
            }

            system("cls");
            menuChoices(user);
            cout << "Pilih menu: "; cin >> choice;
            break;
        case 3:
            system("cls");
            cout << "Genre yang ingin dihapus: "; cin >> tobeDelGenre;
            deleteGenre(P, tobeDelGenre, storeP);
            cout << endl << "Selesai! Tekan enter untuk kembali ke menu utama" << endl;
            getch();

            system("cls");
            menuChoices(user);
            cout << "Pilih menu: "; cin >> choice;
            break;
        case 4:
            system("cls");
            cout << "Judul game yang ingin dihapus: "; cin >> tobeDelGame;
            deleteGame(G, tobeDelGame, storeG);
            cout << endl << "Selesai! Tekan enter untuk kembali ke menu utama" << endl;
            getch();

            system("cls");
            menuChoices(user);
            cout << "Pilih menu: "; cin >> choice;
            break;
        case 5:
            system("cls");
            printParent(P);
            cout << endl << "Selesai! Tekan enter untuk kembali ke menu utama" << endl;
            getch();

            system("cls");
            menuChoices(user);
            cout << "Pilih menu: "; cin >> choice;
            break;
        case 6:
            system("cls");
            printListGame(G);
            cout << "Selesai! Tekan enter untuk kembali ke menu utama" << endl;
            getch();

            system("cls");
            menuChoices(user);
            cout << "Pilih menu: "; cin >> choice;
            break;
        case 7:
            system("cls");
            printParentChild(P);
            cout << "Selesai! Tekan enter untuk kembali ke menu utama" << endl;
            getch();

            system("cls");
            menuChoices(user);
            cout << "Pilih menu: "; cin >> choice;
            break;
        }
    }
    if (choice == 0) {
        system("cls");
        cout << "Selesai!" << endl;
    }
}
void menuCustomer(int user, listParent &P, listGames &G) {
    system("cls");

    menuChoices(user);
    int choice;
    cout << "Pilih menu: "; cin >> choice;
    while (choice != 0) {
        switch (choice) {
        case 1:
            cout << "do action " << choice << endl;

            system("cls");
            menuChoices(user);
            cout << "Pilih menu: "; cin >> choice;
            break;
        case 2:
            cout << "do action " << choice << endl;

            system("cls");
            menuChoices(user);
            cout << "Pilih menu: "; cin >> choice;
            break;
        case 3:
            cout << "do action " << choice << endl;

            system("cls");
            menuChoices(user);
            cout << "Pilih menu: "; cin >> choice;
            break;
        case 4:
            cout << "do action " << choice << endl;

            system("cls");
            menuChoices(user);
            cout << "Pilih menu: "; cin >> choice;
            break;
        }
    }
    if (choice == 0) {
        system("cls");
        cout << "Selesai!" << endl;
    }
}
