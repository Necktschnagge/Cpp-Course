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
   * casts zwischen primitiven Typen und Up-cast bei Vererbungen.
   
* dynamic_cast
   * AKZEPTABEL: Wenn du diesen Cast brauchst, ist das ein Indiz, dass du diese Notwendigkeit durch ein besseres Klassendesign vermeiden könntest.
   * Down-cast bei Vererbungen
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

## 1. Schreib eine Funktion, die zwei Zahlen entgegen nimmt und die Summe zurück gibt.
  1. Übergib die Argumente als Kopie
  2. .. als Referenz
  3. .. mittels Pointer
  4. Was ist die beste Variante? Was sollte man in der Praxis nutzen?
  
## 2. Speicherbedarf von bestimmten Typen
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
4. Wie groß sind die Objekte `s1` und `s2` im Speicher?
5. Wo im Speicher liegt der eigentliche String?
6. Wie ermittelt man zur Laufzeit die Länge eines Strings?

##  3. Pointer
Bekannt ist folgende unvollständig implementierte Klasse:
```
class string_circle_node {
  std::string* const my_string;
  string_circle_node* next;
  string_circle_node* previous;
  
  public:
  // creates a circle with one node:
  string_circle_node(const std::string& string){
   ...
  }
  
  // creates a new node and integrates it into a given circle
  string_circle_node(const std::string& string, string_circle& predecessor){
  ...
  }
  
  // returns the reference to the string of this node
  std::string& operator(){
  ...
  }
  
  
  // removes the next node from the circle
  void remove_successor_node(){
  ...
  }
  
  
  // destroys this node and also the whole circle
  ~string_circle_node(){
  ...
  }
  
};
```
Objekte dieser Klasse bilden eine ringförmig verkettete Sammlung von Strings.

1. Vervollständige alle Methoden!
2. Was ist hier am Design schlecht? Was macht die Nutzung dieser Containerklasse "hässlich"?

## 4. const und cast
1. Schreib eine Funktion `void increase(T)`, die einen Integer um 1 vergrößert. Was muss T sein? Kandidaten: `int`, `const int`, `int&`, `const int&`
2. Schreib eine Funktion, welche die Quersumme einer Zahl berechnet. `int cipher_sum(T)`. Was muss T sein? Kandidaten: `int`, `const int`, `int&`, `const int&`
3. Schreib eine Funktion `long sum(const long& lhs, const long& rhs)`, die eine Summe berechnet, aber außerdem "böse" ist, indem sie den Wert von lhs inkrementiert und den Wert von rhs dekrementiert.
4. Schreib eine Funktion, die zu einem gegebenen Character den Zahlcode auf std::cout ausgibt. `void ascii_code(char character)`. Welchen cast sollte man dafür nehmen?
5. Nutze den reinterpret_cast, um dir die Codierung von double anzuschauen. Stell die Bitsequenz anschaulich dar, und sieh dir selbst gewählte double Zahlen an!

## 5. Namespaces, auto und decltype. - Typinferenz oder einfach nur Faulheit
1. Beschreibe die klassische Syntax einer Funktionsdefinition in C++!
2. Schreibe eine Funktion, die zwei Zahlen addiert!
3. Schreibe eine Funktion, die dasselbe tut, aber nutze die Typbestimmung mit decltype: `auto sum(int x, int y) -> decltype(x + y) { return x + y; }`
4. In einer Schule gibt es viele Klassen, mit einer jeweils eindeutigen Kennnung, z.B. _5a_, _7c_, _12b_. In jeder Klasse gibt es Schüler, die alle einen Vornamen und einen Nachnamen haben. Definiere eine Variable `pupils` vom Typ `std::map<std::string, std::vector<std::pair<std::string, std::string>>>`, die die Klassennamen auf Listen der Schüler der jeweiligen Klasse abbilded, wobei jedes Listenelement ein Paar aus Vorname und Nachname darstellt. Fülle die Variable mit Beispieldaten.
5. Iteriere in einer Schleife durch Abbildung und ordne jeder Klasse die Zahl der Schüler zu, die "Jonas", "Lisa", "Tom", bzw. "Lena" heißen. Nutze dabei `auto`um lange Typangaben einzusparen.
6. Definiere eine Klasse `vec4`, die einen 4-dimensionalen Vektor von Kommazahlen darstellt und mit einer Methode die Länge des Vektors im euklidischen Raum berechnet. Die Klasse soll in mehreren verschachtelten Namensräumen liegen: math::geo::vec. Schreib außerdem eine Methode, die das Objekt, auf welchem sie aufgerufen wird, verändert, indem sie die Vektorlänge verdoppelt und die Richtung invertiert.
7. Schreib eine (statische) Funktion, die ein `const vec4&`entgegennimmt und die Vektorlänge auf `std::cout` ausgibt.
8. Schreib eine (statische) Funktion außerhalb der o.g. Namespaces, die ein `vec4&` entgegennimmt, auf dem Objekt die Methode für das Länge verdoppeln und Richtung invertieren aufruft, aber zuvor noch eine Kopie vom ursprünglichen `vec4` erstellt und am Ende diese Kopie zurückgibt. Nutze `auto`, um beim Kopieren des `vec4` Schreibarbeit für den Typen zu sparen. Was kommt als Rückgabetyp der Funktion in Frage? Was darf man nicht zurückgeben und warum?
