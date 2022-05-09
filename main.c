#include "main.h"

int rand_int() {
    return rand() % 100 + 1;
}

int elso_terulet(char* terulet) {
    for (int i = 0; i < sizeof(teruletek1) / sizeof(teruletek1[0]); i++) {
        if (strcmp(terulet, teruletek1[i]) == 0) {
            return 1;
        }
    }
    return 0;
}

void csovezes() {
    srand(time(NULL));
    int pipe1[2];
    int pipe2[2];

    int status1, status2;

    if (pipe(pipe1) < 0) {
        perror("Hiba a pipe nyitaskor!");
        exit(EXIT_FAILURE);
    }
    if (pipe(pipe2) < 0) {
        perror("Hiba a pipe nyitaskor!");
        exit(EXIT_FAILURE);
    }

    (pid1 = fork()) && (pid2 = fork());

    if (pid1 < 0 || pid2 < 0) {
        perror("Fork hiba");
        exit(EXIT_FAILURE);
    }

    if (pid1 == 0) { //gyerek 1
        int db = 0;
        read(pipe1[0], &db, sizeof(int));
        struct Jelentkezes max = (struct Jelentkezes) {.nev = "", .terulet = "", .alkalom = 0, .db = 0};
        struct Jelentkezes tmp = (struct Jelentkezes) {.nev = "", .terulet = "", .alkalom = 0, .db = 0};
        for (int i = 0; i < db; ++i) {
            read(pipe1[0], &tmp, sizeof(tmp));
            printf("Gyerek1: %s jelentkezett a %s területre %d db-al\n", tmp.nev, tmp.terulet, tmp.db);
            if (tmp.db > max.db) {
                strcpy(max.nev, tmp.nev);
                strcpy(max.terulet, tmp.terulet);
                max.alkalom = tmp.alkalom;
                max.db = tmp.db;
            }
        }

        write(pipe1[1], &max, sizeof(max));
    } else if (pid2 == 0) { //gyerek 2
        int db2 = 0;
        read(pipe2[0], &db2, sizeof(int));
        struct Jelentkezes max = (struct Jelentkezes) {.nev = "", .terulet = "", .alkalom = 0, .db = 0};
        struct Jelentkezes tmp = (struct Jelentkezes) {.nev = "", .terulet = "", .alkalom = 0, .db = 0};
        for (int j = 0; j < db2; ++j) {
            read(pipe2[0], &tmp, sizeof(tmp));
            printf("Gyerek2: %s jelentkezett a %s területre %d db-al\n", tmp.nev, tmp.terulet, tmp.db);
            if (tmp.db > max.db) {
                strcpy(max.nev, tmp.nev);
                strcpy(max.terulet, tmp.terulet);
                max.alkalom = tmp.alkalom;
                max.db = tmp.db;
            }
        }

        write(pipe2[1], &max, sizeof(max));
    } else { // felnott
        struct Jelentkezes jelentkezesek1[MAX_N];
        int db1 = 0;

        for (int i = 0; i < db; ++i) {
            if (elso_terulet(jelentkezesek[i].terulet)) {
                jelentkezesek1[db1] = jelentkezesek[i];
                jelentkezesek1[db1].db = rand_int();
                db1++;
            }
        }

        write(pipe1[1], &db1, sizeof(db1));
        for (int i = 0; i < db1; ++i) {
            write(pipe1[1], &jelentkezesek1[i], sizeof(jelentkezesek1[i]));
        }

        //printf("%s jelentkezett a %s területre %d db-al\n", tmp.nev, tmp.terulet, tmp.db);

        struct Jelentkezes jelentkezesek2[MAX_N];
        int db2 = 0;

        for (int i = 0; i < db; ++i) {
            if (!elso_terulet(jelentkezesek[i].terulet)) {
                jelentkezesek2[db2] = jelentkezesek[i];
                jelentkezesek2[db2].db = rand_int();
                db2++;
            }
        }

        write(pipe2[1], &db2, sizeof(db2));
        for (int i = 0; i < db2; ++i) {
            write(pipe2[1], &jelentkezesek2[i], sizeof(jelentkezesek2[i]));
        }

        waitpid(pid1, &status1, 0);
        waitpid(pid2, &status2, 0);

        struct Jelentkezes tmp = (struct Jelentkezes) {.nev = "", .terulet = "", .alkalom = 0, .db = 0};
        read(pipe1[0], &tmp, sizeof(tmp));
        struct Jelentkezes tmp2 = (struct Jelentkezes) {.nev = "", .terulet = "", .alkalom = 0, .db = 0};
        read(pipe2[0], &tmp2, sizeof(tmp2));

        if (tmp.db > tmp2.db) {
            printf("A legjobb nyuszi: %s a %s teruletrol %d. alkalommal %d db tojassal\n", tmp.nev, tmp.terulet, tmp.alkalom, tmp.db);
        } else {
            printf("A legjobb nyuszi: %s a %s teruletrol %d. alkalommal %d db tojassal\n", tmp2.nev, tmp2.terulet, tmp2.alkalom, tmp2.db);
        }
    }
}

void add_to_array(struct Jelentkezes* mit){
    strcpy(jelentkezesek[db].nev, (*mit).nev);
    strcpy(jelentkezesek[db].terulet, (*mit).terulet);
    jelentkezesek[db].alkalom = (*mit).alkalom;
    db++;
}

int test_data(char words[3][128]) {
    int i;
    for (i = 0; words[0][i] != '\0'; i++) {
        if (!(isalpha(words[0][i]) || words[0][i] == ' ')) {
            return 0;
        }
    }
    if (i = atoi(words[2]), i == 0) {
        return 0;
    }
    int in = 0;
    for (i = 0; i < 7; i++) {
        if (strcmp(words[1], teruletek[i]) == 0) {
            in = 1;
        }
    }
    return in;
}

