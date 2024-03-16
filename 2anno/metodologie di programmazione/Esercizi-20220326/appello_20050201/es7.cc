template <typename T>
class Container {
private:
    T* c;
public:
    Container();
    Container(const Container& y){
        c = new T[y.size];
        for(int i = 0;i<y.size(),++i){
            c[i] = static_cast<int>(y.c[i]);
        }
    }
    Container& operator=(const Container& y){
        c = new T[y.size];
        for(int i = 0;i<y.size(),++i){
            c[i] = static_cast<int>(y.c[i]);
        }
    }
    ~Container();
    int size(){}
private:
// ...
};




int main(){
    Container<int> ci1;
    Container<int> ci2 = ci1;
    Container<double> cd2 = ci1;
    Container<int> ci3;
    Container<double> cd3;
    ci3 = ci1;
    cd3 = ci1;
}