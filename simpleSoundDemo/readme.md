need to install addons:
 - ofxTweenzor : https://github.com/NickHardeman/ofxTweenzor
 - ofxMSAInteractiveObject : https://github.com/memo/ofxMSAInteractiveObject

Need to also install libsndfile, easiest to use homebrew or macports, and then add to xcode project (drag .dylib file into project files)

**gotchas for installing libsndfile**: 
 - make sure your /Developer doesnt exist (from old version of xcode)
 - use flag --universal to install a universal binary
