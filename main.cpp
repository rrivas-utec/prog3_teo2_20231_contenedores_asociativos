#include <iostream>
#include <map>
#include <set>
#include <functional>
using namespace std;

struct Location {

};

struct Building {

};

void ejemplo_map() {
    map<int, string> m1;
    map<string, function<int(int, int)>> m2;
    map<Location, Building> m3;

    map<int, string> m4 = { {4, "Cuarto"}, {1, "Uno"}, {3, "Tres"}, {2, "Dos"} };

    for (const auto& item: m4)
        cout << item.first << " " << item.second << endl;

    for (const auto& [key, value]: m4)
        cout << key << " " << value << endl;

    for (auto it = begin(m4); it != end(m4); ++it) {
        const auto& [key, value] = *it; // Estructura binding
        cout << it->first << " " << it->second << endl;
    }

    // Insertar valores
    auto [iterator, success] = m4.insert({1, "One"});
    if (success) {
        cout << "valor insertado\n";
    }
    else {
        cout << "No se inserto\n";
    }
    for (const auto& [key, value]: m4)
        cout << key << " " << value << endl;

    m4[1] = "One";
    for (const auto& [key, value]: m4)
        cout << key << " " << value << endl;

    auto it = m4.find(5);
    if (it != end(m4))
        cout << "encontro el 5\n";
    else
        cout << "No encontro el 5\n";

    m4.erase(4);
    for (const auto& [key, value]: m4)
        cout << key << " " << value << endl;

    auto it2 = m4.erase(5);
    if (it2 != 0)
        cout << "borro el 5\n";
    else
        cout << "No borro el 5\n";


}

void ejemplo_set() {
    set<int> s1 = {4, 4, 5, 3, 2, 6, 4, 5, 1, 8, 9};
    for (const auto& item: s1)
        cout << item << " ";
    cout << endl;

    s1.insert(7);
    for (const auto& item: s1)
        cout << item << " ";
    cout << endl;
    s1.erase(15);
    for (const auto& item: s1)
        cout << item << " ";

}

template<typename T>
struct Mayor {
    bool operator()(T a, T b) const { return a > b; }
};

void ejemplo_cambiar_criterio_orden() {
    map<int, string, less<>> m1 = {
            {4, "Cuarto"},
            {1, "Uno"},
            {3, "Tres"},
            {2, "Dos"} };
    for (const auto& [key, value]: m1)
        cout << key << ", " << value << " | ";
    cout << endl;

    map<int, string, greater<>> m2 = {
            {4, "Cuarto"},
            {1, "Uno"},
            {3, "Tres"},
            {2, "Dos"} };
    for (const auto& [key, value]: m2)
        cout << key << ", " << value << " | ";
    cout << endl;

    map<int, string, Mayor<int>> m3(
            {
                    {4, "Cuarto"},
                    {1, "Uno"},
                    {3, "Tres"},
                    {2, "Dos"}
                    },
            Mayor<int>{});
    for (const auto& [key, value]: m3)
        cout << key << ", " << value << " | ";
    cout << endl;

    auto mayor_lambda = [](auto a, auto b) { return a > b; };
    auto menor_lambda = [](auto a, auto b) { return a < b; };
//    map<int, string, function<bool(int, int)>> m4(
    map<int, string, decltype(menor_lambda)> m4(
            {
                    {4, "Cuarto"},
                    {1, "Uno"},
                    {3, "Tres"},
                    {2, "Dos"}
            },
            menor_lambda);
    for (const auto& [key, value]: m4)
        cout << key << ", " << value << " | ";
    cout << endl;
}

class Person {
    string name;
public:
    explicit Person(string name): name(std::move(name)) {}
    friend ostream& operator<< (ostream& out, const Person& p);
    friend bool compare_person_desc (Person p1, Person p2);
    string get_name() const { return name; }
};

ostream& operator<< (ostream& out, const Person& p) {
    out << p.name;
    return out;
}

bool compare_person_desc (Person p1, Person p2) {
    return p1.name > p2.name;
}

void ejemplo_map_objetos() {
    auto compare_person = [](auto a, auto b)
            { return a.get_name() > b.get_name(); };
    map<Person, string, decltype(compare_person)> m1(
            { {Person("Tomas"), "Tm"},
                               {Person("Alicia"), "Al"},
                               {Person("Jonas"), "Jn"},
                               {Person("Ana"), "An"}
                            }, compare_person);

    for (const auto& [key, value]: m1)
        cout << key << ", " << value << " | ";
}

int main() {
//    ejemplo_map();
//    ejemplo_set();
//    ejemplo_cambiar_criterio_orden();
    ejemplo_map_objetos();
    return 0;
}
