/*template <typename T>
class Set : public std::list<T> {
public:
    // Costruisce l’insieme vuoto.
    Set();
    // Costruisce il singoletto che contiene t.
    Set(T t);
    Set(Set y);
    void operator=(Set y);
    virtual ~Set();
    unsigned int size();
    bool is_empty();
    bool contains(Set y);
    T& min();
    void pop_min();
    void insert(T z);
    void union_assign(Set y);
    void intersection_assign(Set y);
    void swap(Set y);
    std::ostream operator<<(std::ostream os);

};
*/
//Correzione:
#include <iostream>

template <typename T>
class Set  {
private:
    std::list<T> lista_;
public:
    // Costruisce l’insieme vuoto.
    Set();
    // Costruisce il singoletto che contiene t.
    explicit Set(const T& t);
    Set(const Set& y);
    Set& operator=(const Set& y);
    ~Set();
    unsigned int size() const;
    bool is_empty() const;
    bool contains(const Set& y) const;
    const T& min() const;
    void pop_min();
    void insert(const T& z);
    void union_assign(const Set& y);
    void intersection_assign(const Set& y);
    void swap(Set& y);

};

template <typename T>
std::ostream&
operator<<(const std::ostream& os, const Set<T>& s);