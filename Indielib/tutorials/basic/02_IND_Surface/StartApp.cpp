/*****************************************************************************************
 * Desc: Example For Practice Ivan Peev
 *****************************************************************************************/

#include "CIndieLib_vc2008.h"
#include "IND_Surface.h"
#include "IND_Entity2d.h"
#include "IND_Animation.h"
#include "../../WorkingPath.h"

/*
==================
Main
==================
*/
int IndieLib()			
{
    //Sets the working path as the 'exe' directory. All resource paths are relative to this directory
	if (!WorkingPathSetup::setWorkingPathFromExe(NULL)) {
		std::cout<<"\nUnable to Set the working path !";
	}
	
    
    // ----- IndieLib intialization -----

    

	CIndieLib *mI = CIndieLib::instance();
	if (!mI->init()) return 0;
    
    
	// ----- Surface loading -----

	// Loading Background
	IND_Surface *mSurfaceBack = IND_Surface::newSurface();
	if (!mI->_surfaceManager->add(mSurfaceBack, "../../resources/cherry_blossom_background.png", IND_OPAQUE, IND_32)) return 0;	

	// Loading sprite of a star
	IND_Surface *mSurfaceStar = IND_Surface::newSurface();
	if (!mI->_surfaceManager->add(mSurfaceStar, "../../resources/star.png", IND_ALPHA, IND_32)) return 0;

	// ----- Animations loading -----

	// Characters animations, we apply a color key of (0, 48, 152)
	IND_Animation *mAnimationCharacter1 = IND_Animation::newAnimation();
	if (!mI->_animationManager->addToSurface(mAnimationCharacter1, "../../resources/animations/character1.xml", IND_ALPHA, IND_32, 0, 48, 152)) return 0;

	// Characters animations, we apply a color key of (0, 48, 152)
	IND_Animation *mAnimationCharacter2 = IND_Animation::newAnimation();
	if (!mI->_animationManager->addToSurface(mAnimationCharacter2, "../../resources/animations/character2.xml", IND_ALPHA, IND_32, 0, 48, 152)) return 0;

	// Dust animation, we apply a color key of (255, 0, 255)
	IND_Animation *mAnimationDust = IND_Animation::newAnimation();
	if (!mI->_animationManager->addToSurface(mAnimationDust, "../../resources/animations/dust.xml", IND_ALPHA, IND_16, 255, 0, 255)) return 0;

	// ----- Set the surfaces into 2d entities -----
	
	// Creating 2d entity for the background
	IND_Entity2d *mBack = IND_Entity2d::newEntity2d();				
	mI->_entity2dManager->add(mBack);					// Entity adding
	mBack->setSurface(mSurfaceBack);					// Set the surface into the entity

	// Creating 2d entity for the star 1
	IND_Entity2d *mStar1 = IND_Entity2d::newEntity2d();		
	mI->_entity2dManager->add(mStar1);					// Entity adding
	mStar1->setSurface(mSurfaceStar);					// Set the surface into the entity

	//Creating 2d entity for the star 2
	IND_Entity2d *mStar2 = IND_Entity2d::newEntity2d();					
	mI->_entity2dManager->add(mStar2);					// Entity adding
	mStar2->setSurface(mSurfaceStar);					// Set the surface into the entity

	// Creating 2d entity for the star 3 
	IND_Entity2d *mStar3 = IND_Entity2d::newEntity2d();					
	mI->_entity2dManager->add(mStar3);					    // Entity adding
	mStar3->setSurface(mSurfaceStar);					    // Set the surface into the entity

    // Character 1
	IND_Entity2d *mPlayer1 = IND_Entity2d::newEntity2d();
	mI->_entity2dManager->add(mPlayer1);					// Entity adding
	mPlayer1->setAnimation(mAnimationCharacter1);		    // Set the animation into the entity

	// Character 2
	IND_Entity2d *mPlayer2 = IND_Entity2d::newEntity2d();
	mI->_entity2dManager->add(mPlayer2);					// Entity adding
	mPlayer2->setAnimation(mAnimationCharacter2);		    // Set the animation into the entity

	// Dust explosion
	IND_Entity2d *mDust = IND_Entity2d::newEntity2d();
	mI->_entity2dManager->add(mDust);					    // Entity adding
	mDust->setAnimation(mAnimationDust);					// Set the animation into the entity

	// ----- Changing the attributes of the 2d entities -----
	
	mStar1->setPosition(mI->_window->getWidth() - mSurfaceStar->getWidth(), 0, 100);
	mStar1->setTint(255, 51, 51);
	mStar2->setPosition(mI->_window->getWidth() - mSurfaceStar->getWidth() - 80, 0, 100);
	mStar2->setTint(255, 51, 51);
	mStar3->setPosition(mI->_window->getWidth() - mSurfaceStar->getWidth() - 160, 0, 100);
	mStar3->setTint(255, 51, 51);

	// Player 1
	mPlayer1->setSequence(0);						// Choose sequence
	mPlayer1->setPosition(140, 380, 0);
	mPlayer1->setMirrorX(1);						// Horizontal mirroring

	// Dust explosion
	mDust->setPosition(510, 20, 0);

	// Player 2
	mPlayer2->setSequence(0);						// Choose sequence
	mPlayer2->setPosition(550, 400, 0);
	mPlayer2->setNumReplays(0);

	// ----- Main Loop -----
	int live = 3;
	while (!mI->_input->onKeyPress(IND_ESCAPE) && !mI->_input->quit())
	{
		mI->_input->update();
		if (mI->_input->onKeyPress(IND_SPACE)) 
		{ 
			mPlayer2->setNumReplays(1);
			if (live > 0 && live == 3)
			{
				mStar3->setScale(0, 0);
			}
			else if(live > 0 && live == 2)
			{
				mStar2->setScale(0, 0);
			}
			else if (live > 0 && live == 1)
			{
				mStar1->setScale(0, 0);
			}			
			live--;
		}
		mI->_render->beginScene();
		mI->_entity2dManager->renderEntities2d();
		mI->_render->endScene();	
	}

	// ----- Free -----

	mI->end();

	return 0;
}
