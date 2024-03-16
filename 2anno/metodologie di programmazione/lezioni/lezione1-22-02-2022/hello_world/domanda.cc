namespace N {

struct S { };

void foo(S s);

void bar(int n);

} // namespace N

int main() {
  N::S s;
  foo(s); // questa chiamata è compilata correttamente
  int i = 0;
  bar(i); // questa chiamata genera un errore di compilazione
}