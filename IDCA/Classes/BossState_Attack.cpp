#include "pch.h"
#include "Enemy.h"
#include "EnemyManager.h"
#include "SimpleAudioEngine.h"
#include "Enemy_AncientTree.h"
#include "BossState_Attack.h"
#include "BossState_Strike.h"
#include "BossState_Rush.h"

/*
	BossState_Attack
	�ۼ��� : �̱ٿ�
	Boss�� ������ �ϴ� ����.
	Boss������ ���� Ƚ���� ���� ���� Strike ���·� ����.
	���� player�� ���� ���� �ٱ��̶�� Rush ���·� ����.
	������ �ϴ� ���
		- MakeTentacle�Լ��� ���� �Ѹ��� ��ȯ 
		- Tentacle�� ���ο��� CollideManager�� �̿��� �浹�� ó���� �� �ڱ� ������ �Ҹ��� (���� �ʿ伺�� ����)
*/


void BossState_Attack::startState(Enemy* enemy)
{
	return;
}

void BossState_Attack::runState(Enemy* enemy, float dt)
{
	auto attackNumber = enemy->getAttackNumber();
	m_AccumulateTime += dt;

	// Player�� ���� �Ÿ����� ���ٸ� Rush���·� ����.
	if (!isPlayerInAttackRange(enemy->getChasingRange(), enemy->getDistanceFromPlayer()))
	{
		enemy->changeState<BossState_Rush>();
	}
	// Player�� 3�� ������ ���� �ʾҴٸ�.
	else if (attackNumber != ANCIENT_TREE_ATTACK_NUMBER)
	{
		// ������ AttackFrequency�� ���� �޶�����.
		if (m_AccumulateTime > enemy->getAttackFrequency())
		{
			// Tentacle�� ������� ��, attackNumber�� ����. 
			enemy->MakeTentacle();
			enemy->setAttackNumber(++attackNumber);
			m_AccumulateTime = 0.f;
		}
	}
	// 3�� ������ �ߴٸ� ���� ȸ�� �ʱ�ȭ �� Strike ���·� ����.
	else 
	{
		enemy->setAttackNumber(0);
		enemy->changeState<BossState_Strike>();
	}

	return;
}

void BossState_Attack::endState(Enemy* enemy)
{
	return;
}

const int BossState_Attack::returnStateNumber()
{
	return ENEMY_STATE_TYPE::BOSS_ATTACK;
}
