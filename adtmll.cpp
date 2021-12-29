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
    ADD TO MULTIPLE PARENT (~)
    still error if input descending
    eg.
    1. nGenre = 3
    2. nGenre = 4
    then all genre will be reset with random value
*/
void addChildToParentFirst(listParent &P, listGames G) {
    adrChild C = new elmChild;
    adrGames tobeG = G.lastGames;

    bool foundGenre = false;

    C->infoChild = tobeG;
    C->nextChild = NULL;

    if (P.firstParent == NULL) {
        for (int i = 0; i < C->infoChild->info.nGenre; i++) {
            addParentFirst(P, C->infoChild->info.genre[i]);
            P.firstParent->firstChild = C;
        }
    } else {
        for (int i = 0; i < C->infoChild->info.nGenre; i++) {
            foundGenre = false;
            adrParent tobeP = P.firstParent;
            while (tobeP != NULL && foundGenre == false) {
                if (tobeP->genre == C->infoChild->info.genre[i]) {
                    C->nextChild = tobeP->firstChild;
                    tobeP->firstChild = C;
                    foundGenre = true;
                }
                tobeP = tobeP->nextParent;
            }
            if (foundGenre == false) {
                addParentFirst(P, C->infoChild->info.genre[i]);
                P.firstParent->firstChild = C;
            }
        }
    }

/*
    if (P.firstParent == NULL) {
        addParentFirst(P, C->infoChild->info.genre);
        C->nextChild = P.firstParent->firstChild;
        P.firstParent->firstChild = C;
    } else {
        adrParent tobeP = P.firstParent;
        while (tobeP != NULL && foundGenre == false) {
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
*/
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

void deleteGame(listParent &P, listGames &G, string judulGame, adrGames &storeG) {
    bool found = false;
    adrParent adrP, helperP;
    adrChild storeC;

    if (G.firstGames == NULL) {
        cout << "List kosong!" << endl;
        storeG = NULL;
    } else {
        if (G.firstGames->info.judul == judulGame) {
            storeG = G.firstGames;
            if (G.firstGames->nextGame != NULL) {
                G.firstGames = G.firstGames->nextGame;
            } else {
                G.firstGames = NULL;
            }
            storeG->nextGame = NULL;
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
        }else {
            deleteChild(P, storeG, storeC);
        }
    }
}

void deleteChild(listParent &P, adrGames storeG, adrChild &storeC) {
    adrParent helperGenre = P.firstParent;
    bool found = false;

    for (int i = 0; i < storeG->info.nGenre; i++) {
        found = false;
        while (helperGenre != NULL && found == false) {
            if (helperGenre->genre == storeG->info.genre[i]) {
                found = true;
            } else {
                helperGenre = helperGenre->nextParent;
            }
        }

        if (helperGenre->firstChild->infoChild->info.judul == storeG->info.judul) {
            storeC = helperGenre->firstChild;
            if (helperGenre->firstChild->nextChild != NULL) {
                helperGenre->firstChild = helperGenre->firstChild->nextChild;
            } else {
                helperGenre->firstChild = NULL;
            }
            storeC->nextChild = NULL;
        } else {
            adrChild helperC = helperGenre->firstChild;
            adrChild helperCA = helperGenre->firstChild;
            while (helperCA != NULL) {
                if (helperCA->infoChild->info.judul == storeG->info.judul) {
                    storeC = helperCA;
                    helperC->nextChild = storeC->nextChild;
                    storeC->nextChild = NULL;
                }
                helperC = helperCA;
                helperCA = helperCA->nextChild;
            }
        }
    }

    /*
    while (helperGenre != NULL) {
        if (helperGenre->genre == storeG->info.genre) {
            break;
        }
        helperGenre = helperGenre->nextParent;
    }

    if (helperGenre->firstChild->infoChild->info.judul == storeG->info.judul) {
        storeC = helperGenre->firstChild;
        if (helperGenre->firstChild->nextChild != NULL) {
            helperGenre->firstChild = helperGenre->firstChild->nextChild;
        } else {
            helperGenre->firstChild = NULL;
        }
        storeC->nextChild = NULL;
    } else {
        adrChild helperC = helperGenre->firstChild;
        adrChild helperCA = helperGenre->firstChild;
        bool found = false;
        while (helperCA != NULL && found == false) {
            if (helperCA->infoChild->info.judul == storeG->info.judul) {
                storeC = helperCA;
                helperC->nextChild = storeC->nextChild;
                storeC->nextChild = NULL;
                found = true;
            }
            helperC = helperCA;
            helperCA = helperCA->nextChild;
        }

        if (found == false) {
            storeC = helperCA;
            helperC->nextChild = NULL;
        }
    }
    */
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
            cout << "Genre      : " << endl;
            for (int i = 0; i < helperG->info.nGenre; i++) {
                cout << i+1 << ". " << helperG->info.genre[i] << endl;
            }
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
            i = 1;
            helperPC = helperPC->nextParent;
        }
    }
}

