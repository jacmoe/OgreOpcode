#ifndef __scenehandler_h__
#define __scenehandler_h__

#include <string>
#include <list>
#include <map>

namespace Ogre {
    class Root;
}

class SceneBase;

/*!
 * \brief Class to manage creation and deletion of \ref SceneBase derived
 * objects
 *
 * This class is meant to know about all \ref SceneBase derived classes and
 * provide means to create objects of these classes from "ID" strings.
 *
 * These ID strings could be provided by code (e.g. \ref setDefaultSceneId
 * provides an easy way to change the scene that should be created on program
 * startup) or for example could be configured by a GUI or stored in a
 * configuration file.
 *
 * \author Andreas Beckermann <b_mann@gmx.de>
 */
class SceneHandler {
    public:
        ~SceneHandler();

        static void createSceneHandler();
        static SceneHandler* getSceneHandler();
        static void deleteSceneHandler();
        static void setDefaultSceneId(const std::string& id);
        static const std::string& getDefaultSceneId();

        SceneBase* createScene(const std::string& id, Ogre::Root* root);
        void deleteScene(SceneBase*);
        std::string getSceneId(SceneBase* scene) const;
        std::string getSceneTitle(const std::string& sceneId) const;
        
        std::list<std::string> getAvailableSceneIds() const;
        std::list<std::string> getAvailableSceneTitles() const;
        
    private:
        SceneHandler();

    private:
        static SceneHandler* mSceneHandler;
        static std::string mDefaultSceneId;

        std::map<std::string, SceneBase*> mScenes;
        std::map<std::string, std::string> mSceneTitles;
};

#endif // __scenehandler_h__
