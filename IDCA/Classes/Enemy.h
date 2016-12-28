#pragma once

#include "EnemyState.h"

class AnimationMaker;
class Config;
class ManageEnemyMove;
class EffectManager;

class Enemy : public Node
{
public:
	virtual bool      init(const Vec2);
	virtual void      update(float deltaTime) override;

	/* State */
	template<typename T_STATE>
	void              changeState();

	CC_SYNTHESIZE(EnemyState*, m_pState, State);
	CC_SYNTHESIZE(EnemyState*, m_pBeforeState, BeforeState);

	/* Member Variable */
	CC_SYNTHESIZE(float, m_SearchingRange, SearchingRange);
	CC_SYNTHESIZE(float, m_ChasingRange, ChasingRange);
	CC_SYNTHESIZE(float, m_AttackRange, AttackRange);
	CC_SYNTHESIZE(Vec2, m_Origin, Origin);
	CC_SYNTHESIZE(float, m_MoveSpeed, MoveSpeed);
	CC_SYNTHESIZE(bool, m_IsAttackedOnce, IsAttackedOnce);
	CC_SYNTHESIZE(bool, m_IsEnemyPreemptive, IsEnemyPreemptive);
	CC_SYNTHESIZE(bool, m_AttackChecked, AttackChecked);
	CC_SYNTHESIZE(float, m_StiffTime, StiffTime);

	CC_SYNTHESIZE(Vec2, m_PlayerPosition, PlayerPosition);
	CC_SYNTHESIZE(float, m_DistanceFromPlayer, DistanceFromPlayer);
	CC_SYNTHESIZE(float, m_DistanceFromOrigin, DistanceFromOrigin);
	CC_SYNTHESIZE(Vec2, m_UnitVecToPlayer, UnitVecToPlayer);
	CC_SYNTHESIZE(Vec2, m_UnitVecToOrigin, UnitVecToOrigin);
	CC_SYNTHESIZE(Vec2, m_TranslatedUnitVec, TranslatedUnitVec);
	CC_SYNTHESIZE(int, m_Direction, Direction);
	CC_SYNTHESIZE(int, m_BeforeDirection, BeforeDirection);
	CC_SYNTHESIZE(ENEMY_TYPE, m_EnemyType, EnemyType);
	CC_SYNTHESIZE(TMXTiledMap*, m_pMap, MapPointer);
	CC_SYNTHESIZE(Label*, m_pLabel, Label);
	CC_SYNTHESIZE(const char*, m_pAttackSound, AttackSound);
	CC_SYNTHESIZE(Vec2, m_AttackAnchorPoint, AttackAnchorPoint);
	CC_SYNTHESIZE(Vec2, m_AttackAnchorPointForDebugBox, AttackAnchorPointForDebugBox);
	CC_SYNTHESIZE(Vec2, m_AttackRangeForCollide, AttackRangeForCollide);
	CC_SYNTHESIZE(Vec2, m_BodyAnchorPoint, BodyAnchorPoint);
	CC_SYNTHESIZE(Vec2, m_BodyAnchorPointForDebugBox, BodyAnchorPointForDebugBox);
	CC_SYNTHESIZE(Vec2, m_BodyRangeForCollide, BodyRangeForCollide);
	CC_SYNTHESIZE(int, m_HP, HP);
	CC_SYNTHESIZE(int, m_Damage, Damage);
	CC_SYNTHESIZE(int, m_MaxHP, MaxHP);
	CC_SYNTHESIZE(bool, m_FlagBeAttacked, FlagBeAttacked);

	/* Member Function */
	void				 MoveEnemy(const float deltaTime);
	void				 CalUnitVecToPlayer();
	void				 CalUnitVecToOrigin();
	void				 TranslateUnitVec(Vec2);
	void				 CalDistanceFromPlayer();
	void				 CalDistanceFromOrigin();
	void				 HitedMove(const float deltaTime);
	void				 CalDirection(Vec2);
	void				 CatchStateAndDirection();
	void				 CalculateAttackAnchorPoint();
	void				 CalculateBodyAnchorPoint();
	void				 MakeBox(Vec2, Vec2, const int);
	bool				 IsEnemyMaxHp();
	void				 CheckEnemyAttacked();
	bool				 setAttackedDamage(const int);
	ManageEnemyMove*     getManageEnemyMove();

	void createEffect(int damage);

	/* Animation Function */
	bool				 Stop();
	bool				 IsStopContinued();
	bool				 Move();
	bool				 IsMoveContinued();
	bool				 Attack();
	bool				 IsAttackContinued();
	void				 DecideWhatIsCurrentAnimation();


	/* Create Function Re-define */
	static Enemy* create(const Vec2 initPosition) {
		auto p = new Enemy();
		if (p->init(initPosition)) {
			p->autorelease();
			return p;
		}
		else {
			delete p;
			return nullptr;
		}
	}

	AnimationMaker*	  m_pAnimationMaker;
	Config*			  m_pConfig;
	ManageEnemyMove*  m_pManageEnemyMove;
	EffectManager* m_pEffectManager;
private:
	const int m_RedBoxTag{ RED_BOX_TAG };
	const int m_GreenBoxTag{ GREEN_BOX_TAG };
};

// State를 전환.
template <typename T_STATE>
void Enemy::changeState()
{
	// state가 존재한다면 종료.
	if (m_pState)
	{
		getState()->endState(this);
		removeComponent(m_pState);
	}

	auto m_pState = T_STATE::create();
	setState(m_pState);
	getState()->startState(this);
	addComponent(m_pState);

	return;
}