/*
 * Copyright (C) 2014-2017 StormCore
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation; either version 2 of the License, or (at your
 * option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for
 * more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program. If not, see <http://www.gnu.org/licenses/>.
 */

#include "Map.h"
#include "CreatureAI.h"

#ifndef AUCHINDOUN_H_
#define AUCHINDOUN_H_

#define DataHeader "AU"
#define Auscriptname "instance_auchindoun"
uint32 const encounternumber = 4;
Position const trigger_pos = { 1660.68f, 2953.27f, 34.29f, 1.96f };
Position const Guard_spawn = {1669.06f,3032.20f,35.19f,1.19f};
#define VALUES 11
Position const Niami_waypoints [VALUES] = 
{
    {1563.23f,2959.33f,35.32f,1.32f},
    {1617.22f,2952.83f,35.20f,6.27f},
    {1660.54f,2953.08f,35.24f,1.51f},
    {1664.94f,3007.27f,35.20f,1.41f},
    {1678.28f,3045.0f,35.10f,1.15f},
    {1703.19f,3092.82f,35.10f,1.01f},
    {1740.89f,3140.09f,35.10f,0.63f},
    {1787.75f,3170.17f,35.10f,0.45f},
    {1806.17f,3176.97f,35.10f,0.25f},
    {1839.58f,3187.84f,29.41f,0.47f},
    {1858.82f,3197.27f,29.41f,6.08f}

};
#define defenders_val 11
Position const defender_spawn[defenders_val]=
{
    {1777.24f,3174.75f,35.14f,0.12f},
    {1740.73f,3149.25f,35.14f,0.22f},
    {1750.14f,3138.53f,35.14f,1.01f},
    {1708.16f,3117.15f,35.14f,0.14f},
    {1718.72f,3106.08f,35.14f,0.98f},
    {1680.88f,3077.36f,35.14f,0.27f},
    {1694.45f,3069.67f,35.13f,1.38f},
    {1687.61f,3074.04f,35.13f,0.99f},
    {1665.15f,3030.60f,35.28f,1.05f},
    {1673.63f,3035.94f,35.23f,1.12f},
    {1676.56f,3026.54f,35.14f,1.24f}
}; 
#define magus_val 3
Position const Magus_spawn[magus_val]=
{
    { 1679.83f,3055.71f,35.14f,1.13f },
    {1701.01f,3093.87f,35.14f,1.02f},
    {1727.47f,3146.01f,36.04f,0.20f}
};
#define soulbinder_val 2
Position const Soulbinder_spawn[soulbinder_val]
{
    {1764.31f, 3169.64f, 35.13f, 6.16f},
    { 1702.46f, 3112.62f, 35.14f, 5.77f }
};

enum DataTypes
{
    DATA_KAATHAR = 1,
    DATA_NIAMI = 2,
    DATA_AZAKEL = 3,
    DATA_TERON = 4
};

enum CreatureIds
{
    NPC_KATHAAR = 75839,
    NPC_NIAMI = 76177,
    NPC_AZAKEL = 75927,
    NPC_TERON = 77734,
    NPC_TRIGGER_NIAMI = 100101, // trigger for aura
    NPC_ARBITER = 76284, // summoned_01 from Niami
    NPC_MAGE = 76296, // summoned_02 from Niami
    NPC_DEFENDER = 76283, // summoned_03 from Niami
    NPC_SOUL_AEGIS = 77832,
    NPC_FELGUARD = 79507, //Azzakel start
    NPC_PIROMANIAC = 79510, //end
    NPC_AUCHENAI_DEFENDER = 77693,
    NPC_AUCHENAI_PRIEST = 77696,
    NPC_AUCHENAI_ARBITER = 77695,
    NPC_AUCHENAI_MAGUS = 77694,
    NPC_AUCHENAI_ZEALOT = 77950,
    NPC_AUCHENAI_HOPLITE = 77948,
    NPC_AUCHENAI_WARDEN = 77704,
    NPC_AUCHENAI_RITUALIST = 77949,
    NPC_SPIRIT_TENDER = 77131, // at kaathar_01
    NPC_SOUL_DEFENDER = 77812,
    NPC_CLERIC = 77134,
    NPC_SARGEREI_HOPLITE = 77133,
    NPC_SARGEREI_RITUALIST = 77130,
    NPC_SARGEREI_ZEALOT = 77132,
    NPC_SARGERAI_DEFENDER = 77042, // enemy
    NPC_SARGEREI_ACTOR = 77080,
    NPC_SARGERAI_SOULBINDER = 76595,
    NPC_SARGERAI_MAGE = 76263,
    NPC_SARGERAI_GUARD = 77935 // finish enemy
};

enum BWLEncounter
{
    BOSS_KAATHAR = 0,
    BOSS_NIAMI = 1,
    BOSS_AZAKEL = 2,
    BOSS_TERON = 3

};

enum Objects
{
    OBJECT_Holly_barier = 230399,
    OBJECT_DemonicPortal = 233102,
    OBJECT_Fel_barier = 230400,
    OBJECT_Holly_barier_Wall = 230398
};

enum spells_npc
{
    SPELL_VISUAL_CAST = 183653 // for sargerai at crystal
};

class DelayedAttackStartEvent : public BasicEvent
{
public:
    DelayedAttackStartEvent(Creature* owner) : _owner(owner) { }

    bool Execute(uint64 /*e_time*/, uint32 /*p_time*/)
    {
        _owner->AI()->DoZoneInCombat(_owner, 200.0f);
        return true;
    }

private:
    Creature* _owner;
};

template<class AI>

CreatureAI* GetFirelandsAI(Creature* creature)
{
    if (InstanceMap* instance = creature->GetMap()->ToInstanceMap())
        if (instance->GetInstanceScript())
            if (instance->GetScriptId() == sObjectMgr->GetScriptId(Auscriptname))
                return new AI(creature);
    return NULL;
}
#endif 