void printGenreDetail(listParent P, string genre) {
    if (P.firstParent == NULL) {
        cout << "List kosong!" << endl;
    } else {
        adrParent helper = P.firstParent;
        while (helper != NULL) {
            if (helper->genre == genre) {
                break;
            }
            helper = helper->nextParent;
        }
        if (helper->firstChild == NULL) {
            cout << "List genre kosong!" << endl;
        } else {
            adrChild helperC = helper->firstChild;
            int i = 1;
            while (helperC != NULL) {
                cout << "Game " << i << ":" << endl;
                cout << "Judul      : " << helperC->infoChild->info.judul << endl;
                cout << "Studio     : " << helperC->infoChild->info.studio << endl;
                cout << "Genre      : " << endl;
                for (int i = 0; i < helperC->infoChild->info.nGenre; i++) {
                    cout << i+1 << ". " << helperC->infoChild->info.genre[i] << endl;
                }
                cout << "Tahun Rilis: " << helperC->infoChild->info.tahun << endl;
                cout << "Deskripsi  : " << helperC->infoChild->info.description << endl;
                cout << "Rating     : " << helperC->infoChild->info.rating << endl;
                cout << "Harga      : " << helperC->infoChild->info.harga << endl << endl;
                helperC = helperC->nextChild;
                i++;
            }
        }
    }
}

void printSpcGameDetail(listParent P, listGames G, string judulGame) {
    if (P.firstParent == NULL) {
        cout << "List kosong!" << endl;
    } else {
        adrGames helperG = searchGameJudul(G, judulGame);
        adrParent helperP = P.firstParent;
        int i = 0;
        while (i < helperG->info.nGenre) {
            while (helperP != NULL) {
                if (helperP->genre == helperG->info.genre[i]) {
                    cout << helperG->info.judul << " ditemukan di genre " << helperP->genre[i] << endl;
                }
                helperP = helperP->nextParent;
            }
            i++;
        }
        cout << "Judul      : " << helperG->info.judul << endl;
        cout << "Studio     : " << helperG->info.studio << endl;
        cout << "Genre      : " << endl;
        for (int j = 0; j < helperG->info.nGenre; j++) {
            cout << i+1 << ". " << helperG->info.genre[j] << endl;
        }
        cout << "Tahun Rilis: " << helperG->info.tahun << endl;
        cout << "Deskripsi  : " << helperG->info.description << endl;
        cout << "Rating     : " << helperG->info.rating << endl;
        cout << "Harga      : " << helperG->info.harga << endl << endl;
    }
}

