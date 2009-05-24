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

#include "testapp.h"
#include "inputhandler.h"

#include "gui.h"
#include "framehistory.h"
#include "scenehandler.h"
#include "scenebase.h"

#include <timing.h>

#include <OgreRoot.h>
#include <OgreCamera.h>
#include <OgreRenderWindow.h>
#include <OgreSceneManager.h>
#include <OgreWindowEventUtilities.h>
#include <OgreFrameListener.h>
#include <OgreLogManager.h>

#include <iostream>


class MyWindowEventListener : public Ogre::WindowEventListener {
    public:
        MyWindowEventListener(Ogre::RenderWindow* window) {
            mWindow = window;
            mInputHandler = 0;
            Ogre::WindowEventUtilities::addWindowEventListener(mWindow, this);
        }

        ~MyWindowEventListener() {
            Ogre::WindowEventUtilities::removeWindowEventListener(mWindow, this);
        }

        void setInputHandler(InputHandler* input) {
            mInputHandler = input;
        }

        virtual void windowResized(Ogre::RenderWindow* window) {
            if (window != mWindow) {
                return;
            }
            if (mInputHandler) {
                unsigned int width;
                unsigned int height;
                unsigned int colorDepth;
                int left;
                int top;
                window->getMetrics(width, height, colorDepth, left, top);
                mInputHandler->setWindowSize(width, height);
            }
        }

        virtual void windowClosed(Ogre::RenderWindow* window) {
            if (window != mWindow) {
                return;
            }
            if (mInputHandler) {
                mInputHandler->notifyWindowClosed();
            }
        }
    private:
        InputHandler* mInputHandler;
        Ogre::RenderWindow* mWindow;
};

class MyOgreLogListener : public Ogre::LogListener {
    public:
        virtual void messageLogged(const Ogre::String& message, Ogre::LogMessageLevel m, bool maskDebug, const Ogre::String& logName);
};

void MyOgreLogListener::messageLogged(const Ogre::String& message, Ogre::LogMessageLevel m, bool maskDebug, const Ogre::String& logName) {
    //DCOLLIDE_UNUSED(logName);
    //DCOLLIDE_UNUSED(maskDebug);

    //const int ogreDebugArea = 80000;

    //switch (m) {
    //    default:
    //    case Ogre::LML_TRIVIAL:
    //        break;
    //    case Ogre::LML_NORMAL:
    //        debug(ogreDebugArea) << message;
    //        break;
    //    case Ogre::LML_CRITICAL:
    //        warning(ogreDebugArea) << message;
    //        break;
    //}
}

/*!
 * Constructs a TestApp object, however it does not initialize it. You must call
 * \ref initialize before using it.
 */
TestApp::TestApp() {
    mInputHandler = 0;
    mGui = 0;
    mOgreRoot = 0;
    mSceneManager = 0;
    mScene = 0;
    mWindowEventListener = 0;
    mViewport = 0;
    mUseGUI = true;
    mFrameCount = 0;
    mMaxFrameCount = 0;
    mMyOgreLogListener = new MyOgreLogListener();

    mFrameHistory = new FrameHistory("Complete Frame");
    mGraphicFrameHistory = new FrameHistory("Rendering");
    mCollisionFrameHistory = new FrameHistory("Collision Detection");
    mSceneUpdateHistory = new FrameHistory("Scene (incl. physics) Step");
    mPhysicsStepHistory = new FrameHistory("Physics Step");

    SceneHandler::createSceneHandler();
}

/*!
 * Initialize the application, in particular initialize OGRE and OIS
 * (the input system, see \ref InputHandler).
 *
 * \return TRUE on success, otherwise FALSE. The application should be
 * quit, if initializing failed.
 */
