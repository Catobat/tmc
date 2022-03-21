#include "save.h"
#include "object.h"
#include "functions.h"
#include "item.h"
#include "message.h"
#include "game.h"

extern u16 script_EzloTalkOcarina[];

void Bird_Type0(Entity*);
void Bird_Type1(Entity*);
void Bird_Type2(Entity*);
void Bird_Type3(Entity*);
void Bird_Type8(Entity*);
void Bird_Type9(Entity*);
void Bird_Type10(Entity*);
void Bird_Type0_Init(Entity*);
void Bird_Type0_Action1(Entity*);
void Bird_Type1_Init(Entity*);
void Bird_Type1_Action1(Entity*);
void Bird_Type1_Action1_Subaction0(Entity*);
void Bird_Type1_Action1_Subaction1(Entity*);
void Bird_Type2_Init(Entity*);
void Bird_Type2_Action1(Entity*);

void Bird(Entity* this) {
    static void (*const typeFuncs[])(Entity*) = {
        Bird_Type0, Bird_Type1, Bird_Type2, Bird_Type3, Bird_Type3,  Bird_Type3,
        Bird_Type3, Bird_Type3, Bird_Type8, Bird_Type9, Bird_Type10,
    };
    typeFuncs[this->type](this);
}

void Bird_Type0(Entity* this) {
    static void (*const actionFuncs[])(Entity*) = {
        Bird_Type0_Init,
        Bird_Type0_Action1,
    };

    actionFuncs[this->action](this);
}

void Bird_Type0_Init(Entity* this) {
    Entity* target;

    this->action++;
    this->spriteSettings.draw = TRUE;
    this->actionDelay = 0x31;
    this->field_0xf = 1;
    this->zVelocity = Q_16_16(-1.5);
    this->z.WORD = Q_16_16(-56.75);
    this->field_0x68.HWORD = Q_16_16(-0.03125);
    this->speed = 0x280;
    this->direction = 8;
    this->collisionLayer = 2;
    this->x.HALF.HI = gRoomControls.scroll_x;
    SoundReq(SFX_123);
    UpdateSpriteForCollisionLayer(this);
    InitAnimationForceUpdate(this, 0);
    target = CreateObject(BIRD, 1, 0);
    if (target != NULL) {
        target->parent = this;
        PositionRelative(this, target, 0, Q_16_16(8.0));
        SortEntityAbove(this, target);
    }
}

void Bird_Type0_Action1(Entity* this) {
    LinearMoveUpdate(this);
    GravityUpdate(this, *(s16*)&this->field_0x68.HWORD);
    if (this->actionDelay != 0) {
        if (--this->actionDelay == 0) {
            this->field_0xf = 0;
        }
    } else if (CheckOnScreen(this) == 0) {
        DeleteThisEntity();
    }
    UpdateAnimationSingleFrame(this);
}

void Bird_Type1(Entity* this) {
    static void (*const actionFuncs[])(Entity*) = {
        Bird_Type1_Init,
        Bird_Type1_Action1,
    };
    actionFuncs[this->action](this);
}

void Bird_Type1_Init(Entity* this) {
    this->action++;
    this->collisionLayer = 1;
    UpdateSpriteForCollisionLayer(this);
    InitAnimationForceUpdate(this, 0x17);
}

void Bird_Type1_Action1(Entity* this) {
    static void (*const subActionFuncs[])(Entity*) = {
        Bird_Type1_Action1_Subaction0,
        Bird_Type1_Action1_Subaction1,
    };
    subActionFuncs[this->subAction](this);
}

void Bird_Type1_Action1_Subaction0(Entity* this) {
    u32 temp;

    if (this->parent != NULL) {
        temp = this->parent->field_0xf;
        if (temp != 0) {
            PositionRelative(this->parent, this, 0, Q_16_16(8.0));
        } else {
            this->subAction++;
            this->zVelocity = temp;
        }
    }
}

void Bird_Type1_Action1_Subaction1(Entity* this) {
    Entity* fx;

    if (sub_080044EC(this, 0x1800) < 2) {
        this->type = 2;
        this->action = 1;
        this->z.WORD = 0;
        this->collisionLayer = 1;
        SetLocalFlag(LV3_OCARINA_FALL);
        SoundReq(SFX_SECRET);
        fx = CreateFx(this, FX_DASH, 0);
        if (fx != NULL) {
            SortEntityBelow(this, fx);
        }
    }
}

void Bird_Type2(Entity* this) {
    static void (*const actionFuncs[])(Entity*) = {
        Bird_Type2_Init,
        Bird_Type2_Action1,
    };
    actionFuncs[this->action](this);
}

