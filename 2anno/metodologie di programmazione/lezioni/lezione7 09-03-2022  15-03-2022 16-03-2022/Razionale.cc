#include "Razionale.hh"
#include <numeric>

/*namespace Numerica{
Razionale::Razionale(const Integer& num, const Integer& den)
            : num_(num),den_(den){
            //proprietà invariante di classe
            //implementazione che assicura la canonicità
            if(num == 0){
                den_ = 1;
                return;
            }
            if(den < 0){
                num_ = -num_;
                den_ = -den_;
            }
            Integer gcd = std::gcd(num_,den_);
            if (gcd != 1){
                num_ /= gcd;
                den_ /= gcd;
            }
        }
}   // namespace Numerica
*/
//Metodo alternativo
/*Numerica::Razionale::Razionale(const Integer& num, const Integer& den)
            : num_(num),den_(den){
            //proprietà invariante di classe
            //implementazione che assicura la canonicità
            if(num == 0){
                den_ = 1;
                return;
            }
            if(den < 0){
                num_ = -num_;
                den_ = -den_;
            }
            Integer gcd = std::gcd(num_,den_);
            if (gcd != 1){
                num_ /= gcd;
                den_ /= gcd;
            }
        }
*/