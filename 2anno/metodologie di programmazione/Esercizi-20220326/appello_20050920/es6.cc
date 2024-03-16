



class One {
    int i_one;
};

class Two {
    int i_one;
    int i_two;
};
class Three{
    int i_one;
    int i_two;
    int i_three;
};


class OneTwoThree {
private:
    One* p_one;
    Two* p_two;
    Three* p_three;
    // Dichiarati privati e non implementati.
    OneTwoThree(const OneTwoThree&);
    OneTwoThree& operator=(const OneTwoThree&);
public:
    OneTwoThree(): p_one(new One), p_two(new Two) , p_three(new Three){}
    OneTwoThree(const OneTwoThree&& ott) :
        p_one(ott.p_one) , p_two(ott.p_two) , p_three(ott.p_three){}
    OneTwoThree& operator=(const OneTwoThree&& ott) :
        p_one(ott.p_one) , p_two(ott.p_two) , p_three(ott.p_three){} 
    
    ~OneTwoThree() {
    delete p_two;
    delete p_three;
    delete p_one;
    }

};




