# Egy kis genetika
**Szorgalmi feladat Karsa Zoltántól**. (extra pont: 2)

# Egy kis genetika

Genetikai kódunkat a következő 4 bázis alkotja: 
 * Adenin (A)
 * Citozin (C)
 * Guanin (G)
 * Timin (T)

A genetikai vizsgálatunkhoz egy olyan programot kell írni, ami egy előre meghatározott leírásból (továbbiakban konfiguráció) képes létrehozni egy állapotgépet és egy DNS lánc elemzését el tudja végezni a konfiguráció alapján. 
## Emlékeztető
Emlékezz vissza a Programozás alapjai 1 illetve a Digitális technikák tárgyon használt állapotgépekre (véges automaták), mire voltak elegendőek? Hogyan működtek? 

A korábbi tantárgyakkal ellentétben itt az egyes állapotátmeneteknél nem lesz elvégzendő tevékenység (pl.: ly számláló esetén a számláló növelése, ha ly-t találtunk), hanem lesznek érvényes, "elfogadó" állapotok, azaz miután a bemenet elfogyott, és ebben az állapotban (vagy állapotokban) van az automata, elfogadunk, a bemenet jó volt, különben nem. Ezzel gyakorlatilag a véges automaták matematikai modelljéhez jutunk (Bővebben majd algoritmuselmélet tárgyon). Emiatt a korábban megismert ly számláló mását (pl. AC számláló) nem lehet megvalósítani, csak azt tudjuk eldönteni hogy van-e benne AC szakasz, vagy van-e benne 3db AC szakasz, számlálni nem lehet.

## Konfiguráció
Konfigurációs fájl első sora az állapotok számát kódolja (N), a következő N sorban, soronként az állapotok típusa (elfogadó - I, nem elfogadó - H) és az állapotok nevei (max 20 karakter) találhatóak, szóközzel elválasztva. Az első megadott állapot a felsorolásban a kezdőállapot. Ezután az állapotátmeneteket tartalmazó NxN-es mátrix következik a következő formában (a fejléc és az első oszlop nem része a konfigurációnak):

Állapotok | A_1 | A_2 | ... | A_N |
--- | --- | --- | --- |--- |
A_1 | A_1->A_1  | A_1->A_2 | ... | A_1->A_N |
A_2 | A_2->A_1  | A_2->A_2 | ... | A_2->A_N |
... | ...  | ... | ... | ... |
A_N | A_N->A_1  | A_N->A_2 | ... | A_N->A_N |

Az első sor (A_1-hez tartozó) a mátrixban az első állapotból induló átmeneteket mutatja az előző felsorolás sorrendjében, mely bemeneti bázis esetén mely állapotba kerül onnan az automata. A mátrix 2. (A_2) sorában és 3. (A_3) oszlopában találhatóak azon bázisok, melyek hatására a 2. állapotból a 3.-ba kell kerüljön az automata... A celábban a bázisok a rövidítésekkel vannak feltüntetve elválasztó jelek nélkül (pl. CAT), a mátrix soraiban több és eltérő db szóköz gondoskodik a szeparálásról. Ha valahol nincs átmenet, ott nulla (`'0'`) szerepel.

Beolvasáshoz ajánlott a `std::ifstream` használata, hasonlóan használható, mint az `std::cin`, azaz `>>`-val történő beolvasáskor eldobja a felesleges whitespace-eket.

Minden egyes sorban pontosan egyszer fordulhatnak elő valahol az ACGT betűk, így nem lehet olyan, hogy egy állapotból több állapotba is tudnánk menni egy bázis hatására vagy nem tudnánk eldönteni hova kellene lépni (= az automata determinisztikus és teljes).

## Skeleton program
A beadáshoz készetettem egy tesztprogramot (*genetika_teszt.cpp*) és az `allapotgep.h` fájlban megadtam, hogy az **Allapotgep** osztály miyen publikus interfésszel rendelkezik:
```c++
// A bázisokhoz tartozó felsorolás típus.
enum Bazis {
    Adenin, Citozin, Guanin, Timin
};
// Állapotgép publikis interfésze
class Allapotgep {
public:
    //konfig fájl beolvasása, ha a fájl nem létezik/nem lehet megnyitni eldobja a NEPTUN-kódot
    //újra felépíti az állapotgépet, a korábbit törli ha volt
    void konfigural(const char* fajlnev);
    //visszaadja melyik állapot aktív 
    const char* aktualisallapot();
    //éppen elfogadó állapotban van az állapotgép
    bool elfogad();
    //beérkező bázis hatására, mi történjen
    void atmenet(Bazis b);
    //a lánc feldolgozás után elfogadunk-e, nem áll vissza alaphelyzetbe
    bool feldolgoz(Bazis *b, int n);
    //visszaállítás a kezdő állapotba
    void alaphelyzet();
};
```
Két globális függvényt is készítettem az enum kezeléséhez, ami a `char -> Bazis` és `Bazis -> char` konverziót segíti elő. 

A megoldáshoz az **Allapotgep** belső logikája, mezői szabadon megváltoztathatóak, a publikus interfész azonban nem, és nem is bővíthető. Szükség esetén új osztályok szabadon felvehetők az`allapothep.h` fájlba. (Tipikusan legalább még 1-2 osztály felvétele szükséges a szép megoldáshoz.) Az osztályok tagfüggvényeit az `allapotgep.cpp` fájlban kell megvalósítani.


A `konfigural(const char* fajlnev)` függvény kivételt dob, ha a fájlt nem lehet megnyitni, a kivétel során a **neptun** kódodat kell eldobni.  A konfiguráció minden esetben a fenti leírásnak megfelelő, más hibakezelést nem kell megvalósítani.

## Példa
A konfigurációs fájl:
```
2
I ParosTimin
H ParatlanTimin
ACG     T
T       ACG
```
Ezen fájlhoz tartozó állapotgép diagramja:

![állapotgép](statechart.png) 

Példa bemenet: `{Adenin, Guanin, Timin, Citozin, Citozin, Timin}`, ekkor elfogadunk. Ezen bemenet végeztével az `aktualisallapot()` függvény `"ParosTimin"` karakterláncot adja vissza.

Vizsgáld meg az `implikacio.txt` fájlt is! Rajzold fel a hozzá tartozó diagramot, ha szükséges.

## Megoldás
A Git tárolóból letölthető [https://git.ik.bme.hu/Prog2/szorgalmi_feladatok/genetika](https://git.ik.bme.hu/Prog2/szorgalmi_feladatok/genetika)
fájlok felhasználásával hozz létre a lokális fejlesztőkörnyezetedben egy C++ projektet! Ehhez felhasználható a *Makefile*, amiben megtalálhatók a fordítási opciók. Tervezz, fejlessz, tesztelj, majd töltsd fel a megoldását a Jporta rendszerbe! 

## Beadás
Beadandó az `allapotgep.cpp` és `allapotgep.h` fajl. A `genetika_teszt.cpp`-t nem kell beadni, az a teszteléshez van. A Jporta nagyon hasonló programal fog tesztelni.