#include "entity.h"
#include "script.h"
#include "functions.h"
#include "npc.h"
#include "item.h"

void sub_08066654(Entity*);
void sub_08066688(Entity*);
void sub_080666DC(Entity*);
void sub_080666E4(Entity*);
void sub_0806670C(Entity*);
void sub_08066718(Entity*);

void KingDaltus(Entity* this) {
    static void (*const actionFuncs[])(Entity*) = {
        sub_08066654,
        sub_08066688,
        sub_080666DC,
    };
    static void (*const scriptedActionFuncs[])(Entity*) = {
        sub_080666E4,
        sub_0806670C,
        sub_08066718,
    };
    if ((this->flags & ENT_SCRIPTED) != 0) {
        if (this->interactType == 2) {
            this->interactType = 0;
            this->action = 2;
            InitAnimationForceUpdate(this, sub_0806F5A4(GetFacingDirection(this, &gPlayerEntity)));
            sub_0806F118(this);
        }
        scriptedActionFuncs[this->action](this);
    } else {
        actionFuncs[this->action](this);
        sub_0806ED78(this);
    }
}

void sub_08066654(Entity* this) {
    this->action = 1;
    this->spriteSettings.draw = 1;
    this->field_0x68.HALF.LO = sub_0801E99C(this);
    sub_08078784(this, this->field_0x68.HALF.LO);
    InitAnimationForceUpdate(this, 2);
}

void sub_08066688(Entity* this) {
    s32 tmp = GetAnimationStateInRectRadius(this, 0x28, 0x28);
    if (tmp < 0) {
        tmp = 2;
    } else {
        if (this->subtimer == 0) {
            this->subtimer = 0x10;
        } else {
            this->subtimer -= 1;
            tmp = this->animIndex;
        }
    }
    if (sub_0806F078(this, tmp) == 0) {
        UpdateAnimationSingleFrame(this);
    }
    if (this->interactType != 0) {
        this->action = 2;
        this->interactType = 0;
    }
}

void sub_080666DC(Entity* this) {
    this->action = 1;
}

void sub_080666E4(Entity* this) {
    this->action = 1;
    this->spriteSettings.draw = 1;
    this->field_0x68.HALF.LO = sub_0801E99C(this);
    sub_0807DD50(this);
}

void sub_0806670C(Entity* this) {
    sub_0807DD94(this, NULL);
}

void sub_08066718(Entity* this) {
    if (UpdateFuseInteraction(this) != 0) {
        this->action = 1;
    }
}

void sub_0806672C(Entity* this) {
    sub_08078784(this, this->field_0x68.HALF.LO);
}

void sub_0806673C(Entity* this) {
    static const u16 messageIndices[] = {
        0x1058,
        0x1326,
        0x1329,
        0x132e,
    };
    u32 index;
    if (CheckGlobalFlag(2) == 0) {
        index = 0;
    } else if (GetInventoryValue(ITEM_GREEN_SWORD) == 0) {
        index = 1;
    } else if (GetInventoryValue(ITEM_RED_SWORD) == 0) {
        index = 2;
    } else {
        index = 3;
    }
    MessageNoOverlap(messageIndices[index], this);
}

void KingDaltus_Fusion(Entity* this) {
    if (this->action == 0) {
        this->action += 1;
        this->spriteSettings.draw = 1;
        InitAnimationForceUpdate(this, 6);
    } else {
        UpdateAnimationSingleFrame(this);
    }
}
