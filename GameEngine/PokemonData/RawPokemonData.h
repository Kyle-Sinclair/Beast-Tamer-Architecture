#pragma once

struct RawPokemonData
{
    unsigned int species : 8;

   /* unsigned char NickName_0 : 8;
    unsigned char NickName_1 : 8;
    unsigned char NickName_2 : 8;
    unsigned char NickName_3 : 8;
    unsigned char NickName_4 : 8;
    unsigned char NickName_5 : 8;
    unsigned char NickName_6 : 8;
    unsigned char NickName_7 : 8;
    unsigned char NickName_8 : 8;
    unsigned char NickName_9 : 8; 
    */

    const char* nickName;
    
    unsigned int health : 8;
    unsigned int baseHealth : 8;
    unsigned int baseSpeed : 8;
    unsigned int baseDefence : 8;
    unsigned int baseSpecialDefence : 8;
    unsigned int baseAttack : 8;
    unsigned int baseSpecialAttack : 8;

    /*unsigned int HealthEv : 16;
    unsigned int SpeedEv : 16;
    unsigned int DefenceEv : 16;
    unsigned int SpecialDefenceEv : 16;
    unsigned int AttackEv : 16;
    unsigned int SpecialAttackEv : 16;
    */
    
    unsigned int status : 3;
    unsigned int level : 7;


    void SetName(const char* string);
};
