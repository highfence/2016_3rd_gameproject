#include "pch.h"
#include "AnimationMaker.h"

AnimationMaker * AnimationMaker::create(const char * fileName, const char * fileExtention)
{
	auto maker = new(std::nothrow)AnimationMaker();
	if (maker && maker->init(fileName, fileExtention))
	{
		maker->autorelease();
		return maker;
	}
	else
	{
		delete maker;
		maker = nullptr;
		return nullptr;
	}
}

bool AnimationMaker::init(const char * fileName, const char * fileExtention)
{
	if (!Node::init())
	{
		return false;
	}
	sprintf(m_FileName, "%s", fileName);
	sprintf(m_FileNameExtention, "%s", fileExtention);

	m_ActionName[STATE::STOP] = 'S';
	m_ActionName[STATE::ATTACK] = 'A';
	m_ActionName[STATE::MOVE] = 'M';
	m_ActionName[STATE::SKILL] = 'K';
}

bool AnimationMaker::AddAnimation(int directionNum)
{
	int imageStartNumber = directionNum * MAX_FRAME_NUM;

	Vector<SpriteFrame*> animationFrame;

	for (int i = imageStartNumber; i < imageStartNumber + MAX_FRAME_NUM; ++i)
	{
		MakeAnimationFrameName(i);
		auto frame = SpriteFrameCache::getInstance()->getSpriteFrameByName(m_FrameNameBuffer);

		if (frame == nullptr)
		{
			break;
		}

		animationFrame.pushBack(frame);
	}

	m_pAnimation = Animation::createWithSpriteFrames(animationFrame, ANIMATION_SPEED);
	m_pAnimate = Animate::create(m_pAnimation);

	auto animationOn = CallFunc::create(CC_CALLBACK_0(AnimationMaker::AnimationOn, this));
	auto animationOff = CallFunc::create(CC_CALLBACK_0(AnimationMaker::AnimationOff, this));

	auto sequence = Sequence::create(animationOn, m_pAnimate, animationOff, NULL);

	runAction(sequence);
}

int AnimationMaker::IsAnimationContinued()
{
	if (m_IsAnimationOn = true)
	{
		return m_State;
	}
	else
	{
		return -1;
	}
}

//� �ִϸ��̼����� ���� animationMaker->SetAnimationAttack(); ó�� ����Ѵ�.
void AnimationMaker::SetAnimationAttack()
{
	m_State = STATE::ATTACK;
}

void AnimationMaker::SetAnimationMove()
{
	m_State = STATE::MOVE;
}

void AnimationMaker::SetAnimationStop()
{
	m_State = STATE::STOP;
}

void AnimationMaker::SetAnimationSkill()
{
	m_State = STATE::SKILL;
}

void AnimationMaker::AnimationOn()
{
	m_IsAnimationOn = true;
}

void AnimationMaker::AnimationOff()
{
	m_IsAnimationOn = false;
}

void AnimationMaker::MakeAnimationFrameName(int fileNumber)
{
	sprintf(m_FrameNameBuffer, "%s%s%d%s", m_FileName, m_ActionName + m_State, fileNumber, m_FileNameExtention);
}