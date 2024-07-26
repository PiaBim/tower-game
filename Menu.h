#ifndef __MENU_H__
#define __MENU_H__

#include <string>

class Menu {
public:
    void ProcessMenu() const;
    void ClassMenu() const;
    void GameGuide() const;
    void MainMenu() const;
    int GetIntegerInput() const ;
};
#endif
