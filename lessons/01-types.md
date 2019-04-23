# Typen in C++

## allgemein
* konstante, feste Größe im Speicher
   * `sizeof(T) // Größe von T in Bytes`  
* identifizieren, wie ein Speicherbereich interpretiert werden soll (Semantik)

## diese Typen gibt es (u.a.)
* primitive Typen:
   * int, long, ...
   * unsigned int,
   * char,
   * bool,
   * float, double, long double
* zusammengesetzte Typen:
   * Referenz: Sei `T` ein Typ. Dann heißt der Typ `T&` _Referenz auf ein T_. Eine Referenz ist stets als neuer (zusätzlicher) Identifier auf ein bereits bestehendes Objekt (Speicherbereich) zu verstehen.
   * Pointer: Sei `T`ein Typ. Dann heißt der Typ `T*` _Pointer auf ein T_. Der Pointer auf ein `T` ist als die Speicheradresse eines Objektes (Speicherbereiches) vom Typ T zu verstehen.
   * Array: Sei `T` ein Typ. Dann dann bezeichnet `x` ein Array von `T`s, wenn x definiert ist als beispielsweise `T x[100];`. Ein Array ist eine lückenlose Folge von Objekten desselben Typs `T`im Speicher.
   * Klassen / Strukturen: Eine Klasse ist die Zusammenfassung von Daten nichtnotwendigerweise verschiedenen Typs.
```
   class person {
      std::string first_name;
      std::string last_name;
      double height_m;
      double weight_kg;
      
      public:
      void whats_your_name(){
      std::cout << "Ich heiße " << first_name << "." << std::endl;
      }
   };
      
   class woman : public person {
      std::string birth_name;
      double wardrobe_size_qm;
      
   };
      
   class man : public person {
   public:
      unsigned int number_of_cars;
      std::vector<std::string> sports_clubs;
   };
 
```
   
   
## cv-Modifier:
* const: "konstant", Speicherinhalt der _direkt_ hinter einem Bezeichner vom Typ const T liegt, darf nicht verändert werden, besser gesagt, kann nicht ohne Weiteres und sollte nicht verändert werden.
* volatile: "veränderlich", wird nach dem Compilieren stets in den Hauptspeicher zurückgeschrieben, wird nicht im Cache aufbewahrt.

## casts:

* C-like cast:
   * BÖSE: macht irgendwas, was ihm gerade so passt.
   * `long x = 30; int y = (int) x;`
   
* static_cast
   * GUT: wird statisch zur Compilezeit aufgelöst
   * `long x = 30; int y = static_cast<int>(x);`
   
* dynamic_cast
   * AKZEPTABEL: Wenn du diesen Cast brauchst, ist das ein Indiz, dass du diese Notwendigkeit durch ein besseres Klassendesign vermeiden könntest.
```
   man myself;
   person& someone{ myself };
   try {
      man& the_man_in_someone = dynamic_cast<man&>(someone);
      the_man_in_someone.whats_your_name();
      std::cout << "Ich habe " << the_man_in_someone.number_of_cars << " Autos.\n";
   } catch (std::bad_cast& bc){
      std::cerr << "bad_cast caught: " << bc.what() << '\n';
   }
```   
* reinterpret_cast
   * BÖSE: ändert einfach den Typ, ohne irgendetwas zu prüfen.
   
   
* cv-cast
   * meistens BÖSE: Du kannst const und volatile hin- und wegcasten.
```
const unsigned long x = 30;
unsigned long& y = const_cast<unsigned long&> x;
y = 40;
std::cout << x; // 40 if no error occurs.
```

## Wie liest man Typen
* vom neuen Bezeichner beginnend nach rechts, soweit wie möglich (bis zur Klammer oder zum Zeilenende).
* nach links soweit wie nötig,

* `int* x[4];`
* `void (* x[2])(int, int);`
* `std::string x[4][2];`

```
using my_array_type = int[8];
```

## Pointer, new und delete

Man kann zur Laufzeit Speicherplatz für ein neues Objekt anfordern und dieses gleich an der Speicherstelle initialisieren.
* `int* p_int = new int();`
* `std::string* p_string = new std::string("Neuer String im Heapspeicher");`
* `long* p_long_array = new long[10];`


Durch new allokierter Speicherplatz muss mit delete wieder freigegeben werden, sonst entstehen memory leaks.
* `delete p_int;`
* `delete p_string;`
* `delete [] p_long_array;`

# Aufgaben

1. Schreib eine Funktion, die zwei Zahlen entgegen nimmt und die Summe zurück gibt.
  1. Übergib die Argumente als Kopie
  2. .. als Referenz
  3. .. mittels Pointer
  4. Was ist die beste Variante? Was sollte man in der Praxis nutzen?
2. Speicherbedarf von bestimmten Typen

```
class empty {

};

struct vec2 {
  int x;
  int y;
};

struct intelligent_vec2 {
  int x;
  int y;
  
  int sum() const {
   return x + y;
  }
};
```
  1. Wie viel Speicher benötigt ein `std::string`, `int`, `long double`, `std::string*`, `int*` bzw. `long double*`? Überlege dir erst eine Vermutung und überprüf diese dann.
  2. Wie viel Speicherbedarf hat je ein Objekt der drei gezeigten Klassen?
    1. Was schätzt du?
    2. Ermitte die tatsächliche Größe!
  3. Bekannt ist folgender Code:
  ```
  int main(){
    std::string s1{ "Hallo" };
    std::string s2{ "Welt" };
    // ...
  }
  ```  
    1. Wie groß sind die Objekte `s1` und `s2` im Speicher?
    2. Wo im Speicher liegt der eigentliche String?
    3. Wie ermittelt man zur Laufzeit die Länge eines Strings?
  3. Pointer
    

