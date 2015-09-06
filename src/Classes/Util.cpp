#include "Util.h"


Util::Util()
{
}


Util::~Util()
{
}

TransitionScene * Util::getTransitionSceneRandom(Scene *scene) {
	TransitionScene * transitionScene = NULL;
	const float transitionTime = 0.8f;
	switch (rand() % 26) {
	case 0:
		transitionScene = TransitionJumpZoom::create(transitionTime, scene);
		break;
	case 1:
		transitionScene = TransitionFade::create(transitionTime, scene);
		break;
	case 2:
		transitionScene = TransitionFlipX::create(transitionTime, scene);
		break;
	case 3:
		transitionScene = TransitionFlipY::create(transitionTime, scene);
		break;
	case 4:
		transitionScene = TransitionFlipAngular::create(transitionTime, scene);
		break;
	case 5:
		transitionScene = TransitionZoomFlipX::create(transitionTime, scene);
		break;
	case 6:
		transitionScene = TransitionZoomFlipY::create(transitionTime, scene);
		break;
	case 7:
		transitionScene = TransitionShrinkGrow::create(transitionTime, scene);
		break;
	case 8:
		transitionScene = TransitionRotoZoom::create(transitionTime, scene);
		break;
	case 9:
		transitionScene = TransitionMoveInL::create(transitionTime, scene);
		break;
	case 10:
		transitionScene = TransitionMoveInR::create(transitionTime, scene);
		break;
	case 11:
		transitionScene = TransitionMoveInT::create(transitionTime, scene);
		break;
	case 12:
		transitionScene = TransitionMoveInB::create(transitionTime, scene);
		break;
	case 13:
		transitionScene = TransitionSlideInL::create(transitionTime, scene);
		break;
	case 14:
		transitionScene = TransitionSlideInR::create(transitionTime, scene);
		break;
	case 15:
		transitionScene = TransitionSlideInT::create(transitionTime, scene);
		break;
	case 16:
		transitionScene = TransitionSlideInB::create(transitionTime, scene);
		break;
	case 17:
		transitionScene = TransitionFadeTR::create(transitionTime, scene);
		break;
	case 18:
		transitionScene = TransitionFadeBL::create(transitionTime, scene);
		break;
	case 19:
		transitionScene = TransitionFadeUp::create(transitionTime, scene);
		break;
	case 20:
		transitionScene = TransitionFadeDown::create(transitionTime, scene);
		break;
	case 21:
		transitionScene = TransitionTurnOffTiles::create(transitionTime, scene);
		break;
	case 22:
		transitionScene = TransitionSplitRows::create(transitionTime, scene);
		break;
	case 23:
		transitionScene = TransitionSplitCols::create(transitionTime, scene);
		break;
	case 24:
		Director::getInstance()->setDepthTest(true);
		transitionScene = TransitionPageTurn::create(transitionTime, scene, true);
		break;
	case 25:
		Director::getInstance()->setDepthTest(true);
		transitionScene = TransitionPageTurn::create(transitionTime, scene, false);
		break;
	}
	return transitionScene;
}