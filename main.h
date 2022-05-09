#ifndef NYUSZIKERESES
#define NYUSZIKERESES
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>
#include <sys/wait.h>
#include <string.h>
#include <ctype.h>

struct Jelentkezes {
    char nev[128];
    char terulet[128];
    int alkalom;
    int db;
};

#define MAX_N 100

struct Jelentkezes jelentkezesek[MAX_N];
int db = 0;
char buffer[1024];

pid_t pid1, pid2;

char *teruletek[] = {"Baratfa", "Lovas", "Szula", "Kigyos-patak", "Malom telek", "Paskom", "Kaposztas kert"};

char *teruletek1[] = {"Baratfa", "Lovas", "Kigyos-patak", "Kaposztas kert"};
//char *teruletek2[] = {"Szula", "Malom telek", "Paskom"};

int rand_int();
int elso_terulet(char*);
void csovezes();
void add_to_array(struct Jelentkezes*);
int test_data(char[3][128]);
int read_data_from_console(struct Jelentkezes*);
void write_file(char*);
void delete_data(struct Jelentkezes*);
void write_file_group_by_terulet(char*);
void replace_data(struct Jelentkezes*, struct Jelentkezes*);

#endif // NYUSZIKERESES