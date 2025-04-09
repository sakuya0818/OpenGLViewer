#include "TrackBallController.h"

#include <iostream>

TrackBallController::TrackBallController()
{
}

TrackBallController::~TrackBallController()
{
}

void TrackBallController::onCursor(double xPos, double yPos)
{
	if (mLeftMouseDown)
	{
		// ��������ĸ������
		// ���㾭�ߺ�γ����ת�������Ƕȣ��������п��ܣ�
		float deltaX = (xPos - mCurrentX) * mSensitivity;
		float deltaY = (yPos - mCurrentY)* mSensitivity;

		// �ֿ�pitch��yaw���Լ���
		pitch(-deltaY);
		yaw(-deltaX);
	}
	else if (mRightMouseDown)
	{
		// ƽ��
		float deltaX = (xPos - mCurrentX) * mMoveSpeed;
		float deltaY = (yPos - mCurrentY) * mMoveSpeed;
		mCamera->mPosition += mCamera->mRight * deltaX;
		mCamera->mPosition += mCamera->mUp * deltaY;
	}

	mCurrentX = xPos;
	mCurrentY = yPos;
}

void TrackBallController::onScroll(double offset)
{
	mCamera->scale(mScaleSpeed * offset);
}

void TrackBallController::pitch(float angle)
{
	// pitch��ת��������������right��������ת�������up����Ҳ����֮�仯
	// �ȼ��������ת�ľ���Ȼ����������Ӧ�õ������up������
	auto mat = glm::rotate(glm::identity<glm::mat4>(), glm::radians(angle), mCamera->mRight);
	mCamera->mUp = glm::vec3(mat * glm::vec4(mCamera->mUp, 0.0f));
	mCamera->mPosition = glm::vec3(mat * glm::vec4(mCamera->mPosition, 1.0f));
}

void TrackBallController::yaw(float angle)
{
	// yaw��ת��������������ϵ��up��������ת�������up��right����Ҳ����֮�仯
	// �ȼ��������ת�ľ���Ȼ����������Ӧ�õ������up��right������
	auto mat = glm::rotate(glm::identity<glm::mat4>(), glm::radians(angle), glm::vec3(0.0f, 1.0f, 0.0f));
	mCamera->mUp = glm::vec3(mat * glm::vec4(mCamera->mUp, 0.0f));
	mCamera->mRight = glm::vec3(mat * glm::vec4(mCamera->mRight, 0.0f));
	mCamera->mPosition = glm::vec3(mat * glm::vec4(mCamera->mPosition, 1.0f));
}
