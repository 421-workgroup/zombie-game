#include "Attack.h"

const float ZombieBiteAttack::FREEZE_TIME = 0.5;
void ZombieBiteAttack::attackRole(MainRole * role)
{
	// freeze control of that role for interval FREEZE_TIME,
	// drop blood, and make a displacement on that role's position.
	role->freeze();
	role->scheduleOnce(CC_SCHEDULE_SELECTOR(role->unfreeze), FREEZE_TIME);
	
}