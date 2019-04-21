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
   

# Aufgaben

