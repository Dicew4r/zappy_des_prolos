//
// Created by Ludovica Pagliarani on 20/06/2018.
//

#ifndef INVENTARY_HPP
#define INVENTARY_HPP

#include "IGrphGame.hpp"
#include "IrrlichtLib.hpp"

namespace graphic
{
    class Inventary : public IGrphGame
    {
        graphic::IrrlichtLib *_lib;
    public:
        Inventary(graphic::IrrlichtLib *const lib);
        ~Inventary() = default;
        void  display(); //function de l'interface
        void  eventManager() {} //function de l'interface
        void  eventManager(bool isOpen);
        void  createWindowInventary();
        void  printLinemate(size_t nbrStone);
        void  printDeraumere(size_t nbrStone);
        void  printSibur(size_t nbrStone);
        void  printMendiane(size_t nbrStone);
        void  printPhiras(size_t nbrStone);
        void  printThystame(size_t nbrStone);
    };
}
#endif //INVENTARY_HPP
