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

#include "scenehandler.h"
#include "scenes/defaultscene.h"

#include <iostream>

SceneHandler* SceneHandler::mSceneHandler = 0;
std::string SceneHandler::mDefaultSceneId = "general";

SceneHandler::SceneHandler() {
    mSceneTitles.insert(std::make_pair("general",               "General Testscene                                                              [general]"));

}

SceneHandler::~SceneHandler() {
    for (std::map<std::string, SceneBase*>::iterator it = mScenes.begin(); it != mScenes.end(); ++it) {
        delete (*it).second;
    }
}

/*!
 * Create the global scene manager object. This function must be called at most
 * once, multiple calls are not allowed (SceneManager is a singleton).
 */
void SceneHandler::createSceneHandler() {
    if (mSceneHandler) {
        //std::cerr << dc_funcinfo << "scenehandler already created" << std::endl;
        return;
    }
    mSceneHandler = new SceneHandler();
}

/*!
 * \return The global SceneManager object or NULL if \ref createSceneManager was
 * not yet called.
 */
SceneHandler* SceneHandler::getSceneHandler() {
    return mSceneHandler;
}

/*!
 * Delete the global SceneManager object that was created by \ref
 * createSceneManager
 */
void SceneHandler::deleteSceneHandler() {
    delete mSceneHandler;
    mSceneHandler = 0;
}

/*!
 * Set the scene ID of the class that is used as "default scene", i.e. which is
 * created when the ID "default" is used in \ref createScene.
 *
 * This method is in particular meant to be used as a very early statment in the
 * main() function: you could easily create multiple test programs that are all
 * exactly equal (i.e. use exactly the same sources, except for main.cpp),
 * except for the default scene id that is used.
 */
void SceneHandler::setDefaultSceneId(const std::string& id) {
    mDefaultSceneId = id;
}

/*!
 * \return The scene ID of the class that is created for the ID string
 * "default". See also \ref setDefaultSceneId
 */
const std::string& SceneHandler::getDefaultSceneId() {
    return mDefaultSceneId;
}

/*!
 * Create a new scene as specified by \p id and returns a pointer to it.
 *
 * This class keeps ownership of the created scene and deletes it on
 * destruction.
 */
SceneBase* SceneHandler::createScene(const std::string& id, Ogre::Root* root) {
    if (id == "default") {
        return createScene(getDefaultSceneId(), root);
    }

    if (mScenes.find(id) != mScenes.end()) {
        // no need to create a new scene, we already created one
        return (*mScenes.find(id)).second;
    }

    SceneBase* scene = 0;
    // note: also add new scenes to getAvailableSceneIds() !
    if (id == "general")
	{
        scene = new DefaultScene(root);
    }/* else if (id == "surfacehierarchyply") {
        scene = new DeformableScene(root);
    } else if (id == "surfacehierarchycloth") {
        scene = new DeformableSceneSpheres(root);
    } else if (id == "shcollisions") {
        scene = new DeformableSceneCollisions(root);
    } else if (id == "collisionstop") {
        scene = new CollisionStopScene(root);
    } else if (id == "penetrationdepth") {
        scene = new PenetrationDepthScene(root);
    } else if (id == "copters") {
        scene = new TwoRigidHelicopters(root);
    } else if (id == "coptersgrid") {
        scene = new TwoRigidHelicoptersInGrid(root);
    } else if (id == "parallelboxes") {
        scene = new ManyMovingBoxes(root);
    } else if (id == "spherecloth") {
        scene = new SphereCloth(root);
    } else if (id == "movingbunny") {
        scene = new MovingBunny(root);
    } else if (id == "snooker") {
        scene = new SnookerScene(root);
    } else if (id == "ramp") {
        scene = new RampScene(root);
    } else if (id == "boxstack") {
        scene = new BoxstackScene(root);
    } else if (id == "response") {
        scene = new CollisionResponse(root);
    } else if (id == "dominoday") {
        scene = new DominoDay(root);
    } else if (id == "clothbox") {
        scene = new ClothBox(root);
    } else if (id == "rotatingcloth") {
        scene = new RotatingCloth(root);
    } else if (id == "specification") {
        scene = new SpecificationScene(root);
    } else if (id == "wall") {
        scene = new WallScene(root);
    } else if (id == "shake") {
        scene = new ShakeScene(root);
    } else if (id == "marblerun") {
        scene = new MarblerunScene(root);
    } else if (id == "deforming") {
        scene = new Deforming(root);
    } else if (id == "hangingcloth") {
        scene = new HangingClothScene(root);
    } else if (id == "mixedbenchmark") {
        scene = new MixedBenchmark(root);
    } else if (id == "deformablebenchmark") {
        scene = new DeformableBenchmark(root);
    }*/

    if (!scene) {
        //std::cerr << dc_funcinfo << "unknown identifier " << id << std::endl;
        return 0;
    }
    mScenes.insert(make_pair(id, scene));

    return scene;
}

/*!
 * \brief scene titles
 *
 * these titles are displayed in the scene-chooser combobox
 * used format is [SceneID] short Title
 */
std::list<std::string> SceneHandler::getAvailableSceneTitles() const {
    std::list<std::string> sceneTitles;
    for (std::map<std::string, std::string>::const_iterator iter = mSceneTitles.begin();
         iter != mSceneTitles.end(); ++iter) {
             sceneTitles.push_back((*iter).second);
    }

    return sceneTitles;
}
std::list<std::string> SceneHandler::getAvailableSceneIds() const {
    std::list<std::string> sceneIds;
    for (std::map<std::string, std::string>::const_iterator iter = mSceneTitles.begin();
         iter != mSceneTitles.end(); ++iter) {
        sceneIds.push_back((*iter).first);
    }
    return sceneIds;
}

std::string SceneHandler::getSceneTitle(const std::string& sceneId) const{
    std::map<std::string, std::string>::const_iterator findIter = mSceneTitles.find(sceneId);
    if (findIter != mSceneTitles.end()) {
        return (*findIter).second;
    }
    return "n.A.";
}

/*!
 * Deletes the scene \p scene from the internal list, as well as the \p scene
 * object itself.
 */
void SceneHandler::deleteScene(SceneBase* scene) {
    for (std::map<std::string, SceneBase*>::iterator it = mScenes.begin(); it != mScenes.end(); ++it) {
        if ((*it).second == scene) {
            delete scene;
            scene = 0;
            mScenes.erase(it);
            break;
        }
    }
    delete scene; // in case it was not in the map
}

/*!
 * \return The scene ID of a \p scene that was created using \ref createScene,
 * or an empty string if \p scene is not known to the SceneManager
 */
std::string SceneHandler::getSceneId(SceneBase* scene) const {
    for (std::map<std::string, SceneBase*>::const_iterator it = mScenes.begin(); it != mScenes.end(); ++it) {
        if ((*it).second == scene) {
            return (*it).first;
        }
    }
    return "";
}

/*
 * vim: et sw=4 ts=4
 */
