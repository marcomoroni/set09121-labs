#pragma once

#include <ecm.h>
#include "cmp_actor_movement.h"

class EnemyAIComponent : public ActorMovementComponent {
public:
	explicit EnemyAIComponent(Entity* p);
	EnemyAIComponent() = delete;
	void render() override {}
	void update(float dt) override;
};