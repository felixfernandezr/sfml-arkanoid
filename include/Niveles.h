#ifndef NIVELES_H_INCLUDED
#define NIVELES_H_INCLUDED

#include <vector>

class Niveles{

    public:
        Niveles();

        std::vector<std::vector<unsigned int>> nivel1(void);
        std::vector<std::vector<unsigned int>> nivel2(void);
        std::vector<std::vector<unsigned int>> nivel3(void);

    private:
        std::vector<std::vector<unsigned int>> plantilla;
};

#endif // NIVELES_H_INCLUDED
