/*******************************************************************************
 *  Copyright (C) 2007 by the members of PG 510, University of Dortmund:       *
 *              d-collide-devel@lists.sourceforge.net                          *
 *
 *     Andreas Beckermann, Christian Bode, Marcel Ens, Sebastian Ens,          *
 *     Martin Fassbach, Maximilian Hegele, Daniel Haus, Oliver Horst,         *
 *     Gregor Jochmann, Timo Loist, Marcel Nienhaus and Marc Schulz            *
 *                                                                             *
 *  All rights reserved.                                                       *
 *                                                                             *
 *  Redistribution and use in source and binary forms, with or without         *
 *  modification, are permitted provided that the following conditions are met:*
 *   - Redistributions of source code must retain the above copyright          *
 *     notice, this list of conditions and the following disclaimer.           *
 *   - Redistributions in binary form must reproduce the above copyright       *
 *     notice, this list of conditions and the following disclaimer in the     *
 *     documentation and/or other materials provided with the distribution.    *
 *   - Neither the name of the PG510 nor the names of its contributors may be  *
 *     used to endorse or promote products derived from this software without  *
 *     specific prior written permission.                                      *
 *                                                                             *
 *  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS        *
 *  "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT          *
 *  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR      *
 *  A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER *
 *  OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,   *
 *  EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,        *
 *  PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR         *
 *  PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF     *
 *  LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING       *
 *  NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS         *
 *  SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE                *
 *******************************************************************************/

#include "scenebase.h"

#include <OgreRoot.h>
#include <OgreLight.h>
#include <OgreSceneManager.h>
#include <OgreSceneNode.h>
#include <OgreManualObject.h>
#include <OgreMeshManager.h>

/*!
 * Construct a new d-collide based scene object.
 *
 * The scene itself is not yet created, only the necessary data
 * structures. Call \ref initializeScene to actually create a scene.
 *
 * \param root A pointer to the ogre root object. Ownership is NOT
 * taken, the pointer will not be deleted by this class.
 */
SceneBase::SceneBase(Ogre::Root* root) {
    mOgreRoot = root;

    mInitializeSceneCalled = false;
    mSceneManager = 0;
    mOgreLight = 0;
    mOgreCamera = 0;
}

SceneBase::~SceneBase() {
//    removeAllObjects();

}

bool SceneBase::initScene() {
    if (mInitializeSceneCalled) {
        // already initialized
        return true;
    }


    // AB: We let OGRE pick the best scene manager for us (which will probably
    // be the default one, since we did not load any scene manager plugins).
    // we just tell OGRE what kind of scene we will have.
    // Since we don't know anything about our scene yet, we have a "generic"
    // scene.
    // For possible scene types, see the SceneType enum in OgreSceneManager.h
    mSceneManager = mOgreRoot->createSceneManager(Ogre::ST_GENERIC);

	mSceneManager->setAmbientLight( Ogre::ColourValue(0.5, 0.5, 0.5) );


    mOgreLight = mSceneManager->createLight( "DirectionalLight" );

    mOgreLight->setType( Ogre::Light::LT_DIRECTIONAL );
    mOgreLight->setDiffuseColour( 0.5, 0.5, 0.5 );
    mOgreLight->setSpecularColour( 1, 1, 1 );
    mOgreLight->setDirection( 0, -1, -5 );


    // AB: the camera is created by the sceneManager in Ogre, so we create it
    // here.
    // note that this is imho not very nice: the scene and the view on the scene
    // should not both be handled here.
    mOgreCamera = mSceneManager->createCamera("Camera1");
    mOgreCamera->setFixedYawAxis(false);

    if (!initializeScene()) {
        return false;
    }
    mInitializeSceneCalled = true;

    return true;
}

/*!
 * Calls \ref startNextSceneFrame and does additional tasks that are required
 * when a new (scene) frame begins (such as updating the hierarchical grid).
 *
 * This should be called once per (scene) frame, you should never call \ref
 * startNextSceneFrame directly. Note that a scene frame is not necessarily a
 * graphic frame, i.e. you could render the scene more often or less often than
 * you change the position of the objects in it.
 */
void SceneBase::beginNextSceneFrame()
{
    // call implementation of derived classes
    startNextSceneFrame();
}

/*!
 * Update the Ogre SceneNode and the bounding volumes of all non-fixed objects
 * in the mTopLevelObjects list.
 *
 * \param forced Usually Ogre-scenenodes are only updated if the corresponding
 * proxy has been transformed in any way. If set to true the update is forced
 * (needed for initialization).
 */
Ogre::Camera* SceneBase::getCamera() const {
    return mOgreCamera;
}

void SceneBase::restart() {
    std::cout << "INFO: restart feature is not implemented for this scene." <<std::endl;
}

void SceneBase::action() {
    std::cout << "INFO: action feature is not implemented for this scene." <<std::endl;
}
/*
 * vim: et sw=4 ts=4
 */