bool TestApp::initialize() {
    if (mOgreRoot) {
        // already initialized
        return true;
    }
    Ogre::String pluginFileName = "plugins.cfg"; // don't use any plugin config file
                                      // (we specify everything by code)
    Ogre::String configFileName = "ogre.cfg"; // don't use any config file
                                      // (we specify everything by code)

    // AB: we create our own logmanager - ogre will use that one.
    Ogre::String logFileName = "Ogre.log"; // AB: name to identify the log - won't necessarily write to a file!
    mOgreLogManager = new Ogre::LogManager();

    // create a default log that ogre itself is going to use.
    bool suppressFileOutput = false;
    bool outputToConsole = true;
    Ogre::Log* log = mOgreLogManager->createLog(logFileName, true, outputToConsole, suppressFileOutput);
    log->addListener(mMyOgreLogListener);

    // AB: atm we don't specify the 3rd parameter and thus use the default Ogre
    //     log filename (Ogre.log in the current dir)
    //     we could just use "" to disable the logfile.
    mOgreRoot = new Ogre::Root(pluginFileName, configFileName);

    // we use OpenGL
    //#if defined __APPLE__ || defined WIN32
    //    mOgreRoot->loadPlugin("RenderSystem_GL");
    //#else
    //    mOgreRoot->loadPlugin(DCOLLIDE_OGRE_PLUGIN_DIR "/RenderSystem_GL");
    //#endif

    Ogre::RenderSystemList* renderSystemList = mOgreRoot->getAvailableRenderers();
    if (renderSystemList->empty()) {
        std::cerr << "Could not load any renderers?!" << std::endl;
        return false;
    }
    Ogre::RenderSystem* renderSystem = renderSystemList->at(0);
    mOgreRoot->setRenderSystem(renderSystem);
    mOgreRoot->initialise(false);


    // Create a window
    int width = 1024;
    int height = 768;
    bool fullscreen = false;
    mRenderWindow = mOgreRoot->createRenderWindow("d-collide test application", width, height, fullscreen);
    if (!mUseGUI) {
        mRenderWindow->setVisible(false);
    }
    mWindowEventListener = new MyWindowEventListener(mRenderWindow);

    mOgreRoot->addResourceLocation("../resources/textures", "FileSystem", "DCollideMaterials");

    mOgreRoot->addResourceLocation("../resources/models", "FileSystem", "DCollideModels");

    // input
    int windowHandle = 0;
    mRenderWindow->getCustomAttribute("WINDOW", &windowHandle);
    mInputHandler = new InputHandler(windowHandle);
    mInputHandler->setTestApp(this);
    mInputHandler->setWindowSize(width, height);
    mWindowEventListener->setInputHandler(mInputHandler);

    // GUI
    mGui = new Gui(mOgreRoot, mRenderWindow);
    mGui->setInputHandler(mInputHandler);
    mGui->addFrameHistory(mFrameHistory, false);
    mGui->addFrameHistory(mGraphicFrameHistory, true);
    mGui->addFrameHistory(mSceneUpdateHistory, true);
    mGui->addFrameHistory(mPhysicsStepHistory, true);
    mGui->addFrameHistory(mCollisionFrameHistory, true);
    if (!mGui->initialize()) {
        std::cerr << "Could not initialize the GUI" << std::endl;
        return false;
    }

    // our actual scene
    changeCurrentScene("default");

    if (!mScene) {
        //error() << "NULL current scene: could not initialize default scene";
        return false;
    }

    mInputHandler->initActions();

    return true;
}

TestApp::~TestApp() {
    delete mWindowEventListener;
    delete mGui;
    delete mInputHandler;

    SceneHandler::deleteSceneHandler();

    delete mFrameHistory;
    delete mGraphicFrameHistory;
    delete mCollisionFrameHistory;
    delete mSceneUpdateHistory;
    delete mPhysicsStepHistory;

    delete mMyOgreLogListener;
    delete mOgreLogManager;
//    delete mOgreRoot;
}

void TestApp::setCurrentScene(SceneBase* scene) {
    mInputHandler->setScene(scene);

    // Setup the renderer window (i.e. add a camera/viewport to it)
    Ogre::Camera* camera = scene->getCamera();
    if (!mViewport) {
        mViewport = mRenderWindow->addViewport(camera);
    }
    mViewport->setCamera(camera);
    camera->setAspectRatio(((Ogre::Real)mViewport->getActualWidth())
                                / ((Ogre::Real)mViewport->getActualHeight()));
    camera->setAutoAspectRatio(true);
    camera->setNearClipDistance(5.0f); // AB: default is 100
    camera->moveRelative(Ogre::Vector3(0.0f, 0.0f, 200.0f));
    mInputHandler->setCamera(camera);
    Ogre::SceneManager* manager = scene->getSceneManager();
    mGui->setSceneManager(manager);
    mGui->setSceneId(SceneHandler::getSceneHandler()->getSceneId(scene));
    mGui->setSceneDescription(scene->getSceneDescription());

    mScene = scene;

    mInputHandler->forceToggleCallbackActivation();
}


