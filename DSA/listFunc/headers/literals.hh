

class Literal {

};


class RealNum : public Literal {
    double val;
};

class List : public Literal {
    unsigned size;
    double* vals;
};