void login(int userChoice, listParent &P, listGames &G) {

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
        cout << "99. Kembali ke menu login" << endl;
        cout << "0. Exit" << endl;
    } else if (userChoice == 2) {
        cout << "====== MENU CUSTOMER ======" << endl;
        cout << "1. Tampilkan semua game dengan genre tertentu" << endl;
        cout << "2. Tampilkan detail game berdasarkan judul" << endl;
        cout << "3. Filter genre tertentu menurut harga" << endl;
        cout << "4. " << endl;
        cout << ". Masukkan game ke keranjang" << endl;
        cout << ". Menghitung harga keranjang" << endl;
        cout << "99. Kembali ke menu login" << endl;
        cout << "0. Exit" << endl;
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
    string inputGenre;
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
                cout << "Genre      : " << endl;
                gameData.nGenre = 0;
                for (int i = 0; i < sizeof(gameData.genre) && inputGenre != "-"; i++) {
                    cout << i+1 << ". "; cin >> inputGenre;
                    if (inputGenre != "-") {
                        gameData.genre[i] = inputGenre;
                        gameData.nGenre++;
                    }
                }
                cout << "Tahun rilis: "; cin >> gameData.tahun;
                cout << "Description: "; getline(cin >> std::ws, gameData.description);
                cout << "Rating     : "; cin >> gameData.rating;
                cout << "Harga      : "; cin >> gameData.harga;
                system("cls");
                cout << "Judul game : " << gameData.judul << endl;
                cout << "Studio     : " << gameData.studio << endl;
                cout << "Genre      : " << endl;
                for (int i = 0; i < gameData.nGenre; i++) {
                    cout << i+1 << ". " << gameData.genre[i] << endl;
                }
                cout << "Tahun rilis: " << gameData.tahun << endl;
                cout << "Description: " << gameData.description << endl;
                cout << "Rating     : " << gameData.rating << endl;
                cout << "Harga      : " << gameData.harga << endl;
                cout << endl << "Data sudah benar? (Y/N)"; cin >> yono;
            }

            if (yono == 'Y') {
                addGameLast(P, G, gameData);
                yono = 'N';
                inputGenre = "XX";
            }

            system("cls");
            menuChoices(user);
            cout << "Pilih menu: "; cin >> choice;
            break;
        case 3:
            system("cls");
            cout << "Genre yang ingin dihapus: "; getline(cin >> std::ws, tobeDelGenre);
            deleteGenre(P, tobeDelGenre, storeP);
            cout << endl << "Selesai! Tekan enter untuk kembali ke menu utama" << endl;
            getch();

            system("cls");
            menuChoices(user);
            cout << "Pilih menu: "; cin >> choice;
            break;
        case 4:
            system("cls");
            cout << "Judul game yang ingin dihapus: "; getline(cin >> std::ws, tobeDelGame);
            deleteGame(P, G, tobeDelGame, storeG);
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
        case 99:
            system("cls");
            login(user, P, G);
            break;
        }
    }
    if (choice == 0) {
        system("cls");
        cout << "Selesai!" << endl;
    }
}

/*
cout << "====== MENU CUSTOMER ======" << endl;
cout << "1. Tampilkan semua game dengan genre tertentu" << endl;
cout << "2. Tampilkan detail game berdasarkan judul" << endl;
cout << "3. Filter genre tertentu menurut harga" << endl;
cout << "4. "
cout << ". Masukkan game ke keranjang" << endl;
cout << ". Menghitung harga keranjang" << endl;
*/

void menuCustomer(int user, listParent &P, listGames &G) {
    system("cls");

    menuChoices(user);
    int choice;
    //case 1 variables
    string genreGame;
    //case 2 variables
    string findGame;
    cout << "Pilih menu: "; cin >> choice;
    while (choice != 0) {
        switch (choice) {
        case 1:
            system("cls");
            cout << "Masukkan genre yang ingin dilihat: "; cin >> genreGame;
            printGenreDetail(P, genreGame);
            cout << "Selesai! Tekan enter untuk kembali ke menu utama" << endl;
            getch();

            system("cls");
            menuChoices(user);
            cout << "Pilih menu: "; cin >> choice;
            break;
        case 2:
            system("cls");
            cout << "Masukkan game yang ingin dicari: "; getline(cin >> std::ws, findGame);
            printSpcGameDetail(P, G, findGame);
            cout << "Selesai! Tekan enter untuk kembali ke menu utama" << endl;
            getch();

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
        case 99:
            system("cls");
            login(user, P, G);
            break;
        }
    }
    if (choice == 0) {
        system("cls");
        cout << "Selesai!" << endl;
    }
}