/*!
 * Starts the main event loop. This function does not return, unless the
 * application is supposed to quit - either by closing the rendering window or
 * by telling the \ref InputHandler to quit (see \ref InputHandler::queueQuit).
 */
void TestApp::startEventLoop()
{
//    try {
        Ogre::Timer timer;
        unsigned long lastFrameStarted = timer.getMilliseconds();

        mFrameCount = 0;

    #ifdef USE_CALLGRIND
        CALLGRIND_START_INSTRUMENTATION;
        CALLGRIND_TOGGLE_COLLECT; // switch collect off
    #endif
        while (!mInputHandler->getWantQuit() && (!mRenderWindow->isClosed() || !mUseGUI))
		{
            mFrameHistory->startFrame();

            // emulate Ogre's timeSinceLastFrame feature
            unsigned long now = timer.getMilliseconds();
            float timeSinceLastFrame = ((float)(now - lastFrameStarted)) / 1000.0f;
            lastFrameStarted = now;

            mInputHandler->captureInput(timeSinceLastFrame);
            Ogre::WindowEventUtilities::messagePump();

            // AB: note: a "scene frame" is not necessarily a "graphic frame".
            // -> the collision detection library may be called more often or less
            //    often than ogre.
            //    usually we should NOT couple the scene speed to the rendering
            //    speed, otherwise the scene will be VERY fast with a newer graphic
            //    card
            //
            //    we do this here atm for the sake of simplicity only. we really
            //    should use a timer instead.
            if (!mInputHandler->getPause() )
			{
                
                if (!mInputHandler->isChecked("PauseMovements"))
				{
                    mSceneUpdateHistory->startFrame();
                    mScene->beginNextSceneFrame();
                }

                    mSceneUpdateHistory->stopFrame();
            }

            if (mUseGUI)
			{
                if (!mGui->updateGui(mInputHandler->getPause()))
				{
                    mInputHandler->queueQuit();
                }

                mGraphicFrameHistory->startFrame();
                mOgreRoot->renderOneFrame();
                mGraphicFrameHistory->stopFrame();
            }

            mFrameHistory->stopFrame();

            mFrameCount++;
            if (mMaxFrameCount > 0 && mFrameCount >= mMaxFrameCount)
			{
                mInputHandler->queueQuit();
            }
        }
    //} catch (Exception e) {
    //    std::cerr   << "Unhandled exception reached main-program: \n"
    //            << e.getErrorMessage() <<std::endl;
    //    e.printBacktrace();
    //    exit(1);
    //}
}

void TestApp::changeCurrentScene(const std::string& sceneId_) {
    //try {
        std::string sceneId = sceneId_;
        if (sceneId == "default") {
            sceneId = SceneHandler::getDefaultSceneId();
        }
        SceneBase* scene = SceneHandler::getSceneHandler()->createScene(sceneId, mOgreRoot);
        if (scene == 0) {
            //error() << dc_funcinfo << "could not create scene " << sceneId;
            if (mScene) {
                // continue using current scene
                return;
            } else {
                if (sceneId == SceneHandler::getDefaultSceneId()) {
                    // use a fallback scene
                    sceneId = "general";
                }
                //warning() << dc_funcinfo << "trying fallback scene " << sceneId;
                scene = SceneHandler::getSceneHandler()->createScene(sceneId, mOgreRoot);
                if (!scene) {
                    //throw Exception("Could create neither default scene nor fallback scene");
                }
            }
        }

        if (!scene->initScene()) {
            //std::cerr << "Could not initialize the scene " << sceneId << std::endl;
            SceneHandler::getSceneHandler()->deleteScene(scene);
            return;
        } else {
            // force an initial update of Ogre scenenodes here
            //scene->updateOgreRepresentations(true);
        }
        if (scene) {
            setCurrentScene(scene);
        } else {
            //std::cerr << dc_funcinfo << "NULL scene created: don't know scene ID " << sceneId_ << std::endl;
        }
    //} catch (Exception e) {
    //    std::cerr   << "Unhandled exception reached main-program: \n"
    //            << e.getErrorMessage() <<std::endl;
    //    e.printBacktrace();
    //    exit(1);
    //}

}

/*
 * vim: et sw=4 ts=4
 */
