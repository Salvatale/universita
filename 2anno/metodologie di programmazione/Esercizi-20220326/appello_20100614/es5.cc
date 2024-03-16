#include <iostream>
#include <vector>
#include <iterator>

template <typename T,typename U>
struct Media
{
    double operator()(T t,U u){
        return (t+u)/2.0;
    }
};



template <typename InIter1, typename InIter2,typename OutIter,typename BinaryPred>
OutIter
transform1(InIter1 first1,InIter1 last1, /*prima sequenza ingresso*/
          InIter2 first2 , InIter2 last2, /*seconda sequenza ingresso*/
          OutIter out,BinaryPred pred) 
{
    for(;first1 != last1;++first1){
        *out = pred(*first1,*first2);
        ++first2;
    }
}

int main(){
    std::vector<int> vi = {1,3,2,8,4,2};
    std::vector<double> vd = {1.2,3.6,2.3,8.2,4.1,2.3};
    std::ostream_iterator<double> cout_iter(std::cout,"\n");
    cout_iter = transform1(vi.begin(),vi.end(),
                          vd.begin(),vd.end(),cout_iter,Media<int,double>());
}