namespace A {
    void foo() {}
};
void foo();


int main(){

    foo(); //quella interna al namespace non è visibile quindi richiamo quella globale
    A::foo(); //uso quella interna ad A
    A::foo();

}