int read_data_from_console(struct Jelentkezes* mit) {
    char words[3][128];
    char *pch;

    printf("Kerem a nevet: ");
    fflush(stdout);
    gets(buffer);
    strcpy(words[0], buffer);

    printf("Kerem a teruletet: ");
    fflush(stdout);
    gets(buffer);
    strcpy(words[1], buffer);

    printf("Kerem az alkalmat: ");
    fflush(stdout);
    gets(buffer);
    strcpy(words[2], buffer);

    if (test_data(words) == 1) {
        strcpy((*mit).nev, words[0]);
        strcpy((*mit).terulet, words[1]);
        (*mit).alkalom = atoi(words[2]);
        printf("Az adatok megfeleloek!\n");
        fflush(stdout);
        return 1;
    }

    printf("Hibas adatok!\n");
    fflush(stdout);
    return 0;
}

void write_file(char *filename) {
    FILE *f;
    if ((f = fopen(filename, "w")) == NULL) {
        printf("Nem lehet megnyitni a filet!\n");
        fflush(stdout);
        exit(1);
    }
    int i;
    for (i = 0; i < db; i++) {
        fprintf(f, "%s %s %d\n", jelentkezesek[i].nev, jelentkezesek[i].terulet, jelentkezesek[i].alkalom);
    }
    fflush(stdout);

    fclose(f);
}

void delete_data(struct Jelentkezes* mit) {
    int i, j;
    int status = 0;
    for (i = 0; i < db; i++) {
        if (strcmp(jelentkezesek[i].nev, (*mit).nev) == 0 && strcmp(jelentkezesek[i].terulet, (*mit).terulet) == 0 && jelentkezesek[i].alkalom == (*mit).alkalom) {
            for (j = i; j < db; j++) {
                jelentkezesek[j] = jelentkezesek[j + 1];
            }
            db--;
            status++;
        }
    }
    if (status == 0) {
        printf("A torles nem sikerult!\n");
    } else {
        printf("A torles sikerult!\n");
    }
}

void write_file_group_by_terulet(char* filename) {
    FILE *f;
    if ((f = fopen(filename, "w")) == NULL) {
        printf("Nem lehet megnyitni a filet!\n");
        fflush(stdout);
        exit(1);
    }
    int i, j;
    for (i = 0; i < 7; i++) {
        fprintf(f, "%s:\n", teruletek[i]);
        fflush(stdout);
        for (j = 0; j < db; j++) {
            if (strcmp(teruletek[i], jelentkezesek[j].terulet) == 0) {
                fprintf(f, "%s %d\n", jelentkezesek[j].nev, jelentkezesek[j].alkalom);
            }
            fflush(stdout);
        }
    }
    fclose(f);
}

void replace_data(struct Jelentkezes* mit, struct Jelentkezes* mire) {
    int i;
    int status = 0;
    for (i = 0; i < db; i++) {
        if (strcmp(jelentkezesek[i].nev, (*mit).nev) == 0 && strcmp(jelentkezesek[i].terulet, (*mit).terulet) == 0 && jelentkezesek[i].alkalom == (*mit).alkalom) {
            strcpy(jelentkezesek[i].nev, (*mire).nev);
            strcpy(jelentkezesek[i].terulet, (*mire).terulet);
            jelentkezesek[i].alkalom = (*mire).alkalom;
            status++;
        }
    }
    if (status == 0) {
        printf("A csere nem sikerult!\n");
        fflush(stdout);
    } else {
        printf("A csere sikerult!\n");
        fflush(stdout);
    }
}

int main(int argc, char *argv[])
{
    if (argc != 2) {
        printf("Adj meg egy fajlnevet!\n");
        fflush(stdout);
        exit(1);
    }
    int todo;
    struct Jelentkezes mit;
    struct Jelentkezes mire;
    do {
        printf("1: uj adat felvetele\n");
        fflush(stdout);
        printf("2: adat modositasa\n");
        fflush(stdout);
        printf("3: adat torlese\n");
        fflush(stdout);
        printf("4: adatok listazasa teruleti alapon\n");
        fflush(stdout);
        printf("5: adatok kiiratasa fajlba\n");
        fflush(stdout);
        printf("6: legjobb nyuszi keresese\n");
        fflush(stdout);
        printf("7: kilepes\n");
        fflush(stdout);
        gets(buffer);
        todo = atoi(buffer);
        switch (todo)
        {
            case 1:
                if (read_data_from_console(&mit) != 1) break;
                add_to_array(&mit);
                break;
            case 2:
                printf("Modositando adat:\n");
                fflush(stdout);
                if (read_data_from_console(&mit) != 1) break;
                printf("Modositott adat:\n");
                fflush(stdout);
                if (read_data_from_console(&mire) != 1) break;
                replace_data(&mit, &mire);
                break;
            case 3:
                printf("Torlendo adat:\n");
                fflush(stdout);
                if (read_data_from_console(&mit) != 1) break;
                delete_data(&mit);
                break;
            case 4:
                printf("Terulet szerinti kiiratas fajlba\n");
                fflush(stdout);
                write_file_group_by_terulet(argv[1]);
                break;
            case 5:
                printf("Adatok kiiratasa fajlba\n");
                fflush(stdout);
                write_file(argv[1]);
                break;
            case 6:
                printf("Legjobb nyuszi kereses\n");
                fflush(stdout);
                csovezes();
                if (pid1 == 0 || pid2 == 0) exit(EXIT_SUCCESS);
                break;
        }
    } while (todo != 7);

    return 0;
}

