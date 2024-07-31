#include "MonsterFight.h"
#include "Slime.h"
#include "Goblin.h"
#include "Game.h"
#include <iostream>
#include <cstdlib> // rand(), srand()
#include <ctime>   // time()
#include <thread>   // std::this_thread::sleep_for
#include <chrono>   // std::chrono::seconds

std::unique_ptr<Monster> MonsterFight::CreateRandomMonster() {
    int random = rand() % 2; // Generate a random number (0 or 1)
    if (random == 0) {
        return std::make_unique<Slime>();
    } else {
        return std::make_unique<Goblin>();
    }
}

void MonsterFight::StartFight(const Player& player) {
    std::unique_ptr<Monster> monster = CreateRandomMonster();
    std::cout << "전투가 시작되었습니다! 상대 몬스터: " << monster->GetName() << std::endl;

    // 플레이어를 비가변으로 변경
    Player* mutablePlayer = const_cast<Player*>(&player);

    bool escaped = false;

    while (!mutablePlayer->IsDefeated() && !monster->IsDefeated() && !escaped) {
        PlayerTurn(*mutablePlayer, *monster, escaped);
        if (escaped) {
            break;
        }
        if (!monster->IsDefeated() && !escaped) {
            MonsterTurn(*monster, *mutablePlayer);
        }
    }

    if (escaped) {
        std::cout << "플레이어가 도망쳤습니다! 전투가 종료되었습니다." << std::endl;
    } else if (mutablePlayer->IsDefeated()) {
        std::cout << "플레이어가 패배했습니다!" << std::endl;
        exit(1);
    } else if (monster->IsDefeated()) {
        std::cout << "몬스터가 패배했습니다! 전투에서 승리했습니다!" << std::endl;
        std::this_thread::sleep_for(std::chrono::seconds(1));
        int expReward = monster->GetExperienceReward();
        mutablePlayer->GainExperience(expReward);
        std::cout << "플레이어가 " << expReward << " 경험치를 획득했습니다!" << std::endl;
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
}

void MonsterFight::PlayerTurn(Player& player, Monster& monster, bool& escaped) {
    bool turnEnded = false; // 턴 종료 여부를 확인하는 플래그
    int defenseCost = 2; // 방어에 필요한 CP 비용
    const int recoveryAmount = 1; // 턴 종료 시 회복할 CP 양
    while (!turnEnded && !player.IsDefeated() && !monster.IsDefeated() && !escaped) {
        int choice;


        std::cout << "플레이어의 턴입니다. 선택하세요.\n1. 카드 사용 \n2. 방어하기\n3. 도망가기\n4. 턴 종료\n입력: ";
        std::cin >> choice;

        switch (choice) {
            case 1:
                if (player.GetCards().empty()) {
                    std::cout << "사용 가능한 카드가 없습니다." << std::endl;
                } else {
                    std::cout << "사용할 카드를 선택하세요:" << std::endl;
                    for (size_t i = 0; i < player.GetCards().size(); ++i) {
                        std::cout << i + 1 << ". " << player.GetCards()[i]->GetName() << " (CP 비용: " << player.GetCards()[i]->GetCPCost() << ")" << std::endl;
                    }
                    int cardChoice;
                    std::cout << "카드 선택: ";
                    std::cin >> cardChoice;

                    if (cardChoice >= 1 && cardChoice <= static_cast<int>(player.GetCards().size())) {
                        auto& selectedCard = player.GetCards()[cardChoice - 1];
                        int cpCost = selectedCard->GetCPCost();

                        if (player.GetCP() >= cpCost) {
                            // 카드 사용
                            selectedCard->Use(player, monster);
                            std::cout<<"몬스터의 남은 Hp:"<<monster.GetHealth()<<std::endl;
                            // 턴 종료 여부 확인
                            if (player.GetCP() <= 0) {
                                std::cout << "CP가 부족합니다. 턴을 종료합니다." << std::endl;
                            } else {
                                std::cout << "CP가 " << player.GetCP() << " 남아 있습니다." << std::endl;
                            }
                        } else {
                            std::cout << "CP가 부족하여 카드 사용이 불가능합니다." << std::endl;
                        }
                    } else {
                        std::cout << "잘못된 카드 선택입니다. 다시 시도하세요." << std::endl;
                    }
                }
                break;
            case 2:
                if (player.GetCP() >= defenseCost) {
                    std::cout << "방어합니다." << std::endl;
                    player.SetDefending(true);
                    player.UseCP(defenseCost);
                    std::this_thread::sleep_for(std::chrono::seconds(1));
                } else {
                    std::cout << "CP가 부족하여 방어를 수행할 수 없습니다." << std::endl;
                }
                break;
            case 3:
                AttemptEscape(player, monster, escaped);
                turnEnded = true; // 도망 시 턴 종료
                break;
            case 4:
                std::cout << "턴을 종료합니다." << std::endl;
                player.RecoverCP(recoveryAmount);
                turnEnded = true; // 플레이어가 명시적으로 턴 종료를 선택함
                break;
            default:
                std::cout << "잘못된 선택입니다. 다시 선택하세요." << std::endl;
                break;
        }
    }
}

void MonsterFight::AttemptEscape(Player& player, Monster& monster, bool& escaped) {
    std::cout << "도망을 시도합니다." << std::endl;
    std::this_thread::sleep_for(std::chrono::seconds(1));

    // 민첩성을 기반으로 도망 성공 확률 계산
    int agility = player.GetAgility();
    int escapeChance = std::min(30 + agility, 90); // 기본 30% + 민첩성, 최대 90%
    int randomValue = rand() % 100;

    if (randomValue < escapeChance) {
        std::cout << "도망에 성공했습니다! 다음 층으로 넘어갑니다." << std::endl;
        std::this_thread::sleep_for(std::chrono::seconds(1));
        player.SetCurrentFloor(player.GetCurrentFloor() + 1); // 다음 층으로 넘어가기
        std::cout << "플레이어가 " << player.GetCurrentFloor() << "층으로 이동했습니다." << std::endl;
        std::this_thread::sleep_for(std::chrono::seconds(1));
        escaped = true;
    } else {
        std::cout << "도망에 실패했습니다!" << std::endl;
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
}


void MonsterFight::MonsterTurn(Monster& monster, Player& player) {
    std::this_thread::sleep_for(std::chrono::seconds(1));
    std::cout << monster.GetName() << "의 턴입니다. 플레이어를 공격합니다!" << std::endl;
    std::this_thread::sleep_for(std::chrono::seconds(1));
    monster.Attack(player);
}
