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

};
```

# Aufgaben
1. Wie würden die Sichtbarkeiten aussehen, wenn sublcass _protected_ bzw. _private_ von base erbt?
2. Überschreibe die Methoden get_sum() und swap(). Kannst du beim Überschreiben von swap() die Implementierung aus der Klasse base wiederverwenden?
3. Schreib eine Funktion `void externerTauscher(...)`, die außerhalb beider Klassen liegt, als Parameter einen nichtnegativen Ganzzahlwert sowie ein Objekt vom Typ base oder subclass entgegennimmt. Was musst du für Typen verwenden? Diese Funktion soll die Funktion swap() auf dem Objekt aufrufen, so oft wie es der Ganzzahlwert sagt. Nutze eine friend- Deklaration, um der Funktion den Zugriff auf swap() _(protected)_ zu erlauben!
4. Teste aus, was passiert, wenn du die Funktion von Aufgabe 3 auf Objekten vom Typ base bzw. subclass aufrufst? Beschreibe, was passiert und nenne die Gründe dafür!
5. Nutze das Schlüsselwort **virtual**, um das gewünschte Verhalten herzustellen. Wie funktionieren Aufrufe von virtuellen Funktionen in C++ (Polymorphie)? Wie funktioniert im Vergleich dazu Polymorphie in Java?
6. Erkläre die Schlüsselwörter **override** und **final** und benutze sie in den beiden Klassen, wo es sinnvoll ist! Nenne Vorteile, warum man **override** benutzen sollte!

## 3. Weitere Sachverhalte an Hand von Beispielen

https://github.com/Necktschnagge/Cpp-Course/blob/master/CPP%20Kurs/listings/06-classes.cpp

## 4. Eine etwas umfangreichere Aufgabe

1. Wir betrachten Aussagenlogik erster Stufe:

Wir betrachten dazu aussagenlogische Variablen, bzw. Atome. Diese nennen wir x0, x1, x2, x3, ...
Eine aussagenlogische Formel (Prädikat), hängt von nur endlich vielen Variablen ab. Als Junktoren betrachten wir **not**, **and**, **or**, **implies**, **equivalent**.
Folgende Prädikate sind Beispiele für unsere Definition:
* (x0 and x1) or x2
* (x2 implies x1) or (x0 and x4)
* (x0 implies x1) equivalent (x3 implies x4)

2.
Schreibe eine Klasse `class predicate;`, deren Objekte jeweils genau eins der möglichen Prädikate inklusive seiner Struktur widerspiegelt.
* Um die Struktur abzubilden, wird für jeden Junktor eine Subklasse von predicate geschrieben. Was für erbende Klassen braucht man noch?
* Implementiere **Copy-Konstuktor** und **Copy - operator=** ! Implementiere **Move-Konstruktor** und **Move - operator=** ! Was fehlt noch, um The Big Five vollständig zu implementieren? 
* Überlege dir weitere sinnvolle Konstrukoren, um später Objekte erstellen zu können!
* Schreibe einen Konvertierungsoperator nach std::string, um jederzeit die Möglichkeit zu haben, ein Prädikat in Stringform auszugeben!
* Jedes Predicate soll als Methode den operator() implementieren. Dieser soll einen std::vector<bool> entgegennehmen, der eine Belegung der Variablen x0, x1, x2, ... mit jeweils true oder false darstellt. Der operator() soll true oder false zurückgeben, je nach dem, ob das Prädikat bei gegebener Variablenbelegung zu true oder false auswertet.
* Schreibe eine Methode `replace(unsigned long long old_index, unsigned long long new_index)`, welche es erlaubt, die Variablen umzubennen. Beispiel: Wir betrachten das Objekt zur Formel **x0 implies (x1 or x2)** und rufen replace(0,3) auf dem Objekt auf. Dann werden alle Vorkommen von x0 durch x3 ersetzt. Dasselbe Objekt ändert seinen Zustand in der Art, dass es nun **x3 implies (x1 or x2)** repräsentiert.
* Scheibe eine Methode reduce(unsigned long long index, bool value), welche die gemeinte aussagenlogische Variable mit dem gegebenen Wert ersetzt und anschließend das Predicate unter Beibehaltung seiner Struktur so weit es geht vereinfacht. Beispielsweise kann **true and x3** zu **x3** reduziert werden.
* Implementier für die Klasse die operatoren `&&` (und), `||` (oder), `!` (not) sowie Methoden implies(...) und equivalent(...). Diese sollen (bis auf `! (not)`), das `this` Objekt mit einem zweiten Objekt vom Typ predicate oder einer Unterklasse zu einem neuen predicate zusammensetzen. Beispiel `p1` stelle "x1 and x2" dar, `p2`dagegen "x0 equivalent x2", dann ist `p3 = p1 && p2` das predicate für "(x1 and x2) and (x0 equivalent x2)" Überlege ob du Copy- oder Movesemantik verwenden solltest oder beides und wie du das jeweils umsetzt!

