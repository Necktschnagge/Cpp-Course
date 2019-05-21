# Klassen


## 1. Sichtbarkeit

* private: nur aus derselben Klasse sichtbar
* protected: aus derselben Klasse sichtbar und erbenden Klassen
* public: von überall aus sichtbar

* friend Deklaration: eine bestimmte andere Klasse / Methode / Funktion darf auf private member zugreifen: https://en.cppreference.com/w/cpp/language/friend

```
class base {

int a;
int b;
int c;

protected:

void swap(){ const int old_a{ a }; a = c; c = b; b = old_a; }

public:

int set_a(int a){ const int old_a{ this->a }; this->a = a; return old_a; }

int get_a(){ return a; }

int get_sum() const { return a + b + c; }

};
```
# Aufgaben:
1. Kannst du `std::swap` benutzen für die Methoden swap() oder set_a()? Wenn ja, nutze es, wo es möglich ist.
   Wenn man Klassen und Funktionen der Standardlibrary in C++ benutzen möchte, dann empfiehlt sich meist cppreference.com:
   https://en.cppreference.com/w/cpp/algorithm/swap


## 2. Vererbung

```
class subclass : public base {

/*
access to inheritet members:
a,b,c       not accessible
swap()      protected
get_sum(), get_a(), set_a()   public
*/

int d;



}
```

# Aufgaben
1. Wie würden die Sichtbarkeiten aussehen, wenn sublcass _protected_ bzw. _private_ von base erbt?
2. Überschreibe die Methoden get_sum() und swap(). Kannst du beim Überschreiben von swap() die Implementierung aus der Klasse base wiederverwenden?
3. Schreib eine Funktion, die außerhalb beider Klassen liegt, als Parameter einen nichtnegativen Ganzzahlwert sowie ein Objekt vom Typ base oder subclass entgegennimmt. Diese Funktion soll die Funktion swap() auf dem Objekt aufrufen, so oft wie es der Ganzzahlwert sagt. Nutze eine friend- Deklaration, um der Funktion den Zugriff auf swap() _(protected)_ zu erlauben!


## Weitere Sachverhalte an Hand von Beispielen

https://github.com/Necktschnagge/Cpp-Course/blob/master/CPP%20Kurs/listings/06-classes.cpp
