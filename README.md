# Nyuszi-Fork

## Leírás:

Itt a tavasz, a nyuszik is készülnek a "Húsvéti Locsolókirály" választásra. A nyuszi fiúk között versenyt szervez "Főnyuszi", az lesz a "Locsolókirály", aki a húsvéti locsolás során a legtöbb piros tojást gyűjti össze a nyuszi lányoktól. A versenyre jelentkezni kell. 

Eljött a locsoló verseny ideje. "Főnyuszi" (szülő) két részre osztja a területeket.
Barátfa, Lovas, Kígyós-patak és Káposztás kert területekre küld egy versenyfelügyelőt (gyerek) illetve a maradék Szula, Malom telek, Páskom területekre egy másik versenyfelügyelőt(gyerek).
"Főnyuszi" csövön átküldi a versenyfelügyelőknek a területileg illetékes nyuszi versenyzők adatait, akik várják a gyűjtött piros tojások számát az ott élő nyusziktól (véletlen szám 1-100 között). 
Miután megvannak az adatok, a versenyfelügyelők visszaküldik "Főnyuszinak" az adatokat szintén csővezetéken, aki kihirdeti(képernyőre írja) a Húsvéti Locsolókirály verseny eredményét.
Az lesz a győztes, aki a legtöbb piros tojást gyűjti. 

## Fordítás:
```C
cc main.c
```

> Fordításkor egy Warning-ot ad a fordító, a gets() metódus unsafe megvalósítása miatt. A saját kényelmemért használtam ezt a megvalósítást.

## Futtatás:
```C
./a.out <fájl név>
```

## Használat:
A program futtatásakor megjelenik a menü, melyben megtalálhatóak az elvégezhető műveletek.
A header fájlban lévő MAX_N definíció változtatásával lehet változtatni a maximum méretét az eltárolt versenyzőknek.

> 1. Új adat felvétele
> 2. Adat módosítása (amennyiben létezik, az összes megegyező adatot)
> 3. Adat törlése (amennyiben létezik, az összes megegyező adatot)
> 4. Adatok kiiratása az argumentumként megadott fájlba területek szerint
> 5. Adatok kiiratása az argumentumként megadott fájlba felvétel szerint
> 6. Legjobb nyuszi keresése
> 7. Kilépés a programból

