#include "cmp_physics.h"
#include "system_physics.h"

using namespace std;
using namespace sf;

using namespace Physics;

void PhysicsComponent::update(double dt) {
    _parent->setPosition(invert_height(bv2_to_sv2(_body->GetPosition())));
}

PhysicsComponent::PhysicsComponent(Entity* p, bool dyn, const b2PolygonShape Shape)
    : Component(p), _dynamic(dyn) {

    b2BodyDef BodyDef;

    // Is Dynamic(moving), or static(Stationary)
    BodyDef.type = _dynamic ? b2_dynamicBody : b2_staticBody;
    BodyDef.position = sv2_to_bv2(invert_height(p->getPosition()));

    // Create the body
    _body = Physics::GetWorld()->CreateBody(&BodyDef);
    _body->SetActive(true);
    {
        b2FixtureDef FixtureDef;

        FixtureDef.shape = &Shape;

        _fixture = _body->CreateFixture(&FixtureDef);
    }
}

void PhysicsComponent::setFriction(float r) { _fixture->SetFriction(r); }

void PhysicsComponent::setMass(float m) { _fixture->SetDensity(m); }

void PhysicsComponent::teleport(const sf::Vector2f& v) {
    _body->SetTransform(sv2_to_bv2(invert_height(v)), 0.0f);
}

const sf::Vector2f PhysicsComponent::getVelocity() const {
    return bv2_to_sv2(_body->GetLinearVelocity(), true);
}
void PhysicsComponent::setVelocity(const sf::Vector2f& v) {
    _body->SetLinearVelocity(sv2_to_bv2(v, true));
}

b2Fixture* const PhysicsComponent::getFixture() const { return _fixture; }

PhysicsComponent::~PhysicsComponent() {
    auto a = Physics::GetWorld();
    _body->SetActive(false);
    Physics::GetWorld()->DestroyBody(_body);
    // delete _body;
    _body = nullptr;
}

void PhysicsComponent::render() {}

void PhysicsComponent::impulse(const sf::Vector2f& i) {
    auto a = b2Vec2(i.x, i.y * -1.0f);
    _body->ApplyLinearImpulseToCenter(a, true);
}

void PhysicsComponent::dampen(const sf::Vector2f& i) {
    auto vel = _body->GetLinearVelocity();
    vel.x *= i.x;
    vel.y *= i.y;
    _body->SetLinearVelocity(vel);
}

bool PhysicsComponent::isTouching(const PhysicsComponent& pc) const {
    b2Contact* bc;
    return isTouching(pc, bc);
}

bool PhysicsComponent::isTouching(const PhysicsComponent& pc,
    b2Contact const* bc) const {
    const auto _otherFixture = pc.getFixture();
    const auto& w = *Physics::GetWorld();
    const auto contactList = w.GetContactList();
    const auto clc = w.GetContactCount();
    for (int32 i = 0; i < clc; i++) {
        const auto& contact = (contactList[i]);
        if (contact.IsTouching() && ((contact.GetFixtureA() == _fixture &&
            contact.GetFixtureA() == _otherFixture) ||
            (contact.GetFixtureA() == _otherFixture &&
                contact.GetFixtureA() == _fixture))) {
            bc = &contact;
            return true;
        }
    }
    return false;
}

std::vector<const b2Contact const*> PhysicsComponent::getTouching() const {
    std::vector<const b2Contact const*> ret;

    b2ContactEdge* edge = _body->GetContactList();
    while (edge != NULL) {
        const b2Contact* contact = edge->contact;
        if (contact->IsTouching()) {
            ret.push_back(contact);
        }
        edge = edge->next;
    }

    return ret;
}

void PhysicsComponent::setRestitution(float r) {
    _fixture->SetRestitution(r);
}