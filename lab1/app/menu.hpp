#pragma once

#include "lab1/Set.hpp"
#include "lab1/MultiSet.hpp"
#include <memory>
#include <vector>

// Пункты главного меню
enum class MainChoice
{
    Sets = 1,      // работать с множествами
    MultiSets = 2, // работать с мультимножествами
    Exit = 0
};

// Пункты меню внутри выбранного типа
enum class ActionChoice
{
    Create = 1,
    Remove = 2,
    ShowAll = 3,
    Unary = 4,
    Binary = 5,
    Back = 0
};

// Режим: с чем работаем
enum class Mode
{
    Sets,
    MultiSets
};

class Menu
{
public:
    Menu();
    void run();

private:
    // Данные
    std::vector<std::pair<char, std::shared_ptr<SetLike>>> sets_;
    std::vector<std::pair<char, std::shared_ptr<SetLike>>> multisets_;
    Mode mode_ = Mode::Sets;

    // Главные экраны
    void runMainLoop();
    void switchMode(Mode newMode);
    void showCurrentList() const;

    // Действия
    void handleCreate();
    void handleRemove();
    void handleShowAll() const;
    void handleUnary();
    void handleBinary();

    // Помощники
    std::vector<std::pair<char, std::shared_ptr<SetLike>>> &currentList();
    const std::vector<std::pair<char, std::shared_ptr<SetLike>>> &currentList() const;
    std::shared_ptr<SetLike> selectFromList(const std::string &prompt) const;
    char nextName() const;

    // Ввод
    int readInt(const std::string &prompt) const;
    std::string readLine(const std::string &prompt) const;
    void clearInput() const;

    void runTypeMenu();
};