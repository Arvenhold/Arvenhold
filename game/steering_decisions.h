#pragma once

#include <engine.h>
#include "components/cmp_decision_tree.h"
#include "components/cmp_state_machine.h"

class DistanceDecision : public Decision
{
private:
    std::shared_ptr<Entity> _player;
    float _distance;
protected:
    std::shared_ptr<DecisionTreeNode> getBranch(Entity* owner) final
    {
        float dist = sf::length(owner->getPosition() - _player->getPosition());
        if (dist < _distance)
            return _trueNode;
        else
            return _falseNode;
    }
public:
    DistanceDecision(std::shared_ptr<Entity> player, float distance, std::shared_ptr<DecisionTreeNode> trueNode, std::shared_ptr<DecisionTreeNode> falseNode) : _player(player), _distance(distance), Decision(trueNode, falseNode) { }
};

class StationaryDecision : public DecisionTreeNode
{
public:
    void makeDecision(Entity* owner) final {
        auto sm = owner->get_components<StateMachineComponent>();
        sm[0]->changeState("stationary");
    }
};

class SeekDecision : public DecisionTreeNode
{
public:
    void makeDecision(Entity* owner) final {
        auto sm = owner->get_components<StateMachineComponent>();
        sm[0]->changeState("seek");
    }
};

class FleeDecision : public DecisionTreeNode
{
public:
    void makeDecision(Entity* owner) final {
        auto sm = owner->get_components<StateMachineComponent>();
        sm[0]->changeState("flee");
    }
};

// Melee


// Arrow


// Spell
class CastDecision : public DecisionTreeNode
{
public:
    void makeDecision(Entity* owner) final {
        auto sm = owner->get_components<StateMachineComponent>();
        sm[0]->changeState("cast");
    }
};

// Boss 

