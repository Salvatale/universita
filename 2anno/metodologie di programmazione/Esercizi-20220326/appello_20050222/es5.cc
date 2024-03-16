struct input_iterator{};
struct forward_iterator : public ostream_iterator{};
struct bidirectional_iterator : public forward_iterator{};
struct Random_Acces_Iterator : bidirectional_iterator{};
struct output_iterator{};


//input iterator
template <typename input_iterator>
void foo(input_iterator first,input_iterator last){
    for(;first != last;++first){
        std::cout << *first << std::endl;
    }
}

//forward iterator
template <typename forward_iterator>
void foo(forward_iterator iter1){
   
    forward_iterator iter2 = forward_iterator1;
    ++iter1;
    std::cout << *iter2 << std::endl;
}

//bidirectional iterator

template <typename input_iterator>
void foo(input_iterator first,input_iterator last){
    first1 = first;
    for(;first != last;++first){
        std::cout << *first << std::endl;
    }
    for(;first1 <= last;--last){
        std::cout << *first << std::endl;
    }
}

//random access iterator
void foo(){
    int n = 4;
    //
    Random_Acces_Iterator r;
    r = r+n;
}

//outuput iterator
template <typename Iter,typename out_iterator>
void foo(Iter first,Iter last,out_iterator out){
    for(; first != last;++first;++out){
        *out = *first;
    }
}
