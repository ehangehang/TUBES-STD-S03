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

void addGameLast(listGames &G, dataGame game) {
    adrGames adrG = newGame(game);

    if (G.firstGames == NULL) {
        G.firstGames = adrG;
        G.lastGames = adrG;
    } else {
        G.lastGames->nextGame = adrG;
        adrG->prevGame = G.lastGames;
        G.lastGames = adrG;
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

void addChildToParentFirst(listParent &P, listGames G, string genre, string gameJudul) {
    adrChild C = new elmChild;
    adrGames tobeG = searchGameJudul(G, gameJudul);

    C->infoChild = tobeG;
    C->nextChild = NULL;

    if (P.firstParent == NULL) {
        cout << "List Empty!" << endl;
    } else {
        adrParent tobeP = searchGenre(P, genre);
        if (tobeP->firstChild == NULL) {
            tobeP->firstChild = C;
        } else {
            C->nextChild = tobeP->firstChild;
            tobeP->firstChild = C;
        }
    }
}

void login(int userChoice) {
    cout << "Login sebagai?" << endl;
    cout << "1. Admin" << endl;
    cout << "2. Customer" << endl;
    cout << "Pilih: "; cin >> userChoice;

    /**
        belum dikasi throw error (if choice is not 1 or 2)
    */
    switch(userChoice) {
    case 1:
        menuAdmin(userChoice);
        break;
    case 2:
        menuCustomer(userChoice);
        break;
    }
}

void menuChoices(int userChoice) {
    if (userChoice == 1) {
        cout << "====== MENU ADMIN ======" << endl;
        cout << "1. Tambah genre baru" << endl;
        cout << "2. Tambah game baru" << endl;
        cout << "3. Hapus genre" << endl;
        cout << "4. Hapus game" << endl;
        cout << "5. Tampilkan game berdasarkan genre" << endl;
        cout << "6. Cari game dengan judul tertentu" << endl;
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

void menuAdmin(int user) {
    system("cls");

    menuChoices(user);
    int choice;
    cout << "Pilih menu: "; cin >> choice;
    while (choice != 0) {
        switch (choice) {
        case 1:
            system("cls");
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
        case 5:
            cout << "do action " << choice << endl;

            system("cls");
            menuChoices(user);
            cout << "Pilih menu: "; cin >> choice;
            break;
        case 6:
            cout << "do action " << choice << endl;

            system("cls");
            menuChoices(user);
            cout << "Pilih menu: "; cin >> choice;
            break;
        case 7:
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
void menuCustomer(int user) {
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
