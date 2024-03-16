

struct Matrix {
// ...
size_type num_rows();
size_type num_cols();
value_type& get(size_type row, size_type col);
Matrix& operator-();
Matrix& operator+=(Matrix y);
Matrix& operator+(Matrix y);
void print(ostream os);
// ...
};


//correzione
using size_type = unsigned long;
using value_type = int;

struct Matrix {
// ...
    const size_type num_rows() const;
    const size_type num_cols() const;
    const value_type& get(const size_type row, const size_type col) const;
    Matrix& operator-(const Matrix& y);
    Matrix& operator+=(const Matrix& y);
    Matrix& operator+(const Matrix& y);
    void print(ostream& os) const;
// ...
};