/**
 * \file allapotgep.h
 *
 * Ebben a fájlban találja az Allapotgép osztály kezdeti definicióját
 * és két segédfüggvényt.
 *
 * A fájlt tetszés szerint múdosíthatja, azzal a megkütéssel, hogy
 * nem hozhat létre globális függvényt és nem változtathatja az Allapotgép osztáy
 * publikus interfészét.
 *
 * Új osztályokat, típusokat felvehet
 *
 * Ezt a fájlt be kell adni (fel kell tölteni) a megoldással.
 */

#ifndef ALLAPOTGEP_H
#define ALLAPOTGEP_H

#include <ctype.h>
#include <cstring>
#include <iostream>
#include <exception>

#include "memtrace.h"

/**
 * Bázisok
 */
enum Bazis {
    Adenin, Citozin, Guanin, Timin
};

/**
 * Állapotgép publikus interfésze
 * A privát részt szabadon változtathatja, de a publikus részt
 * ne változtassa, ne bővítse!
 */
class Allapotgep {
public:
    //visszaadja melyik állapot aktív
    const char* aktualisallapot();

    //éppen elfogadó állapotban van az állapotgép
    bool elfogad();

    //beérkező bázis hatására, mi történjen
    void atmenet(Bazis b);

    //a lánc feldolgozás után elfogadunk-e
    bool feldolgoz(const Bazis *b, int n);

    //konfig fájl beolvasása
    void konfigural(const char* fajlnev);

    //visszaállítás a kezdő állapotba
    void alaphelyzet();
    ~Allapotgep();
};

/**
 * Segédfüggvény, karakterből enummá konvertál
 * @param: b - bázis 1 betűs jele
 * @return: Bazis enum kontans
 */
inline Bazis cast(char b) {
    char k =  tolower(b);
    Bazis ret;
    switch(k) {
        case 'a': ret = Adenin; break;
        case 'c': ret = Citozin; break;
        case 'g': ret = Guanin; break;
        case 't': ret = Timin; break;
        default: throw "Format!!"; break;
    }
    return ret;
}

/**
 * Segédfüggvény, Bazis konstansból karakterré konvertál
 * @param: b - bazis enmu konstansa
 * @param: upper - nagybetűs legyen-e
 * @return: bázis 1 betűs jele
 */
inline char cast(Bazis b, bool upper = true) {
    char ret = '0';
    switch (b)
    {
        case Adenin: ret = 'a'; break;
        case Citozin: ret = 'c'; break;
        case Guanin: ret = 'g'; break;
        case Timin: ret = 't'; break;
    }
    if(upper)
        ret = toupper(ret);
    return ret;
}

#endif