void Bird_Type2_Init(Entity* this) {
    this->action++;
    this->collisionLayer = 1;
    UpdateSpriteForCollisionLayer(this);
    InitAnimationForceUpdate(this, 0x17);
}

void Bird_Type2_Action1(Entity* this) {
    if ((gPlayerState.flags & PL_MINISH) != 0) {
        sub_0800445C(this);
    } else if (IsCollidingPlayer(this) != 0) {
        CreateItemEntity(ITEM_OCARINA, 0, 0);
        gSave.windcrests |= 0x10000000;
        DeleteThisEntity();
    }
}

void Bird_Type3(Entity* this) {

    if (this->action == 0) {
        this->action++;
        this->collisionLayer = 2;
        UpdateSpriteForCollisionLayer(this);
        this->frame = 0x80;
    }

    if ((this->frame & ANIM_DONE) != 0) {
        InitializeAnimation(this, Random() & 3);
        this->frameDuration = (Random() & 0xf) + 0x10;
        this->spriteSettings.flipX = FALSE;
        if ((Random() & 1) != 0) {
            this->spriteSettings.flipX = TRUE;
        }
    } else {
        GetNextFrame(this);
    }
}

void Bird_Type8(Entity* this) {
    Entity* pEVar5;

    switch (this->action) {
        case 0:
            if (this->actionDelay != 0) {
                this->frameIndex = 0xff;
                this->actionDelay--;
                return;
            }
            this->action = 1;
            this->zVelocity = 0;
            this->z.WORD = Q_16_16(-20.0);
            this->speed = 0x180;
            this->direction = 8;
            this->collisionLayer = 1;
            this->spritePriority.b0 = 0;
            this->spriteRendering.b3 = 0;
            this->spriteOrientation.flipY = 1;
            this->x.HALF.HI = gRoomControls.scroll_x;
            this->y.HALF.HI = gPlayerEntity.y.HALF.HI;
            this->child = NULL;
            SetDefaultPriority(this, 6);
            InitAnimationForceUpdate(this, 0);
            SoundReq(0x123);
            break;
        case 1:
            this->collisionLayer = gPlayerEntity.collisionLayer;
            this->speed += 8;
            if (this->speed > 0x300) {
                this->speed = 0x300;
            }

            if ((gPlayerEntity.flags & 0x80) != 0 && (gMessage.doTextBox & 0x7f) == 0 && gPlayerEntity.action != 28 &&
                gPlayerEntity.action != 6 && gPlayerEntity.action != 9 && gPlayerState.framestate != 24 &&
                gPlayerState.framestate != 11 && gPlayerState.framestate != 8 && sub_08079F8C() &&
                (EntityInRectRadius(this, &gPlayerEntity, 0xe, 0xe))) {
                s32 z = gPlayerEntity.z.HALF.HI - this->z.HALF.HI - 8;
                if ((u16)z < 0x20 && gPlayerEntity.health != 0) {
                    pEVar5 = CreateObject(0x95, 10, 0);
                    if (pEVar5 != NULL) {
                        this->child = pEVar5;
                        this->action = 2;
                        this->actionDelay = 8;
                        this->speed = 0x300;
                        this->field_0x68.HWORD = 0xe000;
                        sub_08079184();
                        sub_08078B48();
                        ResetPlayerAnimationAndAction();
                        sub_08077B20();
                        gPlayerState.swim_state = 0;
                        gPlayerState.jump_status = 0;
                        gPlayerEntity.flags &= 0x7f;
                        gPlayerEntity.spriteSettings.draw = 0;
                        gPriorityHandler.sys_priority = 6;
                        gUnk_02034490.unk0 = 1;
                    }
                }
            }
            break;
        default:
            sub_08078B48();
            gPlayerEntity.spriteSettings.draw = 0;
            break;
    }
    LinearMoveUpdate(this);
    GravityUpdate(this, (s16)this->field_0x68.HWORD);
    UpdateAnimationSingleFrame(this);
    pEVar5 = this->child;
    if (pEVar5 != NULL) {
        if (gPlayerEntity.x.HALF.HI < this->x.HALF.HI - 8) {
            this->actionDelay = 0;
        }

        if (this->actionDelay == 0) {
            PositionRelative(this, pEVar5, 0xfff80000, 0);
            pEVar5->z.HALF.HI += 0x18;
            pEVar5->spritePriority.b0 = this->spritePriority.b0;
            pEVar5->spriteRendering.b3 = this->spriteRendering.b3;
            pEVar5->spriteOrientation.flipY = this->spriteOrientation.flipY;
        } else {
            this->actionDelay--;
            CopyPosition(&gPlayerEntity, pEVar5);
        }
    }

    if (CheckOnScreen(this) == 0) {
        if (this->action == 2) {
            gSave.windcrests |= 0x10000000;
            MenuFadeIn(9, 0);
        }
        pEVar5 = this->child;
        if (pEVar5 != NULL) {
            DeleteEntityAny(pEVar5);
        }
        DeleteThisEntity();
    }
}

