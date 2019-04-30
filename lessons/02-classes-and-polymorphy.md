# Klassen

https://github.com/Necktschnagge/Cpp-Course/blob/master/CPP%20Kurs/listings/06-classes.cpp

## 1. Sichtbarkeit

* private: nur aus derselben Klasse sichtbar
* protected: aus derselben Klasse sichtbar und erbenden Klassen
* public: von überall aus sichtbar

* friend Deklaration: eine bestimmte andere Klasse / Methode / Funktion darf auf private member zugreifen: https://en.cppreference.com/w/cpp/language/friend

```
class base {
private int a;
private int b;
private int c;

}
```
## Vererbung

`

