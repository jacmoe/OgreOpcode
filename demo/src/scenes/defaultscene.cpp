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

#include "scenes/defaultscene.h"

/*!
 * Construct a new d-collide based scene object.
 *
 * The scene itself is not yet created, only the necessary data
 * structures. Call \ref initializeScene to actually create a scene.
 *
 * \param root A pointer to the ogre root object. Ownership is NOT
 * taken, the pointer will not be deleted by this class.
 */
DefaultScene::DefaultScene(Ogre::Root* root)
        : SceneBase(root) {
}

DefaultScene::~DefaultScene()
{
}

/*!
 * Setup the actual scene, i.e. add objects to the \ref dcollide::World
 * object.
 *
 * \return TRUE on success, otherwise FALSE.
 **/
bool DefaultScene::initializeScene()
{
    return true;
}

/*!
 * Start a new frame of the scene, i.e. moves all movable object by a bit.
 *
 * This is NOT necessarily equal to a graphic frame! In fact the scene frames
 * should depend on time only, not on CPU or GPU power as the graphic frames do.
 */
void DefaultScene::startNextSceneFrame()
{
}

std::string DefaultScene::getSceneDescription() const
{
    return "Default scene to test various aspects of the library.";
}

/*
 * vim: et sw=4 ts=4
 */