void Bird_Type9(Entity* this) {
    Entity* pEVar1;
    Entity* child;

    if (this->action == 0) {
        this->action = 1;
        this->spriteSettings.draw = 1;
        this->zVelocity = -0x28000;
        this->z.WORD = 0xffb4c000;
        this->field_0x68.HWORD = 0xf000;
        this->speed = 0x300;
        this->direction = 8;
        this->collisionLayer = 1;
        this->spritePriority.b0 = 0;
        this->spriteRendering.b3 = 0;
        this->spriteOrientation.flipY = 1;
        ;
        SetDefaultPriority(this, 6);
        this->x.HALF.HI = gRoomControls.scroll_x;
        this->y.HALF.HI = gPlayerEntity.y.HALF.HI;
        SoundReq(SFX_123);
        this->spritePriority.b1 = 2;
        InitAnimationForceUpdate(this, 0);
        sub_08078B48();
    } else if (this->action == 1) {
        gPlayerEntity.spriteSettings.draw = 0;
        child = this->child;
        if (child != NULL) {
            PositionRelative(this, child, Q_16_16(-8), 0);
            child->z.HALF.HI += 0x18;
            child->spritePriority.b0 = this->spritePriority.b0;
            child->spriteRendering.b3 = this->spriteRendering.b3;
            child->spriteOrientation.flipY = this->spriteOrientation.flipY;
        }
        sub_08078B48();
        if (gRoomControls.scroll_x + 0x78 < this->x.HALF.HI) {
            this->action++;
            this->spritePriority.b1 = 1;
            if (child != NULL) {
                child->action++;
            }
            gRoomControls.camera_target = &gPlayerEntity;
            gPlayerEntity.spriteSettings.draw = 1;
            ResetPlayerAnimationAndAction();
            ResetPlayerEventPriority();
            gUnk_02034490.unk0 = 0;
            if (!CheckGlobalFlag(WARP_1ST)) {
                pEVar1 = CreateObject(OBJECT_69, 0, 0);
                if (pEVar1 != NULL) {
                    *(ScriptExecutionContext**)&pEVar1->cutsceneBeh = StartCutscene(pEVar1, script_EzloTalkOcarina);
                    SetGlobalFlag(WARP_1ST);
                }
            }
        }
    }
    LinearMoveUpdate(this);
    GravityUpdate(this, (short)this->field_0x68.HWORD);
    UpdateAnimationSingleFrame(this);
    if (!CheckOnScreen(this)) {
        DeleteThisEntity();
    }
}

void Bird_Type10(Entity* this) {
    this->palette.b.b0 = gPlayerEntity.palette.b.b0;
    switch (this->action) {
        case 0:
            this->action = 1;
            this->spriteSettings.draw = 1;
            this->collisionLayer = 1;
            this->spritePriority.b0 = 0;
            this->spriteRendering.b3 = 0;
            this->spriteOrientation.flipY = 1;
            SetDefaultPriority(this, 6);
            InitAnimationForceUpdate(this, 0xe0);
        case 1:
            UpdateAnimationSingleFrame(this);
            break;
        case 2:
            this->action = 3;
            break;
        case 3:
            DeleteThisEntity();
            break;
    }
}

void CreateBird(void) {
    Entity* birdEnt;

#ifndef EU
    if (AreaAllowsWarp()) {
#else
    if (AreaIsOverworld()) {
#endif
        if (!FindEntity(OBJECT, BIRD, 6, 8, 0)) {
            birdEnt = CreateObject(BIRD, 8, 0);
            if (birdEnt != NULL) {
                birdEnt->actionDelay = 0;
            }
        }
    }
}

void sub_0809D738(void) {
    Entity* pEVar1;
    Entity* pEVar2;

    pEVar1 = CreateObject(BIRD, 9, 0);
    if (pEVar1 != NULL) {
        gRoomControls.camera_target = NULL;
        SetDefaultPriority(pEVar1, 6);
        SetPlayerEventPriority();
        pEVar2 = CreateObject(BIRD, 10, 0);
        if (pEVar2 != NULL) {
            pEVar1->child = pEVar2;
        }
        gUnk_02034490.unk0 = 1;
    } else {
        ResetPlayerAnimationAndAction();
    }
}
